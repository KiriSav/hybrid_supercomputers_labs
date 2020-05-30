#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int size, rank, tmp;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        int result_array[size-1];
        int recv_count = 0;
        for(int i = 0; i < size; i++){
            if (i != 0) {
                MPI_Recv(&tmp,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD, &status);
                result_array[recv_count] = tmp;
                recv_count++;
            }
        }
        printf("result_array = ");
        for (int i = 0; i < size-1; i++) {
            printf("%i ", result_array[i]);
        }
        printf("\n");
      } else {
        int value = rank; 
        printf("process %i \n", rank);
        MPI_Send(&value,1,MPI_INT,0,0,MPI_COMM_WORLD);
      }


    MPI_Finalize();
    return 0;
}