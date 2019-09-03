#ifndef ZZZTOC_H
#define ZZZTOC_H

#include <QtGlobal>
#include <QByteArray>

class ZzzToc
{
public:
	ZzzToc();

	inline void setName(const QByteArray &name) {
		_name = name;
	}

	inline const QByteArray &name() const {
		return _name;
	}

	inline quint64 pos() const {
		return _pos;
	}

	inline void setPos(quint64 pos) {
		_pos = pos;
	}

	inline quint32 size() const {
		return _size;
	}

	inline void setSize(quint32 size) {
		_size = size;
	}
private:
	QByteArray _name;
	quint64 _pos;
	quint32 _size;
};

#endif // ZZZTOC_H
