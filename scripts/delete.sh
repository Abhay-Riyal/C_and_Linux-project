#!/bin/bash
grep -v $1 ./records/account.txt > ./records/exist.txt
cat ./records/exist.txt > ./records/account.txt
