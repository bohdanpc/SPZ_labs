#include <iostream>
#include "mem_allocator.h"
#include "userInterface.h"

int main() {
	/*void *block0 = mem_alloc(20);
	void *block1 = mem_alloc(10);
	void *block2 = mem_alloc(17);

	((unsigned char*)block0)[0] = 15;
	((unsigned char*)block0)[1] = 16;
	((unsigned char*)block0)[2] = 17;

	((unsigned char*)block1)[0] = 25;
	((unsigned char*)block1)[1] = 26;
	((unsigned char*)block1)[2] = 27;

	std::cout << "Heap traverse: \n\n";
	traverseHeap();

	mem_free(block0);

	std::cout << "\n\nHeap traverse: \n\n";
	traverseHeap();

	mem_free(block1);

	std::cout << "\n\nHeap traverse: \n\n";
	traverseHeap();*/

	menu_main();
	return 0;
}