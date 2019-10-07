#!/bin/bash
cd obj/
gcc -c ../src/blocks.c
gcc -c ../src/criptocao.c
gcc -c ../src/main.c
cd ../bin/
gcc -o monstrinho ../obj/blocks.o ../obj/criptocao.o ../obj/main.o
./monstrinho "../src/plaintext.txt"
