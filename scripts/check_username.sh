#!/bin/bash
cat ./records/account.txt | awk '{print $3}' > ./records/temp.txt 
grep -w -c "\b$1\b" ./records/temp.txt > ./records/exist.txt
