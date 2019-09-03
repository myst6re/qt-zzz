#ifndef ZZZFILE_H
#define ZZZFILE_H

#include <QIODevice>
#include "zzztoc.h"

#define CHUNK_SIZE 10485760 // 10 Mio

class ZzzFile
{
public:
	explicit ZzzFile(QIODevice *io);
	bool readHeader(quint32 &fileCount);
	bool readTocEntry(ZzzToc &toc);
	bool copyFile(const ZzzToc &toc, QIODevice *out);
private:
	bool _copyFile(const ZzzToc &toc, QIODevice *out);
	bool readUInt(quint32 &val);
	bool readULong(quint64 &val);

	QIODevice *_io;
};

#endif // ZZZFILE_H
