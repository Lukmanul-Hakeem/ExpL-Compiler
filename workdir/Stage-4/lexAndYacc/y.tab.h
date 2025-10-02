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
    MOD = 285,
    EQUAL = 286,
    LT = 287,
    GT = 288,
    LE = 289,
    GE = 290,
    NOT = 291,
    NE = 292,
    EQ = 293,
    NUM = 294,
    ID = 295,
    STRING_LITERAL = 296,
    DECL = 297,
    ENDDECL = 298,
    INT = 299,
    STR = 300
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
#define MOD 285
#define EQUAL 286
#define LT 287
#define GT 288
#define LE 289
#define GE 290
#define NOT 291
#define NE 292
#define EQ 293
#define NUM 294
#define ID 295
#define STRING_LITERAL 296
#define DECL 297
#define ENDDECL 298
#define INT 299
#define STR 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser.y"

    tnode* node;

#line 151 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
