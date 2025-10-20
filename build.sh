#!/bin/bash
# build.sh - compile the project

# Stop on first error
set -e

# Detect OS
OS="$(uname -s)"

if [[ "$OS" == *"MINGW"* || "$OS" == *"MSYS"* || "$OS" == *"CYGWIN"* ]]; then
    # Windows (Git Bash, MinGW, etc.)
    OUTPUT="project.exe"
else
    # Linux / macOS
    OUTPUT="project"
fi

# Compile sources into output
g++ -std=c++17 -O2 -Wall -o "$OUTPUT" main.cpp Heap.cpp Hash_Map.cpp

echo "Compilation successful! Run the program with:"
if [[ "$OS" == *"MINGW"* || "$OS" == *"MSYS"* || "$OS" == *"CYGWIN"* ]]; then
    echo ".\\$OUTPUT"
else
    echo "./$OUTPUT"
fi
