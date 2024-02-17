#include "mpi.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define COORDINATOR_PROCESS_NUMBER 4
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

void read_file(int rank, int* coordinator_sizes, int** topology) {
    char file_name[50];
	sprintf(file_name, "cluster%d.txt", rank);
	FILE *f = fopen(file_name, "r");

	if(f == NULL){
		perror("Can't open file!\n");	
	}

	fscanf(f, "%d", &coordinator_sizes[rank]);
	topology[rank] = calloc(coordinator_sizes[rank], sizeof(int));
	for (int i = 0; i < coordinator_sizes[rank]; i++) {
		fscanf(f, "%d", &topology[rank][i]);
	}

	fclose(f);
}

void sync_coordinators(int rank, int* coordinator_sizes, int** topology) {
	
    if (rank == 0) {
		MPI_Send(&coordinator_sizes[0], 1, MPI_INT, 3, 1, MPI_COMM_WORLD);
		log_message(rank, 3);
		MPI_Send(topology[0], coordinator_sizes[0], MPI_INT, 3, 2, MPI_COMM_WORLD);
		log_message(rank, 3);
		
        MPI_Status status;
		MPI_Recv(&coordinator_sizes[1], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[1] = calloc(coordinator_sizes[1], sizeof(int));
		MPI_Recv(topology[1], coordinator_sizes[1], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);

		MPI_Recv(&coordinator_sizes[2], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[2] = calloc(coordinator_sizes[2], sizeof(int));
		MPI_Recv(topology[2], coordinator_sizes[2], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);

		MPI_Recv(&coordinator_sizes[3], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[3] = calloc(coordinator_sizes[3], sizeof(int));
		MPI_Recv(topology[3], coordinator_sizes[3], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);
		

    } else if (rank == COORDINATOR_PROCESS_NUMBER - 1) {

		MPI_Status status;
		MPI_Recv(&coordinator_sizes[0], 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		topology[0] = calloc(coordinator_sizes[0], sizeof(int));
		MPI_Recv(topology[0], coordinator_sizes[0], MPI_INT, 0, 2, MPI_COMM_WORLD, &status);

		MPI_Send(&coordinator_sizes[0], 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
		log_message(rank, 2);
		MPI_Send(topology[0], coordinator_sizes[0], MPI_INT, 2, 2, MPI_COMM_WORLD);
		log_message(rank, 2);

		MPI_Send(&coordinator_sizes[3], 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
		log_message(rank, 2);
		MPI_Send(topology[3], coordinator_sizes[3], MPI_INT, 2, 2, MPI_COMM_WORLD);
		log_message(rank, 2);
		
		MPI_Recv(&coordinator_sizes[1], 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		topology[1] = calloc(coordinator_sizes[1], sizeof(int));
		MPI_Recv(topology[1], coordinator_sizes[1], MPI_INT, 2, 2, MPI_COMM_WORLD, &status);

		MPI_Send(&coordinator_sizes[1], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		log_message(rank, 0);
		MPI_Send(topology[1], coordinator_sizes[1], MPI_INT, 0, 2, MPI_COMM_WORLD);
		log_message(rank, 0);

		MPI_Recv(&coordinator_sizes[2], 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		topology[2] = calloc(coordinator_sizes[2], sizeof(int));
		MPI_Recv(topology[2], coordinator_sizes[2], MPI_INT, 2, 2, MPI_COMM_WORLD, &status);

		MPI_Send(&coordinator_sizes[2], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		log_message(rank, 0);
		MPI_Send(topology[2], coordinator_sizes[2], MPI_INT, 0, 2, MPI_COMM_WORLD);
		log_message(rank, 0);

		MPI_Send(&coordinator_sizes[3], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		log_message(rank, 0); 
		MPI_Send(topology[3], coordinator_sizes[3], MPI_INT, 0, 2, MPI_COMM_WORLD); 
		log_message(rank, 0);            

    } else if(rank == 1){
		MPI_Send(&coordinator_sizes[1], 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
		log_message(rank, 2);
		MPI_Send(topology[1], coordinator_sizes[1], MPI_INT, 2, 2, MPI_COMM_WORLD);
		log_message(rank, 2);
		
		MPI_Status status;
		MPI_Recv(&coordinator_sizes[3], 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		topology[3] = calloc(coordinator_sizes[3], sizeof(int));
		MPI_Recv(topology[3], coordinator_sizes[3], MPI_INT, 2, 2, MPI_COMM_WORLD, &status);

		MPI_Recv(&coordinator_sizes[0], 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		topology[0] = calloc(coordinator_sizes[0], sizeof(int));
		MPI_Recv(topology[0], coordinator_sizes[0], MPI_INT, 2, 2, MPI_COMM_WORLD, &status);

		MPI_Recv(&coordinator_sizes[2], 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		topology[2] = calloc(coordinator_sizes[2], sizeof(int));
		MPI_Recv(topology[2], coordinator_sizes[2], MPI_INT, 2, 2, MPI_COMM_WORLD, &status);	
	

    } else if(rank == 2) {

		MPI_Status status;
		MPI_Recv(&coordinator_sizes[0], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[0] = calloc(coordinator_sizes[0], sizeof(int));
		MPI_Recv(topology[0], coordinator_sizes[0], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);

		MPI_Recv(&coordinator_sizes[3], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[3] = calloc(coordinator_sizes[3], sizeof(int));
		MPI_Recv(topology[3], coordinator_sizes[3], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);

		MPI_Send(&coordinator_sizes[3], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		log_message(rank, 1);
		MPI_Send(topology[3], coordinator_sizes[3], MPI_INT, 1, 2, MPI_COMM_WORLD);
		log_message(rank, 1);

		MPI_Send(&coordinator_sizes[0], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		log_message(rank, 1);
		MPI_Send(topology[0], coordinator_sizes[0], MPI_INT, 1, 2, MPI_COMM_WORLD);
		log_message(rank, 1);

		MPI_Send(&coordinator_sizes[2], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		log_message(rank, 1);
		MPI_Send(topology[2], coordinator_sizes[2], MPI_INT, 1, 2, MPI_COMM_WORLD);
		log_message(rank, 1);

		MPI_Recv(&coordinator_sizes[1], 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
		topology[1] = calloc(coordinator_sizes[1], sizeof(int));
		MPI_Recv(topology[1], coordinator_sizes[1], MPI_INT, 1, 2, MPI_COMM_WORLD, &status);

		MPI_Send(&coordinator_sizes[1], 1, MPI_INT, 3, 1, MPI_COMM_WORLD);
		log_message(rank, 3);
		MPI_Send(topology[1], coordinator_sizes[1], MPI_INT, 3, 2, MPI_COMM_WORLD);
		log_message(rank, 3);

		MPI_Send(&coordinator_sizes[2], 1, MPI_INT, 3, 1, MPI_COMM_WORLD);
		log_message(rank, 3);
		MPI_Send(topology[2], coordinator_sizes[2], MPI_INT, 3, 2, MPI_COMM_WORLD);
		log_message(rank, 3);

	}	
	announce_topology(rank, coordinator_sizes, topology);
}

void sync_partition(int rank, int* coordinator_sizes, int** topology) {

	if(rank == 0) {
		MPI_Send(&coordinator_sizes[0], 1, MPI_INT, 3, 1, MPI_COMM_WORLD);
		log_message(rank, 3);
		MPI_Send(topology[0], coordinator_sizes[0], MPI_INT, 3, 2, MPI_COMM_WORLD);
		log_message(rank, 3);
		
        MPI_Status status;

		MPI_Recv(&coordinator_sizes[2], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[2] = calloc(coordinator_sizes[2], sizeof(int));
		MPI_Recv(topology[2], coordinator_sizes[2], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);

		MPI_Recv(&coordinator_sizes[3], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[3] = calloc(coordinator_sizes[3], sizeof(int));
		MPI_Recv(topology[3], coordinator_sizes[3], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);
	
	} else if (rank == COORDINATOR_PROCESS_NUMBER - 1) {

		MPI_Status status;
		MPI_Recv(&coordinator_sizes[0], 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		topology[0] = calloc(coordinator_sizes[0], sizeof(int));
		MPI_Recv(topology[0], coordinator_sizes[0], MPI_INT, 0, 2, MPI_COMM_WORLD, &status);

		MPI_Send(&coordinator_sizes[0], 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
		log_message(rank, 2);
		MPI_Send(topology[0], coordinator_sizes[0], MPI_INT, 2, 2, MPI_COMM_WORLD);
		log_message(rank, 2);

		MPI_Send(&coordinator_sizes[3], 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
		log_message(rank, 2);
		MPI_Send(topology[3], coordinator_sizes[3], MPI_INT, 2, 2, MPI_COMM_WORLD);
		log_message(rank, 2);

		MPI_Recv(&coordinator_sizes[2], 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		topology[2] = calloc(coordinator_sizes[2], sizeof(int));
		MPI_Recv(topology[2], coordinator_sizes[2], MPI_INT, 2, 2, MPI_COMM_WORLD, &status);

		MPI_Send(&coordinator_sizes[2], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		log_message(rank, 0);
		MPI_Send(topology[2], coordinator_sizes[2], MPI_INT, 0, 2, MPI_COMM_WORLD);
		log_message(rank, 0);

		MPI_Send(&coordinator_sizes[3], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		log_message(rank, 0);
		MPI_Send(topology[3], coordinator_sizes[3], MPI_INT, 0, 2, MPI_COMM_WORLD); 
		log_message(rank, 0);            

    } else if(rank == 2) {

		MPI_Status status;
		MPI_Recv(&coordinator_sizes[0], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[0] = calloc(coordinator_sizes[0], sizeof(int));
		MPI_Recv(topology[0], coordinator_sizes[0], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);

		MPI_Recv(&coordinator_sizes[3], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		topology[3] = calloc(coordinator_sizes[3], sizeof(int));
		MPI_Recv(topology[3], coordinator_sizes[3], MPI_INT, 3, 2, MPI_COMM_WORLD, &status);

		MPI_Send(&coordinator_sizes[2], 1, MPI_INT, 3, 1, MPI_COMM_WORLD);
		log_message(rank, 3);
		MPI_Send(topology[2], coordinator_sizes[2], MPI_INT, 3, 2, MPI_COMM_WORLD);
		log_message(rank, 3);

	}


	announce_topology(rank, coordinator_sizes, topology);
}

void sync_workers(int rank, int* coordinator_sizes, int** topology) {
	for (int i = 0; i < coordinator_sizes[rank]; i++) {
		
		MPI_Send(&rank, 1, MPI_INT, topology[rank][i], 4, MPI_COMM_WORLD);
		log_message(rank, topology[rank][i]);

		for (int j = 0; j < COORDINATOR_PROCESS_NUMBER; j++) {
			MPI_Send(&coordinator_sizes[j], 1, MPI_INT, topology[rank][i], 1, MPI_COMM_WORLD);
			log_message(rank, topology[rank][i]);

			MPI_Send(topology[j], coordinator_sizes[j], MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD);
			log_message(rank, topology[rank][i]);
		}
	}
}

void receive_topology(int* parent, int* coordinator_sizes, int** topology, int rank) {
    
	MPI_Recv(parent, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	for (int i = 0; i < COORDINATOR_PROCESS_NUMBER; i++) {
		MPI_Recv(&coordinator_sizes[i], 1, MPI_INT, *parent, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		topology[i] = calloc(coordinator_sizes[i], sizeof(int));
		MPI_Recv(topology[i], coordinator_sizes[i], MPI_INT, *parent, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	announce_topology(rank, coordinator_sizes, topology);
}

void announce_topology(int rank, int* coordinator_sizes, int** topology) {
	printf("%d -> ", rank);
	for (int i = 0; i < COORDINATOR_PROCESS_NUMBER; i++) {
		if(coordinator_sizes[i] != 0){
			printf("%d:", i);
			for (int j = 0; j < coordinator_sizes[i]; j++) {
				if (j == coordinator_sizes[i] - 1) { 
					printf("%d ", topology[i][j]);
				} else if (j == coordinator_sizes[i] - 1 && i == COORDINATOR_PROCESS_NUMBER - 1) {
					printf("%d", topology[i][j]);
				} else {
					printf("%d,", topology[i][j]);
				}
			}
		}
	}
	printf("\n");
}

void process_arr_index(int** starts, int** ends, int num_workers, int array_size) {
	int num_tasks = num_workers + COORDINATOR_PROCESS_NUMBER;
	*starts = calloc(num_tasks, sizeof(int));
	*ends = calloc(num_tasks, sizeof(int));

	for (int i = 4; i < num_tasks; i++) {
		(*starts)[i] = (i - COORDINATOR_PROCESS_NUMBER) * (double)array_size / num_workers;
	 	(*ends)[i] = min(((i - COORDINATOR_PROCESS_NUMBER) + 1) * (double)array_size / num_workers, array_size);
	}
}

void process_task(int size, int parent, int rank) {
    int* arr = calloc(100, sizeof(int));

    MPI_Recv(arr, size, MPI_INT, parent, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    for (int i = 0; i < size; i++) {
        arr[i] *= 5;
    }

    MPI_Send(arr, size, MPI_INT, parent, 2, MPI_COMM_WORLD);
    log_message(rank, parent);
    free(arr);
}

void log_message(int src, int dest) {
	printf("M(%d,%d)\n", src, dest);
}

//run -> mpirun --oversubscribe -np 12 ./tema3 12 1
int main (int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int parent = 0;
	int* coordinator_sizes = calloc(COORDINATOR_PROCESS_NUMBER, sizeof(int));
	int** topology = calloc(COORDINATOR_PROCESS_NUMBER, sizeof(int*));

	if(atoi(argv[2]) == 0 || atoi(argv[2]) == 1){
		if (rank < 4) {
			parent = rank;
			read_file(rank, coordinator_sizes, topology);
			sync_coordinators(rank, coordinator_sizes, topology);
			sync_workers(rank, coordinator_sizes, topology);
		} else {
			receive_topology(&parent, coordinator_sizes, topology, rank);
		}

		//astept ca topologia sa fie completa pe fiecare proces
		MPI_Barrier(MPI_COMM_WORLD);

		int array_size = atoi(argv[1]);
		int *array = calloc(array_size, sizeof(int));

		int num_workers = (coordinator_sizes[0] + coordinator_sizes[1] + coordinator_sizes[2] + coordinator_sizes[3]);
		int* starts;
		int* ends;
		
		if (rank == 0) {

			for (int i = 0; i < array_size; i++) {
				array[i] = array_size - i - 1;
			}

			process_arr_index(&starts, &ends, num_workers, array_size);

			for (int i = 0; i < coordinator_sizes[rank]; i++) {
				int start = starts[topology[rank][i]];
				int size = ends[topology[rank][i]] - start;

				MPI_Send(array + start, size, MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD);
				log_message(rank, topology[rank][i]);
				MPI_Recv(array + start, size, MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}

			MPI_Send(array, array_size, MPI_INT, 3, 2, MPI_COMM_WORLD);
			log_message(rank, 3);

			MPI_Recv(array, array_size, MPI_INT, 3, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			printf("Rezultat: ");
			for (int i = 0; i < array_size - 1; i++) {
				printf("%d ", array[i]);
			}
			printf("%d\n", array[array_size - 1]);

		} else if (rank == 3) {

			MPI_Recv(array, array_size, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
			process_arr_index(&starts, &ends, num_workers, array_size);

			
			for (int i = 0; i < coordinator_sizes[rank]; i++) {
				int start = starts[topology[rank][i]];
				int size = ends[topology[rank][i]] - start;
				MPI_Send(array + start, size, MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD);
				log_message(rank, topology[rank][i]);
				MPI_Recv(array + start, size, MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}

			MPI_Send(array, array_size, MPI_INT, 2, 2, MPI_COMM_WORLD);
			log_message(rank,2);

			MPI_Recv(array, array_size, MPI_INT, 2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			MPI_Send(array, array_size, MPI_INT, 0, 2, MPI_COMM_WORLD);
			log_message(rank, 0);
		
		} else if (rank == 2) {
			
			MPI_Recv(array, array_size, MPI_INT, 3, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			process_arr_index(&starts, &ends, num_workers, array_size);

			for (int i = 0; i < coordinator_sizes[rank]; i++) {
				int start = starts[topology[rank][i]];
				int size = ends[topology[rank][i]] - start;

				MPI_Send(array + start, size, MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD);
				log_message(rank, topology[rank][i]);
				MPI_Recv(array + start, size, MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}

			MPI_Send(array, array_size, MPI_INT, 1, 2, MPI_COMM_WORLD);
			log_message(rank, 1);

			MPI_Recv(array, array_size, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			MPI_Send(array, array_size, MPI_INT, 3, 2, MPI_COMM_WORLD);
			log_message(rank, 3);
		
		} else if (rank == 1){
			MPI_Recv(array, array_size, MPI_INT, 2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			process_arr_index(&starts, &ends, num_workers, array_size);

			for (int i = 0; i < coordinator_sizes[rank]; i++) {
				int start = starts[topology[rank][i]];
				int size = ends[topology[rank][i]] - start;

				MPI_Send(array + start, size, MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD);
				log_message(rank, topology[rank][i]);
				MPI_Recv(array + start, size, MPI_INT, topology[rank][i], 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}

			MPI_Send(array, array_size, MPI_INT, 2, 2, MPI_COMM_WORLD);
			log_message(rank, 2);

		}  else {
			int start = (rank - COORDINATOR_PROCESS_NUMBER) * (double)array_size / num_workers;
			int end = min(((rank - COORDINATOR_PROCESS_NUMBER) + 1) * (double)array_size / num_workers, array_size);
			process_task(end - start, parent, rank);
		}

		if (rank < 4) {
			free(starts);
    		free(ends);
    		free(array);
		}

	} else if(atoi(argv[2]) == 2){
		if (rank < 4) {
			parent = rank;
			read_file(rank, coordinator_sizes, topology);
			sync_partition(rank, coordinator_sizes, topology);
		
			sync_workers(rank, coordinator_sizes, topology);
		} else {
			receive_topology(&parent, coordinator_sizes, topology, rank);
			
		}

		MPI_Barrier(MPI_COMM_WORLD);
	}
	
    free(coordinator_sizes);
    for (int i = 0; i < COORDINATOR_PROCESS_NUMBER; i++) {
        free(topology[i]);
    }
    free(topology);
	
    MPI_Finalize();
}
