#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    char c;
    int ocurrencias = 0;
    size_t len;

    // 1. Pedir la cadena
    printf("Ingrese una cadena (máx. %d caracteres): ", MAX_LONG);
    leerCadena(cadena, MAX_LONG);

    // 2. Pedir un carácter, validando que sea:
    //    a) exactamente un carácter
    //    b) no sea un dígito (0–9)
    while (1) {
        printf("Ingrese un carácter para buscar (no numérico): ");
        leerCadena(bufferChar, MAX_LONG);
        if (strlen(bufferChar) != 1) {
            printf("  Entrada no válida. Debe ingresar un único carácter.\n");
            continue;
        }
        if (isdigit((unsigned char)bufferChar[0])) {
            printf("  Entrada no válida. El carácter no puede ser numérico.\n");
            continue;
        }
        // Si llegamos aquí, es un solo carácter y no es dígito
        c = bufferChar[0];
        break;
    }

    // 3. Recorrer la cadena y contar ocurrencias
    len = strlen(cadena);
    for (size_t i = 0; i < len; i++) {
        if (cadena[i] == c) {
            ocurrencias++;
        }
    }

    // 4. Mostrar resultado
    printf("El carácter '%c' aparece %d vez%s en la cadena.\n",
           c, ocurrencias, (ocurrencias == 1) ? "" : "es");

    return 0;
}
