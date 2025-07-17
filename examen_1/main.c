#include <stdio.h>
#include <string.h>

#define MAX_AUTOS 100
#define MODELO_LEN 30

typedef struct {
    int registro;
    char modelo[MODELO_LEN];
    int potencia;
} Auto;

int main() {
    Auto autos[MAX_AUTOS];
    int num_autos = 0;
    int opcion;

    do {
        // Menú principal
        printf("\n--- Gestión de Autos ---\n");
        printf("1. Añadir elemento\n");
        printf("2. Listar\n");
        printf("3. Buscar\n");
        printf("4. Salir\n");
        printf("Elige una opción: ");
        if (scanf("%d", &opcion) != 1) {
            // Lectura fallida: limpiamos buffer y seguimos
            while (getchar() != '\n');
            opcion = 0;
        }
        getchar(); // consumir '\n' residual

        switch (opcion) {
            case 1: {
                char respuesta;
                do {
                    if (num_autos >= MAX_AUTOS) {
                        printf("El arreglo está lleno. No se pueden añadir más autos.\n");
                        break;
                    }
                    // Lectura de datos del coche
                    printf("\nRegistro (%d): ", num_autos + 1);
                    printf("Introduce el número de registro: ");
                    scanf("%d", &autos[num_autos].registro);
                    getchar();

                    printf("Introduce el modelo: ");
                    fgets(autos[num_autos].modelo, MODELO_LEN, stdin);
                    // quitamos salto de línea si existe
                    size_t len = strlen(autos[num_autos].modelo);
                    if (len > 0 && autos[num_autos].modelo[len-1] == '\n') {
                        autos[num_autos].modelo[len-1] = '\0';
                    }

                    printf("Introduce la potencia (CV): ");
                    scanf("%d", &autos[num_autos].potencia);
                    getchar();

                    num_autos++;
                    printf("¿Deseas añadir otro coche? (s/n): ");
                    respuesta = getchar();
                    while (getchar() != '\n'); // limpiar buffer
                } while ((respuesta == 's' || respuesta == 'S') && num_autos < MAX_AUTOS);
                break;
            }

            case 2:
                // Listar todos los coches
                if (num_autos == 0) {
                    printf("\nNo hay coches registrados.\n");
                } else {
                    printf("\nLista de coches registrados:\n");
                    for (int i = 0; i < num_autos; i++) {
                        printf("Auto %d -- Registro: %d | Modelo: %s | Potencia: %d CV\n",
                               i + 1,
                               autos[i].registro,
                               autos[i].modelo,
                               autos[i].potencia);
                    }
                }
                break;

            case 3: {
                // Buscar por número de registro
                if (num_autos == 0) {
                    printf("\nNo hay coches registrados.\n");
                } else {
                    int reg_buscar;
                    int encontrado = 0;
                    printf("\nIntroduce el número de registro a buscar: ");
                    scanf("%d", &reg_buscar);
                    getchar();

                    for (int i = 0; i < num_autos; i++) {
                        if (autos[i].registro == reg_buscar) {
                            printf("Registro: %d | Modelo: %s | Potencia: %d CV\n",
                                   autos[i].registro,
                                   autos[i].modelo,
                                   autos[i].potencia);
                            encontrado = 1;
                            break;
                        }
                    }
                    if (!encontrado) {
                        printf("No se encontró ningún coche con registro %d.\n", reg_buscar);
                    }
                }
                break;
            }

            case 4:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción no válida. Intenta de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}
