#include <math.h>
#include <stdio.h>
#include "token.h"
#include "parser.h"
#include "logicwalker.h"

TokenLmap LogicWalker::tokenlmap;
TokenList LogicWalker::tokenlist;

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
void LogicWalker::MakeContext(Context& context)
{
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
}
