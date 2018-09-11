#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"
int getpower(int a,int radix)
{
	int r;
	r = 1;
	while(a > 0)
	{
		r=r*radix;
		a--;
	}
	return r;
}

int getbit(long num,int radix)
{
	int c = 0;
	while((num /= radix) > 0)
	{
		c++;
	}
	return c;
}

void print_integer(int n, int radix, char* prefix)
{
	long num = n;
	int a;
	char nc;
	int s = 0;

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
		if((num/getpower(a,radix)) < 0)
		{
			fputc('0',stdout);
			a = a - 1;
		}
		else
		{
			if(num/getpower(a,radix) >= 10)
			{
				fputc('a' + num / getpower(a,radix) - 10, stdout);
				num %= getpower(a,radix);
				a = a - 1;
			}
			else
			{
				nc = num/getpower(a,radix) + '0';
				fputc(nc,stdout);
				num %= getpower(a,radix);
				a = a - 1;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printch(const char ch)
{
	fputc(ch,stdout);
}

void printstr(const char *ptr)
{
	while(*ptr)
	{
		fputc(*ptr,stdout);
		ptr++;
	}
}

void printcash(double flt)
{
	int tmpint = (int)flt;
	int tmpint2 = 0;
	if(flt >= 0)
	{
		tmpint2 = (int)((flt-tmpint)*100);
	}
	else
	{
		tmpint2 = (int)((tmpint-flt)*100);
	}

    print_integer(tmpint,10,"$");
	fputc('.',stdout);
	if(tmpint2 < 10)
	{
		fputc('0',stdout);
	}
	print_integer(tmpint2,10,"");
}

void mintf(const char *format,...)
{
	va_list ap;
	va_start(ap,format);
	while(*format)
	{
		if(*format != '%')
		{
			fputc(*format,stdout);
			format++;
		}
		else
		{
			format++;
			switch(*format)
			{
				case 'c':
				{
					char valch = va_arg(ap,int);
					fputc(valch,stdout);
					format++;
					break;
				}
				case 'd':
				{
					int valint = va_arg(ap,int);
					print_integer(valint,10,"");
					format++;
					break;
				}
				case 's':
				{
					char *valstr = va_arg(ap,char *);
					printstr(valstr);
					format++;
					break;
				}
				case 'x':
				{
					int valint = va_arg(ap,int);
					print_integer(valint,16,"0x");
					format++;
					break;
				}
				case 'b':
				{
					int valint = va_arg(ap,int);
					print_integer(valint,2,"0b");
					format++;
					break;
				}
				case '%':
				{
					fputc('%',stdout);
					format++;
					break;
				}
				case '$':
				{
					double valdou = va_arg(ap,double);
					printcash(valdou);
					format++;
					break;
				}
				case '\0':
				{
					fputc('%',stdout);
					format++;
					break;
				}
				
				default:
				{
					fputc('%',stdout);
					printch(*format);
					format++;
				}
			}
		}
	}
	va_end(ap);
}

