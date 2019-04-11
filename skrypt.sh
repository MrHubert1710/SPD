#!/bin/bash
for z in $(seq 1 10 111)
do
    for i in $(LANG=en_US seq 0.8 0.01 0.99)
    do
	for j in $(seq 1000 1000 20000)
	do
	    ./WyzarzanieIns $z TEST_INS_BR/test$z $i $j 1
	done
    done
done
