#ifndef __hw02_h__
#define __hw02_c__
#include<stdio.h>

int getpower(int a,int radix)
{
	int r;
	r = 1;
	while(a > 0)
	{
		r = r * radix;
		a--;
	}
	return r;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getbit(long num,int radix)
{
	int c = 0;
	while((num /= radix) > 0)
	{
		c++;
	}
		return c;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_integer(int n,int radix,char* prefix)
{
	long num;
	int a;
	char nc;
	int s = 0;

	num = n;

 if(num < 0)
 {
 	num = 0 - num;
 	fputc('-',stdout);
 }

while(prefix[s] != '\0')
{
	fputc(prefix[s],stdout);
	s += 1;
}

	a = getbit(num,radix);

	while(a >= 0)
	{
	if((num / getpower(a,radix)) < 0)
 	{
 		fputc('0',stdout);
		a = a - 1;
	}
	else
	{
	if(num / getpower(a,radix) >= 10)
	{
		fputc('a' + num / getpower(a,radix) - 10, stdout);
		num %= getpower(a,radix);
		a = a - 1;
	}
	else
	{
	 	nc = num / getpower(a,radix) + '0';
	 	fputc(nc,stdout);
	 	num %= getpower(a,radix);
	 	a = a - 1;
	 }
	 }
	 }
	 }

#endif
