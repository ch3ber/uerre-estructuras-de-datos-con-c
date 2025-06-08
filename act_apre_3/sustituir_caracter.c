#include <stdio.h>
#include <string.h>

#define MAX_LONG 100

// Lee una línea de stdin en buffer (hasta MAX_LONG), eliminando '\n'
void leerCadena(char *buffer, int largo) {
    if (fgets(buffer, largo + 1, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

int main() {
    char cadena[MAX_LONG + 1];
    char bufferChar[MAX_LONG + 1];
    char origen, destino;
    size_t len;
    
    // 1. Pedir la cadena
    printf("Ingrese una cadena (máx. %d caracteres): ", MAX_LONG);
    leerCadena(cadena, MAX_LONG);
    
    // 2. Pedir el carácter a sustituir (validación de único carácter)
    while (1) {
        printf("Ingrese el carácter a sustituir: ");
        leerCadena(bufferChar, MAX_LONG);
        if (strlen(bufferChar) == 1) {
            origen = bufferChar[0];
            break;
        } else {
            printf("Entrada no válida. Debe ingresar un único carácter.\n");
        }
    }
    
    // 3. Pedir el carácter sustituto (validación de único carácter)
    while (1) {
        printf("Ingrese el carácter sustituto: ");
        leerCadena(bufferChar, MAX_LONG);
        if (strlen(bufferChar) == 1) {
            destino = bufferChar[0];
            break;
        } else {
            printf("Entrada no válida. Debe ingresar un único carácter.\n");
        }
    }
    
    // 4. Recorrer la cadena y sustituir
    len = strlen(cadena);
    for (size_t i = 0; i < len; i++) {
        if (cadena[i] == origen) {
            cadena[i] = destino;
        }
    }
    
    // 5. Mostrar cadena resultante
    printf("Cadena modificada: %s\n", cadena);
    
    return 0;
}
