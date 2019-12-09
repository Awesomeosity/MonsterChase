#pragma once
#include "../Mallocate/HeapManagerProxy.h"
#include "../Mallocate/FixedSizeAllocator.h"
#include <vector>

// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect();

// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem();

HeapManager* heap;
std::vector<FixedSizeAllocator*> allFSAs;