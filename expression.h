#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
#include <list>
#include <string>
#include "token.h"
#include "context.h"
using namespace std;

class Expression 
{
protected:
	Token token;
	Context *context;
	Expression *lchild;
	Expression *rchild;
public:
	~Expression(void);
	Expression(void):lchild(0),rchild(0),context(0){}
	Expression(const Expression& t):lchild(0),rchild(0),context(0){*this = t;}
public:
	signed GetType(void);
	const string& GetName(void);
	void SetContext(Context& c);
public:
	void CreateTree(list<Token>& l);
	void CreateLeft(list<Token>& l);
	void CreateRight(list<Token>& l);
	void PreorderTraversal(void);
	void InorderTraversal(void);
	void PostorderTraversal(void);
public:
	Expression& operator=(const Expression& t);
public:
	double Execute(void);
	double Execute_IF(void);
	double Execute_THEN(void);
	double Execute_ELSE(void);
	double Execute_AND(void);
	double Execute_OR(void);
	double Execute_NOT(void);
	double Execute_EQ(void);
	double Execute_NE(void);
	double Execute_GE(void);
	double Execute_LE(void);
	double Execute_GT(void);
	double Execute_LT(void);
	double Execute_ADD(void);
	double Execute_MIN(void);
	double Execute_MUL(void);
	double Execute_DIV(void);
	double Execute_MOD(void);
	double Execute_LC(void);
	double Execute_LCO(void);
	double Execute_LCF(void);
	double Execute_ID(void);
	double Execute_IDR(void);
	double Execute_IDO(void);
	double Execute_IDF(void);
	double Execute_IDV(void);
	double Execute_NUM(void);
	double Execute_HEX(void);
	double Execute_TIME(void);
	double Execute_DATE(void);
	double Execute_DATETIME(void);
	double Execute_SET(void);
	double Execute_GOTO(void);
	double Execute_LABEL(void);
};

#endif//__EXPRESSION_H__
