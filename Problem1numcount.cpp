#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <iostream>
#include <mpi.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <ctime>
using namespace std;

int nnodes, //total number of nodes
chunk,    //number of array elements looked at by each node
startx,    //start index for given process
endx,    //end index for given process
me;     //process number

unordered_map <string, int> localCopy;

int *numcount(int *x, int n, int m) {
  // Master node
  // Determine the chunk size
  chunk = n / nnodes;
  // For master node
  if(!me) {
    // Use status to receive the node number(for debugging purposes)
    MPI_Status status;
    // This is the global hash that the node 0 maintains
    unordered_map<string, int> globalHash;
    for(int t = 0; t < nnodes - 1; t++){
      // OUR APPROACH FOR THE BELOW IS GOING TO BE THIS
      // 1. COLLECT / RECEIVE THE MINI HASH MAPS FROM ALL THE WORKERS
      // IN ARRAY FORM IN WHICH THIS IS THE FORM (KEY1|KEY2|KEY3|COUNT1|... WHEN M = 3)
      // FOR EXAMPLE
      // 2. TAKE THOSE ARRAYS AND PUT THE KEYS IN HASH MAP AND INCREMENT
      // THE COUNT FROM THE MINI HASH MAPS

      // HERE IS THE IMPORTANT PART(PLEASE READ)!!
      // WE CAN DYNAMICALLY DETERMINE THE BUFFER LENGTH FROM RECEIVE AND
      // TURNS OUT EVEN N IS NOT A GOOD APPROX.
      // HENCE WE USE PROBE AND GET_COUNT TO GET THE BUFFER LENGTH
      int buffer_size;
      MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      MPI_Get_count(&status, MPI_INT, &buffer_size);

      // BASED ON WHAT WE DYNAMICALLY RECEIVE, CONSTRUCT A BUFFER
      // TO HOLD THE ELEMENTS
      int* buffer = new int[buffer_size * sizeof(int)]; 
      MPI_Recv(buffer, // Where we are storing the array
        buffer_size, // Buffer size, overestimating because it can't be bigger than n
        MPI_INT, 
        MPI_ANY_SOURCE, // Don't care from which node we're recieveing
        MPI_ANY_TAG, // ***Tag contains the size of the array sent!***
        MPI_COMM_WORLD,
        &status); // We use status to extract the MPI_TAG.


      // THE RECEIVED BUFFER IS IN THE FORM OF KEY1,KEY2,KEY3,COUNT1
      // KEY2,KEY3,KEY4,COUNT2 WHEN M = 3 FOR EXAMPLE, SO RUN THE FOR
      // LOOP ACCORDING TO THAT ARRANGEMENT / PATTERN
      // After receive array, put in hash map
      for(int i = 0; i < buffer_size; i = i + m + 1){
        stringstream convert;
        int j;
        for(j = i; j < i + m; j++) {
              if(j == i + m - 1)
                convert << buffer[j];
              else
                convert << buffer[j] << ",";
          }
          string key = convert.str();
          // Take the counts from the mini-hash maps and
          // add their counts to the global one
          globalHash[key] = globalHash[key] + buffer[j];
        }
      // Have to delete it since you allocated space on the heap
      delete buffer;
  }

  // Decoding process
  // Basically converting hash into array in final step
  vector<int> results;
  string key = "";
  results.push_back(globalHash.size());
  for(auto j = globalHash.begin(); j != globalHash.end(); ++j) {
    key = j->first; // Key
    int temp = j->second; // Global value local key
    istringstream ss(key); // Stringstream is for converting key back to integers
    //loop that stores the integer value of the key string for the hash seperated by ','
    while(getline(ss,key,',')) {
      results.push_back(atoi(key.c_str()));
    }
    results.push_back(temp);
    ss.clear();
  }

  // Left here for debugging purposes
  // STEFAN AND BIJAN, you guys can uncomment this if you wanna test
  // cout << "Size of the results array is: " << results[0] << endl;
  // for(int i = 1; i < results.size(); i++ ) {
  //   cout << results[i] << ",";
  //   if(i % (m + 1) == 0)
  //     cout << endl;
  // }
  // cout << endl;

  // RETURN A POINTER TO THE ARRAY
  // SINCE RESULTS IS A VECTOR
  return &results[0];

  //DO NOT FORGET TO RETURN SHIT
  }

  // For all the other nodes
  else {
    // Determine its chunks
    startx = (me - 1) * chunk;
    // This boundaries formula and scenario is very similar
    // to homework 1
    if(me == (nnodes-1))
      endx = n - m + 1; //account for last thread taking care of rest of array
    else
      endx = startx + chunk;
    
    // Encode and put it into hash table
    for(int i = startx; i < endx; i++) {
      stringstream convert;
      for(int j = i; j < i + m; j++) {
        if(j == i + m - 1)
          convert << x[j];
        else
          convert << x[j] << ",";
      }
      string key = convert.str();
      localCopy[key]++;
    }

    vector<int> hashArray;
    
    // Decoding process, straighforward
    for(auto j = localCopy.begin(); j != localCopy.end(); ++j) {
      string key = j->first; // Key
      int temp = j->second;
      istringstream ss(key);
      while(getline(ss,key,',')){
        int key_int = atoi(key.c_str());
        hashArray.push_back(key_int);
      }
      hashArray.push_back(temp);
      ss.clear();
    }

    // Turns out we can actually send vectors
    // because essentially the vector's first element points to the array
    MPI_Send(&hashArray[0],(hashArray.size()), MPI_INT, 0, me, MPI_COMM_WORLD);
  }
};



void Init(){
  //initializes MPI
  MPI_Init(NULL, NULL);
  //sets nnodes (number of nodes)
  MPI_Comm_size(MPI_COMM_WORLD, &nnodes); 
  //sets me (thread number)
  MPI_Comm_rank(MPI_COMM_WORLD, &me);
};


// int main(){
//   Init();

//   // Matloff's example
//   //double t1, t2;
//   int x[]={3,4,5,12,13,4,5,12,4,5,6,3,4,5,13,4,5};
//   // Turns out this is how you time
//   // Will print nnodes times since the
//   // same program will run on multiple machines
  
//   //t1 = MPI_Wtime();
//   int *results = numcount(x, 17, 3);
//   //t2 = MPI_Wtime();
//   //cout << "Elapsed time is " << (t2-t1) << " seconds." << endl;

//   // Stefan's testing data
//   // int array_size = 1000000;
//   // int x[array_size];
//   // for(int i = 0; i < array_size; i++)
//   //   x[i] = rand()%100+1;
//   // int * y;
//   // y = x;

//   // Turns out this is how you time
//   // Will print nnodes times since the
//   // same program will run on multiple machines
//   // double t1, t2;
//   // t1 = MPI_Wtime();
//   // int *test = numcount(y, array_size, 6);
//   // t2 = MPI_Wtime();
//   // cout << "Elapsed time is " << (t2-t1) << " seconds." << endl;

//   MPI_Finalize();
//   return 0;
// }
