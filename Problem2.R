#nth: number of threads
#xl: left limit
#xr: right limit
#yb: bottom limit
#yt: top limit
#inc: distance between ticks on X, Y axes
#maxiters: maximum number of iterations
#sched: quoted string indicating which OMP scheduling method is to be used
#chunksize: OMP chunk size

.Call("rmandel", nth, xl, xr, yb, yt, inc, maxiters, sched, chunksize)
