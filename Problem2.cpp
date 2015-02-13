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

// int nth = 8,
// xl = -2, 
// xr = 1,
// yb = -1, 
// yt = 1,
// maxiters = 10,
// chunksize = 30;
// double inc = 0.1;
// string sched = "static";

// Yo, stefo after I briefly read Matloff's tutorial for Rcpp, I belive the return type/header
// see 5.5.6 of the tutorial
// should be
// RcppExport SEXP rmandel(blablabla)
SEXP rmandel(SEXP _nth, SEXP _xl, SEXP _xr, SEXP _yb, SEXP _yt, SEXP _inc, SEXP _maxiters, SEXP _sched, SEXP _chunksize) {
	
	_nth = coerceVector(_nth, INTSXP);
	int nth = INTEGER(_nth)[0];

	_xl = coerceVector(_xl, INTSXP);
	int xl = INTEGER(_xl)[0];

	_xr = coerceVector(_xr, INTSXP);
	int xr = INTEGER(_xr)[0];

	_yb = coerceVector(_yb, INTSXP);
	int yb = INTEGER(_yb)[0];

	_yt = coerceVector(_yt, INTSXP);
	int yt = INTEGER(_yt)[0];

	_inc = coerceVector(_inc, REALSXP);
	double inc = REAL(_inc)[0];

	_maxiters = coerceVector(_maxiters, INTSXP);
	int maxiters = INTEGER(_maxiters)[0];

	string sched = CHAR(STRING_ELT(_sched,0));

	_chunksize = coerceVector(_chunksize, INTSXP);
	int chunksize = INTEGER(_chunksize)[0];



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

	SEXP Rval;
	//create array init to 0 for mandelbrot set
	PROTECT(Rval = allocMatrix(INTSXP, nxticks, nyticks));
	UNPROTECT(1);
	double *rRval;
	rRval = REAL(Rval);
	// int mandelbrot[nxticks][nyticks];

	//handles the sched variable passed in which controls scheduling in OMP
    if(sched == "guided") {
        #pragma omp for schedule(guided)
    }
    else if(sched == "static") {
        #pragma omp for schedule(static)
    }
    else if(sched == "dynamic") {
        #pragma omp for schedule(dynamic) 
    }  	
    else if(sched == "runtime") {
        #pragma omp for schedule(runtime)
    }
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
					rRval[i + nyticks*j] = 1;	
			}
		}
	}
	return Rval;
};


int main (int argc, char** argv) {
	// rmandel(nth, xl, xr, yb, yt, inc, maxiters, sched, chunksize);
	return 0;
}

    
