#!/bin/bash
cat ./records/account.txt | awk '{print $3}' > ./records/temp.txt 
grep -x -c $1 ./records/temp.txt > ./records/exist.txt
