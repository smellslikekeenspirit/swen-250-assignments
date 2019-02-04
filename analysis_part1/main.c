// main program for the Document Analysis Project

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unit_tests.h"

extern char *malloc_options ;		// Keep this line. Do not change it.

// Run the unit tests or as a "normal program".
// You can run this as a "normal program" if you want for a simple test of the sort_two_positions function.
int main( int argc, char *argv[] )
{
	malloc_options = "CFGSU" ;		// Keep this line. Do not change it. Provides memory misuse protections.
	
	test() ;
	
	return 0 ;
}
