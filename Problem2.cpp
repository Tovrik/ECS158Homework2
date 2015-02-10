#include <stdio.h>
#include <stdlib.h>
#include <complex>
#include <cmath>
#include <iostream>
// #include <omp.h>
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>

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

// Yo, stefo after I briefly read Matloff's tutorial for Rcpp, I belive the return type/header
// see 5.5.6 of the tutorial
// should be
// RcppExport SEXP rmandel(blablabla)
void rmandel(int nth, int xl, int xr, int yb, int yt, double inc, int maxiters, string sched, int chunksize) {
	
	//temporary values for x and y
	int xti, ytj;
	//number of ticks on the x-axis
	int nxticks = (xr - xl) / inc;
	//number of ticks on the y-axis
	int nyticks = (yt - yb) / inc;
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
	// Maybe this should be Rcpp : : NumericMatrix????
	bool mandelbrot[nxticks][nyticks];

	//loop through the x values
	for(int i = 0; i < nxticks; i++) {
		//get the current x value
		xti = xticks[i];
		//loop through the y values
		for (int j = 0; j < nyticks; j++) {
			//get the current y value
			ytj = yticks[j];
			//create a complex variable with x as the real and y as the imaginary
			complex<double> cpt(xti, ytj);
			complex<double> z = cpt;
			for(int k = 0; k < maxiters; k++) {
				//mandlebrot set calculations (z -> z^2 + c)
				z = pow(z, 2) + cpt;
				if(abs(z) > 2) 
					break;
				//if we reach maxiters, that value is in the mandlebrot set
				//so we set it to 1, otherwise it stays 0
				if(k == maxiters)
					mandelbrot[i][j] = 1;	
			}
		}
	}
	// return mandelbrot;
};


int main (int argc, char** argv) {
	return 0;
}

    
