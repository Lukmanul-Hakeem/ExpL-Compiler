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
    COMMA = 267,
    NEWLINE = 268,
    IF = 269,
    ELSE = 270,
    THEN = 271,
    ENDIF = 272,
    WHILE = 273,
    DO = 274,
    REPEAT = 275,
    UNTIL = 276,
    BREAK = 277,
    CONTINUE = 278,
    PLUS = 279,
    MINUS = 280,
    MULT = 281,
    DIV = 282,
    EQUAL = 283,
    LT = 284,
    GT = 285,
    LE = 286,
    GE = 287,
    NOT = 288,
    NE = 289,
    EQ = 290,
    NUM = 291,
    ID = 292,
    STRING_LITERAL = 293,
    DECL = 294,
    ENDDECL = 295,
    INT = 296,
    STR = 297
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
#define COMMA 267
#define NEWLINE 268
#define IF 269
#define ELSE 270
#define THEN 271
#define ENDIF 272
#define WHILE 273
#define DO 274
#define REPEAT 275
#define UNTIL 276
#define BREAK 277
#define CONTINUE 278
#define PLUS 279
#define MINUS 280
#define MULT 281
#define DIV 282
#define EQUAL 283
#define LT 284
#define GT 285
#define LE 286
#define GE 287
#define NOT 288
#define NE 289
#define EQ 290
#define NUM 291
#define ID 292
#define STRING_LITERAL 293
#define DECL 294
#define ENDDECL 295
#define INT 296
#define STR 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser.y"

    tnode* node;

#line 145 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
