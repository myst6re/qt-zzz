#ifndef ZZZTOCENTRY_H
#define ZZZTOCENTRY_H

#include <QtGlobal>
#include <QByteArray>

class ZzzTocEntry
{
public:
	ZzzTocEntry();

	inline void setFileName(const QByteArray &name) {
		_name = name;
	}

	inline const QByteArray &fileName() const {
		return _name;
	}

	inline quint64 filePos() const {
		return _pos;
	}

	inline void setFilePos(quint64 pos) {
		_pos = pos;
	}

	inline quint32 fileSize() const {
		return _size;
	}

	inline void setFileSize(quint32 size) {
		_size = size;
	}
private:
	QByteArray _name;
	quint64 _pos;
	quint32 _size;
};

#endif // ZZZTOCENTRY_H
