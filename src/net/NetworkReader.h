#ifndef NETWORK_READER_H
#define NETWORK_READER_H

#include <string>
#include <cstring>
#include <cstdint>

#include "notifier/Notify.h"
#include "net/NetworkWriter.h"

class NetworkWriter;

class NetworkReader
{
	public:
		NetworkReader(std::string &data, unsigned int offset = 0);
		NetworkReader(NetworkWriter &data, unsigned int offset = 0);
		~NetworkReader();

		std::string readData(unsigned int length);
		std::string getRemainingData();

		int8_t readInt8();
		uint8_t readUint8();

		int16_t readInt16();
		uint16_t readUint16();

		int32_t readInt32();
		uint32_t readUint32();

		std::string readString();

	private:
		char* buffer;
		unsigned int buffer_end;
		unsigned int index;

		void checkReadOverflow(unsigned int bytes_to_read);
};

#endif // NETWORK_READER_H