#!/bin/bash
#for tabu only

for (( i=1; i<=20; i++ ))
do
	./tabu $1 >> $2
done
