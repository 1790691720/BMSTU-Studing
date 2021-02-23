#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    char ch;
    for(int i=1; i<argc; i++)
    {
        std::ifstream infile(argv[i]);
        if(!infile)
        {
        	std::cerr<<"Can not read file. Terminate\n";
            return -1;
        }
        
        while(infile)
        {
            infile.read(&ch, 1);
            putchar(ch);
        }
        infile.close();
    }
    return 0;
}