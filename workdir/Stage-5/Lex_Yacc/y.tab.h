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
    IF = 262,
    ELSE = 263,
    THEN = 264,
    ENDIF = 265,
    WHILE = 266,
    DO = 267,
    REPEAT = 268,
    UNTIL = 269,
    BREAK = 270,
    CONTINUE = 271,
    EQUAL = 272,
    LT = 273,
    GT = 274,
    LE = 275,
    GE = 276,
    NOT = 277,
    NE = 278,
    EQ = 279,
    AND = 280,
    DECL = 281,
    ENDDECL = 282,
    INT = 283,
    STR = 284,
    NUM = 285,
    ID = 286,
    STRING_LITERAL = 287
  };
#endif
/* Tokens.  */
#define PBEGIN 258
#define END 259
#define READ 260
#define WRITE 261
#define IF 262
#define ELSE 263
#define THEN 264
#define ENDIF 265
#define WHILE 266
#define DO 267
#define REPEAT 268
#define UNTIL 269
#define BREAK 270
#define CONTINUE 271
#define EQUAL 272
#define LT 273
#define GT 274
#define LE 275
#define GE 276
#define NOT 277
#define NE 278
#define EQ 279
#define AND 280
#define DECL 281
#define ENDDECL 282
#define INT 283
#define STR 284
#define NUM 285
#define ID 286
#define STRING_LITERAL 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "parser.y"

    ast_node* AST_node;
    gst_node* GST_node;
    p_node* param_node;

#line 127 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
