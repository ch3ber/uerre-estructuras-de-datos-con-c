// Eugenio Salinas Montemayor
// Eber Edrey Alejo Berrones

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256

static int son_anagramas(const char *str1, const char *str2)
{
  size_t n1 = strlen(str1);
  size_t n2 = strlen(str2);

  if (n1 != n2)
    return 0; // early return: longitudes distintas => no anagrama

  int count[26] = {0};

  for (size_t i = 0; i < n1; ++i)
  {
    unsigned char a = (unsigned char)str1[i];
    unsigned char b = (unsigned char)str2[i];

    if (!isalpha(a) || !isalpha(b))
      return 0; // solo letras permitido

    int ia = tolower(a) - 'a'; // siempre minúsculas
    int ib = tolower(b) - 'a';

    // sumamos para str1 y restamos para str2
    count[ia]++;
    count[ib]--;
  }

  // Si todos vuelven a 0, son anagramas
  for (int k = 0; k < 26; ++k)
  {
    if (count[k] != 0)
      return 0;
  }
  return 1;
}

int main(void)
{
  char p1[MAX_LEN], p2[MAX_LEN];

  printf("Ingresa la primera palabra: ");
  if (!fgets(p1, sizeof p1, stdin))
  {
    fprintf(stderr, "Error al leer.\n");
    return 1;
  }
  p1[strcspn(p1, "\n")] = '\0'; // quitar '\n' si quedó

  printf("Ingresa la segunda palabra: ");
  if (!fgets(p2, sizeof p2, stdin))
  {
    fprintf(stderr, "Error al leer.\n");
    return 1;
  }
  p2[strcspn(p2, "\n")] = '\0';

  if (son_anagramas(p1, p2))
  {
    printf("Son anagramas.\n");
  }
  else
  {
    printf("No son anagramas.\n");
  }
  return 0;
}
