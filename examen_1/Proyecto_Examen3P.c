/*
Nombre y Matricula de Integrantes:

Jesus Leonardo Jimenez Gonzalez - 735817
Israel Treviño Leyva - 744747
Eber Edrey Alejo Berrones - 746237
Eugenio Salinas Montemayor - 740960
*/

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

void insertar_ingrediente(Postre *p, const char *ing) {

    Ingrediente *nuevo = malloc(sizeof(Ingrediente));
    if (!nuevo) {
        printf("Error al asignar memoria");
        return;
    }

    strncpy(nuevo->nombre, ing, MAX_ING);
    nuevo->nombre[MAX_ING - 1] = '\0';
    nuevo->sig = NULL;
    if (p->ingredientes == NULL) {
        p->ingredientes = nuevo;
        return;
    }

    Ingrediente *actual = p->ingredientes;
    while (actual->sig != NULL)
        actual = actual->sig;

    actual->sig = nuevo;
}

void imprimir_ingredientes(Postre *p)
{
  Ingrediente *actual = p->ingredientes;

  if (!actual)
  {
    printf("(sin ingredientes)\n");
    return;
  }

  while (actual)
  {
    printf("- %s\n", actual->nombre);
    actual = actual->sig;
  }
}

void eliminar_ingrediente(Postre *p, const char *ing) {
    Ingrediente *actual = p->ingredientes, *anterior = NULL;

    while (actual && strcmp(actual->nombre, ing) != 0) {
        anterior = actual;
        actual = actual->sig;
    }

    if (!actual) {
        printf("Ingrediente no encontrado\n");
        return;
    }

    if (anterior) {
        anterior->sig = actual->sig;
    } else {
        p->ingredientes = actual->sig;
    }

    free(actual);
    printf("Ingrediente eliminado\n");
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
  int i = buscar_postre(postres, n, nombre);
  if (i == -1)
  {
    printf("No existe el postre\n");
    return;
  }
  printf("Ingredientes de %s:\n", postres[i].nombre);
  imprimir_ingredientes(&postres[i]);
}

void listar_postres(Postre postres[], int n)
{
  if (n == 0)
  {
    printf("No hay postres registrados\n");
    return;
  }

  printf("Lista de postres:\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d. %s\n", i + 1, postres[i].nombre);
  }
}


void agregar_ingredientes_postre(Postre postres[], int n)
{
  char nombre[MAX_NOMBRE];
  printf("Nombre del postre: ");
  fgets(nombre, MAX_NOMBRE, stdin);
  nombre[strcspn(nombre, "\n")] = '\0';
  int i = buscar_postre(postres, n, nombre);
  if (i == -1)
  {
    printf("No existe el postre\n");
    return;
  }
  char ing[MAX_ING];
  printf("Ingrese ingredientes (enter para terminar)\n");
  while (1)
  {
    printf("Ingrediente: ");
    fgets(ing, MAX_ING, stdin);
    if (ing[0] == '\n')
      break;
    ing[strcspn(ing, "\n")] = '\0';
    insertar_ingrediente(&postres[i], ing);
  }
}

void eliminar_ingrediente_postre(Postre postres[], int n)
{
  char nombre[MAX_NOMBRE];
  printf("Nombre del postre: ");
  fgets(nombre, MAX_NOMBRE, stdin);
  nombre[strcspn(nombre, "\n")] = '\0';

  if (strlen(nombre) == 0)
  {
    printf("Nombre del postre no puede estar vacio\n");
    return;
  }

  int i = buscar_postre(postres, n, nombre);
  if (i == -1)
  {
    printf("No existe el postre\n");
    return;
  }

  if (postres[i].ingredientes == NULL)
  {
    printf("El postre no tiene ingredientes\n");
    return;
  }

  char ing[MAX_ING];
  printf("Ingrediente a eliminar: ");
  fgets(ing, MAX_ING, stdin);
  ing[strcspn(ing, "\n")] = '\0';

  if (strlen(ing) == 0)
  {
    printf("Nombre del ingrediente no puede estar vacio\n");
    return;
  }

  eliminar_ingrediente(&postres[i], ing);
}


void alta_postre(Postre postres[], int *n)
{
  if (*n >= MAX_POSTRES)
  {
    printf("Arreglo lleno\n");
    return;
  }
  char nombre[MAX_NOMBRE];
  printf("Nombre del nuevo postre: ");
  fgets(nombre, MAX_NOMBRE, stdin);
  nombre[strcspn(nombre, "\n")] = '\0';
    if (strlen(nombre) == 0) {
        printf("Nombre del postre no puede estar vacio\n");
        return;
    }

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
  printf("Ingrese ingredientes (enter para terminar)\n");
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
  int i = buscar_postre(postres, *n, nombre);
  if (i == -1)
  {
    printf("No existe el postre.\n");
    return;
  }
  liberar_ingredientes(postres[i].ingredientes);
  for (int j = i; j < *n - 1; j++)
    {
    postres[j] = postres[j + 1];
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
    printf("\n=== MENU DE POSTRES ===\n");
    printf("1. Listar todos los postres\n");
    printf("2. Dar de alta un nuevo postre\n");
    printf("3. Mostrar ingredientes de un postre\n");
    printf("4. Agregar ingredientes a un postre\n");
    printf("5. Eliminar ingrediente a un postre\n");
    printf("6. Dar de baja un postre\n");
    printf("0. Salir\n");
    printf("Opcion: ");
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
      listar_postres(postres, num_postres);
      break;
    case 2:
      alta_postre(postres, &num_postres);
      break;
    case 3:
      imprimir_postre(postres, num_postres);
      break;
    case 4:
      agregar_ingredientes_postre(postres, num_postres);
      break;
    case 5:
      eliminar_ingrediente_postre(postres, num_postres);
      break;
    case 6:
      baja_postre(postres, &num_postres);
      break;
    case 0:
      break;
    default:
      printf("Opcion no valida\n");
    }
  } while (opcion != 0);


  return 0;
}
