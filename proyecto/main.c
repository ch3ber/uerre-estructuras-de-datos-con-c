/*
Nombre y Matricula de Integrantes:

Jesus Leonardo Jimenez Gonzalez - 735817
Israel Treviño Leyva - 744747
Eber Edrey Alejo Berrones - 746237
Eugenio Salinas Montemayor - 740960
*/

// Escribir el programa para resolver el siguiente caso:
// En el arreglo “Postres” se almacenan los datos de Postres, ordenados alfabéticamente. A su vez,
// cada elemento del arreglo tiene una lista de todos los ingredientes que pertenecen a dicho postre.
// Escribir un programa que:
// a) Dado el nombre de un postre, imprima la lista de todos sus ingredientes.
// b) Dado el nombre de un postre, inserte nuevos ingredientes a su correspondiente lista.
// c) Dado el nombre de un postre, elimine alguno de sus ingredientes.
// d) Dé de alta un nuevo postre con todos sus ingredientes.
// e) Dé de baja un postre con todos sus ingredientes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGITUD 50
#define MAX_POSTRES 50

typedef struct Ingrediente
{
  char nombre[MAX_LONGITUD];
  struct Ingrediente *sig;
  struct Ingrediente *prev;
} Ingrediente;

typedef struct
{
  char nombre[MAX_LONGITUD];
  Ingrediente *inicio;
  Ingrediente *fin;
} Postre;

Postre postres[MAX_POSTRES];
int totalPostres = 0;

Ingrediente *crearIngrediente(const char *nombre)
{
  Ingrediente *nuevo = (Ingrediente *)malloc(sizeof(Ingrediente));
  strncpy(nuevo->nombre, nombre, MAX_LONGITUD);
  nuevo->sig = nuevo->prev = NULL;
  return nuevo;
}

int buscarPostre(const char *nombre)
{
  for (int i = 0; i < totalPostres; i++)
  {
    if (strcmp(postres[i].nombre, nombre) == 0)
    {
      return i;
    }
  }
  return -1;
}

void imprimirIngredientes(const char *nombre)
{
  int index = buscarPostre(nombre);
  if (index == -1)
  {
    printf("Postre no encontrado.\n");
    return;
  }

  printf("Ingredientes de %s:\n", postres[index].nombre);
  Ingrediente *temp = postres[index].inicio;
  while (temp)
  {
    printf("- %s\n", temp->nombre);
    temp = temp->sig;
  }
}

void insertarIngrediente(const char *nombrePostre, const char *nombreIngrediente)
{
  int index = buscarPostre(nombrePostre);
  if (index == -1)
  {
    printf("Postre no encontrado.\n");
    return;
  }

  Ingrediente *nuevo = crearIngrediente(nombreIngrediente);
  if (!postres[index].inicio)
  {
    postres[index].inicio = postres[index].fin = nuevo;
  }
  else
  {
    postres[index].inicio->sig = nuevo;
    nuevo->prev = postres[index].fin;
    postres[index].fin = nuevo;
  }

  printf("Ingrediente '%s' agregado a '%s'.\n", nombreIngrediente, nombrePostre);
}

void eliminarIngrediente(const char *nombrePostre, const char *nombreIngrediente)
{
  // Buscar el postre por su nombre
  int i = buscarPostre(nombrePostre);
  if (i == -1)
  {
    printf("Postre no encontrado.\n");
    return;
  }

  // Buscar el ingrediente dentro de la lista del postre
  Ingrediente *actual = postres[i].inicio;
  while (actual != NULL && strcmp(actual->nombre, nombreIngrediente) != 0)
  {
    actual = actual->sig;
  }

  // Si no se encontró el ingrediente
  if (actual == NULL)
  {
    printf("Ingrediente no encontrado.\n");
    return;
  }

  // Si el ingrediente tiene un anterior, actualizar su next
  if (actual->prev != NULL)
  {
    actual->prev->sig = actual->sig;
  }
  else
  {
    // Si es el primero de la lista, actualizar la cabeza
    postres[i].inicio = actual->sig;
  }

  // Si el ingrediente tiene un siguiente, actualizar su prev
  if (actual->sig != NULL)
  {
    actual->sig->prev = actual->prev;
  }
  else
  {
    // Si es el último de la lista, actualizar la cola
    postres[i].fin = actual->prev;
  }

  // Liberar memoria del ingrediente eliminado
  free(actual);
  printf("Ingrediente eliminado correctamente.\n");
}
void eliminarPostre(const char *nombre)
{
  // Buscar el índice del postre por nombre
  int index = buscarPostre(nombre);
  if (index == -1)
  {
    printf("Postre no encontrado.\n");
    return;
  }

  // Liberar todos los ingredientes del postre
  Ingrediente *actual = postres[index].inicio;
  while (actual != NULL)
  {
    Ingrediente *temp = actual;
    actual = actual->sig;
    free(temp);
  }

  // Eliminar el postre del arreglo moviendo todos los siguientes una posición
  for (int i = index; i < totalPostres - 1; i++)
  {
    postres[i] = postres[i + 1];
  }

  // Disminuir el contador de postres
  totalPostres--;

  printf("Postre eliminado.\n");
}

/*--------------------  Menú --------------------*/
void menu(void)
{
  int opc;
  do
  {
    puts(
        "\n=== Datos de Postres ===\n"
        "1) Dado el nombre de un postre, imprima la lista de todos sus ingredientes.\n"
        "2) Dado el nombre de un postre, inserte nuevos ingredientes a su correspondiente lista.\n"
        "3) Dado el nombre de un postre, elimine alguno de sus ingredientes.\n"
        "4) Dé de alta un nuevo postre con todos sus ingredientes.\n"
        "5) Dé de baja un postre con todos sus ingredientes.\n"
        "0) Salir\n");
    printf("Opción: ");
    if (scanf("%d", &opc) != 1)
      exit(EXIT_FAILURE);

    switch (opc)
    {
    case 1:
      break;

    case 2:
      break;

    case 3:
      break;

    case 4:
      break;

    case 5:
      break;

    case 0:
      puts("Fin del programa.");
      break;

    default:
      puts("Opción no válida.");
    }
  } while (opc != 0);
}

/*--------------------  main --------------------*/
int main(void)
{
  menu();
  return 0;
}
