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
	int pickOption = 0;

	while (pickOption != 5)
	{
		cout << endl;
		cout << "Hello valued customer! Please select the desired option." << endl;
		cout << "[1] Add item to cart" << endl;
		cout << "[2] Remove item from cart" << endl;
		cout << "[3] List items in cart" << endl;
		cout << "[4] Checkout" << endl;
		cout << "[5] Quit" << endl;
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
		case 5:
			return;
			break;
		}
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
}

//Michael K
void Inventory::deleteItemFromInventory()
{
	int option = 1;
	do 
	{
		string name;
		displayInventory();
		cout << "\nPlease Enter The Item You'd Like To Delete: ";
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
	for (Vendor* i : inventoryList)
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
	vector<Vendor*> aisleItems;
	int chosenItem;
	ifstream inventoryFile;
	int again = 0;
	do
	{
		inventoryFile.open(INVENTORY_FILE);
		if (!inventoryFile.is_open()) { throw Exceptions("Can't Open " + INVENTORY_FILE); }
		int option = -1;
		int index = 0;
		for (string i : CATEGORY_NAMES)
		{
			cout << i << " " << "[" << index << "]" << endl;
			index++;
		}

		cout << endl;

		cout << "Which aisle would you like to add from?" << endl;
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

				if (categoryNum == SERVICE)
				{
					aisleItems.push_back(new Service(name, price));
				}
				else
				{
					aisleItems.push_back(new Item(categoryNum, name, price));
				}
			}
			else
			{
				inventoryFile.ignore(1000, '\n');
			}
		}

		int amount;
		double phoneNumber;


		index = 0;
		for (Vendor* i : aisleItems)
		{
			cout << "[" << index << "]";
			i->getDescription();
			index++;
		}

		cout << endl;
		cout << "Which item would you like to purchase?: ";
		cin >> chosenItem;

		if (chosenItem > aisleItems.size() - 1) { cout << "Please Enter a Valid Item" << endl; cout << endl; continue; }

		if (option == SERVICE)
		{
			cout << "Please enter your Phone Number so we can contact you with further instructions: ";
			cin >> phoneNumber;

			Service* serviceToAdd = new Service(aisleItems[chosenItem]->getName(), aisleItems[chosenItem]->getPrice(), phoneNumber);
		}
		else
		{
			cout << "How many would you like?: ";
			cin >> amount;

			Item* itemToAdd = new Item(aisleItems[chosenItem]->getCategory(), amount, aisleItems[chosenItem]->getName(), aisleItems[chosenItem]->getPrice());
			cart.push_back(itemToAdd);
		}

		cout << "Add Another? [0 for No] [1 for Yes]: ";
		cin >> again;

		cout << endl;


		for (Vendor* i : aisleItems)
		{
			delete i;
		}
		aisleItems.clear();
		inventoryFile.close();
	} while (again == 1);
}

// Mikey M
void Cart::removeFromCart()
{
	int option = 1;
	do
	{
		displayCart();
		string name;

		cout << "What would you like to remove?: ";
		cin >> name;

		for (int i = 0; i < cart.size(); i++)
		{
			if (cart[i]->getName() != name) continue;

			cart.erase(cart.begin() + i);
		}
		cout << "Would you like to remove another? [0 for No] [1 for Yes]: ";
		cin >> option;

		cout << endl;
	} while (option == 1);
}


//Michael K
void Cart::displayCart()
{
	for (Vendor* i : cart) 
	{
		i->getDescription();
	}
}

//Michael K
void Cart::calculateTotalPrice()
{
	double totalPrice = 0;
	for (Vendor* i : cart)
	{
		double salesTaxAmount = 0;
		i->getDescription();
		salesTaxAmount += SALES_TAX * *i;
		totalPrice = totalPrice + *i; 
		totalPrice += salesTaxAmount;
	}

	cout << "Total Cost: $" << fixed << setprecision(2) << totalPrice;
}

//Michael K
string Item::fileFormat()
{
	return to_string(itemCategory) + " " + name + " " + to_string(price);
}

//Michael K
int Item::getCategory()
{
	return itemCategory;
}

//Michael K
int Item::getItemCategory()
{
	return itemCategory;
}

//Michael K
int Item::getAmount()
{
	return amount;
}

//Michael K
string Vendor::getName()
{
	return name;
}

//Michael K
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

//Mikey M
double operator+(const double& left, Vendor& right)
{

	return left + right.totalAmount();
}

//Mikey M
double operator*(const double& left, Vendor& right)
{
	
	return left * right.totalAmount();
}

//Michael K
double Item::totalAmount()
{
	if (amount > 0) 
	{
		double taxPrice = (price * amount) * CATEGORY_TAX[itemCategory];
		return (price*amount) + taxPrice;
	}
	else 
	{
		throw Exceptions("You don't have any " + name + " in your cart");
		return 0;
	}
}

//Michael K
Vendor::Vendor()
{
	name = "";
	price = 0;
}

//Michael K
Vendor::Vendor(string name, double price)
{
	this->name = name;
	this->price = price;
}

//Michael K
Item::Item() : Vendor()
{
	itemCategory = 0;
	amount = 0;
}

//Michael K
Item::Item(int itemCatagory, string name, double price) : Vendor(name, price)
{
	this->itemCategory = itemCatagory;
	amount = 0;
}

//Michael K
Item::Item(int itemCatagory, int amount, string name, double price) : Vendor(name, price)
{
	this->itemCategory = itemCatagory;
	this->amount = amount;
}

//Michael K
Service::Service()
{
	category = 0;
	phoneNumber = 1111111111;
}

//Michael K
Service::Service(string name, double price) : Vendor(name, price)
{
	category = 0;
	phoneNumber = 1111111111;
}

//Michael K
Service::Service(string name, double price, double phoneNumber) : Vendor(name, price)
{
	category = 0;
	this->phoneNumber = phoneNumber;
}

//Michael K
double Service::totalAmount()
{
	double taxAmount = price * CATEGORY_TAX[category];
	return price + taxAmount;
}

//Michael K
string Service::fileFormat()
{
	return string();
}

//Michael K
void Service::getDescription()
{
	cout << "Service Name: " << name << " | ";
	cout << "Price: $" << price << " | ";
}

//Michael K
int Service::getCategory()
{
	return category;
}
