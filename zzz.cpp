#include "zzz.h"
#include "zzzfile.h"
#include <QMap>
#include <QDirIterator>

Zzz::Zzz(const QString &fileName) : f(fileName)
{
}

bool Zzz::extractTo(const QDir &dir, Observer *observer)
{
	if (!f.open(QIODevice::ReadOnly)) {
		return false;
	}

	ZzzFile zzzFile(&f);
	quint32 fileCount;

	if (!zzzFile.readHeader(fileCount)) {
		return false;
	}

	if (observer) {
		observer->setMaximum(fileCount);
	}

	for (quint32 i = 0; i < fileCount; ++i) {
		ZzzTocEntry tocEntry;

		if (observer) {
			observer->setValue(i);
		}

		if (!zzzFile.readTocEntry(tocEntry)) {
			return false;
		}

		QFileInfo fileInfo = toQtSeparators(tocEntry.fileName());

		if (!dir.mkpath(fileInfo.dir().path())) {
			return false;
		}

		QFile out(dir.filePath(fileInfo.filePath()));

		if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			_lastOutError = out.error();
			_lastOutErrorString = out.errorString();

			return false;
		}

		if (!zzzFile.copyFile(tocEntry, &out)) {
			_lastOutError = out.error();
			_lastOutErrorString = out.errorString();

			return false;
		}
	}

	return true;
}

bool Zzz::packFrom(const QDir &dir, Observer *observer)
{
	QString oldFilename = f.fileName();
	f.setFileName(f.fileName().append(".tmp"));

	if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		return false;
	}

	bool ok = _packFrom(&f, dir, observer);

	if (!ok) {
		f.remove();
	} else {
		if (QFile::exists(oldFilename)) {
			QFile::remove(oldFilename);
		}

		if (!f.rename(oldFilename)) {
			return false;
		}
	}

	return ok;
}

bool Zzz::_packFrom(QFile *temp, const QDir &dir, Observer *observer)
{
	ZzzFile zzzFile(temp);
	QStringList files;
	QMap<QString, ZzzTocEntry> entries;
	quint64 dataPos = 4;
	QDirIterator it(dir.path(), QDir::Files, QDirIterator::Subdirectories);

	if (observer) {
		observer->setValue(0);
	}

	while (it.hasNext()) {
		const QString &path = it.next();
		QString fileName = path.mid(dir.path().size() + 1);
		QFileInfo fileInfo(path);

		if (fileInfo.size() > qint64(quint32(-1))) {
			// TODO: error
			return false;
		}

		ZzzTocEntry entry;
		entry.setFilePos(0);
		entry.setFileSize(quint32(fileInfo.size()));
		entry.setFileName(toFF8Separators(fileName).toLatin1());

		entries.insert(path, entry);
		dataPos += quint64(entry.fileName().size() + 16);
	}

	int fileCount = entries.size();

	if (observer) {
		observer->setMaximum(fileCount - 1);
	}

	if (!zzzFile.writeHeader(quint32(fileCount))) {
		return false;
	}

	quint32 i = 0;
	QMutableMapIterator<QString, ZzzTocEntry> it2(entries);

	while (it2.hasNext()) {
		it2.next();
		ZzzTocEntry &entry = it2.value();

		entry.setFilePos(dataPos);

		if (!zzzFile.writeTocEntry(entry)) {
			return false;
		}

		dataPos += entry.fileSize();
	}

	QMapIterator<QString, ZzzTocEntry> it3(entries);

	while (it3.hasNext()) {
		it3.next();
		const QString &path = it3.key();

		if (observer) {
			observer->setValue(i++);
		}

		QFile in(path);

		if (!in.open(QIODevice::ReadOnly)) {
			_lastOutError = in.error();
			_lastOutErrorString = in.errorString();

			return false;
		}

		if (!zzzFile.writeFile(&in)) {
			_lastOutError = in.error();
			_lastOutErrorString = in.errorString();

			return false;
		}
	}

	return true;
}

QString Zzz::toQtSeparators(const QString &path)
{
	QString n(path);
	QChar * const data = n.data();

	for (int i = 0; i < n.length(); ++i) {
		if (data[i] == QLatin1Char('\\')) {
			data[i] = QLatin1Char('/');
		}
	}

	return n;
}

QString Zzz::toFF8Separators(const QString &path)
{
	QString n(path);
	QChar * const data = n.data();

	for (int i = 0; i < n.length(); ++i) {
		if (data[i] == QLatin1Char('/')) {
			data[i] = QLatin1Char('\\');
		}
	}

	return n;
}
