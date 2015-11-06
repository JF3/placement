#define _GNU_SOURCE

#include<sched.h>
#include<stdio.h>
#include<omp.h>
#include<mpi.h>
#include<stdlib.h>
#include <unistd.h>


/**
Copyright (C) 2013-2015 JFEngels

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

int main (int argc, char* argv[])
{
	int impi, iomp;

	int myProc;
	int nProcs;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myProc);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);


	int nCoresInSystem;
	nCoresInSystem = sysconf( _SC_NPROCESSORS_ONLN );
	
	if (myProc == 0)
	{
		printf("Checking the placement of your job.\n");
		printf("by JFEngels (software (at) jfengels . de)\n\n");
		printf("This system seems to have %d cores.\n", nCoresInSystem);
		printf("mpi\tomp\tcore\n");
		printf("rank\tthread\n");
	}
	for (impi = 0; impi < nProcs; impi++)
	{
		MPI_Barrier( MPI_COMM_WORLD );

		if (impi != myProc)
			continue;

		for (iomp = 0; iomp < omp_get_max_threads(); iomp++)
		{
			#pragma omp parallel 
			{
				#pragma omp barrier
				if (iomp == omp_get_thread_num())
				{
	
					cpu_set_t cpuSet;
					sched_getaffinity(0, sizeof(cpu_set_t), &cpuSet);
				
					int i=0;

					printf("%d\t%d\t", impi, iomp);

					if (CPU_COUNT(&cpuSet) == nCoresInSystem)
					{
						printf("any");
					}
					else
					{
						for (i=0; i < CPU_SETSIZE; i++)
						{
							if (CPU_ISSET(i, &cpuSet))
							{
								printf("%2d ", i);
							}
						}
					}
					printf("\n");
				
					fflush(stdout);
				}
			}
		}
	}
	MPI_Barrier( MPI_COMM_WORLD );
	
	MPI_Finalize();
	exit(0);

}
