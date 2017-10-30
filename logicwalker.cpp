#include <math.h>
#include <stdio.h>
#include "token.h"
#include "parser.h"
#include "logicwalker.h"

TokenLmap LogicWalker::tokenlmap;
TokenList LogicWalker::tokenlist;
extern class Cache GlobalVariable;

void LogicWalker::AddToken(const Token& node)
{
	tokenlist.push_back(node);
}
void LogicWalker::AddList(void)
{
	static int i = 0;
	tokenlmap[i++] = tokenlist;
	tokenlist.clear();
}
void LogicWalker::ShowList(void)
{
	while( tokenlist.end() != tokenlist.begin() )
	{
		Token &node = tokenlist.back();
		printf("%s\n", node.name.data());
		tokenlist.pop_back();
	}
}
void LogicWalker::Execute(void)
{
	Context context;
	int linecout = tokenlmap.size();

	for(int i = 0; i < linecout; i++)
	{
		Statement statement;
		tokenlist = tokenlmap[i];
		while( !tokenlist.empty() )
		{
			Expression expression;
			expression.CreateTree(tokenlist);
			statement.AddExpression(expression);
			statement.SetContext(context);
		}
		context.AddStatement(statement);
	}
	tokenlist.clear();
	tokenlmap.clear();
	while(1)
	{
		context.Execute();
		static time_t old = time(0);
		if( time(0) - old != 0 )
		{
			old = time(0);
			GlobalVariable.ShowToken();
			context.GetLocalVariable().ShowToken();
		}
	}
}
