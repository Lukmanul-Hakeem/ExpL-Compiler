#!/bin/bash

# Exit immediately if any command fails
set -e

# Filenames
PARSER="parser.y"
LEXER="lexical.l"
OUTPUT="final"

# Cleanup previous builds
echo "Cleaning previous builds..."
rm -f y.tab.c y.tab.h lex.yy.c $OUTPUT

# Step 1: Generate parser from Yacc/Bison
echo "Running Yacc/Bison..."
yacc -d $PARSER

# Step 2: Generate lexer from Flex
echo "Running Flex..."
flex $LEXER

# Step 3: Compile all C files together
echo "Compiling with GCC..."
gcc y.tab.c lex.yy.c ./../GlobalSymbolTable/GlobalSymbolTable.c ./../utils/parseTree.c -o $OUTPUT

echo "Build successful! Executable: $OUTPUT"