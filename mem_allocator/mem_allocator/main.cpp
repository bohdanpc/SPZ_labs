#include <iostream>
#include "mem_allocator.h"

int main() {
	void *block = mem_alloc(20);
	void *block2 = mem_alloc(10);

	((unsigned char*)block)[0] = 15;
	((unsigned char*)block)[1] = 16;
	((unsigned char*)block)[2] = 17;

	((unsigned char*)block2)[0] = 25;
	((unsigned char*)block2)[1] = 26;
	((unsigned char*)block2)[2] = 27;

	//(unsigned char* (block = 3;
	printHeap();

	std::cout << "Heap traverse: \n\n";
	traverseHeap();

	std::cout << std::endl << std::endl << sizeof(memBlock_header) << std::endl;
	return 0;
}