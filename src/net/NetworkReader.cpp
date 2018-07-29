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
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[NR]", "Attempted to read more data than available");
		throw std::exception("Read Overflow");
	}
}

int8_t NetworkReader::readInt8()
{
	this->checkReadOverflow(1);

	int8_t read = *(int8_t*)(this->buffer + this->index);
	this->index += 1;

	return read;
}

/*
std::string NetworkReader::readString()
{}
*/