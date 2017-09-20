#pragma once

enum class BlockStatus {
	free = 0,
	used
};

struct mem_header {
	BlockStatus blockStatus;
	size_t block_size;
	size_t prev_block_size;
};

void printHeap();
void *mem_alloc(const size_t size);
void mem_free(void *mem_block);
void *mem_realloc(void *block, const size_t new_size);

