#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"
#define MASTER 0

int main(int argc, char** argv){
    int array[6] = {1,2,3,4,5,6};
    int dummy[6];
    int flag = 1;
     
    int rank, size;

    MPI_Init(&argc, &argv);
	
	MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
 
    if(rank == MASTER){
        int* recv;
        recv=(int*)malloc(sizeof(int));
        MPI_Scatter(array, 1, MPI_INT, recv, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        printf("Tutti hanno stampato\n");
        printf("Rank [%d]: recn num %d\n", rank, recv[0]);
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Gather(recv, 1, MPI_INT, dummy, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        printf("Stampa dummy\n");
        for(int i=0; i<6; i++){
            printf("%d\n", dummy[i]);
        }
        printf("Adesso breakko\n");
        flag = 0;
    }
    else{
        int* recv;
        recv=(int*)malloc(sizeof(int));
        MPI_Scatter(MPI_IN_PLACE, 1, MPI_INT, recv, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        printf("Rank [%d]: recn num %d\n", rank, recv[0]);
        MPI_Barrier(MPI_COMM_WORLD);
        
        MPI_Gather(recv, 1, MPI_INT, dummy, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        flag= 0;
    }    

    MPI_Finalize();
}