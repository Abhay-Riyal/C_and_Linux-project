#!/bin/bash
grep -w  $1 ./records/account.txt > ./records/exist.txt
