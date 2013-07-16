#define _GNU_SOURCE

#include<sched.h>
#include<stdio.h>
#include<omp.h>
#include<mpi.h>

int main (int argc, char* argv[])
{
	int impi, iomp, jomp;

	int myProc;
	int nProcs;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myProc);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
	
	if (myProc == 0)
		printf("mpi\tomp\tcore\n");
	for (impi = 0; impi < nProcs; impi++)
	{
		MPI_Barrier( MPI_COMM_WORLD );

		if (impi != myProc)
			continue;

		for (iomp = 0; iomp < omp_get_max_threads(); iomp++)
		{
			#pragma omp parallel //for schedule(dynamic,1)
			{
				#pragma omp barrier
				if (iomp == omp_get_thread_num())
				{
	
					cpu_set_t cpuSet;
					sched_getaffinity(0, sizeof(cpu_set_t), &cpuSet);
				
					int i=0;
					int cpunum;

					for (i=0; i < CPU_SETSIZE; i++)
					{
						if (CPU_ISSET(i, &cpuSet))
						{
							cpunum=i;
						}
					}
				
					if (CPU_COUNT(&cpuSet)==1)
						printf("%d\t%d\t%d\n", impi, iomp, cpunum);
					else
						printf("%d\t%d\t%c\n", impi, iomp, '-');
	
					fflush(stdout);
				}
			}
		}
	}
	MPI_Barrier( MPI_COMM_WORLD );
	
	if (myProc == 0)
		printf("by JFEngels (mail@jfengels.de)\n");

	MPI_Finalize();
	exit(0);

}
