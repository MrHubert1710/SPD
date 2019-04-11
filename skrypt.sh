#!/bin/bash
for z in $(seq 1 10 111)
do
    for i in $(LANG=en_US seq 0.9 0.005 0.995)
    do
	for j in $(seq 100 100 2000)
	do
	    ./Wyzarzanie $z TEST/test$z $i $j 0.1
	done
    done
done
