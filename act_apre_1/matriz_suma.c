#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 5
#define N 3
#define MAX_RANDOM 30

// Function to print a matrix
void printMatrix(int rows, int cols, int matrix[rows][cols], const char* name) {
    printf("Matriz %s:\n", name);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int A[M][N];          // Matrix A (5x3)
    int B[N][M];          // Matrix B (3x5)
    int BT[M][N];         // Transpose of B (5x3)
    int result[M][N];     // Result of A + BT (5x3)
    
    // Initialize random seed
    srand(time(NULL));
    
    // Generate random values for Matrix A
    printf("Generando matrices con valores aleatorios entre 1 y %d...\n\n", MAX_RANDOM);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % MAX_RANDOM + 1;
        }
    }
    
    // Generate random values for Matrix B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            B[i][j] = rand() % MAX_RANDOM + 1;
        }
    }
    
    // Calculate transpose of B
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            BT[i][j] = B[j][i];
        }
    }
    
    // Calculate A + BT
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = A[i][j] + BT[i][j];
        }
    }
    
    // Print matrices
    printMatrix(M, N, A, "A (5x3)");
    printMatrix(N, M, B, "B (3x5)");
    printMatrix(M, N, BT, "B transpuesta (5x3)");
    printMatrix(M, N, result, "A + BT (5x3)");
    
    return 0;
} 