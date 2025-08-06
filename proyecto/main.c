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

#define MAX_POSTRES 100
#define MAX_NOMBRE 50
#define MAX_ING 50

typedef struct Ingrediente
{
  char nombre[MAX_ING];
  struct Ingrediente *sig;
} Ingrediente;

typedef struct
{
  char nombre[MAX_NOMBRE];
  Ingrediente *ingredientes;
} Postre;

void insertar_ingrediente(Postre *p, const char *ing)
{
  Ingrediente *nuevo = malloc(sizeof(Ingrediente));
  if (!nuevo)
  {
    perror("malloc");
    return;
  }
  strncpy(nuevo->nombre, ing, MAX_ING);
  nuevo->nombre[MAX_ING - 1] = '\0';
  nuevo->sig = NULL;
  if (!p->ingredientes)
  {
    p->ingredientes = nuevo;
  }
  else
  {
    Ingrediente *aux = p->ingredientes;
    while (aux->sig)
      aux = aux->sig;
    aux->sig = nuevo;
  }
}

void imprimir_ingredientes(Postre *p)
{
  if (!p->ingredientes)
  {
    printf("(sin ingredientes)\n");
    return;
  }
  for (Ingrediente *aux = p->ingredientes; aux; aux = aux->sig)
  {
    printf("- %s\n", aux->nombre);
  }
}

void eliminar_ingrediente(Postre *p, const char *ing)
{
  Ingrediente *act = p->ingredientes, *prev = NULL;
  while (act && strcmp(act->nombre, ing) != 0)
  {
    prev = act;
    act = act->sig;
  }
  if (!act)
  {
    printf("Ingrediente no encontrado.\n");
    return;
  }
  if (prev)
    prev->sig = act->sig;
  else
    p->ingredientes = act->sig;
  free(act);
  printf("Ingrediente eliminado.\n");
}

void liberar_ingredientes(Ingrediente *ing)
{
  while (ing)
  {
    Ingrediente *tmp = ing;
    ing = ing->sig;
    free(tmp);
  }
}

int buscar_postre(Postre postres[], int n, const char *nombre)
{
  for (int i = 0; i < n; i++)
  {
    if (strcmp(postres[i].nombre, nombre) == 0)
      return i;
  }
  return -1;
}

void imprimir_postre(Postre postres[], int n)
{
  char nombre[MAX_NOMBRE];
  printf("Nombre del postre: ");
  fgets(nombre, MAX_NOMBRE, stdin);
  nombre[strcspn(nombre, "\n")] = '\0';
  int idx = buscar_postre(postres, n, nombre);
  if (idx == -1)
  {
    printf("No existe el postre.\n");
    return;
  }
  printf("Ingredientes de %s:\n", postres[idx].nombre);
  imprimir_ingredientes(&postres[idx]);
}

void agregar_ingredientes_postre(Postre postres[], int n)
{
  char nombre[MAX_NOMBRE];
  printf("Nombre del postre: ");
  fgets(nombre, MAX_NOMBRE, stdin);
  nombre[strcspn(nombre, "\n")] = '\0';
  int idx = buscar_postre(postres, n, nombre);
  if (idx == -1)
  {
    printf("No existe el postre.\n");
    return;
  }
  char ing[MAX_ING];
  printf("Ingrese ingredientes (línea vacía para terminar)\n");
  while (1)
  {
    printf("Ingrediente: ");
    fgets(ing, MAX_ING, stdin);
    if (ing[0] == '\n')
      break;
    ing[strcspn(ing, "\n")] = '\0';
    insertar_ingrediente(&postres[idx], ing);
  }
}

void eliminar_ingrediente_postre(Postre postres[], int n)
{
  char nombre[MAX_NOMBRE];
  printf("Nombre del postre: ");
  fgets(nombre, MAX_NOMBRE, stdin);
  nombre[strcspn(nombre, "\n")] = '\0';
  int idx = buscar_postre(postres, n, nombre);
  if (idx == -1)
  {
    printf("No existe el postre.\n");
    return;
  }
  char ing[MAX_ING];
  printf("Ingrediente a eliminar: ");
  fgets(ing, MAX_ING, stdin);
  ing[strcspn(ing, "\n")] = '\0';
  eliminar_ingrediente(&postres[idx], ing);
}

void alta_postre(Postre postres[], int *n)
{
  if (*n >= MAX_POSTRES)
  {
    printf("Arreglo lleno.\n");
    return;
  }
  char nombre[MAX_NOMBRE];
  printf("Nombre del nuevo postre: ");
  fgets(nombre, MAX_NOMBRE, stdin);
  nombre[strcspn(nombre, "\n")] = '\0';
  if (buscar_postre(postres, *n, nombre) != -1)
  {
    printf("El postre ya existe.\n");
    return;
  }
  int pos = *n;
  while (pos > 0 && strcmp(postres[pos - 1].nombre, nombre) > 0)
  {
    postres[pos] = postres[pos - 1];
    pos--;
  }
  strcpy(postres[pos].nombre, nombre);
  postres[pos].ingredientes = NULL;
  char ing[MAX_ING];
  printf("Ingrese ingredientes (línea vacía para terminar)\n");
  while (1)
  {
    printf("Ingrediente: ");
    fgets(ing, MAX_ING, stdin);
    if (ing[0] == '\n')
      break;
    ing[strcspn(ing, "\n")] = '\0';
    insertar_ingrediente(&postres[pos], ing);
  }
  (*n)++;
}

void baja_postre(Postre postres[], int *n)
{
  char nombre[MAX_NOMBRE];
  printf("Nombre del postre a eliminar: ");
  fgets(nombre, MAX_NOMBRE, stdin);
  nombre[strcspn(nombre, "\n")] = '\0';
  int idx = buscar_postre(postres, *n, nombre);
  if (idx == -1)
  {
    printf("No existe el postre.\n");
    return;
  }
  liberar_ingredientes(postres[idx].ingredientes);
  for (int i = idx; i < *n - 1; i++)
  {
    postres[i] = postres[i + 1];
  }
  (*n)--;
  printf("Postre eliminado.\n");
}

int main()
{
  Postre postres[MAX_POSTRES];
  int num_postres = 0;
  int opcion;
  do
  {
    printf("\n--- Gestión de Postres ---\n");
    printf("1. Mostrar ingredientes de un postre\n");
    printf("2. Añadir ingredientes a un postre\n");
    printf("3. Eliminar ingrediente de un postre\n");
    printf("4. Dar de alta un nuevo postre\n");
    printf("5. Dar de baja un postre\n");
    printf("0. Salir\n");
    printf("Opción: ");
    if (scanf("%d", &opcion) != 1)
    {
      while (getchar() != '\n')
        ;
      opcion = -1;
    }
    getchar();
    switch (opcion)
    {
    case 1:
      imprimir_postre(postres, num_postres);
      break;
    case 2:
      agregar_ingredientes_postre(postres, num_postres);
      break;
    case 3:
      eliminar_ingrediente_postre(postres, num_postres);
      break;
    case 4:
      alta_postre(postres, &num_postres);
      break;
    case 5:
      baja_postre(postres, &num_postres);
      break;
    case 0:
      break;
    default:
      printf("Opción no válida.\n");
    }
  } while (opcion != 0);

  for (int i = 0; i < num_postres; i++)
  {
    liberar_ingredientes(postres[i].ingredientes);
  }
  return 0;
}
