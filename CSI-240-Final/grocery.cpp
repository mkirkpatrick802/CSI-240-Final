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
		Exceptions("something went wrong");
		break;
	}
}

//Mikey
//Output char depending on result: a, or c
char login() 
{
	string username;
	string password;
	cout << "Username: ";
	cin >> username;
	cout  << "\nPassword: ";
	cin >> password;

	ifstream login;
	login.open("login.dat");
	if (!login.is_open())
	{
		throw Exceptions("Error - File cannot be found");
	}
	else
	{
		while (!login.eof())
		{
			string temp;
			getline(login, temp);
			if (temp == username)
			{
				getline(login, temp);
				if (temp == password)
				{
					if (username == ADMIN_USER)
					{
						return 'a';
					}
					else
					{
						return 'c';
					}
				}
				else		
				throw Exceptions("Incorrect Password");
			}
		}
		throw Exceptions("Username does not exist");
	}
}

void adminMenu() 
{
	Inventory inventory;
	inventory.importInventory();
	int pickOption = 0;
	//while (pickOption != 4)
	//{

		cout << endl;
		cout << "Please Select How You'd Like to Proceed" << endl;
		cout << "[1] Add Item To Inventory" << endl;
		cout << "[2] Delete Item From Inventory" << endl;
		cout << "[3] Display Inventory" << endl;
		cout << "[4] Save and Quit" << endl;
		cout << "Please Select One To Continue: ";
		cin >> pickOption;
		cout << endl;

		switch (pickOption)
		{
		case 1:
			inventory.addToInventory();
			break;
		case 2:
			inventory.deleteItemFromInventory();
			break;
		case 3:
			inventory.displayInventory();
			break;
		default:
			inventory.exportInventory();
			return;
			break;
		}
	//}

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

//Michael K
void Inventory::addToInventory()
{
	int option = 1;
	do 
	{
		int categoryNum;
		string name;
		double price;

		int index = 0;
		for (string i : CATEGORY_NAMES)
		{
			cout << i << " " << "[" << index << "]" << endl;
			index++;
		}
		cout << "Please Enter A Category Number: ";
		cin >> categoryNum;

		cout << "Please Enter The Name Of The Item (No Spaces): ";
		cin >> name;

		cout << "Please Enter The Price Of The Item: ";
		cin >> price;

		inventoryList.push_back(new Item(categoryNum, name, price));

		cout << "Add Another? [0 for No] [1 for Yes]: ";
		cin >> option;
	} while (option == 1);

	return;
}

//Michael K
void Inventory::deleteItemFromInventory()
{
}

//Michael K
void Inventory::displayInventory()
{
	for (Item* i : inventoryList)
	{
		i->getDescription();
	}

	return;
}

//Michael K
void Inventory::importInventory()
{
	ifstream inventoryFile;
	if (!inventoryFile.is_open()) { throw Exceptions("Error - File not found"); }

	if (!inventoryFile.is_open()) { /*throw exception*/ }

	while (!inventoryFile.eof()) 
	{
		int categoryNum;
		string name;
		double price;
		inventoryFile >> categoryNum;
		inventoryFile >> name;
		inventoryFile >> price;

		if (name.empty()) continue; // Skips empty lines in file

		inventoryList.push_back(new Item(categoryNum, name, price));
	}

	cout << endl << "[[IMPORT SUCCESSFUL]]" << endl;
	return;
}

//Michael K
void Inventory::exportInventory()
{
	ofstream inventoryFile;
	inventoryFile.open(INVENTORY_FILE_NAME);

	if (!inventoryFile.is_open()) { /*throw exception*/ }

	for (Item* i : inventoryList)
	{
		inventoryFile << i->fileFormat() << endl;
	}
	return;
}

string Item::fileFormat()
{
	return to_string(itemCategory) + " " + name + " " + to_string(price);
}

void Item::getDescription()
{
	cout << "Item Type: " << CATEGORY_NAMES[itemCategory] << " | ";
	cout << "Item Name: " << name << " | ";
	cout << "Price: $" << price << " | " << endl;
}

Item::Item(int itemCatagory, string name, double price)
{
	this->itemCategory = itemCatagory;
	this->name = name;
	this->price = price;
}

Exceptions::Exceptions(string message)
{
	this->message = message;
}
