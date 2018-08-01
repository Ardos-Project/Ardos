#ifndef NETWORK_WRITER_H
#define NETWORK_WRITER_H

#include <cstdint>

class NetworkWriter
{
	public:
		NetworkWriter();
		~NetworkWriter();

		char* getData();
		unsigned int getSize();

		void addInt8(int8_t &value);
		void addUint8(uint8_t &value);

		void addInt16(int16_t &value);
		void addUint16(uint16_t &value);

	private:
		char* buffer;
		unsigned int index;

		void checkAddOverflow(unsigned int bytes_to_add);
};

#endif // NETWORK_WRITER_H