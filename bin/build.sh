#!/bin/bash

set -Eeuo pipefail

cd "$(dirname "$0")/.."

cd src
bison -d parse.y -o parse.tab.cc --debug -t
flex -o lex.flex.cc lex.l

export CMAKE_INCLUDE_PATH="/usr/local/opt/flex/include"
export CMAKE_LIBRARY_PATH="/usr/local/opt/flex/lib;/usr/local/opt/bison/lib"
export PATH="/usr/local/opt/flex/bin:/usr/local/opt/bison/bin:$PATH"

cd ../

# Clean cache
rm -f CMakeCache.txt
rm -rf build
find . -name 'CMakeCache.txt' -o -name '*.cmake' -o -name 'Makefile' -o -name 'CMakeFiles' -exec rm -rf {} +

cmake -H. -Bbuild
cmake --build build -- -j3


