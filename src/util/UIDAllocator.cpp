#include "util/UIDAllocator.h"

UIDAllocator::UIDAllocator(uint32_t lo, uint32_t hi)
{
	this->lo = lo; // Starting id.
	this->hi = hi; // Maximum id.

	this->index = this->lo; // Start us off at the minimum.
}

UIDAllocator::~UIDAllocator()
{}

uint32_t UIDAllocator::allocate()
{
	std::lock_guard<std::mutex> guard(this->uid_alloc_lock);

	// Do we have a free uid waiting to be re-allocated?
	if (!this->free_uids.empty())
	{
		// Get the oldest free uid first.
		uint32_t free_uid = this->free_uids.front();
		this->free_uids.erase(this->free_uids.begin());

		return free_uid;
	}

	// Have we reached our limit?
	if (this->index >= this->hi)
	{
		// Start off again at the minimum. Better than crashing/returning max value over and over.
		this->index = (this->index + this->lo) % this->hi;
	}
	
	uint32_t uid = this->index;
	this->index++;
	
	return uid;
}

void UIDAllocator::free(uint32_t free_uid)
{
	std::lock_guard<std::mutex> guard(this->uid_alloc_lock);

	// Index hasn't even reached this id yet. Did we overflow?
	if (this->index < free_uid)
	{
		return;
	}

	this->free_uids.push_back(free_uid);
}