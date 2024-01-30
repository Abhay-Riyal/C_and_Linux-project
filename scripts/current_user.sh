#!/bin/bash
grep -x  $1 ./records/account.txt > ./records/exist.txt
