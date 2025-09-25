/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PBEGIN = 258,
    END = 259,
    READ = 260,
    WRITE = 261,
    LPAREN = 262,
    RPAREN = 263,
    LBRACE = 264,
    RBRACE = 265,
    PUNCTUATION = 266,
    NEWLINE = 267,
    IF = 268,
    ELSE = 269,
    THEN = 270,
    ENDIF = 271,
    WHILE = 272,
    DO = 273,
    REPEAT = 274,
    UNTIL = 275,
    BREAK = 276,
    CONTINUE = 277,
    PLUS = 278,
    MINUS = 279,
    MULT = 280,
    DIV = 281,
    EQUAL = 282,
    LT = 283,
    GT = 284,
    LE = 285,
    GE = 286,
    NOT = 287,
    NE = 288,
    EQ = 289,
    NUM = 290,
    ID = 291
  };
#endif
/* Tokens.  */
#define PBEGIN 258
#define END 259
#define READ 260
#define WRITE 261
#define LPAREN 262
#define RPAREN 263
#define LBRACE 264
#define RBRACE 265
#define PUNCTUATION 266
#define NEWLINE 267
#define IF 268
#define ELSE 269
#define THEN 270
#define ENDIF 271
#define WHILE 272
#define DO 273
#define REPEAT 274
#define UNTIL 275
#define BREAK 276
#define CONTINUE 277
#define PLUS 278
#define MINUS 279
#define MULT 280
#define DIV 281
#define EQUAL 282
#define LT 283
#define GT 284
#define LE 285
#define GE 286
#define NOT 287
#define NE 288
#define EQ 289
#define NUM 290
#define ID 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "parser.y"

    struct tnode* node;

#line 133 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
