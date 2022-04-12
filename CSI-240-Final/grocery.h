#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

//Global Constants
const string INVENTORY_FILE_NAME = "inventory.dat";
const string ADMIN_USER = "admin";
//Global Functions
char login();
void startMenu();
void adminMenu();
void customerMenu();

class Exceptions
{
public:
	Exceptions(string message = "")
	{
		this->message = message;
	}
private:
	string message;
};

class Item
{
public:

	Item(string name, double price) 
	{
		this->name = name;
		this->price = price;
	}

	void getDisciption();

private:
	string name;
	double amount;
	double price;
};

class Inventory
{
public:
	Inventory();

	~Inventory();

	void addToInventory();
	void deleteItemFromInventory();
	void displayInventory();

	void importInventory();
	void exportInventory();
private:
	vector<Item> inventoryList;
};

class Cart
{
public:
	Cart();

	~Cart();

	void addToCart();
	void displayCart();
	void calculateTotalPrice();
private:
	vector<Item> cart;
};


class Meats : public Item 
{
public:

private:
};

class Vegetables : public Item
{
public:

private:
};

class Fruits : public Item
{
public:

private:
};

class BakedGoods : public Item
{
public:

private:
};

class Snacks : public Item
{
public:

private:
};

class Drinks : public Item
{
public:

private:
};