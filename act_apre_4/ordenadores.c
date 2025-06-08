#include <stdio.h>
#include <string.h>

#define MAX_ORDENADORES 100
#define MAX_LEN 50

// Estructura para almacenar informacion de un ordenador
typedef struct {
    char marca[MAX_LEN + 1];
    char modelo[MAX_LEN + 1];
    int memoria;          // en GB
    int disco;            // en GB
    char tipo_procesador[MAX_LEN + 1];
    float precio;
} Ordenador;

void leerCadena(char *buffer, int largo) {
    if (fgets(buffer, largo + 1, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

void rellenar(Ordenador ordenadores[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nOrdenador #%d\n", i + 1);
        printf("Marca: ");
        leerCadena(ordenadores[i].marca, MAX_LEN);

        printf("Modelo: ");
        leerCadena(ordenadores[i].modelo, MAX_LEN);

        printf("Memoria (GB): ");
        while (scanf("%d", &ordenadores[i].memoria) != 1) {
            printf("Entrada no valida. Ingrese un numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        printf("Disco (GB): ");
        while (scanf("%d", &ordenadores[i].disco) != 1) {
            printf("Entrada no valida. Ingrese un numero: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        printf("Tipo de procesador: ");
        leerCadena(ordenadores[i].tipo_procesador, MAX_LEN);
    }
}

int precioProcesador(const char *tipo) {
    if (strcmp(tipo, "PIV-2.4") == 0) return 100;
    if (strcmp(tipo, "PIV-2.0") == 0) return 90;
    if (strcmp(tipo, "PIV-1.8") == 0) return 75;
    if (strcmp(tipo, "Ath-2.1") == 0) return 93;
    if (strcmp(tipo, "Ath-2.3") == 0) return 98;
    return 90;
}

void calcular(Ordenador ordenadores[], int n) {
    for (int i = 0; i < n; i++) {
        int pp = precioProcesador(ordenadores[i].tipo_procesador);
        ordenadores[i].precio = 400 + 10 * ordenadores[i].memoria +
                                15 * ordenadores[i].disco + pp;
    }
}

void mostrar(const Ordenador ordenadores[], int n) {
    printf("\n+--------+------------+---------+-------+-------+--------+\n");
    printf("| %-6s | %-10s | %-7s | %-5s | %-5s | %-6s |\n", "Marca", "Modelo", "Memoria", "Disco", "Proc.", "Precio");
    printf("+--------+------------+---------+-------+-------+--------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-6s | %-10s | %7d | %5d | %-5s | %6.2f |\n",
               ordenadores[i].marca,
               ordenadores[i].modelo,
               ordenadores[i].memoria,
               ordenadores[i].disco,
               ordenadores[i].tipo_procesador,
               ordenadores[i].precio);
    }
    printf("+--------+------------+---------+-------+-------+--------+\n");
}

int main() {
    int n;
    Ordenador ordenadores[MAX_ORDENADORES];

    printf("Cuantos ordenadores desea ingresar (1-%d): ", MAX_ORDENADORES);
    while (scanf("%d", &n) != 1 || n < 1 || n > MAX_ORDENADORES) {
        printf("Valor no valido. Ingrese un numero entre 1 y %d: ", MAX_ORDENADORES);
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    rellenar(ordenadores, n);
    calcular(ordenadores, n);
    mostrar(ordenadores, n);

    return 0;
}
