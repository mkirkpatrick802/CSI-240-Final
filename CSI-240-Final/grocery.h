#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

//Global Functions
char login();
void startMenu();
void adminMenu();
void customerMenu();

class Inventory
{
public:
	Inventory();

	~Inventory();

	void addToInventory() 
	{

	}

	void displayInventory() 
	{

	}
private:
	static vector<Item> inventory;
};

class Cart
{
public:
	Cart()
	{

	}

	~Cart()
	{

	}


	void addToCart()
	{

	}

	void displayCart() 
	{

	}
private:
	static vector<Item> cart;
};

class Item
{
public:

private:
	string name;
	int amount;
	double price;
};

//Meats class
//Vegetables class
//Fruits class
//Baked Goods class
//Snacks class
//Drinks class