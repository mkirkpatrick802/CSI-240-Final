#include "grocery.h"
// Mikey M
/*
	Input: an Exception object
	Output: none
	Purpose: run the startMenu, and throw an exception if an error ocurrs
*/
int main()
{
	try
	{
		startMenu();
	}
	catch (Exceptions e)
	{
		cout << e.getMessage() << endl;
	}
}

