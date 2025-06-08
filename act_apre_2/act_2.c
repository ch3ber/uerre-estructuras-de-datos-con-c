#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALUMNOS 100
#define MAX_LONG  30

// Definición del registro Alumno
typedef struct {
    int matricula;
    char nombre[MAX_LONG + 1];
    char carrera[MAX_LONG + 1];
} Alumno;

// Prototipos de funciones
void agregarAlumnos(Alumno alumnos[], int *contador);
void buscarAlumno(const Alumno alumnos[], int contador);
void reporteAlumnos(const Alumno alumnos[], int contador);
void leerCadena(char *buffer, int largo);

int main() {
    Alumno alumnos[MAX_ALUMNOS];
    int contador = 0;   // Número de alumnos actualmente registrados
    int opcion;

    do {
        printf("\n=== Menú ===\n");
        printf("1. Registro de alumnos\n");
        printf("2. Buscar alumno por matrícula\n");
        printf("3. Reporte de alumnos registrados\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        if (scanf("%d", &opcion) != 1) {
            // Si la entrada no es numérica, limpiar buffer y continuar
            printf("Entrada no válida. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); // Limpiar resto de la línea

        switch (opcion) {
            case 1:
                agregarAlumnos(alumnos, &contador);
                break;
            case 2:
                buscarAlumno(alumnos, contador);
                break;
            case 3:
                reporteAlumnos(alumnos, contador);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    return 0;
}

// Función para leer una cadena de hasta 'largo' caracteres (sin incluir '\n')
void leerCadena(char *buffer, int largo) {
    if (fgets(buffer, largo + 1, stdin) != NULL) {
        // Eliminar salto de línea al final, si existe
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

// Opción 1: Registrar alumnos hasta que el usuario decida parar
void agregarAlumnos(Alumno alumnos[], int *contador) {
    char opcion = 's';

    while (opcion == 's' || opcion == 'S') {
        if (*contador >= MAX_ALUMNOS) {
            printf("El registro está lleno (máximo %d alumnos).\n", MAX_ALUMNOS);
            break;
        }

        Alumno nuevo;
        printf("\n--- Registro de nuevo alumno ---\n");
        printf("Ingrese matrícula: ");
        while (scanf("%d", &nuevo.matricula) != 1) {
            printf("Entrada no válida. Ingrese un número para matrícula: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n'); // Limpiar resto de la línea

        printf("Ingrese nombre (máx. %d caracteres): ", MAX_LONG);
        leerCadena(nuevo.nombre, MAX_LONG);

        printf("Ingrese carrera (máx. %d caracteres): ", MAX_LONG);
        leerCadena(nuevo.carrera, MAX_LONG);

        // Guardar en el arreglo
        alumnos[*contador] = nuevo;
        (*contador)++;

        printf("Alumno registrado correctamente. Total registrados: %d\n", *contador);

        // Preguntar si desea seguir agregando
        printf("¿Desea registrar otro alumno? (s/n): ");
        opcion = getchar();
        while (getchar() != '\n'); // Limpiar resto de la línea
    }
}

// Opción 2: Buscar un alumno por matrícula
void buscarAlumno(const Alumno alumnos[], int contador) {
    if (contador == 0) {
        printf("No hay alumnos registrados.\n");
        return;
    }

    int matBuscada;
    printf("\n--- Búsqueda de alumno ---\n");
    printf("Ingrese la matrícula a buscar: ");
    while (scanf("%d", &matBuscada) != 1) {
        printf("Entrada no válida. Ingrese un número para matrícula: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n'); // Limpiar resto de la línea

    // Recorrer arreglo para buscar
    for (int i = 0; i < contador; i++) {
        if (alumnos[i].matricula == matBuscada) {
            printf("\nAlumno encontrado:\n");
            printf("Matrícula: %d\n", alumnos[i].matricula);
            printf("Nombre   : %s\n", alumnos[i].nombre);
            printf("Carrera  : %s\n", alumnos[i].carrera);
            return;
        }
    }

    printf("No se encontró alumno con matrícula %d.\n", matBuscada);
}

// Opción 3: Mostrar reporte de todos los alumnos registrados
void reporteAlumnos(const Alumno alumnos[], int contador) {
    if (contador == 0) {
        printf("No hay alumnos registrados para mostrar.\n");
        return;
    }

    printf("\n=== Reporte de alumnos registrados ===\n");
    for (int i = 0; i < contador; i++) {
        printf("\nAlumno #%d:\n", i + 1);
        printf("  Matrícula: %d\n", alumnos[i].matricula);
        printf("  Nombre   : %s\n", alumnos[i].nombre);
        printf("  Carrera  : %s\n", alumnos[i].carrera);
    }
    printf("\nTotal de alumnos registrados: %d\n", contador);
}
