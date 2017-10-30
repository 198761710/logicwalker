#include <math.h>
#include "parser.h"
#include "context.h"
#include "expression.h"
#include "statement.h"


void Statement::SetContext(Context& context)
{
	if( statement.empty() )
	{
		return;
	}
	Expression& expression = statement.front();
	if( expression.GetType() == LABEL )
	{
		context.AddLabel(expression.GetName());
	}
	for(Iterator i = statement.begin(); i != statement.end(); i++)
	{
		i->SetContext(context);
	}
}
void Statement::AddExpression(Expression& expression)
{
	statement.push_back(expression);
	expression_count++;
}
void Statement::Execute(void)
{
	switch(expression_count)
	{
		case 1:
			statement.back().Execute();
			break;
		case 2:
			if( fabs(statement.back().Execute()) > 0.9999 )
			{
				statement.front().Execute();
			}
			break;
		case 3:
			if( fabs(statement.back().Execute()) > 0.9999 )
			{
				Iterator i = statement.begin();
				i++;i->Execute();
			}
			else
			{
				statement.front().Execute();
			}
			break;
	}
}
Statement& Statement::operator=(Statement& s)
{
	statement = s.statement;
	expression_count = s.expression_count;
}
