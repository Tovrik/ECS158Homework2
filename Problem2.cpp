#include <stdio.h>
#include <stdlib.h>
#include <complex>
#include <cmath>
#include <iostream>
#include <omp.h>

using namespace std;

// nth: number of threads
// xl: left limit
// xr: right limit
// yb: bottom limit
// yt: top limit
// inc: distance between ticks on X, Y axes
// maxiters: maximum number of iterations
// sched: quoted string indicating which OMP scheduling method is to be used
// chunksize: OMP chunk size

int[] xticks, yticks;

rmandel(nth, xl, xr, yb, yt, inc, maxiters, sched, chunksize) {
	
	int xti, ytj;
	complex<double> cpt; 
	//number of ticks on the x-axis
	nxticks = (xr - xl) / inc;
	//number of ticks on the y-axis
	nyticks = (yt - yb) / inc;
	//array set containing the tick marks on the x-axis
	int xticks[nxticks];
	//array set containing the tick marks on the y-axis 
	int yticks[nyticks];
	//set the left most tick mark
	xticks[0] = xl;
	for(int i = 1; i < nxticks; i++)
		xticks[i] = xticks[i-1] + inc;
	//set the bottom most tick mark
	yticks[0] = yb;
	for(int i = 1; i < nyticks; i++)
		yticks[i] = yticks[i-1] + inc;   

	//create array init to 0 for mandelbrot set
	bool mandelbrot[nxticks][nyticks];

	for(i = 0; i < nxticks; i++) {
		xti = xticks[i];
		for (int j = 0; j < nyticks; j++) {
			ytj = yticks[j];
			cpt = pow(xti, 2);
		}
	}


};


    
