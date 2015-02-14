#!/bin/bash
# Clean up the initial files
rm -f *.so;
rm -f *.o;
# Compiler options for R CMD SHLIB
g++ -I/usr/share/R/include -DNDEBUG -fpic  -O3 -pipe -lgomp -g  -c Problem2.cpp -fopenmp -o Problem2.o;
g++ -shared -o Problem2.so Problem2.o -L/usr/lib/R/lib -lR;