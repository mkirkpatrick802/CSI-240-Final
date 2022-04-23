#include "grocery.h"

// Mikey M
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

