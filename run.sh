#!/bin/bash
set -e
OS="$(uname -s)"

if [[ "$OS" == *"MINGW"* || "$OS" == *"MSYS"* || "$OS" == *"CYGWIN"* ]]; then
    OUTPUT="project.exe"
else
    OUTPUT="project"
fi

g++ -std=c++17 -O2 -Wall -o "$OUTPUT" main.cpp heap.cpp file.cpp tree.cpp

echo "Compilation successful! Run the program with:"
if [[ "$OS" == *"MINGW"* || "$OS" == *"MSYS"* || "$OS" == *"CYGWIN"* ]]; then
    echo ".\\$OUTPUT"
else
    echo "./$OUTPUT"
fi
