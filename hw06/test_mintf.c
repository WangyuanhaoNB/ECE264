#include<stdio.h>  
#include<stdlib.h>  
#include<limits.h>  
#include<stdarg.h>
#include<limits.h>
#include "mintf.h"


int main(int argc, char* argv[])
{
mintf("52189757\n");
mintf("This song %s %d is so nice !\n","Number",89757);
mintf("%d could be written in hex as %x.\n",-89757,-89757);
mintf("And it also could be written in binary as %b.\n",89757,89757);
mintf("I'm 100%% sure that everyone will be 100%%%% love it\n");
mintf("Yo, number %d\n",89757,89757);
mintf("Give me money %$\n",-89.89238923892389238923892389238923892349);
mintf("%%%d\n",97);
mintf("%c\n",97);
mintf("%d\n",86,86,86);

EXIT_SUCCESS;
}
