#ifndef UID_ALLOCATOR_H
#define UID_ALLOCATOR_H

#include <vector>

#include "notifier/Notify.h"

class UIDAllocator
{
	public:
		UIDAllocator(uint32_t lo, uint32_t hi);
		~UIDAllocator();

		uint32_t allocate();
		void free(uint32_t id);

	private:
		std::mutex uid_alloc_lock;
		uint32_t lo;
		uint32_t hi;
		uint32_t index;
		std::vector<uint32_t> free_uids;
};

#endif // UID_ALLOCATOR_H