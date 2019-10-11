#!/bin/bash
cd obj/
gcc -c ../src/util.c
gcc -c ../src/blocks.c
gcc -c ../src/criptocao.c
gcc -c ../src/main.c
cd ../bin/
gcc -o monstrinho ../obj/util.o ../obj/blocks.o ../obj/criptocao.o ../obj/main.o
./monstrinho "../plaintext.txt"
