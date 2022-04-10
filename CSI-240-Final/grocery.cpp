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
	int pickOption;
	switch (pickOption)
	{
	case 1:
		//Add chosen item to inventory
		break;
	case 2: 
		//Delete item from inventory
		break;
	case 3: 
		//Load Inventory from file
		break;
	case 4:
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
