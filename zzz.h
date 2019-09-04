#ifndef ZZZ_H
#define ZZZ_H

#include <QString>
#include <QFile>
#include <QDir>
#include "observer.h"

class Zzz
{
public:
	explicit Zzz(const QString &fileName);
	bool extractTo(const QDir &dir, Observer *observer);
	bool packFrom(const QDir &dir, Observer *observer);

	inline const QString &lastOutErrorString() const {
		return _lastOutErrorString;
	}

	inline QString lastInErrorString() const {
		return f.errorString();
	}
private:
	bool _packFrom(QFile *temp, const QDir &dir, Observer *observer);
	static QString toQtSeparators(const QString &path);
	static QString toFF8Separators(const QString &path);
	QFile f;
	QFile::FileError _lastOutError;
	QString _lastOutErrorString;
};

#endif // ZZZ_H
