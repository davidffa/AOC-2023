#!/bin/sh

CC=cc
CFLAGS="-Wall -Wextra -Wshadow -pedantic"

usage() {
  echo "Usage: $0 <day>" >&2
  exit 1
}

if [[ $# -lt 1 ]]; then
  usage
fi

if [[ ! -d "$1" ]]; then
  echo "Directory $1 does not exist!" >&2
  exit 1
fi

cd $1 && $CC $CFLAGS -o $1 main.c && ./$1 && cd ..