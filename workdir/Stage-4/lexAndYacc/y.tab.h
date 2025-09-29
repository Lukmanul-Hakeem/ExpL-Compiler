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
    LSQUARE = 266,
    RSQUARE = 267,
    PUNCTUATION = 268,
    COMMA = 269,
    NEWLINE = 270,
    IF = 271,
    ELSE = 272,
    THEN = 273,
    ENDIF = 274,
    WHILE = 275,
    DO = 276,
    REPEAT = 277,
    UNTIL = 278,
    BREAK = 279,
    CONTINUE = 280,
    PLUS = 281,
    MINUS = 282,
    MULT = 283,
    DIV = 284,
    EQUAL = 285,
    LT = 286,
    GT = 287,
    LE = 288,
    GE = 289,
    NOT = 290,
    NE = 291,
    EQ = 292,
    NUM = 293,
    ID = 294,
    STRING_LITERAL = 295,
    DECL = 296,
    ENDDECL = 297,
    INT = 298,
    STR = 299
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
#define LSQUARE 266
#define RSQUARE 267
#define PUNCTUATION 268
#define COMMA 269
#define NEWLINE 270
#define IF 271
#define ELSE 272
#define THEN 273
#define ENDIF 274
#define WHILE 275
#define DO 276
#define REPEAT 277
#define UNTIL 278
#define BREAK 279
#define CONTINUE 280
#define PLUS 281
#define MINUS 282
#define MULT 283
#define DIV 284
#define EQUAL 285
#define LT 286
#define GT 287
#define LE 288
#define GE 289
#define NOT 290
#define NE 291
#define EQ 292
#define NUM 293
#define ID 294
#define STRING_LITERAL 295
#define DECL 296
#define ENDDECL 297
#define INT 298
#define STR 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser.y"

    tnode* node;

#line 149 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
