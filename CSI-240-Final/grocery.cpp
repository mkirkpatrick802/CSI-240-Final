#include "grocery.h"

Exceptions::Exceptions(string message)
{
	this->message = message;
}
string Exceptions::getMessage()
{
	return message;
}

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
	case 'r':
		startMenu();
		break;
	}
}

//Mikey M
//Output char depending on result: a, or c
char login() 
{
	string username;
	string password;
	ifstream login;
	login.open(LOGIN_FILE);
	if (!login.is_open())
	{
		throw Exceptions("Can't Open " + LOGIN_FILE);
	}
	else
	{
		cout << "Username: ";
		cin >> username;
		while (!login.eof())
		{
			string line;
			getline(login, line);
			if (line != username) continue;
			if (line == ADMIN_USER) 
			{
				cout << "Password: ";
				cin >> password;

				getline(login, line);
				if (line != password) { throw Exceptions("Incorrect Password"); return 'r'; }
				return 'a';
			}
			else if(line == CUSTOMER_USER)
			{
				cout << "Password: ";
				cin >> password;

				getline(login, line);
				if (line != password) { throw Exceptions("Incorrect Password"); return 'r'; }
				return 'c';
			}
		}
		throw Exceptions("Username does not exist");
	}
	return 'r';
}

//Michael K
void adminMenu() 
{
	Inventory inventory;
	inventory.importInventory();
	int pickOption = 0;
	while (pickOption != 4)
	{

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
	}

}
// Mikey M
void customerMenu() 
{
	Cart cart;
	Inventory inventory;
	int pickOption;
	inventory.displayInventory();
	cout << "Hello valued customer! Please select the desired option." << endl;
	cout << "[1] Add item to cart" << endl;
	cout << "[2] Remove item from cart" << endl;
	cout << "[3] List items in cart" << endl;
	cout << "[4] Checkout" << endl;
	cout << "Input any other number to quit" << endl;
	cout << "Option: ";
	cin >> pickOption;
	cout << endl;
	switch (pickOption)
	{
	case 1:
		cart.addToCart();
		break;
	case 2:
		cart.removeFromCart();
		break;
	case 3:
		cart.displayCart();
		break;
	case 4: 
		cart.calculateTotalPrice();
		break;
	default:
		return;
		break;
	}
}

Inventory::Inventory()
{
	inventoryList.resize(0);
}

Inventory::~Inventory()
{
	for (Item* i : inventoryList)
	{
		delete i;
	}
	inventoryList.clear();
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

		cout << endl;
	} while (option == 1);
}

//Michael K
void Inventory::deleteItemFromInventory()
{
	int option = 1;
	do 
	{
		string name;

		cout << "Please Enter The Item You'd Like To Delete: ";
		cin >> name;

		for (int i = 0; i < inventoryList.size(); i++) 
		{
			if (inventoryList[i]->getName() != name) continue;

			inventoryList.erase(inventoryList.begin()+i);
		}


		cout << "Delete Another? [0 for No] [1 for Yes]: ";
		cin >> option;

		cout << endl;

	} while (option == 1);
}

//Michael K
void Inventory::displayInventory()
{
	for (Item* i : inventoryList)
	{
		i->getDescription();
	}
}

//Michael K
void Inventory::importInventory()
{
	ifstream inventoryFile;
	inventoryFile.open(INVENTORY_FILE);

	if (!inventoryFile.is_open()) { throw Exceptions("Can't Open " + INVENTORY_FILE); }

	while (!inventoryFile.eof()) 
	{
		int categoryNum;
		string name;
		double price;
		inventoryFile >> categoryNum;
		inventoryFile >> name;
		inventoryFile >> price;

		if (name.empty()) continue; // Skips empty lines in file

		;
	}

	cout << endl << "[[IMPORT SUCCESSFUL]]" << endl;
}

//Michael K
void Inventory::exportInventory()
{
	ofstream inventoryFile;
	inventoryFile.open(INVENTORY_FILE);

	if (!inventoryFile.is_open()) { throw Exceptions("Can't Open " + INVENTORY_FILE); }

	for (Item* i : inventoryList)
	{
		inventoryFile << i->fileFormat() << endl;
	}
}
// Mikey M
Cart::Cart()
{

}
// Mikey M
Cart::~Cart()
{

}
// Mikey M
void Cart::addToCart()
{
	vector<Item*> aisleItems;
	int chosenItem;
	int option;
	ifstream inventoryFile;
	inventoryFile.open(INVENTORY_FILE);
	if (!inventoryFile.is_open()) { throw Exceptions("Can't Open " + INVENTORY_FILE); }

	cout << "Which aisle would you like to add from?" << endl;
	int index = 0;
	for (string i : CATEGORY_NAMES)
	{
		cout << i << " " << "[" << index << "]" << endl;
		index++;
	}

	cout << "Aisle: ";
	cin >> option;

	index = 0;
	while (!inventoryFile.eof()) 
	{
		int categoryNum;
		inventoryFile >> categoryNum;
		if (categoryNum == option)
		{
			index++;

			string name;
			double price;
			inventoryFile >> name;
			inventoryFile >> price;

			aisleItems.push_back(new Item(categoryNum, name, price));
			aisleItems[index--]->getDescription();
		}
		else
			inventoryFile.ignore('\n');
	}
	cout << endl;
	cout << "Which item would you like to purchase?: ";
	cin >> chosenItem;

	//cart.push_back(aisleItems[chosenItem]);
	//cart[1]->getDescription();

	customerMenu();
}

// Mikey M
void Cart::removeFromCart()
{
	cout << "What would you like to remove?" << endl;
	customerMenu();
}

// Mikey M
void Cart::displayCart()
{
	cout << "There are X items in your cart." << endl;
	customerMenu();
}

// Mikey M
void Cart::calculateTotalPrice()
{
	cout << "The X items purchased cost a total of Y." << endl;
	customerMenu();
}


string Item::fileFormat()
{
	return to_string(itemCategory) + " " + name + " " + to_string(price);
}

string Item::getName()
{
	return name;
}

void Item::getDescription()
{

	cout << "Item Type: " << CATEGORY_NAMES[itemCategory] << " | ";
	cout << "Item Name: " << name << " | ";
	cout << "Price: $" << price << " | " << endl;

}

int Item::totalAmount()
{
	return 0;
}



Item::Item()
{
	itemCategory = 0;
	name = "";
	price = 0;
}

Item::Item(int itemCatagory, string name, double price)

{

	this->itemCategory = itemCatagory;
	this->name = name;
	this->price = price;

}

Meats::Meats()
{
	itemCategory = 1;
}

Meats::Meats(string name, double price)
{
	this->name = name;
	this->price = price;
}

int Meats::totalAmount()
{
	return 0;
}

Vegetables::Vegetables()
{
}

Vegetables::Vegetables(string name, double price)
{
	this->name = name;
	this->price = price;
}

int Vegetables::totalAmount()
{
	return 0;
}

Fruits::Fruits()
{
}

Fruits::Fruits(string name, double price)
{
	this->name = name;
	this->price = price;
}

int Fruits::totalAmount()
{
	return 0;
}

BakedGoods::BakedGoods()
{
}

BakedGoods::BakedGoods(string name, double price)
{
	this->name = name;
	this->price = price;
}

int BakedGoods::totalAmount()
{
	return 0;
}

Snacks::Snacks()
{
}

Snacks::Snacks(string name, double price)
{
	this->name = name;
	this->price = price;
}

int Snacks::totalAmount()
{
	return 0;
}

Drinks::Drinks()
{
}

Drinks::Drinks(string name, double price)
{
	this->name = name;
	this->price = price;
}

int Drinks::totalAmount()
{
	return 0;
}

Stock::Stock()
{
	itemCategory = 0;
	name = "";
	price = 0;
	amount = 0;
}
