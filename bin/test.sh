#!/bin/bash

set -Eeuo pipefail

cd "$(dirname "$0")/.."

cd src
bison -d parse.y -o parse.tab.cc --debug -t
flex -o lex.flex.cc lex.
