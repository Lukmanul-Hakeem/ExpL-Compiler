#!/bin/bash

# Usage: ./run_xsm.sh file_name [input.txt output.txt]

EXEC="./xsm"
DIR="./workdir/Stage-4/lexAndYacc"
FILE_NAME=$1

if [[ -z "$FILE_NAME" ]]; then
    echo "Usage: $0 file_name [input.txt output.txt]"
    exit 1
fi

PROGRAM="$DIR/$FILE_NAME"

# If input/output files are provided
if [[ -n "$2" && -n "$3" ]]; then
    $EXEC -e "$PROGRAM" < "$2" > "$3"
    echo "Execution finished. Output saved to $3"
else
    $EXEC -e "$PROGRAM"
fi