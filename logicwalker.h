#ifndef __LOGICWALKER_H__
#define __LOGICWALKER_H__
#include <map>
#include <list>
#include "token.h"
#include "context.h"
using namespace std;

typedef list<class Token> TokenList;
typedef map<signed,TokenList> TokenLmap;

class LogicWalker
{
protected:
	static TokenLmap tokenlmap;
	static TokenList tokenlist;
public:
	typedef TokenLmap::iterator MapIterator;
	typedef TokenList::iterator ListIterator;
public:
	static void AddToken(const Token& node);
	static void AddList(void);
	static void ShowList(void);
	static void Execute(void);
};
#define NODE(x,y) LogicWalker::AddToken(Token(x,y))

#endif//__LOGICWALKER_H__
