#include "zzz.h"
#include "zzzfile.h"

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
		ZzzToc toc;

		if (observer) {
			observer->setValue(i);
		}

		if (!zzzFile.readTocEntry(toc)) {
			return false;
		}

		QFileInfo fileInfo = toQtSeparators(toc.name());

		if (!dir.mkpath(fileInfo.dir().path())) {
			return false;
		}

		QFile out(dir.filePath(fileInfo.filePath()));

		if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			_lastOutError = out.error();
			_lastOutErrorString = out.errorString();

			return false;
		}

		if (!zzzFile.copyFile(toc, &out)) {
			_lastOutError = out.error();
			_lastOutErrorString = out.errorString();

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
