#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"
#define MASTER 0

typedef struct 
{
	double _x;
	double _y;
} Point;

int main(int argc, char** argv){
    Point num[300000];

    int* array;
    array = malloc(sizeof(int)*30);

    int* dummy;
    int flag = 1;
     
    int rank, size;

    MPI_Init(&argc, &argv);
	
	MPI_Status status;
    MPI_Request request;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(int i=0; i<30; i++){
        array[i] = i;
    }
    
 
    if(rank == MASTER){
        int* recv;
        recv=(int*)malloc(sizeof(int)*30);
        dummy=(int*)malloc(sizeof(int)*30);
        
        MPI_Scatter(array, 5, MPI_INT, recv, 5, MPI_INT, MASTER, MPI_COMM_WORLD);
        printf("Rank [%d]: recn num %d\n", rank, recv[0]);
        MPI_Barrier(MPI_COMM_WORLD);
        printf("Tutti hanno stampato\n");

        MPI_Gather(recv, 5, MPI_INT, dummy, 5, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);

        printf("Stampa dummy\n");
        for(int i=0; i<30; i++){
            printf("%d\n", dummy[i]);
        }
        printf("Adesso breakko\n");
        flag = 0;
    }
    else{
        int* recv;
        recv=(int*)malloc(sizeof(int)*30);
        dummy=(int*)malloc(sizeof(int)*30);
        
        MPI_Scatter(NULL, 5, MPI_INT, recv, 5, MPI_INT, MASTER, MPI_COMM_WORLD);
        printf("Rank [%d]: recn num %d\n", rank, recv[0]);
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Gather(recv, 5, MPI_INT, NULL, 5, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        flag= 0;
    }    

    MPI_Finalize();
}