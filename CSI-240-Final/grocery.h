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
	SERVICE = 0,
	MEAT,
	VEGETABLE,
	FRUIT,
	BAKED_GOOD,
	SNACKS,
	DRINK
};
const string CATEGORY_NAMES[] = { "Service", "Meat", "Vegetable", "Fruit", "Baked Good", "Snack", "Drink" };
const double CATEGORY_TAX[] = {.5, 0.2, 0.05, 0.15, 0.5, 0.5, 0.3};

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


class Vendor
{
public:
	Vendor();
	Vendor(string name, double price);

	string getName();
	double getPrice();

	virtual int totalAmount() = 0;
	virtual string fileFormat() = 0;
	virtual void getDescription() = 0;
	virtual int getCategory() = 0;
protected:
	string name;
	double price;
};


class Item : public Vendor
{
public:
	Item();
	Item(int itemCatagory, string name, double price);
	Item(int itemCatagory, int amount, string name, double price);

	void getDescription() override;
	int totalAmount() override;
	string fileFormat() override;
	int getCategory() override;

	int getItemCategory();
	int getAmount();

	//double operator*(const Item& left);

private:
	int itemCategory;
	int amount;
};


class Service : public Vendor
{
public:
	Service();
	Service(string name, double price);
	Service(string name, double price, double phoneNumber);

	int totalAmount() override;
	string fileFormat() override;
	void getDescription() override;
	int getCategory() override;

private:
	double phoneNumber;
	int category;
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
	vector<Vendor*> inventoryList;
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
	vector<Vendor*> cart;
};