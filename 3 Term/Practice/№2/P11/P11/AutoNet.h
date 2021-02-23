#pragma once
#ifndef AUTONETH

#define AUTONETH



#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
class AutoNet
{

private:
	std::vector <std::vector<std::string>> _adjacencyMatrix;
	std::vector <std::vector<std::string>> _pathwayMatrix;
	std::vector<std::string> _nodes;
	void calcPathwayMatrix(int);
	void calcAdjacencyMatrix(std::vector<std::vector <std::string>>);
public:
	AutoNet(std::string);
	void printAdjacencyMatrix();
	void findPath(std::string, std::string);
	void findPath(std::string, std::string,int);
	void printNodes();
};

#endif // AUTONETH