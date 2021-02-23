#include "Don.h"
#include "Camel.h"
#include "Alfil.h"
#include <iostream>
int main(int argc, char* argv[])
{
	//Initialization start position
	const char* pos = "a1";
	if (argc < 2) {
		std::cout << "Incorrect count arguments. Using default: " << pos << std::endl;
	}
	else
	{
		if (Figure::deskout(argv[1]))
		{
			std::cout << "Incorrect position: " << argv[1];
			std::cout << " Using default: " << pos << std::endl;
		}
		else
			pos = argv[1];
	}
	//Init figure
	Don f(pos);
	int inputs = 0;//for nice output
	do
	{
		//from this for nice output
		if (inputs != 0)
		{
			for (int i = 0; i < (inputs + 10); i++)
				std::cout << "\x1b[A";
			f.printBoard();
			for (int i = 0; i < inputs; i++)
				std::cout << "\n\r";
		}
		else//to this for nice output
			f.printBoard();
		std::cout << f << "-" << f.isA();
		inputs++;
	} while (std::cin >> f); //input new position

	return 0;
}