#include "grocery.h"

//Mikey M
/*
	Input: A message string
	Output: An exception object
	Purpose: Print out an error message if an error ocurrs
*/
Exceptions::Exceptions(string message)
{
	this->message = message;
}
string Exceptions::getMessage()
{
	return message;
}

//Michael K
/*
	Input: a char given by the login function
	Output: none
	Purpose: Bring the user to the appropriate menu based on their login credentials
*/
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
/*
	Input: login.dat file, strings inputted by the user
	Output: a char bit for use by the startMenu function
	Purpose: takes the strings inputted by the user, compares them to the login.dat file, and returns a char depending on the inputs
*/
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
/*
	Input: char from startMenu 
	Output: the menu for shop employees
	Purpose: Allows employees to access the appropriate functions 
*/
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
/*
	Input: char from startMenu
	Output: the menu for shop customers
	Purpose: Allows customers to access the appropriate functions 
*/
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
/*
	Input: Inventory linked list
	Output: Inventory linked list
	Purpose: resizes the inventory linked list upon creation of an inventory item
*/
Inventory::Inventory()
{
	inventoryList.resize(0);
}

//Michael K
/*
	Input: Inventory linked list
	Output: Inventory linked list
	Purpose: resizes the inventory linked list upon destruction of an inventory item
*/
Inventory::~Inventory()
{
	for (Vendor* i : inventoryList)
	{
		delete i;
	}
	inventoryList.clear();
}

//Michael K
/*
	Input: inventory linked list
	Output: inventory linked list
	Purpose: adds an item to the inventory linked list
*/
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
/*
	Input: inventory linked list
	Output: inventory linked list
	Purpose: removes an item from the inventory linked list
*/
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
/*
	Input: inventory linked list
	Output: inventory linked list
	Purpose: prints the items of the inventory linked list to the screen
*/
void Inventory::displayInventory()
{
	for (Vendor* i : inventoryList)
	{
		i->getDescription();
	}
}

//Michael K
/*
	Input: inventory.dat
	Output: inventory linked list
	Purpose: creates a linked list from the items in inventory.dat
*/
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
/*
	Input: inventory linked list
	Output: inventory.dat
	Purpose: saves the items from the linked list into the inventory.dat file
*/
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
/*
	Input: Cart linked list
	Output: Cart linked list
	Purpose: resizes the cart linked list upon addition of an item to the cart
*/
Cart::Cart()
{
	cart.resize(0);
}
// Mikey M
/*
	Input: Cart linked list
	Output: Cart linked list
	Purpose: resizes the cart linked list upon removal of an item from the cart
*/
Cart::~Cart()
{
	for (Vendor* i : cart)
	{
		delete i;
	}
	cart.clear();
}

//Michael K
/*
	Input: cart linked list
	Output: cart linked list
	Purpose: adds an item to the cart linked list
*/
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
			cart.push_back(serviceToAdd);
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
/*
	Input: cart linked list
	Output: cart linked list
	Purpose: removes an item from the cart linked list
*/
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
/*
	Input: cart linked list
	Output: cart linked list
	Purpose: prints the items of the cart linked list to the screen
*/
void Cart::displayCart()
{
	for (Vendor* i : cart) 
	{
		i->getDescription();
	}
}

//Michael K
/*
	Input: cart linked list, float price & int amount
	Output: double totalPrice
	Purpose: takes the items from the cart linked list, calculates the price owed by the customers to pay the shop
*/
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
/*
	Input: enum category
	Output: category string
	Purpose: takes the category enum and converts it to the appropriate aisle string
*/
string Item::fileFormat()
{
	return to_string(itemCategory) + " " + name + " " + to_string(price);
}

//Michael K
/*
	Input: Item object
	Output: category string
	Purpose: gets the category string from the inputted item
*/
int Item::getCategory()
{
	return itemCategory;
}

//Michael K
/*
	Input: Item object
	Output: category string
	Purpose: gets the category string from the inputted item
*/
int Item::getItemCategory()
{
	return itemCategory;
}

//Michael K
/*
	Input: Item object
	Output: amount integer
	Purpose: gets the amount integer from the inputted item
*/
int Item::getAmount()
{
	return amount;
}

//Michael K
/*
	Input: Vendor object
	Output: name string
	Purpose: gets the name string from the inputted vendor
*/
string Vendor::getName()
{
	return name;
}

//Michael K
/*
	Input: Vendor object
	Output: float price
	Purpose: gets the float price from the inputted vendor
*/
double Vendor::getPrice()
{
	return price;
}

//Michael K
/*
	Input: Item object
	Output: the details of the item
	Purpose: prints the category, name, and price of each item to the screen
*/
void Item::getDescription()
{

	cout << left << "Item Type: " << setw(FIELD_WIDTH) << right << CATEGORY_NAMES[itemCategory] << " | ";
	cout << left << "Item Name: " << setw(FIELD_WIDTH) << right << name << " | ";
	cout << left << "Price: $" << setw(FIELD_WIDTH) << right << fixed << setprecision(2) << price << " | ";
	if (amount > 0) 
	{
		cout << left << "Amount: " << setw(FIELD_WIDTH) << right << amount << " | " << endl;
	}
	else
	{
		cout << endl;
	}
}

//Mikey M
/*
	Input: two prices
	Output: the total amount
	Purpose: calculates the total amount owed by the customer for the items paid
*/
double operator+(const double& left, Vendor& right)
{

	return left + right.totalAmount();
}

//Mikey M
/*
	Input: the item price, and the amount of items purchased
	Output: the total amount
	Purpose: calculates the total amount owed by the customer for the items paid
*/
double operator*(const double& left, Vendor& right)
{
	
	return left * right.totalAmount();
}

//Michael K
/*
	Input: the tax price
	Output: the total amount
	Purpose: adds the tax amount to the amount owed by the customer
*/
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
/*
	Input: none
	Output: Vendor item
	Purpose: Vendor constructor
*/
Vendor::Vendor()
{
	name = "";
	price = 0;
}

//Michael K
/*
	Input: Empty vendor
	Output: Vendor items with details
	Purpose: adds the details inputted by the admin to the empty vendor item
*/
Vendor::Vendor(string name, double price)
{
	this->name = name;
	this->price = price;
}

//Michael K
/*
	Input: Vendor object
	Output: Item object
	Purpose: Adds the item-specific details to a vendor object
*/
Item::Item() : Vendor()
{
	itemCategory = 0;
	amount = 0;
}

//Michael K
/*
	Input: Empty item
	Output: Item with category
	Purpose: allocates the item object to the correct aisle
*/
Item::Item(int itemCatagory, string name, double price) : Vendor(name, price)
{
	this->itemCategory = itemCatagory;
	amount = 0;
}

//Michael K
/*
	Input: Empty item
	Output: Item object
	Purpose: Gives the item specific details the correct details inputted by the admin
*/
Item::Item(int itemCatagory, int amount, string name, double price) : Vendor(name, price)
{
	this->itemCategory = itemCatagory;
	this->amount = amount;
}

//Michael K
/*
	Input: none
	Output: Service object
	Purpose: Service constructor
*/
Service::Service()
{
	category = 0;
	phoneNumber = 1111111111;
}

//Michael K
/*
	Input: Service object
	Output: Service object with Vendor variables
	Purpose: gives vendor variables to a service object
*/
Service::Service(string name, double price) : Vendor(name, price)
{
	category = 0;
	phoneNumber = 1111111111;
}

//Michael K
/*
	Input: Service object
	Output: Updated service object
	Purpose: adds an inputted phone number to a service object
*/
Service::Service(string name, double price, double phoneNumber) : Vendor(name, price)
{
	category = 0;
	this->phoneNumber = phoneNumber;
}

//Michael K
/*
	Input: Service object
	Output: price for service
	Purpose: calculates the price with tax for the service
*/
double Service::totalAmount()
{
	double taxAmount = price * CATEGORY_TAX[category];
	return price + taxAmount;
}

//Michael K
/*
	Input: Service object
	Output: string name in inventory.dat
	Purpose: Gives a name to the service object
*/
string Service::fileFormat()
{
	return string();
}

//Michael K
/*
	Input: service object
	Output: description on screen
	Purpose: prints the name and price of the service to the screen
*/
void Service::getDescription()
{
	cout << left << "Service Name: " << setw(FIELD_WIDTH) << right << name << " | ";
	cout << left << "Price: $" << setw(FIELD_WIDTH) << right << fixed << setprecision(2) << price << " | ";
}

//Michael K
/*
	Input: Service object
	Output: category integer
	Purpose: Gets the category integer by the Service class
*/
int Service::getCategory()
{
	return category;
}
