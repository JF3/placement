**placement** is a tool to check the placement or pinning of MPI/OpenMP hybrid
jobs. 

Compilation
===========

Please edit the Makefile according to your environment. Some combinations of 
compiler and MPI library are already in there.

Running
=======

Usually you can run the code with
```
mpirun ./placement.COMPILER.MPILIB
```

The output then looks like (8 MPI processes and 6 OpenMP threads using openmpi):
```
Checking the placement of your job.
by JFEngels (software (at) jfengels . de)

This system seems to have 48 cores.
mpi     omp     core
rank    thread
0       0        0  1  2  3  4  5  6  7  8  9 10 11 
0       1        0  1  2  3  4  5  6  7  8  9 10 11 
0       2        0  1  2  3  4  5  6  7  8  9 10 11 
0       3        0  1  2  3  4  5  6  7  8  9 10 11 
0       4        0  1  2  3  4  5  6  7  8  9 10 11 
0       5        0  1  2  3  4  5  6  7  8  9 10 11 
1       0       12 13 14 15 16 17 18 19 20 21 22 23 
1       1       12 13 14 15 16 17 18 19 20 21 22 23 
1       2       12 13 14 15 16 17 18 19 20 21 22 23 
1       3       12 13 14 15 16 17 18 19 20 21 22 23 
1       4       12 13 14 15 16 17 18 19 20 21 22 23 
1       5       12 13 14 15 16 17 18 19 20 21 22 23 
2       0       24 25 26 27 28 29 30 31 32 33 34 35 
2       1       24 25 26 27 28 29 30 31 32 33 34 35 
2       2       24 25 26 27 28 29 30 31 32 33 34 35 
2       3       24 25 26 27 28 29 30 31 32 33 34 35 
2       4       24 25 26 27 28 29 30 31 32 33 34 35 
2       5       24 25 26 27 28 29 30 31 32 33 34 35 
3       0       36 37 38 39 40 41 42 43 44 45 46 47 
3       1       36 37 38 39 40 41 42 43 44 45 46 47 
3       2       36 37 38 39 40 41 42 43 44 45 46 47 
3       3       36 37 38 39 40 41 42 43 44 45 46 47 
3       4       36 37 38 39 40 41 42 43 44 45 46 47 
3       5       36 37 38 39 40 41 42 43 44 45 46 47 
4       0        0  1  2  3  4  5  6  7  8  9 10 11 
4       1        0  1  2  3  4  5  6  7  8  9 10 11 
4       2        0  1  2  3  4  5  6  7  8  9 10 11 
4       3        0  1  2  3  4  5  6  7  8  9 10 11 
4       4        0  1  2  3  4  5  6  7  8  9 10 11 
4       5        0  1  2  3  4  5  6  7  8  9 10 11 
5       0       12 13 14 15 16 17 18 19 20 21 22 23 
5       1       12 13 14 15 16 17 18 19 20 21 22 23 
5       2       12 13 14 15 16 17 18 19 20 21 22 23 
5       3       12 13 14 15 16 17 18 19 20 21 22 23 
5       4       12 13 14 15 16 17 18 19 20 21 22 23 
5       5       12 13 14 15 16 17 18 19 20 21 22 23 
6       0       24 25 26 27 28 29 30 31 32 33 34 35 
6       1       24 25 26 27 28 29 30 31 32 33 34 35 
6       2       24 25 26 27 28 29 30 31 32 33 34 35 
6       3       24 25 26 27 28 29 30 31 32 33 34 35 
6       4       24 25 26 27 28 29 30 31 32 33 34 35 
6       5       24 25 26 27 28 29 30 31 32 33 34 35 
7       0       36 37 38 39 40 41 42 43 44 45 46 47 
7       1       36 37 38 39 40 41 42 43 44 45 46 47 
7       2       36 37 38 39 40 41 42 43 44 45 46 47 
7       3       36 37 38 39 40 41 42 43 44 45 46 47 
7       4       36 37 38 39 40 41 42 43 44 45 46 47 
7       5       36 37 38 39 40 41 42 43 44 45 46 47 
```
In the column called core you find the index of the core(s) the thread may 
run on. If the thread may run on all cores there will be the word any. In the 
example above the thread 0,0 may run on cores 0-11, which correspond to all 
cores on the first socket on this machine.
