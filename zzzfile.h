#ifndef ZZZFILE_H
#define ZZZFILE_H

#include <QIODevice>
#include "zzztocentry.h"

#define CHUNK_SIZE 10485760 // 10 Mio

class ZzzFile
{
public:
	explicit ZzzFile(QIODevice *io);
	bool readHeader(quint32 &fileCount);
	bool writeHeader(const quint32 &fileCount);
	bool readTocEntry(ZzzTocEntry &tocEntry);
	bool writeTocEntry(const ZzzTocEntry &tocEntry);
	bool copyFile(const ZzzTocEntry &tocEntry, QIODevice *out);
	bool writeFile(QIODevice *in);
private:
	bool _copyFile(const ZzzTocEntry &tocEntry, QIODevice *out);
	bool readUInt(quint32 &val);
	bool writeUInt(const quint32 &val);
	bool readULong(quint64 &val);
	bool writeULong(const quint64 &val);

	QIODevice *_io;
};

#endif // ZZZFILE_H
