#!/bin/sh

if test $# -eq 1; then
  case $1 in
    "1")
     gcc -o part1.out assignment1_part1.c
     echo ""
     ./part1.out
     echo ""
     ;;
    "2")
     gcc -o part2.out assignment1_part2.c
     echo ""
     ./part2.out 12345 41976
     echo ""
     ;;
     *)
     echo "Invalid Argument"
     ;;
  esac
elif test $# -gt 1; then
  echo "Usage: run part# or run"
else
  gcc -o part1.out assignment1_part1.c
  gcc -o part2.out assignment1_part2.c
  echo ""
  ./part1.out
  echo ""
  ./part2.out 12345 41976
  echo ""
fi
