#ifndef __STATEMENT_H__
#define __STATEMENT_H__
#include <list>
#include "context.h"
#include "expression.h"
using namespace std;


class Expression;
class Statement
{
protected:
	int expression_count;
	list<Expression> statement;
	typedef list<Expression>::iterator Iterator;
public:
	Statement(void):expression_count(0){}
public:
	void SetContext(Context& context);
	void AddExpression(Expression& expression);
	void Execute(void);
public:
	Statement& operator=(Statement&);
};

#endif//__STATEMENT_H__
