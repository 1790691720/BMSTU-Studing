#include <stdio.h>

int main()
{
	int year, month, day, result=0;
	int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	scanf("%d", &year);
	scanf("%d", &month);
	scanf("%d", &day);
	if( (year%4==0 && year%100!=0) || year%400==0) months[1]++;
	for(int i=0; i<month-1;i++) result=result+months[i];
	result=result+day;
	printf("%d\n",result);

	return 0;
}
