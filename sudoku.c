#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

/*
2.Cree la función int is_valid(Node *n), para validar si un estado/nodo es válido (cumple con las restricciones del problema). 
Debe validar que:
  - No se repitan números en las filas.
  - No se repitan números en las columnas.
  - No se repitan números en las submatrices de 3x3.
Si el estado es válido la función retorna 1, si no lo es retorna 0.

Para marcar los números que vayan apareciendo en una fila/columna/submatriz puede usar un arreglo de enteros de largo 
10 inicializado con 0s. Cada vez que aparezca un número i, verifique que la casilla i del arreglo sea igual a 0, luego márquela 
con un '1'. Si la casilla es '1' quiere decir que el número ya estaba marcado por lo que la fla/columna/submatriz no es válida.
*/
int is_valid(Node *n)
{
  // Verificacion de que no se repitan números en las filas.
  for (int f = 0 ; f < 9 ; f++) // Indices fila del sudoku (del 0 al 8)
  {
    int vistos[10] = {0} ;  // Arreglo para saber si se repite un valor dentro de la matriz

    for (int c = 0 ; c < 9 ; c++) // Indices columna del sudoku (del 0 al 8)
    {
      int validar = n->sudo[f][c] ; // Variable "validar" que me dirá el valor de la celda

      if (!validar) // Como la celda es 0, salta la validación (celda vacía)
        continue ;

      if (vistos[validar])  // Si es true (1), quiere decir que esta repetido
        return 0 ;  // No valido
      
      vistos[validar] = 1 ; // Si no esta repetido, marcamos la casilla con un 1, para saber que ya lo vimos
    }
  }

  // Verificacion de que no se repitan números en las columnas.
  for (int c = 0 ; c < 9 ; c++) // Indices columna del sudoku (del 0 al 8)
  {
    int vistos[10] = {0} ;  // Arreglo para saber si se repite un valor dentro de la matriz

    for (int f = 0 ; f < 9 ; f++) // nIdices fila del sudoku (del 0 al 8)
    {
      int validar = n->sudo[f][c] ; // Variable "validar" que me dirá el valor de la celda

      if (!validar) // Como la celda es 0, salta la validación (celda vacía)
        continue ;

      if (vistos[validar])  // Si es true (1), quiere decir que esta repetido
        return 0 ;  // No valido
      
      vistos[validar] = 1 ; // Si no esta repetido, marcamos la casilla con un 1, para saber que ya lo vimos
    }
  }

  /*
  ¿Cómo recorrer las submatrices de 3x3? El siguiente código se puede usar para recorrer los elementos de 
  una sumbatriz k (por ejemplo k=4):
    int k=4,p; 
    for(p=0;p<9;p++)
    {
      int i = 3 * (k / 3) + (p / 3) ;
      int j = 3 * (k % 3) + (p % 3) ;
      printf("%d ",nodo->sudo[i][j]);
      if(p%3 == 2) printf("\n");
    }
  */
  // Verificacion de que no se repitan números en las submatrices de 3x3.
  for (int k = 0 ; k < 9 ; k++) // Indices fila del sudoku (del 0 al 8)
  {
    int vistos[10] = {0} ;  // Arreglo para saber si se repite un valor dentro de la matriz

    for (int p = 0 ; p < 9 ; p++) // Indices columna del sudoku (del 0 al 8)
    {
      // Código dado para recorrer submatrices de 3x3
      int f = 3 * (k / 3) + (p / 3) ;
      int c = 3 * (k % 3) + (p % 3) ;

      int validar = n->sudo[f][c] ; // Variable "validar" que me dirá el valor de la celda

      if (!validar) // Como la celda es 0, salta la validación (celda vacía)
        continue ;

      if (vistos[validar])  // Si es true (1), quiere decir que esta repetido
        return 0 ;  // No valido
      
      vistos[validar] = 1 ; // Si no esta repetido, marcamos la casilla con un 1, para saber que ya lo vimos
    }
  }

  return 1 ; // Es valido
}

/*
1. Cree una función que a partir de un nodo genere una lista con los nodos adyacentes:
  - Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.
  - Para el caso del ejemplo, la función debería retornar una lista con 9 nodos. Cada uno de ellos idéntico al nodo original 
  pero cambiando el valor de la primera casilla vacía, es decir: sudo[0][2], por 1, 2, ..., 9.
Utilice la función Node *copy(Node *n) para copiar nodos.
*/
List *get_adj_nodes(Node *n)
{
  List *list = createList() ;

  // Variables que guardarán la posicion fila y columna de la primera celda vacia
  int fila = -1 ;
  int columna = -1 ;

  for (int f = 0; f < 9; f++) // Indices fila del sudoku (del 0 al 8)
  {
    for (int c = 0; c < 9; c++) // Indices columna del sudoku (del 0 al 8)
    {
      if (n->sudo[f][c] == 0) // Encontramos la primera celda vacia (0)
      {
        // Le asignamos a fila y columna la posicion (f y c) de la celda vacia
        fila = f ;
        columna = c ;
        break ;
      }
    }
    if (fila != -1) // Condicion para terminar el bucle de filas
      break ;
  }
  
  // 3. Modifique la función get_adj_nodes para que sólo los nodos válidos sean retornados (use la función is_valid).
  for (int k = 1 ; k < 10 ; k++)  // Valores permitidos en el sudoku (del 1 al 9)
  {
    Node *nuevo_nodo = copy(n) ;  // Creo nuevo_nodo y utilizo la funcion "copy" para copiar el nodo n en nuevo_nodo
    nuevo_nodo->sudo[fila][columna] = k ; // Le damos el valor de k a la celda vacia

    if (is_valid(nuevo_nodo)) // Si es valido el nodo
      pushBack(list, nuevo_nodo) ;  // Insertamos el nodo en la lista
    else  // Si no es valido
      free(nuevo_nodo) ;  // Lo liberamos
  }

  return list ; // Retornamos la lista
}

/*
4.Implemente la función int is_final(Node *n). Esta función retorna 1 si el nodo corresponde a un nodo final (es decir, todos los 
valores de la matriz son distintos a 0) y 0 en caso contrario.
*/
int is_final(Node *n)
{
  
  for (int f = 0 ; f < 9 ; f++) // Indices fila del sudoku (del 0 al 8)
  {
    for (int c = 0 ; c < 9 ; c++) // Indices columna del sudoku (del 0 al 8)
    {
      if (!n->sudo[f][c]) // Si la celda es 0 (celda vacía)
        return 0 ;  // No corresponde a un nodo final (valores distintos de 0)
    }
  }
  
  return 1 ;  // Corresponde a un nodo final (valores distintos de 0)
}

/*
5.Implemente la función Node* DFS(Node* n, int* cont). Esta función realiza una búsqueda en profundidad a partir del nodo n. 
El algoritmo es el siguiente:
  - Cree un stack S (pila) e inserte el nodo.
  - Mientras el stack S no se encuentre vacío:
    a) Saque y elimine el primer nodo de S.
    b) Verifique si corresponde a un estado final, si es así retorne el nodo.
    c) Obtenga la lista de nodos adyacentes al nodo.
    d) Agregue los nodos de la lista (uno por uno) al stack S.
    e) Libere la memoria usada por el nodo.

  - Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.
  - Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.
*/

Node *DFS(Node *initial, int *cont)
{
  Stack *s = createStack() ;
  *cont = 0 ;
  push(s, initial) ;

  while (!is_empty(s))
  {
    Node *primer_nodo = top(s) ;
    pop(s) ;
    (*cont)++ ;
    
    if (is_final(primer_nodo))
      return primer_nodo ;

    List *adyacentes = get_adj_nodes(primer_nodo) ;
    Node *nodo_adyacente = first(adyacentes) ;

    while (nodo_adyacente != NULL)
    {
      push(s, nodo_adyacente) ;
      nodo_adyacente = next(adyacentes) ;
    }
    free(primer_nodo) ;
    free(adyacentes) ; 
  }
  
  return NULL ;
}

int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}

//Compile: gcc sudoku -o sudoku y ejecute: ./sudoku