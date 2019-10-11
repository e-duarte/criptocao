#!/bin/bash

outfile="benckmark.txt"
par=$*
case $par in
    "-c") echo "Execução: criptocao -c plaintext.txt" >> $outfile
    echo "----------------------------------------" >> $outfile
    (time ./bin/criptocao -c plaintext.txt) >> $outfile 2>&1
    echo "" >> $outfile
    ;;
    "-d") echo "Execução: criptocao -d encripted.txt key.txt" >> $outfile
    echo "----------------------------------------" >> $outfile
    (time ./bin/criptocao -d encripted.txt key.txt) >> $outfile 2>&1
    echo "" >> $outfile
esac



