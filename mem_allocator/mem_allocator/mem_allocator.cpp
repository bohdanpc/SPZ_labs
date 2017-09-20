#include "mem_allocator.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

enum {
	HEAP_SIZE = 100,
};


static unsigned char heap[HEAP_SIZE] = { 0 };

void printHeap() {
	for (int i = 0; i < HEAP_SIZE; i++) {
		cout << std::setw(3) << (int) heap[i] << " ";
		if (i % 20 == 19)
			cout << endl;
	}
}


void *mem_alloc(const size_t size) {
	bool isFound = false;
	int prev_block_size = 0;
	mem_header *curr_block = (mem_header*)heap;

	do {
		if (curr_block->blockStatus == BlockStatus::free && curr_block->block_size >= size)
			isFound = true;
		else {
			prev_block_size = curr_block->block_size;
			curr_block = (mem_header*)((unsigned char*)(curr_block + 1) + size);
		}
	} while (!isFound && &heap[HEAP_SIZE-1] - (unsigned char*)(curr_block+1) + 1 <= size);	//till there still could be enough free space to allocate
	
	if (!isFound)
		return nullptr;
	curr_block->blockStatus = BlockStatus::used;
	curr_block->block_size = size;
	curr_block->prev_block_size = prev_block_size;

	return (void*)(curr_block + 1);
}

void mem_free(void *block) {

}

void *mem_realloc(void *block, const size_t new_size) {
	return nullptr;
}