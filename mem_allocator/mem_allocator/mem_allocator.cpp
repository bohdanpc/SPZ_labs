#include "mem_allocator.h"
#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::endl;

enum {
	BLOCK_ALIGNMENT = 4,
	HEAP_SIZE = 100,
};


static unsigned char heap[HEAP_SIZE] = { 0 };
static bool isInitializedHeap = false;


void initHeap() {
	if (!isInitializedHeap) {
		memBlock_header *curr_block = (memBlock_header*)heap;
		curr_block->blockStatus = BlockStatus::free;
		curr_block->prev_size = 0;
		curr_block->size = HEAP_SIZE - sizeof(memBlock_header);
		isInitializedHeap = true;
	}
}

void *mem_alloc(const int size) {
	initHeap();

	bool isFound = false;
	int prev_block_size = 0;
	memBlock_header *curr_block = (memBlock_header*)heap;
	int alignedSize = size;
	if (alignedSize % BLOCK_ALIGNMENT != 0)
	alignedSize += BLOCK_ALIGNMENT - alignedSize % BLOCK_ALIGNMENT;

	do {
		if (curr_block->blockStatus == BlockStatus::free && curr_block->size >= alignedSize)
			isFound = true;
		else {
			prev_block_size = curr_block->size;
			curr_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + curr_block->size);
		}
	} while (!isFound && &heap[HEAP_SIZE - 1] - (unsigned char*)(curr_block + 1) + 1 >= alignedSize);
	
	if (!isFound)
		return nullptr;

	//try to break one block in 2 (one will be returned and next one will be set as free)
	if (curr_block->size > alignedSize + sizeof(memBlock_header)) {
		auto next_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + alignedSize);
		next_block->blockStatus = BlockStatus::free;
		next_block->prev_size = alignedSize;
		next_block->size = curr_block->size - alignedSize - sizeof(memBlock_header);
	}
	else								 //if free space equal or less then memHeader size
		alignedSize = curr_block->size;  //then there's no need to have block with size==0
		
	curr_block->size = alignedSize;
	curr_block->blockStatus = BlockStatus::used;
	curr_block->prev_size = prev_block_size;
	
	return (void*)(curr_block + 1);
}


void mem_free(void *block) {
	if (block) {
		memBlock_header *curr_head = (memBlock_header *)block - 1;
		memBlock_header *prev_head, *next_head;

		if (curr_head->blockStatus == BlockStatus::free)
			return;

		//try to get left block
		if (curr_head->prev_size) 
			prev_head = (memBlock_header *)((unsigned char *)curr_head - curr_head->prev_size) - 1;
		else
			prev_head = nullptr;

		//try to get right block
		if (&heap[HEAP_SIZE - 1] - (unsigned char*)(curr_head + 1) - curr_head->size + 1 > 0)
			next_head = (memBlock_header*)((unsigned char*)(curr_head + 1) + curr_head->size);
		else
			next_head = nullptr;

		curr_head->blockStatus = BlockStatus::free;

		//unite current and left block
		if (prev_head && prev_head->blockStatus == BlockStatus::free) {
			prev_head->size += curr_head->size + sizeof(memBlock_header);
			curr_head = prev_head;
			if (next_head) {
				next_head->prev_size = curr_head->size;
			}
		}

		//unite current and right block
		if (next_head && next_head->blockStatus == BlockStatus::free) {
			curr_head->size += next_head->size + sizeof(memBlock_header);
		}
	}
}


void *mem_realloc(void *block, const int new_size) {
	void *new_block = mem_alloc(new_size);
	if (new_block) {
		mem_free(block);
		return new_block;
	}
	return block;
}


void printHeap() {
	for (int i = 0; i < HEAP_SIZE; i++) {
		cout << std::setw(3) << (int)heap[i] << " ";
		if (i % 20 == 19)
			cout << endl;
	}
}

const std::string blockStatusToStr(const BlockStatus status) {
	if (status == BlockStatus::free)
		return "free";
	if (status == BlockStatus::used)
		return "used";
	return "";
}

void traverseHeap() {
	initHeap();
	memBlock_header *curr_block = (memBlock_header*)heap;
	int blockCount = 0;
	int value = 0;
	while (true) {
		value = &heap[HEAP_SIZE - 1] - (unsigned char*)(curr_block + 1) - curr_block->size + 1;
		cout << "Block " << blockCount++ << ": " << endl;
		cout << "\t  Status: " << blockStatusToStr(curr_block->blockStatus) << endl;
		cout << "\t    Size: " << curr_block->size << endl;
		cout << "\tPrevSize: " << curr_block->prev_size << endl << endl;

		if (&heap[HEAP_SIZE - 1] - (unsigned char*)(curr_block + 1) - curr_block->size + 1 > 0)
			curr_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + curr_block->size);
		else
			break;
	}
}

void *getBlockById(const int id) {
	memBlock_header *curr_block = (memBlock_header*)heap;
	for (int i = 0; i < id; i++) {
		if (&heap[HEAP_SIZE - 1] - (unsigned char*)(curr_block + 1) - curr_block->size + 1 > 0)
			curr_block = (memBlock_header*)((unsigned char*)(curr_block + 1) + curr_block->size);
		else
			return nullptr;
	}
	return (void*)(curr_block + 1);
}
