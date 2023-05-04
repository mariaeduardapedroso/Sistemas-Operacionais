//1
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int row[3];

    if (rank == 0) {
        printf("Matriz original:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Scatter(matrix, 3, MPI_INT, row, 3, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Processo %d: linha recebida: %d %d %d\n", rank, row[0], row[1], row[2]);

    MPI_Finalize();
    return 0;
}
//2
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int row[3];

    if (rank == 0) {
        printf("Matriz original:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Scatter(matrix, 3, MPI_INT, row, 3, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < 3; i++) {
        row[i] += 1;
    }

    int result[3][3];
    MPI_Gather(row, 3, MPI_INT, result, 3, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Matriz resultante:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
//3
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ROWS 3
#define COLS 3

int main(int argc, char** argv) {
    int rank, size, tag = 0;
    int a[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int b[ROWS][COLS] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int c[ROWS][COLS];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != ROWS) {
        fprintf(stderr, "O número de processos deve ser igual ao número de linhas das matrizes\n");
        MPI_Finalize();
        exit(1);
    }

    int row = rank;

    // cada processo soma a sua linha
    for (int j = 0; j < COLS; j++) {
        c[row][j] = a[row][j] + b[row][j];
    }

    // envia a linha para o processo 0
    if (rank != 0) {
        MPI_Send(&c[row][0], COLS, MPI_INT, 0, tag, MPI_COMM_WORLD);
    } else {
        // o processo 0 recebe as linhas dos outros processos e coloca na matriz de resultados
        for (int i = 1; i < size; i++) {
            MPI_Recv(&c[i][0], COLS, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
        }
        // imprime a matriz resultante
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}

