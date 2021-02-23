#include <iostream>
#include <cctype>
using namespace std;
class Alpha
{
private:
	unsigned int bin;
public:
	Alpha();
	Alpha(char*);
	Alpha operator+(Alpha&);
	Alpha operator~();
	friend ostream& operator << (ostream&, Alpha&);
};

Alpha::Alpha()
{
	bin = 0;
}
Alpha::Alpha(char* str)
{
	bin = 0;
	while (*str != '\0')
	{
		if (((*str >= 'A') && (*str <= 'Z')) || ((*str >= 'a') && (*str <= 'z')))
			bin = bin | (1 << (tolower(*str) - 'a'));
		str++;
	}
}
Alpha Alpha::operator+(Alpha& other)
{
	Alpha result;
	result.bin = this->bin | other.bin;
	return result;
}
Alpha Alpha::operator~()
{
	Alpha result;
	result.bin = ~(this->bin);
	return result;
}
ostream& operator << (ostream& out, Alpha& result)
{
	unsigned  bit = 33554432;
	int i;
	for (i = 25; i >= 0; i--)
	{
		if ((result.bin & bit) > 0)
			out << (char)('a' + i);
		bit = bit >> 1;
	}
	return out;
}
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Not count arguments.\n";
		return -1;
	}
	Alpha first(argv[1]);
	Alpha second(argv[2]);
	Alpha summa = first + second;
	Alpha  result = ~summa;
	cout << result << endl;
	return 0;
}
