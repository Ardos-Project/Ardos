#ifndef DC_HASH_GENERATOR_H
#define DC_HASH_GENERATOR_H

#include "notifier/Notify.h"
#include "config/ConfigManager.h"

class DCHashGenerator
{
	public:
		DCHashGenerator();
		~DCHashGenerator();

		void addInt(int size);
		void addString(std::string value);
		uint32_t getHash();

	private:
		const uint32_t max_hash_size = 0xffffffff;
		const int max_index_size = 10000;
		uint32_t hash;
		unsigned int index;

		unsigned int getIndexPrime();
};

#endif // DC_HASH_GENERATOR_H