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
		int8_t readInt8();
		std::string readString();

	private:
		char* buffer;
		unsigned int buffer_end;
		unsigned int index;

		void checkReadOverflow(unsigned int bytes_to_read);
};

#endif // NETWORK_READER_H