#pragma once

void *mem_alloc(const size_t size);
void mem_free(void *mem_block);
void *mem_realloc(void *block, const size_t new_size);

