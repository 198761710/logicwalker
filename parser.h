/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     IDR = 259,
     IDO = 260,
     IDF = 261,
     IDV = 262,
     LC = 263,
     LCO = 264,
     LCF = 265,
     NUM = 266,
     HEX = 267,
     DATE = 268,
     TIME = 269,
     DATETIME = 270,
     IF = 271,
     THEN = 272,
     ELSE = 273,
     AND = 274,
     OR = 275,
     NOT = 276,
     EQ = 277,
     NE = 278,
     GE = 279,
     LE = 280,
     GT = 281,
     LT = 282,
     ADD = 283,
     MIN = 284,
     MUL = 285,
     DIV = 286,
     MOD = 287,
     LP = 288,
     RP = 289,
     LB = 290,
     RB = 291,
     CM = 292,
     SET = 293,
     GOTO = 294,
     LABEL = 295
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 11 "logicwalker.y"

	struct
	{
		double v;
		char t[128];
	};



/* Line 2068 of yacc.c  */
#line 100 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


