#include "mem_allocator.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

enum {
	BLOCK_ALIGNMENT = 4,
	HEAP_SIZE = 100,
};


static unsigned char heap[HEAP_SIZE] = { 0 };
static bool isInitializedHeap = false;

void printHeap() {
	for (int i = 0; i < HEAP_SIZE; i++) {
		cout << std::setw(3) << (int) heap[i] << " ";
		if (i % 20 == 19)
			cout << endl;
	}
}

void initHeap() {
	if (!isInitializedHeap) {
		memBlock_header *curr_block = (memBlock_header*)heap;
		curr_block->blockStatus = BlockStatus::free;
		curr_block->prev_size = 0;
		curr_block->size = HEAP_SIZE - sizeof(memBlock_header);
		isInitializedHeap = true;
	}
}

void traverseHeap() {
	memBlock_header *curr_block = (memBlock_header*)heap;
	int blockCount = 0;
	int value = 0;
	while (true) {
		value = &heap[HEAP_SIZE - 1] - (unsigned char*)(curr_block + 1) - curr_block->size + 1;
		cout << "Block " << blockCount++ << ": " << endl;
		cout << "\t  Status: " << (int) curr_block->blockStatus << endl;
		cout << "\t    Size: " << curr_block->size << endl;
		cout << "\tPrevSize: " << curr_block->prev_size << endl << endl;

		if (&heap[HEAP_SIZE - 1] - (unsigned char*)(curr_block + 1) - curr_block->size + 1 > 0)
			curr_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + curr_block->size);
		else
			break;
	}
}

void *mem_alloc(const size_t size) {
	initHeap();

	bool isFound = false;
	int prev_block_size = 0;
	memBlock_header *curr_block = (memBlock_header*)heap;
	int alignedSize = size + BLOCK_ALIGNMENT - size % BLOCK_ALIGNMENT;

	while (true) {
		if (curr_block->blockStatus == BlockStatus::free && curr_block->size >= alignedSize)
			isFound = true;
		else {
			prev_block_size = curr_block->size;
			if (!isFound && &heap[HEAP_SIZE - 1] - (unsigned char*)(curr_block + 1) + 1 >= alignedSize)
				curr_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + alignedSize);
			else break;
		}
	}
	
	if (!isFound)
		return nullptr;

	//try to break one block in 2 (one will be returned and smaller one will be set as free)
	if (curr_block->size >= BLOCK_ALIGNMENT + sizeof(memBlock_header)) {
		auto next_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + alignedSize);
		next_block->blockStatus = BlockStatus::free;
		next_block->prev_size = alignedSize;
		next_block->size = &heap[HEAP_SIZE - 1] - (unsigned char*)(next_block + 1) + 1;
	}

	curr_block->blockStatus = BlockStatus::used;
	curr_block->size = alignedSize;
	curr_block->prev_size = prev_block_size;
	
	return (void*)(curr_block + 1);
}

void mem_free(void *block) {

}

void *mem_realloc(void *block, const size_t new_size) {
	return nullptr;
}