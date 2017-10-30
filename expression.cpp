#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "token.h"
#include "context.h"
#include "expression.h"


Expression::~Expression(void)
{
	if( lchild )
	{
		delete lchild;
		lchild = NULL;
	}
	if( rchild )
	{
		delete rchild;
		rchild = NULL;
	}
	context = NULL;
}
signed Expression::GetType(void)
{
	return token.type;
}
const string& Expression::GetName(void)
{
	return token.name;
}
void Expression::SetContext(Context& c)
{
	context = &c;
	token.SetContext(c);
	if( lchild )
	{
		lchild->SetContext(c);
	}
	if( rchild )
	{
		rchild->SetContext(c);
	}
}
void Expression::CreateLeft(list<Token>& line)
{
	if( lchild )
	{
		delete lchild;
	}
	lchild = new Expression;
	if( lchild )
	{
		lchild->context = context;
		lchild->CreateTree(line);
	}
}
void Expression::CreateRight(list<Token>& line)
{
	if( rchild )
	{
		delete rchild;
	}
	rchild = new Expression;
	if( rchild )
	{
		rchild->context = context;
		rchild->CreateTree(line);
	}
}
void Expression::CreateTree(list<Token>& line)
{
	if( line.begin() == line.end() )
	{
		return;
	}
	Token& node = line.back();
	switch(node.type)
	{
		case ID:
		case LC:
		case LCO:
		case LCF:
		case IDR:
		case IDO:
		case IDF:
		case IDV:
		case NUM:
		case HEX:
		case DATE:
		case TIME:
		case DATETIME:
			token = node;
			line.pop_back();
			break;
		case IF:
			token = node;
			line.pop_back();
			CreateLeft(line);
			break;
		case THEN:
		case ELSE:
			token = node;
			line.pop_back();
			CreateRight(line);
			break;
		case NOT:
			token = node;
			line.pop_back();
			CreateLeft(line);
			break;
		case AND:
		case OR:
		case EQ:
		case NE:
		case GE:
		case LE:
		case GT:
		case LT:
		case ADD:
		case MIN:
		case MUL:
		case DIV:
		case MOD:
			token = node;
			line.pop_back();
			CreateRight(line);
			CreateLeft(line);
			break;
		case LP:
		case RP:
		case LB:
		case RB:
		case CM:
			break;
		case SET:
			token = node;
			line.pop_back();
			CreateLeft(line);
			CreateRight(line);
			break;
		case GOTO:
			token = node;
			line.pop_back();
			CreateRight(line);
			break;
		case LABEL:
			token = node;
			line.pop_back();
			break;
	}
}
void Expression::PreorderTraversal(void)
{
	//printf("%s\n", token.name.data());
	if( lchild )
	{
		lchild->PreorderTraversal();
	}
	if( rchild )
	{
		rchild->PreorderTraversal();
	}
}
void Expression::InorderTraversal(void)
{
	if( token.type == IF )
	{
		//printf("%s\n", token.name.data());
	}
	if( lchild )
	{
		lchild->InorderTraversal();
	}
	if( token.type != IF )
	{
		//printf("%s\n", token.name.data());
	}
	if( rchild )
	{
		rchild->InorderTraversal();
	}
}
void Expression::PostorderTraversal(void)
{
	if( token.type == IF )
	{
		//printf("%s\n", token.name.data());
	}
	if( lchild )
	{
		lchild->PostorderTraversal();
	}
	if( rchild )
	{
		rchild->PostorderTraversal();
	}
	if( token.type != IF )
	{
		//printf("%s\n", token.name.data());
	}
}
Expression& Expression::operator=(const Expression& t)
{
	token = t.token;
	context = t.context;
	if( t.lchild )
	{
		if( lchild )
		{
			delete lchild;
			lchild = NULL;
		}
		if( lchild = new Expression )
		{
			*lchild = *t.lchild;
		}
	}
	if( t.rchild )
	{
		if( rchild )
		{
			delete rchild;
			rchild = NULL;
		}
		if( rchild = new Expression )
		{
			*rchild = *t.rchild;
		}
	}
	return *this;
}
double Expression::Execute(void)
{
	switch( token.type )
	{
		case IF:
			return Execute_IF();
		case THEN:
			return Execute_THEN();
		case ELSE:
			return Execute_ELSE();
		case AND:
			return Execute_AND();
		case OR:
			return Execute_OR();
		case NOT:
			return Execute_NOT();
		case EQ:
			return Execute_EQ();
		case NE:
			return Execute_NE();
		case GE:
			return Execute_GE();
		case LE:
			return Execute_LE();
		case GT:
			return Execute_GT();
		case LT:
			return Execute_LT();
		case ADD:
			return Execute_ADD();
		case MIN:
			return Execute_MIN();
		case MUL:
			return Execute_MUL();
		case DIV:
			return Execute_DIV();
		case MOD:
			return Execute_MOD();
		case LC:
			return Execute_LC();
		case LCO:
			return Execute_LCO();
		case LCF:
			return Execute_LCF();
		case ID:
			return Execute_ID();
		case IDR:
			return Execute_IDR();
		case IDO:
			return Execute_IDO();
		case IDF:
			return Execute_IDF();
		case IDV:
			return Execute_IDV();
		case NUM:
			return Execute_NUM();
		case HEX:
			return Execute_HEX();
		case TIME:
			return Execute_TIME();
		case DATE:
			return Execute_DATE();
		case DATETIME:
			return Execute_DATETIME();
		case SET:
			return Execute_SET();
		case GOTO:
			return Execute_GOTO();
		case LABEL:
			return Execute_LABEL();
	}
	//printf("%s(%s,%d)\n", __func__, token.name.data(), token.type);
	return 0.0;
}
double Expression::Execute_IF(void)
{
	//printf("%s ", token.name.data());
	if( lchild )
	{
		return lchild->Execute();
	}
	if( rchild )
	{
		return rchild->Execute();
	}
	return 0.0;
}
double Expression::Execute_THEN(void)
{
	//printf("%s ", token.name.data());
	if( lchild )
	{
		return lchild->Execute();
	}
	if( rchild )
	{
		return rchild->Execute();
	}
	return 0.0;
}
double Expression::Execute_ELSE(void)
{
	//printf("%s ", token.name.data());
	if( lchild )
	{
		return lchild->Execute();
	}
	if( rchild )
	{
		return rchild->Execute();
	}
	return 0.0;
}
double Expression::Execute_AND(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return (fabs(lchild->Execute()) > 0.9999) && (fabs(rchild->Execute()) > 0.9999);
	}
	return 0.0;
}
double Expression::Execute_OR(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return (fabs(lchild->Execute()) > 0.9999) || (fabs(rchild->Execute()) > 0.9999);
	}
	return 0.0;
}
double Expression::Execute_NOT(void)
{
	//printf("%s ", token.name.data());
	if( lchild )
	{
		return !(fabs(lchild->Execute()) > 0.9999);
	}
	if( rchild )
	{
		return !(fabs(rchild->Execute()) > 0.9999);
	}
	return 0.0;
}
double Expression::Execute_EQ(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return fabs(lchild->Execute() - rchild->Execute()) < 0.0001;
	}
	return 0.0;
}
double Expression::Execute_NE(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return fabs(lchild->Execute() - rchild->Execute()) > 0.0001;
	}
	return 0.0;
}
double Expression::Execute_GE(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return ( lchild->Execute() >= rchild->Execute() );
	}
	return 0.0;
}
double Expression::Execute_LE(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return (lchild->Execute() <= rchild->Execute());
	}
	return 0.0;
}
double Expression::Execute_GT(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return lchild->Execute() > rchild->Execute();
	}
	return 0.0;
}
double Expression::Execute_LT(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return lchild->Execute() < rchild->Execute();
	}
	return 0.0;
}
double Expression::Execute_ADD(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return lchild->Execute() + rchild->Execute();
	}
	return 0.0;
}
double Expression::Execute_MIN(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return lchild->Execute() - rchild->Execute();
	}
	return 0.0;
}
double Expression::Execute_MUL(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		return lchild->Execute() * rchild->Execute();
	}
	return 0.0;
}
double Expression::Execute_DIV(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		double r = rchild->Execute();
		if( r == 0.0 )
		{
			//return 0.0;
		}
		return lchild->Execute() / r;
	}
	return 0.0;
}
double Expression::Execute_MOD(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		double r = rchild->Execute();
		if( r == 0.0 )
		{
			//return 0.0;
		}
		return fmod(lchild->Execute(), r);
	}
	return 0.0;
}
double Expression::Execute_LC(void)
{
	//printf("%s ", token.name.data());
	return token.GetValue();
}
double Expression::Execute_LCO(void)
{
	//printf("%s ", token.name.data());
	return token.OnTime();
}
double Expression::Execute_LCF(void)
{
	//printf("%s ", token.name.data());
	return token.OffTime();
}
double Expression::Execute_ID(void)
{
	//printf("%s ", token.name.data());
	return token.GetValue();
}
double Expression::Execute_IDR(void)
{
	//printf("%s ", token.name.data());
	return token.GetRuntime();
}
double Expression::Execute_IDO(void)
{
	//printf("%s ", token.name.data());
	return token.OnTime();
}
double Expression::Execute_IDF(void)
{
	//printf("%s ", token.name.data());
	return token.OffTime();
}
double Expression::Execute_IDV(void)
{
	//printf("%s ", token.name.data());
	return token.GetValue();
}
double Expression::Execute_NUM(void)
{
	//printf("%s ", token.name.data());
	return token.GetValue();
}
double Expression::Execute_HEX(void)
{
	//printf("%s ", token.name.data());
	return token.GetValue();
}
double Expression::Execute_TIME(void)
{
	//printf("%s ", token.name.data());
	return token.GetValue();
}
double Expression::Execute_DATE(void)
{
	//printf("%s ", token.name.data());
	return token.GetValue();
}
double Expression::Execute_DATETIME(void)
{
	//printf("%s ", token.name.data());
	return token.GetValue();
}
double Expression::Execute_SET(void)
{
	//printf("%s ", token.name.data());
	if( lchild && rchild )
	{
		lchild->token.SetValueAuto( rchild->Execute() );
	}
	return 0.0;
}
double Expression::Execute_GOTO(void)
{
	if( lchild && context )
	{
		context->GotoLabel(lchild->token.name);
	}
	if( rchild && context )
	{
		context->GotoLabel(rchild->token.name);
	}
	return 0.0;
}
double Expression::Execute_LABEL(void)
{
	//printf("%s ", token.name.data());
	return 0.0;
}
