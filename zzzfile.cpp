#include "zzzfile.h"

ZzzFile::ZzzFile(QIODevice *io) : _io(io)
{
}

bool ZzzFile::readHeader(quint32 &fileCount)
{
	return readUInt(fileCount);
}

bool ZzzFile::readTocEntry(ZzzToc &toc)
{
	quint32 size;

	if (!readUInt(size)) {
		return false;
	}

	if (size > 256) {
		return false;
	}

	QByteArray name = _io->read(size);

	if (name.size() != int(size)) {
		return false;
	}

	toc.setName(name);

	quint64 filePos;
	quint32 fileSize;

	if (!readULong(filePos)) {
		return false;
	}

	toc.setPos(filePos);

	if (!readUInt(fileSize)) {
		return false;
	}

	toc.setSize(fileSize);

	return true;
}

bool ZzzFile::copyFile(const ZzzToc &toc, QIODevice *out)
{
	qint64 curPos = _io->pos();

	if (!_io->seek(qint64(toc.pos()))) {
		return false;
	}

	bool ret = _copyFile(toc, out);

	if (!_io->seek(curPos)) {
		return false;
	}

	return ret;
}

bool ZzzFile::_copyFile(const ZzzToc &toc, QIODevice *out)
{
	quint32 chunkCount = toc.size() / CHUNK_SIZE,
	        remaining = toc.size() % CHUNK_SIZE;
	QByteArray data;

	for (quint32 i = 0; i < chunkCount; ++i) {
		data = _io->read(CHUNK_SIZE);

		if (data.size() != CHUNK_SIZE) {
			return false;
		}

		if (out->write(data) != data.size()) {
			return false;
		}
	}

	if (remaining > 0) {
		data = _io->read(remaining);

		if (data.size() != int(remaining)) {
			return false;
		}

		if (out->write(data) != data.size()) {
			return false;
		}
	}

	return true;
}

bool ZzzFile::readUInt(quint32 &val)
{
	return _io->read((char *)&val, 4) == 4;
}

bool ZzzFile::readULong(quint64 &val)
{
	return _io->read((char *)&val, 8) == 8;
}
