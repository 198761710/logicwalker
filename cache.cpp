#include "token.h"
#include "cache.h"
#include "variable.h"

Cache CacheVariable;

void Cache::SetToken(Token& token)
{
	token.SetVariable( variablemap[token.name] );
}
