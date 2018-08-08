#ifndef NETWORK_WRITER_H
#define NETWORK_WRITER_H

#include <string>
#include <cstdint>

class NetworkReader;

class NetworkWriter
{
	public:
		NetworkWriter();
		~NetworkWriter();

		char* getData();
		unsigned int getSize();

		void addRaw(const std::string &value);

		void addInt8(const int8_t &value);
		void addUint8(const uint8_t &value);

		void addInt16(const int16_t &value);
		void addUint16(const uint16_t &value);

		void addInt32(const int32_t &value);
		void addUint32(const uint32_t &value);

	private:
		char* buffer;
		unsigned int index;

		void checkAddOverflow(unsigned int bytes_to_add);
};

#endif // NETWORK_WRITER_H