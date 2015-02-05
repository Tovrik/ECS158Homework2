#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <iostream>
#include <mpi.h>

using namespace std;

#define MYMIN_MSG 0
// #define 

int nnodes, me;


unordered_map <string, int> globalHash;
unordered_map <int, int> t0;
unordered_map <int, int> t1;
unordered_map <int, int> t2;
unordered_map <int, int> t3;
unordered_map <int, int> t4;
unordered_map <int, int> t5;
unordered_map <int, int> t6;
unordered_map <int, int> t7;

int *numcount(int *x, int n, int m) {

	MPI_Init(NULL, NULL);
	MPI_COMM_size(MPI_COMM_WORLD, &nnodes); //number of nodes
	MPI_COMM_rank(MPI_COMM_WORLD, &me); //assigns me (thread number)
	MPI_Scatter();//distributes the task to the workers



	MPI_Finalize();

};