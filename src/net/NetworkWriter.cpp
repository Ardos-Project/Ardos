#include "net/NetworkWriter.h"

#include "net/NetworkReader.h"

NetworkWriter::NetworkWriter() : buffer(new char[64]), index(0)
{}

NetworkWriter::~NetworkWriter()
{
	delete this->buffer;
}

void NetworkWriter::checkAddOverflow(unsigned int bytes_to_add)
{
	
}

char* NetworkWriter::getData()
{
	return this->buffer;
}

unsigned int NetworkWriter::getSize()
{
	return this->index;
}

void NetworkWriter::addHeader(const uint16_t &pid, const uint16_t &msg_type)
{
	this->addUint16(pid);
	this->addUint16(msg_type);
}

void NetworkWriter::addRaw(const std::string &value)
{
	this->checkAddOverflow(value.length());

	std::memcpy(this->buffer + this->index, value.c_str(), value.length());
	this->index += value.length();
}

void NetworkWriter::addInt8(const int8_t &value)
{
	this->checkAddOverflow(1);

	*(int8_t*)(this->buffer + this->index) = value;
	this->index += 1;
}

void NetworkWriter::addUint8(const uint8_t &value)
{
	this->checkAddOverflow(1);

	*(uint8_t*)(this->buffer + this->index) = value;
	this->index += 1;
}

void NetworkWriter::addInt16(const int16_t &value)
{
	this->checkAddOverflow(2);

	*(int16_t*)(this->buffer + this->index) = value;
	this->index += 2;
}

void NetworkWriter::addUint16(const uint16_t &value)
{
	this->checkAddOverflow(2);

	*(uint16_t*)(this->buffer + this->index) = value;
	this->index += 2;
}

void NetworkWriter::addInt32(const int32_t &value)
{
	this->checkAddOverflow(4);

	*(int32_t*)(this->buffer + this->index) = value;
	this->index += 4;
}

void NetworkWriter::addUint32(const uint32_t &value)
{
	this->checkAddOverflow(4);

	*(uint32_t*)(this->buffer + this->index) = value;
	this->index += 4;
}