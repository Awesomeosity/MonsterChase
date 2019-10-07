// Mallocate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include "HeapManagerProxy.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define SUPPORTS_ALIGNMENT
#define SUPPORTS_SHOWFREEBLOCKS
#define SUPPORTS_SHOWOUTSTANDINGALLOCATIONS

int main()
{
	using namespace HeapManagerProxy;
	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 0;

	// round our size to a multiple of memory page size
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	assert(pHeapMemory);
	HeapManager* pHeapManager = CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
	assert(pHeapManager);

	if (pHeapManager == nullptr)
	{
		std::cout << "BAD POINTER GENERATED\n";
	}
	std::vector<void*> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

		void* pPtr = alloc(pHeapManager, sizeAlloc);
		if (pPtr == nullptr)
		{
			break;
		}
		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

	} while (1);

	printf("After exhausting allocations:\n");
	ShowFreeBlocks(pHeapManager);
	ShowOutstandingAllocations(pHeapManager);
	printf("\n");

	_getch();
}

