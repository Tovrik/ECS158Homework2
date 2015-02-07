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


// unordered_map <string, int> globalHash;
// unordered_map <int, int> t0;
// unordered_map <int, int> t1;
// unordered_map <int, int> t2;
// unordered_map <int, int> t3;
// unordered_map <int, int> t4;
// unordered_map <int, int> t5;
// unordered_map <int, int> t6;
// unordered_map <int, int> t7;
unordered_map <string, int> localCopy;

int *numcount(int *x, int n, int m) {
	// Master node
	if(me == 0) {
		// Compute the total number of chunks
		chunk = n / nnodes;
		// This is the global hash that the node 0 maintains
		unordered_map<string, int> globalHash;
	}

	// For all the other nodes
	else {
		// Determine its chunks
		start = (me - 1) * chunk;
		end = start + chunk - 1;

		stringstream convert;
		for(int i = start; i < end; i++) {
			if(i == end - 1)
      	convert << x[i];
      else
      	convert << x[i] << ",";
		}
		string key = convert.str();
		localCopy[key]++;

		// move our gaze to the next chunk of size m
		start++;
		end++;
		vector<string> keys;
		vector<int> values;

		for(auto j = localCopy.begin(); j != localCopy.end(); ++j) {
    string key = j->first; // Key
    int temp = j->second;

    keys.push_back(key);
    values.push_back(temp);

    // Send to the master node all the vectors of keys and values
		for(int i = 1; i < nnodes; i++) {
			MPI_Send(&keys[0], keys.size(), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			MPI_Send(&values[0], values.size(), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		}
	}





};



void Init(int Argc, char** Argv){
	//initializes MPI
	MPI_Init(NULL, NULL);
	//sets nnodes (number of nodes)
	MPI_COMM_size(MPI_COMM_WORLD, &nnodes); 
	//sets me (thread number)
	MPI_COMM_rank(MPI_COMM_WORLD, &me);
	//distributes tasks to the workers
	//MPI_Scatter();

	//determine chunck size, start/end for each node
	//chunk = n/nnodes;
	//start = me * chunck;
	//end = start + chunk - 1;

	//MPI_Scatter(sendbuf, chunk, MPI_INT, rbuf, ;
};


int main(int argc, char** argv){
	Init(argc, argv);

	// Master Node
	// if(me == 0) {
	// 	Node0();
	// }


	MPI_Finalize();
	return 0;
}
