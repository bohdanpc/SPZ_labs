#pragma once

enum class BlockStatus {
	free = 0,
	used
};

struct memBlock_header {
	BlockStatus blockStatus;
	size_t size;
	size_t prev_size;
};

void printHeap();
void traverseHeap();
void *getBlockById(const size_t id);

void *mem_alloc(const size_t size);
void mem_free(void *mem_block);
void *mem_realloc(void *block, const size_t new_size);

