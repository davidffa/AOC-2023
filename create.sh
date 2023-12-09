#!/bin/sh

# Creates a new day folder with C code template and input/sample empty text files

usage() {
  echo "Usage: $0 <day>" >&2
  exit 1
}

if [[ $# -lt 1 ]]; then
  usage
fi

if [[ ! -f "./template.c" ]]; then
  echo "Oopsie, template file does not exist!" >&2
  exit 1
fi

day="$1"

if [[ -d "$day" ]]; then
  echo "Day $day already exists!" >&2
  exit 1
fi

mkdir "$day"
cp ./template.c "$day/main.c"
touch "./$day/sample.txt"
touch "./$day/input.txt"

echo "Day $day created!"
