#include "userInterface.h"
#include <iostream>
#include <string>
#include <map>

using std::map;
using std::string;
using std::cout;
using std::cin;
using std::endl;

static map<int, void*> IdToMemBlock;



void menu_allocate() {
	string  strBlockSize;
	size_t blockSize;

	do {
		cout << "Enter block size: ";
		cin >> strBlockSize;
		try {
			blockSize = stoi(strBlockSize);
			break;
		}
		catch (std::invalid_argument &) {
			std::cout << "Invalid size!\n";
		}
		catch (std::out_of_range) {
			std::cout << "Value is out of range!\n";
		}

	} while (true);

	mem_alloc(blockSize);
}


void menu_traverse() { 
	traverseHeap();
};


void menu_free() {
	string  strBlockSize;
	size_t blockSize;

	do {
		cout << "Enter block id: ";
		cin >> strBlockSize;
		try {
			blockSize = stoi(strBlockSize);
			break;
		}
		catch (std::invalid_argument &) {
			cout << "Invalid id!\n";
		}
		catch (std::out_of_range) {
			cout << "Value is out of range!\n";
		}

	} while (true);

	void *block = getBlockById(blockSize);
	if (block) {
		mem_free(block);
		cout << "Success!\n";
	}
	else
		std::cout << "Block wasn't found!\n";
};

void menu_realloc() {

};


void menu_exit() {
	cout << "Exiting...\n";
};



void menu_main() {
	int key = 0;
	string choice;
	do {
		cout << "1. Show the whole memory status" << endl;
		cout << "2. Allocate new block" << endl;
		cout << "3. Free block by id" << endl;
		cout << "4. Realloc existing block by id" << endl;
		cout << "5. Exit" << endl << endl;

		cout << "Enter: ";
		cin >> choice;
		cout << endl;
		if (choice == "1")
			menu_traverse();
		else if (choice == "2")
			menu_allocate();
		else if (choice == "3")
			menu_free();
		else if (choice == "4")
			menu_realloc();
		else if (choice == "5")
			menu_exit();
		else
			cout << "Invalid choice\n\n";

	} while (choice != "5");
}
