#! /bin/bash

echo "starting Updating C code ...."

gcc -std=c11 -Wall -Wextra -pedantic -c -fPIC mylib.c -o mylib.o

gcc -shared mylib.o -o mylib.dll

gcc -shared -o mylib.so mylib.o

echo "Done Updating"