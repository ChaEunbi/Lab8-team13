#!/bin/bash

tar -xvf tsp.tar
mkdir gz
mv *.gz gz
cd gz
ls > input
cp ../jy .
./jy $(cat input)
