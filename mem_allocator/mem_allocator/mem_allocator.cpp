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

void *mem_alloc(const size_t size) {
	initHeap();

	bool isFound = false;
	int prev_block_size = 0;
	memBlock_header *curr_block = (memBlock_header*)heap;

	do {
		if (curr_block->blockStatus == BlockStatus::free && curr_block->size >= size)
			isFound = true;
		else {
			prev_block_size = curr_block->size;
			curr_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + size);
		}
	//till there still could be enough free space to allocate
	} while (!isFound && &heap[HEAP_SIZE-1] - (unsigned char*)(curr_block+1) + 1 >= size);	
	
	if (!isFound)
		return nullptr;

	//try to break one block in 2 (one will be returned and smaller one will be set as free)
	if (curr_block->size >= BLOCK_ALIGNMENT + sizeof(memBlock_header)) {
		auto next_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + size);
		next_block->blockStatus = BlockStatus::free;
		next_block->prev_size = size + size % BLOCK_ALIGNMENT;
		next_block->size = &heap[HEAP_SIZE - 1] - (unsigned char*)(next_block + 1) + 1;
	}

	curr_block->blockStatus = BlockStatus::used;
	curr_block->size = size;
	curr_block->prev_size = prev_block_size;
	
	return (void*)(curr_block + 1);
}

void mem_free(void *block) {

}

void *mem_realloc(void *block, const size_t new_size) {
	return nullptr;
}