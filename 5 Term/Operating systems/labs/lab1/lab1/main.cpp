#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

const int code[32] = { 30,  0,  1, 22,  4,  5, 20, 3, 21,  8, 9, 10, 11, 12, 13, 14, 15, 31, 16, 17, 18, 19,  6, 2, 28, 27, 7, 24, 29, 25, 23, 26 };
int main()
{

    for (int i = 0; i < 32; i++)
    {
        int x = code[i];
        char ch;
        string s1 = "";
        int t = 0;
        while (x >= 1)
        {
            t = x % 8;
            x = (x - t) / 8;
            s1 += _itoa(t, &ch, 10);

        }
        reverse(s1.begin(), s1.end());
        cout << s1 << endl;
    }
    return 0;
}