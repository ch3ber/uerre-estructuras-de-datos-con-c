// Escribe una función que reciba una cadena y un carácter, y devuelva el número de veces que aparece ese carácter.
// Valida que la cadena no sea nula y que el carácter sea un único byte.

#include <stdio.h>
#include <string.h>

#define MAX_LEN 126

void leerCadena(char *buffer, int largo)
{
  if (fgets(buffer, largo + 1, stdin) != NULL)
  {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
      buffer[len - 1] = '\0';
    }
  }
}

int count_characters(char user_string[], char character_to_find[])
{
  int count_character_in_string = 0;
  for (int i = 0; i < strlen(user_string); i++)
  {
    if (user_string[i] == character_to_find[0])
    {
      count_character_in_string += 1;
    }
  }

  return count_character_in_string;
}

void input_single_character(char *string)
{
  while (strlen(string) != 1)
  {
    printf("El caracter a buscar debe de ser de un solo digito y no puede estar vacio.");
    printf("Ingresa el caracter a buscar: ");
    scanf("%s", &string);
    while (getchar() != '\n')
      ;
  }
}

int main()
{

  char user_string[MAX_LEN + 1];
  printf("Ingresa la cadena: ");
  leerCadena(user_string, MAX_LEN);

  printf("Ingresa el caracter a buscar: ");
  char character_to_find[MAX_LEN + 1];
  scanf("%s", &character_to_find);
  while (getchar() != '\n')
    ;
  input_single_character(character_to_find);

  int count_character_in_string = 0;
  count_character_in_string = count_characters(user_string, character_to_find);

  printf("El caracter aparecio un total de: %d", count_character_in_string);

  return 0;
}