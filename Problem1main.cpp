#include "Problem1numcount.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mpi.h>

int main(){
  Init();

  // Matloff's example
  //double t1, t2;
  int x[]={3,4,5,12,13,4,5,12,4,5,6,3,4,5,13,4,5};
  // Turns out this is how you time
  // Will print nnodes times since the
  // same program will run on multiple machines
  
  //t1 = MPI_Wtime();
  int *results = numcount(x, 17, 3);
  //t2 = MPI_Wtime();
  //cout << "Elapsed time is " << (t2-t1) << " seconds." << endl;

  // Stefan's testing data
  // int array_size = 1000000;
  // int x[array_size];
  // for(int i = 0; i < array_size; i++)
  //   x[i] = rand()%100+1;
  // int * y;
  // y = x;

  // Turns out this is how you time
  // Will print nnodes times since the
  // same program will run on multiple machines
  // double t1, t2;
  // t1 = MPI_Wtime();
  // int *test = numcount(y, array_size, 6);
  // t2 = MPI_Wtime();
  // cout << "Elapsed time is " << (t2-t1) << " seconds." << endl;

  MPI_Finalize();
  return 0;
}