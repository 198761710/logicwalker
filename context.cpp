#include "cache.h"
#include "context.h"
#include "statement.h"

Cache& Context::GetLocalVariable(void)
{
	return LocalVariable;
}
void Context::AddStatement(Statement& statement)
{
	context[statement_count] = statement;
	context[statement_count].SetContext(*this);
	statement_count++;
}
void Context::AddLabel(const string& label)
{
	labelmap[label] = statement_count;
}
void Context::GotoLabel(const string& label)
{
	map<string,int>::iterator i = labelmap.find(label);
	if( labelmap.end() != i )
	{
		Iterator it = context.find(i->second);
		if( context.end() != it )
		{
			index = it;
		}
	}
}
void Context::Execute(void)
{
	for(index = context.begin(); index != context.end(); index++)
	{
		index->second.Execute();
	}
}
