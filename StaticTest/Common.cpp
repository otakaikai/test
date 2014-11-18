#include "Common.h"
#include <stdlib.h>
#include <time.h>

int Common::randNumbers( int lower/* =0 */, int upper/* =0 */ )
{
	if( lower >= upper )
	{
		return 0;
	}
	
	int balance = upper - lower + 1;

	//srand( time( 0 ) );
	int randNum = rand();
	balance = randNum % balance;

	return lower + balance;
}