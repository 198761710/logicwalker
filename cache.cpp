#include <stdio.h>
#include "token.h"
#include "cache.h"
#include "variable.h"

Cache GlobalVariable("GlobalVariable");

void Cache::SetToken(Token& token)
{
	token.SetVariable( variablemap[token.name] );
}
void Cache::Show(void)
{
	printf("_______________________________________________________________\n");
	printf("|*********************** %14s **********************|\n", cachename.data());
	printf("|-------------------------------------------------------------|\n");
	printf("|     name     |      value      | runtime | ontime | offtime |\n");
	printf("|-------------------------------------------------------------|\n");
	for(Iterator i = variablemap.begin(); i != variablemap.end(); i++)
	{
		printf("| %-12s | ", i->first.data());
		printf(" %-14.1f |", i->second.GetValue());
		printf(" %-7d |", (int)i->second.Runtime());
		printf(" %-7d |", (int)i->second.OnTime());
		printf(" %-6d |\n", (int)i->second.OffTime());
	}
}
