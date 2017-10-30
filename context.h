#ifndef __CONTEXT_H__
#define __CONTEXT_H__
#include <map>
#include <string>
#include "cache.h"
#include "statement.h"
using namespace std;

class Context
{
protected:
	int statement_count;
	Cache LocalVariable;
	map<string,int> labelmap;
	map<int,class Statement> context;
	map<int,class Statement>::iterator index;
	typedef map<int,class Statement>::iterator Iterator;
public:
	Context(void):LocalVariable("LocalVariable"),statement_count(0){}
public:
	class Cache& GetLocalVariable(void);
	void AddStatement(class Statement& statement);
	void AddLabel(const string& label);
	void GotoLabel(const string& label);
	void Execute(void);
};
#endif//__CONTEXT_H__
