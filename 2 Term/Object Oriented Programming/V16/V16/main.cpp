#include <stdlib.h>
#include <iostream>
#include "Man.h"
#include "Pen.h"
#include "Heap.h"


int main(int argc, char* argv[])
{

	//Checking input
	if (argc != 3 || atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 || atoi(argv[1]) <= atoi(argv[2]))
	{
		std::cout << "Invalid start position. Terminate.\n";
		return 0;
	}

	//init game
	Heap heap(atoi(argv[1]));
	Gambler* players[] = {
		new Man(heap,atoi(argv[2]),"Man"),
		new Pen(heap,atoi(argv[2]),"Pen")
	};

	//Start output
	std::cout << "Start position: " << heap.get() << std::endl;
	std::cout << "Limit for move:" << atoi(argv[2]) << std::endl;

	//Start game
	int i = 0;
	while (heap.get() != 0)
	{
		players[i]->query();
		if (!players[i]->move())
		{
			std::cout << "Invalid input. Terminate.\n";
			return 0;
		}
		if (++i > 1)
			i = 0;
	}
	std::cout << "Winner!";
	//Clearing memory
	delete players[0];
	delete players[1];
	return 0;
}