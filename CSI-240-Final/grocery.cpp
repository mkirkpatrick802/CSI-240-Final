#include "grocery.h"

//Mikey M
Exceptions::Exceptions(string message)
{
	this->message = message;
}
string Exceptions::getMessage()
{
	return message;
}

//Michael K
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
// Mikey M
void customerMenu() 
{
	cout << endl;

	Cart cart;
	Inventory inventory;
	int pickOption;
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

//Michael K
Inventory::Inventory()
{
	inventoryList.resize(0);
}

//Michael K
Inventory::~Inventory()
{
	for (Vendor* i : inventoryList)
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

	adminMenu();
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

	adminMenu();
}

//Michael K
void Inventory::displayInventory()
{
	for (Vendor* i : inventoryList)
	{
		i->getDescription();
	}

	adminMenu();
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
		inventoryList.push_back(new Item(categoryNum, name, price));
	}

	cout << endl << "[[IMPORT SUCCESSFUL]]" << endl;
}

//Michael K
void Inventory::exportInventory()
{
	ofstream inventoryFile;
	inventoryFile.open(INVENTORY_FILE);

	if (!inventoryFile.is_open()) { throw Exceptions("Can't Open " + INVENTORY_FILE); }

	for (Vendor* i : inventoryList)
	{
		inventoryFile << i->fileFormat() << endl;
	}
}
// Mikey M
Cart::Cart()
{
	cart.resize(0);
}
// Mikey M
Cart::~Cart()
{
	for (Vendor* i : cart)
	{
		delete i;
	}
	cart.clear();
}

//Michael K
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

	cout << endl;

	while (!inventoryFile.eof()) 
	{
		int categoryNum;
		inventoryFile >> categoryNum;
		if (categoryNum == option)
		{
			string name;
			double price;
			inventoryFile >> name;
			inventoryFile >> price;

			aisleItems.push_back(new Item(categoryNum, name, price));
		}
		else
		{
			inventoryFile.ignore(1000, '\n');
		}
	}

	int continueOption = 1;
	int amount;
	do
	{
		int index = 0;
		for (Item* i : aisleItems) 
		{
			cout << "[" << index << "]";
			i->getDescription();
			index++;
		}

		cout << endl;
		cout << "Which item would you like to purchase?: ";
		cin >> chosenItem;

		if (chosenItem > aisleItems.size() - 1) { cout << "Please Enter a Valid Item" << endl; cout << endl; continue; }

		cout << "How many would you like?: ";
		cin >> amount;

		Item* itemToAdd = new Item(aisleItems[chosenItem]->getItemCategory(), amount, aisleItems[chosenItem]->getName(), aisleItems[chosenItem]->getPrice());
		cart.push_back(itemToAdd);

		cout << "Add Another? [0 for No] [1 for Yes]: ";
		cin >> continueOption;

		cout << endl;
	} while (continueOption != 0);

	customerMenu();
}

// Mikey M
void Cart::removeFromCart()
{
	cout << "What would you like to remove?" << endl;
	customerMenu();
}

//Michael K
void Cart::displayCart()
{
	cout << cart.size();
	for (Vendor* i : cart) 
	{
		i->getDescription();
	}
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

int Item::getItemCategory()
{
	return itemCategory;
}

int Item::getAmount()
{
	return amount;
}

string Vendor::getName()
{
	return name;
}

double Vendor::getPrice()
{
	return price;
}

//Michael K
void Item::getDescription()
{

	cout << "Item Type: " << CATEGORY_NAMES[itemCategory] << " | ";
	cout << "Item Name: " << name << " | ";
	cout << "Price: $" << price << " | ";
	if (amount > 0) 
	{
		cout << "Amount: " << amount << " | " << endl;
	}
	else
	{
		cout << endl;
	}
}

//double Item::operator*(const Item& left)
//{
//	double subtotal = left.price * left.amount;
//	double afterTax = subtotal * CATEGORY_TAXS[left.itemCategory];
//	return afterTax;
//}

int Item::totalAmount()
{
	return 0;
}

Vendor::Vendor()
{
	name = "";
	price = 0;
}

Vendor::Vendor(string name, double price)
{
	this->name = name;
	this->price = price;
}

Item::Item() : Vendor()
{
	itemCategory = 0;
	amount = 0;
}

Item::Item(int itemCatagory, string name, double price) : Vendor(name, price)
{
	this->itemCategory = itemCatagory;
	amount = 0;
}

Item::Item(int itemCatagory, int amount, string name, double price) : Vendor(name, price)
{
	this->itemCategory = itemCatagory;
	this->amount = amount;
}
