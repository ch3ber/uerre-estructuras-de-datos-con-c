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
void insertarPostreOrdenado(const char *nombre, char ingredientes[][MAX_LONGITUD], int cantidad)
{
  if (totalPostres >= MAX_POSTRES)
  {
    printf("No se pueden agregar más postres.\n");
    return;
  }

  int pos = 0;
  while (pos < totalPostres && strcmp(postres[pos].nombre, nombre) < 0)
  {
    pos++;
  }

  for (int i = totalPostres; i > pos; i--)
  {
    postres[i] = postres[i - 1];
  }

  strcpy(postres[pos].nombre, nombre);
  postres[pos].inicio = postres[pos].fin = NULL;

  for (int i = 0; i < cantidad; i++)
  {
    insertarIngrediente(nombre, ingredientes[i]);
  }

  totalPostres++;
  printf("Postre '%s' agregado.\n", nombre);
}

void menu()
{
  int opcion;
  char nombrePostre[MAX_LONGITUD];
  char nombreIngrediente[MAX_LONGITUD];
  char ingredientes[10][MAX_LONGITUD];
  int cantidad;

  do
  {
    printf("\nMenu:\n");
    printf("1. Imprimir ingredientes de un postre\n");
    printf("2. Agregar ingrediente a un postre\n");
    printf("3. Eliminar ingrediente de un postre\n");
    printf("4. Agregar nuevo postre\n");
    printf("5. Eliminar postre\n");
    printf("0. Salir\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    getchar(); // limpiar buffer

    switch (opcion)
    {
    case 1:
      printf("Nombre del postre: ");
      fgets(nombrePostre, MAX_LONGITUD, stdin);
      nombrePostre[strcspn(nombrePostre, "\n")] = '\0';
      imprimirIngredientes(nombrePostre);
      break;

    case 2:
      printf("Nombre del postre: ");
      fgets(nombrePostre, MAX_LONGITUD, stdin);
      nombrePostre[strcspn(nombrePostre, "\n")] = '\0';
      printf("Ingrediente a agregar: ");
      fgets(nombreIngrediente, MAX_LONGITUD, stdin);
      nombreIngrediente[strcspn(nombreIngrediente, "\n")] = '\0';
      insertarIngrediente(nombrePostre, nombreIngrediente);
      break;

    case 3:
      printf("Nombre del postre: ");
      fgets(nombrePostre, MAX_LONGITUD, stdin);
      nombrePostre[strcspn(nombrePostre, "\n")] = '\0';
      printf("Ingrediente a eliminar: ");
      fgets(nombreIngrediente, MAX_LONGITUD, stdin);
      nombreIngrediente[strcspn(nombreIngrediente, "\n")] = '\0';
      eliminarIngrediente(nombrePostre, nombreIngrediente);
      break;

    case 4:
      printf("Nombre del nuevo postre: ");
      fgets(nombrePostre, MAX_LONGITUD, stdin);
      nombrePostre[strcspn(nombrePostre, "\n")] = '\0';

      printf("Cantidad de ingredientes: ");
      scanf("%d", &cantidad);
      getchar();

      for (int i = 0; i < cantidad; i++)
      {
        printf("Ingrediente %d: ", i + 1);
        fgets(ingredientes[i], MAX_LONGITUD, stdin);
        ingredientes[i][strcspn(ingredientes[i], "\n")] = '\0';
      }

      insertarPostreOrdenado(nombrePostre, ingredientes, cantidad);
      break;

    case 5:
      printf("Nombre del postre a eliminar: ");
      fgets(nombrePostre, MAX_LONGITUD, stdin);
      nombrePostre[strcspn(nombrePostre, "\n")] = '\0';
      eliminarPostre(nombrePostre);
      break;
    }
  } while (opcion != 0);
}

int main()
{
  menu();
  return 0;
}
