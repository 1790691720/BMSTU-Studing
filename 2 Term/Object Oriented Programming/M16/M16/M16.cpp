#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
class Magic
{
private:
	unsigned int** _table;
	int _degree;
	int  reflect(int n);
public:
	Magic(int);
	~Magic();
	void print();
	void fill();
};
Magic::Magic(int n)
{
	_degree = n;
	_table = new unsigned int* [_degree];
	for (int i = 0; i < _degree; i++)
		_table[i] = new unsigned int[_degree];
	for (int i = 0; i < _degree; i++)
		for (int j = 0; j < _degree; j++)
			_table[i][j]=0;
}
Magic::~Magic()
{
	for (int i = 0; i < _degree; i++)
		delete[] _table[i];
	delete[] _table;
}
void Magic::print()
{
	int degree2 = _degree*_degree;
	int len = 0;
	while (degree2 > 0)
	{
		len++;
		degree2 /= 10;
	}

	for (int i = 0; i < _degree; i++, cout << endl)
		for (int j = 0; j < _degree; j++)
			printf("%*d ",len,_table[i][j]);
	cout << endl;
}
void Magic::fill()
{
	int curr = 1;
	int degree2 = _degree * _degree;
	int i, j;
	int col = _degree-1;
	int row = 1;
	_table[row][col] = curr;
	while (curr < degree2)
	{
		i = reflect(row + 2);
		j = reflect(col - 2);
		if (_table[i][j] != 0)
		{
			i = reflect(row +3);
			j = reflect(col -1);
		}
		row = i;
		col = j;
		_table[row][col] = ++curr;
		cout << "Iteration " << curr << ":\n";
		print();
	}
	
}
int Magic::reflect(int n)
{
	if (n < 0)
		return (n + _degree);
	if (n > (_degree - 1))
		return (n - _degree);
	return n;
}
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid count argument.\n";
		exit(1);
	}

	int degree = atoi(argv[1]);
	cout << "Usage degree of magic square: " << degree << ".\n";

	Magic result(degree);
	result.fill();
	cout << "Final result.\n";
	result.print();


	return 0;
}
