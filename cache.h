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
	string cachename;
	map<string,Variable> variablemap;
	typedef map<string,Variable>::iterator Iterator;
public:
	Cache(const string& name):cachename(name){}

public:
	void SetToken(Token& token);
	void Show(void);
};

#endif//__CACHE_H__
