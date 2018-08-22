#include "net/NetworkReader.h"

#include "net/NetworkWriter.h"

NetworkReader::NetworkReader(std::string &data, unsigned int offest) : buffer(new char[data.length()]), buffer_end(data.length()), index(offest)
{
	std::memcpy(this->buffer, data.c_str(), data.length());
}

NetworkReader::NetworkReader(NetworkWriter &writer, unsigned int offset) : buffer(new char[writer.getSize()]), buffer_end(writer.getSize()), index(offset)
{
	std::memcpy(this->buffer, writer.getData(), writer.getSize());
}

NetworkReader::~NetworkReader()
{
	delete this->buffer;
}

void NetworkReader::checkReadOverflow(unsigned int bytes_to_read)
{
	if (this->index + bytes_to_read > this->buffer_end)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[NetworkReader]", "Attempted to read more data than available");
		throw std::exception("Read Overflow");
	}
}

std::string NetworkReader::readData(unsigned int length)
{
	this->checkReadOverflow(length);

	std::string read(this->buffer + this->index, length);
	this->index += length;

	return read;
}

std::string NetworkReader::getRemainingData()
{
	return this->readData(this->buffer_end - this->index);
}

int8_t NetworkReader::readInt8()
{
	this->checkReadOverflow(1);

	int8_t read = *(int8_t*)(this->buffer + this->index);
	this->index += 1;

	return read;
}

uint8_t NetworkReader::readUint8()
{
	this->checkReadOverflow(1);

	uint8_t read = *(uint8_t*)(this->buffer + this->index);
	this->index += 1;

	return read;
}

int16_t NetworkReader::readInt16()
{
	this->checkReadOverflow(2);

	int16_t read = *(int16_t*)(this->buffer + this->index);
	this->index += 2;

	return read;
}

uint16_t NetworkReader::readUint16()
{
	this->checkReadOverflow(2);

	uint16_t read = *(uint16_t*)(this->buffer + this->index);
	this->index += 2;

	return read;
}

int32_t NetworkReader::readInt32()
{
	this->checkReadOverflow(4);

	int32_t read = *(int32_t*)(this->buffer + this->index);
	this->index += 4;

	return read;
}

uint32_t NetworkReader::readUint32()
{
	this->checkReadOverflow(4);

	uint32_t read = *(uint32_t*)(this->buffer + this->index);
	this->index += 4;

	return read;
}

/*
std::string NetworkReader::readString()
{}
*/