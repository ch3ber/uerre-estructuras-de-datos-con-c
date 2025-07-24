#include <stdio.h>
#include <stdlib.h>

/*--------------------  Definición de la estructura --------------------*/
typedef struct base
{
  int num;
  struct base *ant;
  struct base *sig;
} Nodo;

Nodo *primero = NULL, *ultimo = NULL;

/*--------------------  Utilidades básicas --------------------*/
int listaVacia(void) { return primero == NULL; }

void imprimirLista(void)
{
  if (listaVacia())
  {
    puts("[lista vacía]");
    return;
  }
  Nodo *aux = primero;
  while (aux)
  {
    printf("%d%s", aux->num, aux->sig ? " <-> " : "\n");
    aux = aux->sig;
  }
}

Nodo *buscarValor(int v)
{
  Nodo *aux = primero;
  while (aux && aux->num != v)
    aux = aux->sig;
  return aux; /* NULL si no existe */
}

/*--------------------  Operaciones de inserción --------------------*/
void insertarAlFinal(int v)
{
  Nodo *nuevo = malloc(sizeof *nuevo);
  if (!nuevo)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  nuevo->num = v;
  nuevo->ant = ultimo;
  nuevo->sig = NULL;

  if (listaVacia())
    primero = ultimo = nuevo;
  else
  {
    ultimo->sig = nuevo;
    ultimo = nuevo;
  }
}

void insertarAntesDe(int clave, int v)
{
  Nodo *ref = buscarValor(clave);
  if (!ref)
  {
    printf("Valor %d no encontrado.\n", clave);
    return;
  }

  Nodo *nuevo = malloc(sizeof *nuevo);
  if (!nuevo)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  nuevo->num = v;

  nuevo->sig = ref;
  nuevo->ant = ref->ant;
  if (ref->ant)
    ref->ant->sig = nuevo;
  else
    primero = nuevo; /* Nuevo es ahora el primero */
  ref->ant = nuevo;
}

void insertarDespuesDe(int clave, int v)
{
  Nodo *ref = buscarValor(clave);
  if (!ref)
  {
    printf("Valor %d no encontrado.\n", clave);
    return;
  }

  Nodo *nuevo = malloc(sizeof *nuevo);
  if (!nuevo)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  nuevo->num = v;

  nuevo->ant = ref;
  nuevo->sig = ref->sig;
  if (ref->sig)
    ref->sig->ant = nuevo;
  else
    ultimo = nuevo; /* Nuevo es ahora el último */
  ref->sig = nuevo;
}

/*--------------------  Operaciones de eliminación --------------------*/
void eliminarNodo(Nodo *n)
{
  if (!n)
    return;
  if (n->ant)
    n->ant->sig = n->sig;
  else
    primero = n->sig; /* Quitamos el primero */

  if (n->sig)
    n->sig->ant = n->ant;
  else
    ultimo = n->ant; /* Quitamos el último */

  free(n);
}

void eliminarPorValor(int v)
{
  Nodo *n = buscarValor(v);
  if (!n)
  {
    printf("Valor %d no encontrado.\n", v);
    return;
  }
  eliminarNodo(n);
}

void eliminarPorPosicion(int pos)
{ /* 1‑basado: 1 = primer nodo */
  if (listaVacia() || pos <= 0)
  {
    puts("Posición inválida.");
    return;
  }

  Nodo *aux = primero;
  int i = 1;
  while (aux && i < pos)
  {
    aux = aux->sig;
    ++i;
  }
  if (!aux)
  {
    printf("Posición %d fuera de rango.\n", pos);
    return;
  }
  eliminarNodo(aux);
}

/*--------------------  Menú --------------------*/
void menu(void)
{
  int opc, x, y;
  do
  {
    puts(
        "\n=== Lista doblemente enlazada ===\n"
        "1) Insertar elemento (al final)\n"
        "2) Insertar antes de un valor\n"
        "3) Insertar después de un valor\n"
        "4) Eliminar por valor\n"
        "5) Eliminar por posición\n"
        "6) Mostrar lista\n"
        "0) Salir\n");
    printf("Opción: ");
    if (scanf("%d", &opc) != 1)
      exit(EXIT_FAILURE);

    switch (opc)
    {
    case 1:
      printf("Valor a insertar: ");
      scanf("%d", &x);
      insertarAlFinal(x);
      imprimirLista();
      break;

    case 2:
      printf("Valor de referencia: ");
      scanf("%d", &x);
      printf("Nuevo valor: ");
      scanf("%d", &y);
      insertarAntesDe(x, y);
      imprimirLista();
      break;

    case 3:
      printf("Valor de referencia: ");
      scanf("%d", &x);
      printf("Nuevo valor: ");
      scanf("%d", &y);
      insertarDespuesDe(x, y);
      imprimirLista();
      break;

    case 4:
      printf("Valor a eliminar: ");
      scanf("%d", &x);
      eliminarPorValor(x);
      imprimirLista();
      break;

    case 5:
      printf("Posición a eliminar (1‑n): ");
      scanf("%d", &x);
      eliminarPorPosicion(x);
      imprimirLista();
      break;

    case 6:
      imprimirLista();
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
