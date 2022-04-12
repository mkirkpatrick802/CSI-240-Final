#include "grocery.h"


void startMenu() 
{
	switch (login())
	{
	case 'a':
		adminMenu();
		break;
	case 'c':
		customerMenu();
		break;
	default:
		//throw exception
		break;
	}
}

//Mikey
//Output char depending on result: a, or c
char login() 
{
	//Ask for Username
	//Input Username

	//Check if username exists in login.dat file

	//Ask for password
	//Input password
}

void adminMenu() 
{
	Inventory inventory;
	inventory.importInventory();

	int pickOption;
	cout << "Please Select How You'd Like to Proceed" << endl;
	cout << "[1] Add Item To Inventory" << endl;
	cout << "[2] Delete Item From Inventory" << endl;
	cout << "[3] Display Inventory" << endl;
	cout << "[4] Save and Quit" << endl;
	cout << "Please Select One To Continue: ";
	cin >> pickOption;
	switch (pickOption)
	{
	case 1:
		inventory.addToInventory();
		break;
	case 2: 
		//Delete item from inventory
		break;
	case 3:
		//Display Inventory
		break;
	default:
		// Load vector to file
		// Quit
		break;
	}
}

void customerMenu() 
{
	int pickOption;
	switch (pickOption)
	{
	case 1:
		//Add Inventory Item to cart
		break;
	case 2:
		//REmove Item form cart
		break;
	case 3:
		//Display Cart
		break;
	case 4: 
		//Checkout
		break;
	default:
		//Quit
		break;
	}
}

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

void Inventory::addToInventory()
{

}

void Inventory::displayInventory()
{

}

void Inventory::importInventory()
{
	stringstream ss;
	ifstream inventoryFile;
	//check if file exists
	inventoryFile.open(INVENTORY_FILE_NAME);
	while (!inventoryFile.eof()) 
	{
		string newLine;
		getline(inventoryFile, newLine);
		ss << newLine;
	}

	cout << "[[IMPORT SUCCESSFUL]]" << endl;
}

void Inventory::exportInventory()
{

}
