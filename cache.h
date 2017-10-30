#ifndef __CACHE_H__
#define __CACHE_H__
#include <map>
#include <string>
#include "token.h"
#include "variable.h"
using namespace std;

class Cache
{
protected:
	map<string,Variable> variablemap;

public:
	void SetToken(Token& token);
};

#endif//__CACHE_H__
