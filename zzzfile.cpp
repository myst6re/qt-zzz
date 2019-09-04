#include "zzzfile.h"

ZzzFile::ZzzFile(QIODevice *io) : _io(io)
{
}

bool ZzzFile::readHeader(quint32 &fileCount)
{
	return readUInt(fileCount);
}

bool ZzzFile::writeHeader(const quint32 &fileCount)
{
	return writeUInt(fileCount);
}

bool ZzzFile::readTocEntry(ZzzTocEntry &tocEntry)
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

	tocEntry.setFileName(name);

	quint64 filePos;
	quint32 fileSize;

	if (!readULong(filePos)) {
		return false;
	}

	tocEntry.setFilePos(filePos);

	if (!readUInt(fileSize)) {
		return false;
	}

	tocEntry.setFileSize(fileSize);

	return true;
}

bool ZzzFile::writeTocEntry(const ZzzTocEntry &tocEntry)
{
	quint32 size = quint32(tocEntry.fileName().size());

	if (!writeUInt(size)) {
		return false;
	}

	_io->write(tocEntry.fileName());

	if (!writeULong(tocEntry.filePos())) {
		return false;
	}

	return writeUInt(tocEntry.fileSize());
}

bool ZzzFile::copyFile(const ZzzTocEntry &tocEntry, QIODevice *out)
{
	qint64 curPos = _io->pos();

	if (!_io->seek(qint64(tocEntry.filePos()))) {
		return false;
	}

	bool ret = _copyFile(tocEntry, out);

	if (!_io->seek(curPos)) {
		return false;
	}

	return ret;
}

bool ZzzFile::_copyFile(const ZzzTocEntry &tocEntry, QIODevice *out)
{
	quint32 chunkCount = tocEntry.fileSize() / CHUNK_SIZE,
	        remaining = tocEntry.fileSize() % CHUNK_SIZE;
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

bool ZzzFile::writeFile(QIODevice *in)
{
	qint64 chunkCount = in->size() / CHUNK_SIZE,
	       remaining = in->size() % CHUNK_SIZE;
	QByteArray data;

	for (quint32 i = 0; i < chunkCount; ++i) {
		data = in->read(CHUNK_SIZE);

		if (data.size() != CHUNK_SIZE) {
			return false;
		}

		if (_io->write(data) != data.size()) {
			return false;
		}
	}

	if (remaining > 0) {
		data = in->read(remaining);

		if (data.size() != int(remaining)) {
			return false;
		}

		if (_io->write(data) != data.size()) {
			return false;
		}
	}

	return true;
}

bool ZzzFile::readUInt(quint32 &val)
{
	return _io->read((char *)&val, 4) == 4;
}

bool ZzzFile::writeUInt(const quint32 &val)
{
	return _io->write((const char *)&val, 4) == 4;
}

bool ZzzFile::readULong(quint64 &val)
{
	return _io->read((char *)&val, 8) == 8;
}

bool ZzzFile::writeULong(const quint64 &val)
{
	return _io->write((const char *)&val, 8) == 8;
}
