#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <iostream>
#include <mpi.h>

using namespace std;


int nnodes, //total number of nodes
chunk, 		//number of array elements looked at by each node
start,		//start index for given process
end,		//end index for given process
me;			//process number


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



};



void init(){
	//initializes MPI
	MPI_Init(NULL, NULL);
	//sets nnodes (number of nodes)
	MPI_COMM_size(MPI_COMM_WORLD, &nnodes); 
	//sets me (thread number)
	MPI_COMM_rank(MPI_COMM_WORLD, &me);
	//distributes tasks to the workers
	MPI_Scatter();

	//determine chunck size, start/end for each node
	chunk = n/nnodes;
	start = me * chunck;
	end = start + chunk - 1;

	MPI_Scatter(sendbuf, chunk, MPI_INT, rbuf, ;
};


int main(int ac, char** av){
	MPI_Finalize();
	return 0;
}
