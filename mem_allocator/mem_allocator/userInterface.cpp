#include "userInterface.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

void menu_allocate() {
	

}

void menu_traverse() { };
void menu_free() {};
void menu_realloc() {};
void menu_exit() {};



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
			cout << "Exiting...\n";
		else
			cout << "Invalid choice\n\n";

	} while (choice != "5");
}
