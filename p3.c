#include "mpi.h"
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
int rank, size;
char hostname[1024];
int msgtag;
int A[10],B[10];
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
msgtag = 1234;
if(rank==0){
	for(int i=0;i<10;i++){
		A[i]=i+1;
	}
	MPI_Send(&A,10,MPI_INT,1,msgtag,MPI_COMM_WORLD);
	MPI_Recv(&B,10,MPI_INT,1,msgtag,MPI_COMM_WORLD,&status);
	printf("array B received is\n");
	for(int j=0;j<10;j++){
		printf("%d\n",B[j]);
	}
}
if(rank==1){
	MPI_Recv(&A,10,MPI_INT,0,msgtag,MPI_COMM_WORLD,&status);
	for(int i=0;i<10;i++){
		B[i]=10*A[i];
	}
	MPI_Send(&B,10,MPI_INT,0,msgtag,MPI_COMM_WORLD);
}
MPI_Finalize();
return 0;
}