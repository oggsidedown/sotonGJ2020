#!/bin/bash
#Compile olcPixelGameEngine program
FILENAME=$1
OUTPUT=$2
g++ -o $OUTPUT $FILENAME -lX11 -lGL -lpthread -lpng -lstdc++fs -ggdb
