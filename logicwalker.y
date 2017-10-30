%{
#include <stdio.h>
#include "logicwalker.h"
extern "C" int yylex(void);
extern "C" void yyerror(const char*);
%}
%union
{
	struct
	{
		double v;
		char t[128];
	};
}
%type <double>	NUM

%token	ID IDR IDO IDF IDV LC LCO LCF NUM HEX DATE TIME DATETIME

%token	IF THEN ELSE 

%token	AND OR NOT 

%token	EQ NE GE LE GT LT

%token	ADD MIN MUL DIV MOD

%token	LP RP LB RB CM

%token	SET GOTO LABEL

%left AND OR NOT
%left EQ NE GT LT GE LE
%left ADD MIN
%left MUL DIV MOD
%%

logicwalker:
	logicwalker line_expression {LogicWalker::AddList();}
	|
	line_expression {LogicWalker::AddList();}
	;
line_expression:
	if_else_expression
	|
	execute_expression
	|
	label_expression
	;
if_else_expression:
	if_expression then_expression
	|
	if_expression then_expression else_expression
	;
if_expression:
	IF value_expression {NODE(IF, "if");}
	;
then_expression:
	THEN execute_expression {NODE(THEN, "then");}
	;
else_expression:
	ELSE execute_expression {NODE(ELSE, "else");}
	;
execute_expression:
	set_expression
	|
	goto_expression
	;
set_expression:
	ID SET value_expression {NODE(ID, $<t>1); NODE(SET,"=");}
	|
	LC SET value_expression {NODE(LC, $<t>1); NODE(SET,"=");}
	;
goto_expression:
	GOTO ID {NODE(ID,string($<t>2)+":"); NODE(GOTO,"goto");}
	;
label_expression:
	LABEL {NODE(LABEL, $<t>1);}
	;
value_expression:
	NOT value_expression                   {NODE(NOT, "!");}
	|
	value_expression AND value_expression  {NODE(AND, "&&");}
	|
	value_expression OR value_expression   {NODE(OR, "||");}
	|
	value_expression EQ value_expression   {NODE(EQ, "==");}
	|
	value_expression NE value_expression   {NODE(NE, "!=");}
	|
	value_expression GE value_expression   {NODE(GE, ">=");}
	|
	value_expression LE value_expression   {NODE(LE, "<=");}
	|
	value_expression GT value_expression   {NODE(GT, ">");}
	|
	value_expression LT value_expression   {NODE(LT, "<");}
	|
	value_expression ADD value_expression  {NODE(ADD, "+");}
	|
	value_expression MIN value_expression  {NODE(MIN, "-");}
	|
	value_expression MUL value_expression  {NODE(MUL, "*");}
	|
	value_expression DIV value_expression  {NODE(DIV, "/");}
	|
	value_expression MOD value_expression  {NODE(MOD, "%");}
	|
	LP value_expression RP {}
	|
	ID {NODE(ID, $<t>1);}
	|
	IDR {NODE(IDR, $<t>1);}
	|
	IDO {NODE(IDO, $<t>1);}
	|
	IDF {NODE(IDF, $<t>1);}
	|
	IDV {NODE(IDV, $<t>1);}
	|
	LC {NODE(LC, $<t>1);} 
	| 
	LCO {NODE(LCO, $<t>1);} 
	| 
	LCF {NODE(LCF, $<t>1);} 
	| 
	NUM {NODE(NUM, $<t>1);} 
	| 
	HEX {NODE(HEX, $<t>1);} 
	| 
	DATE {NODE(DATE, $<t>1);}
	|
	TIME {NODE(TIME, $<t>1);}
	|
	DATETIME {NODE(DATETIME, $<t>1);}
	;
%%

void yyerror(const char *p)
{
	printf("error:%s\n", p?p:"null");
}

#ifdef TEST_PARSER
int main(int argc, char **argv)
{
	yyparse();
	LogicWalker::Execute();
	return 0;
}
#endif//TEST_PARSER
