#include "net/NetworkWriter.h"

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

void NetworkWriter::addInt8(int8_t &value)
{
	this->checkAddOverflow(1);

	*(int8_t*)(this->buffer + this->index) = value;
	this->index += 1;
}