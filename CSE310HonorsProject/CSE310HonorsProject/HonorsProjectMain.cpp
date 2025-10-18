// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Daniel Budavari
// ASU ID:1224612207
// Description: 

//used past assignments for menu structure
#include <iostream> 
#include <iomanip>
#include <string>
#include "AVLTree.h"

using namespace std;

void printMenu();

int main()
{
	char input1 = 'Z';
	int key;
	bool success = false;

	printMenu();
	Tree tree; //removed from inside the do-while loop

	do { //This menu will be used to test all the functions
		
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer


		// matches one of the cases
		switch (input1)
		{

		case 'S':	//Search Node
			cout << "Enter the key of the desired node: ";
			cin >> key;
			cin.ignore(20, '\n');	//flush the buffer 
			if (tree.search(key, tree.getRoot()) == -1) {
				cout << "Car with key: " << key << " cannot be found." << endl;
			}
			else {
				cout << "Car with key: " << key << " is found!" << endl;
			}
			break;

		case 'I':	//Insert Node
			
			cout << "Insert the node, enter the node's key: " << endl;
			cin >> key;
			cin.ignore(20, '\n');
			if (tree.insert(key, tree.getRoot(), NULL) == false) {
				cout << "Node cannot be inserted." << endl;
			}
			else {
				cout << "Node has been inserted." << endl;
			}
			
			break;

		case 'D':	//Delete Node
			cout << "Enter the key of the node to be deleted: " << endl;
			cin >> key;
			cin.ignore(20, '\n');

			//figure out what data is and if I should change prev
			if (tree.deleteNode(key, tree.getRoot(), NULL, NULL) == false) {
				cout << "Node cannot be deleted." << endl;
			}
			else {
				cout << "Node has been deleted." << endl;
			}
			break;

		case 'R':	//Pre-Order
			cout << "Pre-Order Traversal: " << endl;
			tree.preOrderPrint(tree.getRoot());
			break;

		case 'T':	//Post-Order
			cout << "Post-Order Traversal: " << endl;
			tree.postOrderPrint(tree.getRoot());
			break;
	
		case 'P':	//Print tree 
			cout << "Print the Tree (In-Order): " << endl;
			tree.printTree(tree.getRoot());
			
			break;

		case 'Q':	//Quit
			tree.~Tree(); cout << "Program Ended, thank you!" << endl;
			break;

		case '?':	//Display Menu
			printMenu();
			break;

		default:
			cout << "Unknown action\n";
			break;
		}
	} while (input1 != 'Q');

	exit(0);
}
//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "S\t\tSearch Node\n";
	cout << "I\t\tInsert Node\n";
	cout << "D\t\tDelete Node\n";
	cout << "R\t\tPre-Order\n";
	cout << "T\t\tPost-Order\n";
	cout << "P\t\tPrint Tree (In-Order)\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}