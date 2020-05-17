#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int auctionCapacity;
    MPI_Comm_size(MPI_COMM_WORLD, &auctionCapacity);

    printf("Started %d\n", rank);

    srand(time(NULL) + rank);

    // Min 2 process required
    if (auctionCapacity < 2) {
        fprintf(stderr, "auction capacity than 1 for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    int num_parts_report = 0;
    int report[10];

    if (rank == 1) {
        int received = 0;
        int report[10];
 	    int summ = 0;
            MPI_Status status;
            MPI_Recv(
                    /* data         = */ report,
                    /* count        = */ 10,
                    /* datatype     = */ MPI_INT,
                    /* source       = */ 0,
                    /* tag          = */ 10,
                    /* communicator = */ MPI_COMM_WORLD,
                    /* status       = */ &status);
            printf("Received full report\n");
            for (int i=0; i<10; i++) {
                summ += report[i];
	        printf("%i> : %i\n", i+1, report[i]);
            }
            printf("Final score %i\n", summ);
            printf("\n");
     

    } if (rank == 0)  {

	for (int i=0; i<10; i++) {
        int part_report = rand() % 1000;
	    printf("part report %i : %i\n", i+1, part_report);
	    report[i] = part_report;
	}
        MPI_Send(
                /* data         = */ report,
                /* count        = */ 10,
                /* datatype     = */ MPI_INT,
                /* destination  = */ 1,
                /* tag          = */ 10,
                /* communicator = */ MPI_COMM_WORLD);
         
    }
    MPI_Finalize();
}
