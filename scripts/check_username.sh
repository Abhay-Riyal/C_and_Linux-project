#!/bin/bash
cat ./records/account.txt | awk '{print $3}' | grep -xc > ./records/exist.txt
