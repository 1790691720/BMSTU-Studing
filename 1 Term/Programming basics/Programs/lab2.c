#include <stdio.h>
#include <time.h>
//Start=00:00:00
int main()
{
	int Sec_From_Start, Hours, Minutes, Seconds;
	int GMT=+3;
	Sec_From_Start = time(NULL)%(60*60*24);
	Seconds=Sec_From_Start%60;
	Minutes=Sec_From_Start%3600/60;
	Hours=(Sec_From_Start/3600+GMT)%24;
	printf("%d:%2d:%2d\n", Hours, Minutes, Seconds);
	return 0;
}
