#include "mpi.h"
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
int rank, size;
char hostname[1024];
int msgtag,x,x2;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
msgtag = 1234;
if(rank==0){
	x = 99;
	MPI_Send(&x,1,MPI_INT,1,msgtag,MPI_COMM_WORLD);
	printf("processor %d sent %d\n",rank,x );
	MPI_Recv(&x2,1,MPI_INT,1,msgtag,MPI_COMM_WORLD,&status);
	printf("processor %d got %d\n",rank,x );
	printf(" %d squared equal %d\n",x,x2 );
}
if(rank==1){
	MPI_Recv(&x,1,MPI_INT,0,msgtag,MPI_COMM_WORLD,&status);
	printf("processor %d got %d\n",rank,x );
	x2 = x*x;
	MPI_Send(&x2,1,MPI_INT,0,msgtag,MPI_COMM_WORLD);
	printf("processor %d sent %d\n",rank,x2);
}
MPI_Finalize();
return 0;
}