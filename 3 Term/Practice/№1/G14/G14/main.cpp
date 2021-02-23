#include "Figure.h"
#include "Man.h"
#include "Pen.h"
#include <iostream>

void fastPrint(int inputs, Figure& f)
{
	std::cout << "\x1b[14D";
	for (int i = 0; i < (inputs + 10); i++)
		std::cout << "\x1b[A";
	f.printBoard();
	for (int i = 0; i < inputs; i++)
		std::cout << "\n\r";
}
int main(int argc, char* argv[])
{
	//Initialization start position
	char* pos = (char*)"a1";
	char* endPos = (char*)"h8";
	//Init Game
	Figure f(pos);
	f.printBoard();
	//Player* p = new Player(std::string("First"));
	Gambler* players[] = {
		new Man(f, "First"),
		new Pen(f, "Second")
	};
	//Start Game
	int i = 0;
	int inputs = 0;
	while (f != endPos)
	{
		players[i%2]->query();
		if (!players[i%2]->move())
		{
			std::cout << "Invalid input. Terminate.\n";
			return 0;
		}
		inputs++;
		fastPrint(inputs,f);
		i++;

	}
	std::cout << std::endl << players[(i+1) % 2]->getName()<<" Wins"<<std::endl;
	
	delete players[0];
	delete players[1];
	return 0;
}