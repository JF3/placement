intel.intel:
	mpiicc main.c -o placement.intel.intel -openmp

gnu.intel:
	mpigcc main.c -o placement.gnu.intel -fopenmp

intel.open:
	icc main.c -o placement.intel.open -openmp

gnu.open:
	mpicc main.c -o placement.gnu.open -fopenmp
