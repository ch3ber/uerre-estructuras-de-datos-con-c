// Eugenio Salinas Montemayor
// Eber Edrey Alejo Berrones

#include <stdio.h>

char desencriptar(char c)
{
  switch (c)
  {
  case 'e':
    return 'a';
  case 'i':
    return 'e';
  case 'o':
    return 'i';
  case 'u':
    return 'o';
  case 'a':
    return 'u';
  default:
    return c;
  }
}

int main()
{
  char mensaje[1000];

  printf("Ingresa el mensaje encriptado:\n");
  fgets(mensaje, sizeof(mensaje), stdin);

  printf("El mensaje desencriptado es:\n");
  for (int i = 0; mensaje[i] != '\0'; i++)
  {
    printf("%c", desencriptar(mensaje[i]));
  }

  return 0;
}
