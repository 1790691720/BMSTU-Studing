#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>	
class Point
{
private:
	int _x;
	int _y;
public:
	Point(int x, int y) : _x(x), _y(y) {  }
	int GetX() { return _x; }
	int GetY() { return _y; }
};
double frac(Point* a)
{
	return (double)(a->GetX()) / (double)(a->GetY());
}
int compare(const void* a, const void* b)
{
	Point** f = (Point**)a;
	Point** s = (Point**)b;
	double temp = frac(*f) - frac(*s);
	if (temp > 0)
		return 1;
	if (temp < 0)
		return -1;
	return 0;
}


int main(int argc, char* argv[])
{
	if (argc < 2)
		return 1;
	Point** p;
	p = new Point * [argc - 1];
	for (int i = 1; i < argc; i++)
	{
		int x, y;
		sscanf(argv[i], "(%d%*c%d)", &x, &y);
		p[i - 1] = new Point(x, y);
	}
	qsort(p, argc - 1, sizeof(Point*), compare);
	double min = frac(p[1]) - frac(p[0]);
	int m1 = 0;
	int m2 = 1;
	for (int i = 0; i < (argc - 2); i++)
	{
		double temp = frac(p[i + 1]) - frac(p[i]);
		if (temp < min)
		{
			min = temp;
			m1 = i;
			m2 = i + 1;
		}
	}
	printf("Min Differ X/Y between: \n (%d;%d) and (%d;%d)\n\n", p[m1]->GetX(), p[m1]->GetY(), p[m2]->GetX(), p[m2]->GetY());
	for (int i = 0; i < (argc - 1); i++)
		delete p[i];
	delete[] p;
	return 0;
}