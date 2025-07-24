#include <stdio.h>
#include <stdlib.h>

struct dato
{
  int num;
  struct dato *sig;
};

/* Punteros globales a la cabeza y la cola */
struct dato *primer = NULL, *ultimo = NULL;

/* Prototipos */
int agregarInicio(int tam);
int agregarFinal(int tam);
int agregarDespuesInicio(int tam);
int agregarAntesValor(int tam);
int agregarDespuesValor(int tam);
void recorrer(void);

/* --------------------------------------------------------------------- */
int agregarFinal(int tam)
{
  int band;
  struct dato *nuevo = NULL;
  do
  {
    // system("clear");
    nuevo = (struct dato *)malloc(sizeof(struct dato));
    if (nuevo == NULL)
    {
      printf("\nNo hay suficiente espacio en memoria!\n");
      getchar();
    }
    else
    {
      printf("Ingresa un numero entero: ");
      scanf("%d", &nuevo->num);
      nuevo->sig = NULL;
      if (primer == NULL)
      {
        /* Lista vacía */
        primer = nuevo;
        ultimo = nuevo;
      }
      else
      {
        /* Insertar al final */
        ultimo->sig = nuevo;
        ultimo = nuevo;
      }
      tam++;
    }
    printf("\n\n\tEscribe 0 para terminar: ");
    scanf("%d", &band);
  } while (band);
  return tam;
}

/* --------------------------------------------------------------------- */
int agregarInicio(int tam)
{
  struct dato *nuevo = NULL;
  nuevo = (struct dato *)malloc(sizeof(struct dato));
  if (nuevo == NULL)
  {
    printf("\nNo hay memoria!\n");
    getchar();
  }
  else
  {
    printf("\nIngresa el numero: ");
    scanf("%d", &nuevo->num);
    if (primer == NULL)
    {
      /* Lista vacía */
      nuevo->sig = NULL;
      primer = nuevo;
      ultimo = nuevo;
    }
    else
    {
      /* Insertar al inicio */
      nuevo->sig = primer;
      primer = nuevo;
    }
    tam++;
  }
  return tam;
}

/* --------------------------------------------------------------------- */
/* Inserta un nodo inmediatamente DESPUÉS del primer nodo de la lista */
int agregarDespuesInicio(int tam)
{
  if (primer == NULL)
  {
    printf("\nLa lista está vacía. Se insertará como primer nodo.\n");
    return agregarInicio(tam);
  }

  struct dato *nuevo = (struct dato *)malloc(sizeof(struct dato));
  if (nuevo == NULL)
  {
    printf("\nNo hay memoria!\n");
    getchar();
    return tam;
  }
  printf("\nIngresa el numero: ");
  scanf("%d", &nuevo->num);

  /* Inserción */
  nuevo->sig = primer->sig;
  primer->sig = nuevo;
  if (primer == ultimo)
  {
    /* Solo había un elemento, ahora "nuevo" es el último */
    ultimo = nuevo;
  }
  return ++tam;
}

/* --------------------------------------------------------------------- */
/* Inserta un nodo ANTES del nodo que contiene "valorBusqueda". */
int agregarAntesValor(int tam)
{
  if (primer == NULL)
  {
    printf("\nLa lista está vacía, no se puede insertar antes de un valor inexistente.\n");
    getchar();
    return tam;
  }

  int valorBusqueda;
  printf("\nIngresa el valor de referencia: ");
  scanf("%d", &valorBusqueda);

  struct dato *actual = primer, *anterior = NULL;
  while (actual != NULL && actual->num != valorBusqueda)
  {
    anterior = actual;
    actual = actual->sig;
  }

  if (actual == NULL)
  {
    printf("\nEl valor %d no existe en la lista.\n", valorBusqueda);
    getchar();
    return tam;
  }

  /* Valor encontrado, pedir nuevo dato */
  struct dato *nuevo = (struct dato *)malloc(sizeof(struct dato));
  if (nuevo == NULL)
  {
    printf("\nNo hay memoria disponible!\n");
    getchar();
    return tam;
  }

  printf("Ingresa el numero a insertar: ");
  scanf("%d", &nuevo->num);

  if (anterior == NULL)
  {
    /* Insertar antes del primer nodo */
    nuevo->sig = primer;
    primer = nuevo;
  }
  else
  {
    /* Insertar entre anterior y actual */
    anterior->sig = nuevo;
    nuevo->sig = actual;
  }
  return ++tam;
}

/* --------------------------------------------------------------------- */
/* Inserta un nodo DESPUÉS del nodo que contiene "valorBusqueda". */
int agregarDespuesValor(int tam)
{
  if (primer == NULL)
  {
    printf("\nLa lista está vacía, no se puede insertar después de un valor inexistente.\n");
    getchar();
    return tam;
  }

  int valorBusqueda;
  printf("\nIngresa el valor de referencia: ");
  scanf("%d", &valorBusqueda);

  struct dato *actual = primer;
  while (actual != NULL && actual->num != valorBusqueda)
  {
    actual = actual->sig;
  }

  if (actual == NULL)
  {
    printf("\nEl valor %d no existe en la lista.\n", valorBusqueda);
    getchar();
    return tam;
  }

  struct dato *nuevo = (struct dato *)malloc(sizeof(struct dato));
  if (nuevo == NULL)
  {
    printf("\nNo hay memoria disponible!\n");
    getchar();
    return tam;
  }

  printf("Ingresa el numero a insertar: ");
  scanf("%d", &nuevo->num);

  nuevo->sig = actual->sig;
  actual->sig = nuevo;
  if (actual == ultimo)
  {
    /* Se insertó después del último */
    ultimo = nuevo;
  }
  return ++tam;
}

/* --------------------------------------------------------------------- */
void recorrer(void)
{
  struct dato *aux = primer;
  // system("cls");
  if (aux == NULL)
  {
    printf("\nLa lista está vacía!\n");
  }
  else
  {
    printf("\nContenido de la lista:\n");
    while (aux != NULL)
    {
      printf("Numero = %d\n", aux->num);
      aux = aux->sig;
    }
  }
  getchar();
}

/* --------------------------------------------------------------------- */
int main(void)
{
  int op, tam = 0;
  do
  {
    // system("cls");
    printf("\n********** LISTA SIMPLEMENTE ENLAZADA **********\n");
    printf("1. Agregar nodo al inicio\n");
    printf("2. Agregar nodo al final\n");
    printf("3. Agregar nodo DESPUES del inicio\n");
    printf("4. Agregar nodo ANTES de un valor\n");
    printf("5. Agregar nodo DESPUES de un valor\n");
    printf("6. Recorrer la lista\n");
    printf("0. Salir\n");
    printf("Elige opcion: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
      tam = agregarInicio(tam);
      break;
    case 2:
      tam = agregarFinal(tam);
      break;
    case 3:
      tam = agregarDespuesInicio(tam);
      break;
    case 4:
      tam = agregarAntesValor(tam);
      break;
    case 5:
      tam = agregarDespuesValor(tam);
      break;
    case 6:
      recorrer();
      break;
    case 0:
      printf("\nSaliendo...\n");
      break;
    default:
      printf("\nOpcion no valida\n");
      getchar();
      break;
    }
  } while (op != 0);

  return 0;
}
