All:
	/usr/lib64/mpich/bin/mpicxx -g -std=c++0x -o Problem1.out Problem1numcount.cpp

run:
	/usr/lib64/mpich/bin/mpirun -n 8 -hostfile HOSTFILE Problem1.out

clean:
	rm *.out