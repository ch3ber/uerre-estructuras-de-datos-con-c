#include<stdio.h>
#include<stdlib.h>

/*
  Este programa implementa una lista simplemente enlazada y permite
  realizar diversas operaciones de inserción.  Se añadieron las
  siguientes funciones extra solicitadas:

    1. agregarDespuesInicio  – Inserta un nodo después del primero.
    2. agregarAntesValor     – Inserta un nodo antes de un valor dado.
    3. agregarDespuesValor   – Inserta un nodo después de un valor dado.

  Además se añadió un pequeño reemplazo de la función getche() de
  conio.h para evitar dependencias fuera del estándar.
*/

#ifndef _WIN32
#define CLS "clear"
#else
#define CLS "cls"
#endif

/* Pequeña implementación portátil de getche() para que el programa
   compile con gcc en cualquier plataforma.  Lee un carácter y lo
   muestra en pantalla. */
static int getche(void)
{
  int ch = getchar();
  putchar(ch);
  fflush(stdout);
  return ch;
}
struct dato
{
  int num;
  struct dato *sig;
};
struct dato *primer=NULL, *ultimo=NULL;

/* Prototipos de funciones */
int agregarFinal(int tam);
int agregarInicio(int tam);
int agregarDespuesInicio(int tam);
int agregarAntesValor(int tam);
int agregarDespuesValor(int tam);
void recorrer(void);

int agregarFinal(int tam)
{
  int band;
  struct dato *nuevo=NULL;
  do
  {
    system(CLS);
    nuevo=(struct dato*) malloc(sizeof(struct dato));
    if(nuevo==NULL)
    {
      printf("\nNo hay suficiente espacio!\n");
      getche();
    }
    else
  {
      printf("Ingresa un numero entero\t");
      scanf("%d",&nuevo->num);
      nuevo->sig=NULL;
      if(primer==NULL)
      {
        primer=nuevo;
        ultimo=nuevo;
        tam++;
      }
      else
    {
        ultimo->sig=nuevo;
        ultimo=nuevo;
        tam++;
      }
    }
    printf("\n\n\tEscribe 0 para terminar\t");
    scanf("%d",&band);
  }while(band);
  return tam;
}

/*
  Inserta un nodo inmediatamente después del primer nodo de la lista.
  Si la lista está vacía, el nodo se convierte en el primero.
*/
int agregarDespuesInicio(int tam)
{
  struct dato *nuevo = (struct dato*)malloc(sizeof(struct dato));
  if(nuevo == NULL)
  {
    printf("\nNo hay suficiente memoria!\n");
    getche();
    return tam;
  }

  printf("\nIngresa el numero\t");
  scanf("%d", &nuevo->num);
  nuevo->sig = NULL;

  if(primer == NULL) /* lista vacía */
  {
    primer = ultimo = nuevo;
  }
  else
  {
    nuevo->sig = primer->sig;
    primer->sig = nuevo;
    if(primer == ultimo) /* la lista tenía un solo nodo */
      ultimo = nuevo;
  }
  tam++;
  return tam;
}

/* Inserta un nodo antes del nodo que contenga el valor objetivo. */
int agregarAntesValor(int tam)
{
  int objetivo;
  printf("\nIngresa el valor antes del cual se insertará el nuevo nodo: ");
  scanf("%d", &objetivo);

  if(primer == NULL)
  {
    printf("\nLa lista está vacía!\n");
    getche();
    return tam;
  }

  /* Si el objetivo está en el primer nodo se reutiliza agregarInicio */
  if(primer->num == objetivo)
  {
    return agregarInicio(tam);
  }

  struct dato *prev = primer;
  struct dato *curr = primer->sig;
  while(curr != NULL && curr->num != objetivo)
  {
    prev = curr;
    curr = curr->sig;
  }

  if(curr == NULL)
  {
    printf("\nValor no encontrado en la lista!\n");
    getche();
    return tam;
  }

  struct dato *nuevo = (struct dato*)malloc(sizeof(struct dato));
  if(nuevo == NULL)
  {
    printf("\nNo hay suficiente memoria!\n");
    getche();
    return tam;
  }

  printf("Ingresa el numero del nuevo nodo\t");
  scanf("%d", &nuevo->num);

  nuevo->sig = curr;
  prev->sig = nuevo;
  tam++;
  return tam;
}

/* Inserta un nodo después del nodo que contenga el valor objetivo. */
int agregarDespuesValor(int tam)
{
  int objetivo;
  printf("\nIngresa el valor después del cual se insertará el nuevo nodo: ");
  scanf("%d", &objetivo);

  struct dato *curr = primer;
  while(curr != NULL && curr->num != objetivo)
    curr = curr->sig;

  if(curr == NULL)
  {
    printf("\nValor no encontrado en la lista!\n");
    getche();
    return tam;
  }

  struct dato *nuevo = (struct dato*)malloc(sizeof(struct dato));
  if(nuevo == NULL)
  {
    printf("\nNo hay suficiente memoria!\n");
    getche();
    return tam;
  }

  printf("Ingresa el numero del nuevo nodo\t");
  scanf("%d", &nuevo->num);

  nuevo->sig = curr->sig;
  curr->sig = nuevo;
  if(curr == ultimo) /* actualizado si se añadió al final */
    ultimo = nuevo;

  tam++;
  return tam;
}

int agregarInicio(int tam)
{
  struct dato *nuevo=NULL;
  nuevo=(struct dato*)malloc(sizeof(struct dato));
  if(nuevo==NULL)
  {
    printf("\nNo hay memoria!");
    getche();
    return tam;
  }

  printf("\nIngresa el numero\t");
  scanf("%d", &nuevo->num);
  nuevo->sig = NULL;

  if(primer == NULL) /* lista vacía */
  {
    primer = ultimo = nuevo;
  }
  else /* lista con elementos */
  {
    nuevo->sig = primer;
    primer = nuevo;
  }

  tam++;
  return tam;
}

void recorrer()
{
  struct dato *aux=NULL;
  aux=primer;
  system(CLS);
  if(aux==NULL)
  {
    printf("\nLista no existe!");
    getche();
  }
  else
{
    while(aux!=NULL)
    {
      printf("\nNumero = %d", aux->num);
      aux=aux->sig;
    }
    getche();
  }
}
int main()
{
  int op,tam=0;
  do
  {
    system(CLS);
    printf("\n1. Agregar nodo al inicio de la lista");
    printf("\n2. Agregar nodo al final de la lista");
    printf("\n3. Agregar nodo DESPUES del inicio");
    printf("\n4. Agregar nodo ANTES de un valor dado");
    printf("\n5. Agregar nodo DESPUES de un valor dado");
    printf("\n6. Recorrer la lista");
    printf("\n0. Salir");
    printf("\nElige opcion ");
    scanf("%d",&op);
    switch(op)
    {
      case 1: tam=agregarInicio(tam);
        printf("\nCantidad de nodos: %d\n",tam);
        recorrer();
        break;
      case 2:
        tam=agregarFinal(tam);
        printf("\nCantidad de nodos: %d\n",tam);
        recorrer();
        break;
      case 3:
        tam = agregarDespuesInicio(tam);
        printf("\nCantidad de nodos: %d\n",tam);
        recorrer();
        break;
      case 4:
        tam = agregarAntesValor(tam);
        printf("\nCantidad de nodos: %d\n",tam);
        recorrer();
        break;
      case 5:
        tam = agregarDespuesValor(tam);
        printf("\nCantidad de nodos: %d\n",tam);
        recorrer();
        break;
      case 6:
        recorrer();
        break;
    }
  }while(op!=0);

  return 0;
}
