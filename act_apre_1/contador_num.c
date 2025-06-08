#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MAX_RANDOM 20

int main() {
    int VEC[SIZE];
    int NUM;
    int count = 0;
    
    // Initialize random seed
    srand(time(NULL));
    
    // Generate random values for the array (1 to 20)
    printf("Generando arreglo con valores aleatorios entre 1 y %d...\n", MAX_RANDOM);
    for (int i = 0; i < SIZE; i++) {
        VEC[i] = rand() % MAX_RANDOM + 1;
    }
    
    // Display the generated array
    printf("Arreglo generado:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", VEC[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    
    // Ask for the number to search
    printf("\nIngrese el número a buscar (entre 1 y %d): ", MAX_RANDOM);
    scanf("%d", &NUM);
    
    // Count occurrences of NUM in VEC
    for (int i = 0; i < SIZE; i++) {
        if (VEC[i] == NUM) {
            count++;
        }
    }
    
    printf("El número %d aparece %d veces en el arreglo.\n", NUM, count);
    
    return 0;
} 