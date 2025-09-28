#!/bin/bash
# Script to build and run the label transition project

# Stop if any command fails
set -e

# Step 1: Generate C file from flex
flex -o label_transition.c label.l

# Step 2: Compile with label.c
gcc label_transition.c ./labelTransition/label.c -o label_transition

# Step 3: Run executable (if you have an input file, pass it as argument)
./label_transition