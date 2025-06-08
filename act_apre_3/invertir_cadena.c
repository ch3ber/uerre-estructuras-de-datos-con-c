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
    char original[MAX_LONG + 1];
    char invertida[MAX_LONG + 1];
    size_t len;
    
    // 1. Pedir la cadena original
    printf("Ingrese una cadena (máx. %d caracteres): ", MAX_LONG);
    leerCadena(original, MAX_LONG);
    
    // 2. Calcular longitud
    len = strlen(original);
    
    // 3. Invertir carácter por carácter
    for (size_t i = 0; i < len; i++) {
        invertida[i] = original[len - 1 - i];
    }
    invertida[len] = '\0';  // Fin de cadena
    
    // 4. Mostrar la cadena invertida
    printf("Cadena original: %s\n", original);
    printf("Cadena invertida: %s\n", invertida);
    
    return 0;
}
