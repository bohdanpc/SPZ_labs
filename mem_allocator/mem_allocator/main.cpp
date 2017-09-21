#include <iostream>
#include "mem_allocator.h"

int main() {
	void *block = mem_alloc(20);
	((unsigned char*)block)[0] = 35;
	((unsigned char*)block)[1] = 36;
	((unsigned char*)block)[2] = 37;

	//(unsigned char* (block = 3;
	printHeap();

	std::cout << std::endl << std::endl << sizeof(memBlock_header) << std::endl;
	return 0;
}