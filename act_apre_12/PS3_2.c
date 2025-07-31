// Eugenio Salinas Montemayor
// Eber Edrey Alejo Berrones

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
  char frase[200];
  int palabras = 0, enPalabra = 0;

  printf("Ingresa tu frase favorita: ");
  fgets(frase, sizeof(frase), stdin);

  for (int i = 0; frase[i] != '\0'; i++)
  {
    if (!isspace(frase[i]) && !enPalabra)
    {
      enPalabra = 1;
      palabras++;
    }
    else if (isspace(frase[i]))
    {
      enPalabra = 0;
    }
  }

  printf("Tu frase tiene un total de: %d palabras.\n", palabras);
  return 0;
}
