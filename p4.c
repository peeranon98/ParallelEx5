#include "mpi.h"
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
int rank, size,msgtag;
char hostname[1024];
int A[8][8];
int sum1 = 0;
int sum2 = 0;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
for(int i=0;i<8;i++){
	for(int j=0;j<8;j++){
		A[i][j]=i+j;
	}
}
msgtag = 1234;
if(rank==0){
	MPI_Send(&A,32,MPI_INT,1,msgtag,MPI_COMM_WORLD);
	MPI_Send(&A,32,MPI_INT,2,msgtag,MPI_COMM_WORLD);
	MPI_Recv(&sum1,1,MPI_INT,1,msgtag,MPI_COMM_WORLD,&status);
	MPI_Recv(&sum2,1,MPI_INT,2,msgtag,MPI_COMM_WORLD,&status);
	printf("Total sum is %d\n",(sum1+sum2));
}
else{
	int start,stop;
	int sum = 0;
	MPI_Recv(&A,32,MPI_INT,0,msgtag,MPI_COMM_WORLD,&status);
	if(rank==1){
		start = 0;
		stop = 4;
	}
	else{
		start = 4;
		stop = 8;
	}
	for(int i=start;i<stop;i++){
		for(int j=0;j<8;j++){
			sum = sum+A[i][j];
		}
	}
	printf("Sum for %d = %d\n",rank,sum);
	MPI_Send(&sum,1,MPI_INT,0,msgtag,MPI_COMM_WORLD);
}
MPI_Finalize();
return 0;
}