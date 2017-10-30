#include <math.h>
#include <stdlib.h>
#include "token.h"
#include "parser.h"
#include "cache.h"
#include "context.h"
#include "variable.h"

extern Cache GlobalVariable;

Token::Token(void)
{
	var = 0;
	type = -1;
	value = 0.0;
	name = "unknow-token";
}
Token::Token(signed t, const string& n)
{
	var = 0;
	type = t;
	name = n;
	TokenValue();
}
void Token::SetContext(Context& context)
{
	switch(type)
	{
	case ID:
		GlobalVariable.SetToken(*this);
		break;
	case IDR:
	case IDO:
	case IDF:
	case IDV:
		name[name.find_first_of(".")] = 0;
		name = name.data();
		GlobalVariable.SetToken(*this);
		break;
	case LC:
		context.GetLocalVariable().SetToken(*this);
		break;
	case LCO:
	case LCF:
		name[name.find_first_of(".")] = 0;
		name = name.data();
		context.GetLocalVariable().SetToken(*this);
		break;
	}
}
void Token::SetVariable(Variable& variable)
{
	var = &variable;
}
const double& Token::GetValue(void)
{
	switch(type)
	{
	case NUM:
	case HEX:
	case TIME:
	case DATE:
	case DATETIME:
		return value;
	case LCO:
	case LCF:
	case IDO:
	case IDF:
	case IDR:
		string idname;
		for(const char *p = name.data(); p && *p; p++)
		{
			if( '.' == *p )
				break;
			idname += *p;
		}
		name = idname;
	}
	if( var )
	{
		return var->GetValue();
	}
	return value;
}
bool Token::SetValue(const double& v)
{
	if( var )
	{
		var->SetValueAuto((double&)v);
		return true;
	}
	return false;
}
bool Token::SetValueAuto(const double& v)
{
	if( var )
	{
		var->SetValueAuto((double&)v);
		return true;
	}
	return false;
}
bool Token::SetValueManual(const double& v)
{
	if( var )
	{
		var->SetValueManual((double&)v);
		return true;
	}
	return false;
}
const time_t Token::GetRuntime(void)
{
	if( var )
	{
		return (const time_t)var->Runtime();
	}
	return (const time_t)(0);
}
void Token::SetRuntime(const time_t t)
{
	if( var )
	{
		var->SetRuntime((time_t)t);
	}
}
const time_t Token::OnTime(void)
{
	if( var )
	{
		return var->OnTime();
	}
	return time_t(0);
}
const time_t Token::OffTime(void)
{
	if( var )
	{
		return var->OffTime();
	}
	return time_t(0);
}
void Token::TokenValue(void)
{
	if( name.empty() )
	{
		return;
	}
	switch(type)
	{
	case NUM:
		value = strtod(name.data(), 0); 
		break;
	case HEX:
		value = strtol(name.data(), 0, 16);
		break;
	case TIME:
	{
		struct tm t = {0,0,0,0,0,0,0,0,0,0,0};
		strptime(name.data(), "%H:%M:%S", &t);
		value = (t.tm_hour * 60 * 60);
		value += (t.tm_min * 60);
		value += (t.tm_sec);
	}
	break;
	case DATE:
	{
		struct tm t = {0,0,0,0,0,0,0,0,0,0,0};
		strptime(name.data(), "%Y-%m:%d", &t);
		value = mktime(&t);
	}
	break;
	case DATETIME:
	{
		struct tm t = {0,0,0,0,0,0,0,0,0,0,0};
		strptime(name.data(), "%Y-%m:%d %H:%M:%S", &t);
		value = mktime(&t);
	}
	break;
	}
}
