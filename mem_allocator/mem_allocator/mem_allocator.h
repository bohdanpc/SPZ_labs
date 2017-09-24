#pragma once

enum class BlockStatus {
	free = 0,
	used
};

struct memBlock_header {
	BlockStatus blockStatus;
	int size;
	int prev_size;
};

void printHeap();
void traverseHeap();
void *getBlockById(const int id);

void *mem_alloc(const int size);
void mem_free(void *mem_block);
void *mem_realloc(void *block, const int new_size);

