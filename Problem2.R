library(Rcpp)
dyn.load("Problem2.so")

#nth: number of threads
nth <- 8
#xl: left limit
xl <- -2
#xr: right limit
xr <- 1
#yb: bottom limit
yb <- -1
#yt: top limit
yt <- 1
#inc: distance between ticks on X, Y axes
inc <- 0.01
#maxiters: maximum number of iterations
maxiters <- 10
#sched: quoted string indicating which OMP scheduling method is to be used
sched = "static"
#chunksize: OMP chunk size
chunksize <- 1000


m <- .Call("rmandel", nth, xl, xr, yb, yt, inc, maxiters, sched, chunksize)

