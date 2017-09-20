#include "mem_allocator.h"

enum class BlockStatus {
	free = 0,
	used
};
struct header {
	BlockStatus blockStatus;
	size_t block_size;
	size_t prev_block_size;
};


enum {
	HEAP_SIZE = 1000,
};


static unsigned char heap[HEAP_SIZE];

void *mem_alloc(const size_t size) {
	
}

void mem_free(void *block) {

}

void *mem_realloc(void *block, const size_t new_size) {

}