#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

//Global Constants
const string INVENTORY_FILE = "inventory.dat";
const string LOGIN_FILE = "login.dat";
const string ADMIN_USER = "admin";
const string CUSTOMER_USER = "customer";
const enum category
{
	NULL_CATAGORY = 0,
	MEAT,
	VEGETABLE,
	FRUIT,
	BAKED_GOOD,
	SNACKS,
	DRINK
};
const string CATEGORY_NAMES[] = { "Null", "Meat", "Vegetable", "Fruit", "Baked Good", "Snack", "Drink" };

//Global Functions
char login();
void startMenu();
void adminMenu();
void customerMenu();

class Exceptions
{
public:
	Exceptions(string message = "");
	string getMessage();
private:
	string message;
};

class Stock
{
public:
	virtual int totalAmount() = 0;
protected:
	int itemCategory;
	string name;
	double price;
	double amount;
};

class Item : public Stock
{
public:
	Item(int itemCatagory, string name, double price);
	void getDescription();
	int totalAmount();
	string fileFormat();
	string getName();
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
	vector<Item*> inventoryList;
};

class Cart
{
public:
	Cart();

	~Cart();

	void addToCart();
	void removeFromCart();
	void displayCart();
	void calculateTotalPrice();
private:
	vector<Item> cart;
};


class Meats : public Item
{
public:
	int totalAmount()
	{

	}
private:
	float tax;
};

class Vegetables : public Item
{
public:
private:
	float tax;
};

class Fruits : public Item
{
public:
private:
	float tax;
};

class BakedGoods : public Item
{
public:
private:
	float tax;
};

class Snacks : public Item
{
public:
private:
	float tax;
	float sugarTax;
};

class Drinks : public Item
{
public:
private:
	float tax;
};