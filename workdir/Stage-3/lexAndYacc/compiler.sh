#!/bin/bash
# Script to compile and run the EXP LEX-YACC project

# Stop on first error
set -e

# Step 1: Generate parser files
yacc -d parser.y

# Step 2: Generate lexical analyzer
flex lexical.l

# Step 3: Compile everything
gcc lex.yy.c y.tab.c ./../utils/parseTree.c ./../utils/codeGeneration.c -o final

# Step 4: Run with input and output files
./final input.txt output.txt