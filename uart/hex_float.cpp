#include "stdio.h"
int main(void)
{
	//lum:157.50  temp:23.69  hum:47.15
	float fa = 157.50;
	char farray[4] = {0};
	*(float*)farray = fa;
	printf("%f\n",*(float*)farray);//157.500000
	return 0;
 } 
