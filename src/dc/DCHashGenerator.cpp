#include "dc/DCHashGenerator.h"

DCHashGenerator::DCHashGenerator()
{
	this->hash = 0;
	this->index = 0;
}

DCHashGenerator::~DCHashGenerator()
{}

void DCHashGenerator::addInt(int size)
{
	this->hash = (this->hash + (this->getIndexPrime() * size)) % this->max_hash_size; // Enforce our max hash size.
	this->index = (this->index + 1) % this->max_index_size; // Enforce our max index limit.
}

void DCHashGenerator::addString(std::string value)
{
	this->addInt(value.length());
	for (auto i = value.begin(); i != value.end(); ++i)
	{
		this->addInt(*i);
	}
}

uint32_t DCHashGenerator::getHash()
{
	return (this->hash & 0xffffffff);
}

unsigned int DCHashGenerator::getIndexPrime()
{
	// TODO
	return this->index;
}