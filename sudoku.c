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
2.Cree la función int is_valid(Node * n), para validar si un estado/nodo es válido (cumple con las restricciones del problema). 
Debe validar que:
  - No se repitan números en las filas
  - No se repitan números en las columnas
  - No se repitan números en las submatrices de 3x3
Si el estado es válido la función retorna 1, si no lo es retorna 0.

Para marcar los números que vayan apareciendo en una fila/columna/submatriz puede usar un arreglo de enteros de largo 
10 inicializado con 0s. Cada vez que aparezca un número i, verifique que la casilla i del arreglo sea igual a 0, luego márquela 
con un '1'. Si la casilla es '1' quiere decir que el número ya estaba marcado por lo que la fla/columna/submatriz no es válida.

}
La salida del código con el estado de la figura es (submatriz del centro):

0 6 0
8 0 3
0 2 0
*/
int is_valid(Node *n)
{
  for (int f = 0 ; f < 9 ; f++)
  {
    int vistos[10] = {0} ;

    for (int c = 0 ; c < 9 ; c++)
    {
      int validar = n->sudo[f][c] ;

      if (vistos[validar])  // si es true (1), quiere decir que esta repetido
        return 0 ;
      
      vistos[validar] = 1 ;
    }
    
  }

  for (int c = 0 ; c < 9 ; c++)
  {
    int vistos[10] = {0} ;

    for (int f = 0 ; f < 9 ; f++)
    {
      int validar = n->sudo[f][c] ;

      if (vistos[validar])  // si es true (1), quiere decir que esta repetido
        return 0 ;
      
      vistos[validar] = 1 ;
    }
  }

  /*
  ¿Cómo recorrer las submatrices de 3x3? El siguiente código se puede usar para recorrer los elementos de una sumbatriz k (por ejemplo k=4):

  int k=4,p; 
  for(p=0;p<9;p++){
    int i=3*(k/3) + (p/3) ;
    int j=3*(k%3) + (p%3) ;
    printf("%d ",nodo->sudo[i][j]);
    if(p%3 == 2) printf("\n");
  */
  for (int k = 0 ; k < 9 ; k++)
  {
    int vistos[10] = {0} ;

    for (int p = 0 ; p < 9 ; p++)
    {
      int f = 3 * (k / 3) + (p / 3) ;
      int c = 3 * (k % 3) + (p % 3) ;
      int validar = n->sudo[f][c] ;

      if (vistos[validar])  // si es true (1), quiere decir que esta repetido
        return 0 ;
      
      vistos[validar] = 1 ;
    }
  }
  return 1 ;
}

/*
1.Cree una función que a partir de un nodo genere una lista con los nodos adyacentes:
- Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.
- Para el caso del ejemplo, la función debería retornar una lista con 9 nodos. Cada uno de ellos idéntico al nodo original 
pero cambiando el valor de la primera casilla vacía, es decir: sudo[0][2], por 1, 2, ..., 9.
Utilice la función Node* copy(Node* n) para copiar nodos.

3.Modifique la función get_adj_nodes para que sólo los nodos válidos sean retornados (use la función is_valid).
*/
List *get_adj_nodes(Node *n)
{
  List *list = createList() ;
  int fila = -1 ;
  int columna = -1 ;

  for (int f = 0; f < 9; f++)
  {
    for (int c = 0; c < 9; c++)
    {
      if (n->sudo[f][c] == 0)
      {
        fila = f ;
        columna = c ;
        break ;
      }
      
    }
    if (fila != -1)
      break ;
  }
  
  if (fila == -1)
    return list ;

  for (int k = 0 ; k < 10 ; k++)
  {
    Node *nuevo_nodo = copy(n) ;
    nuevo_nodo->sudo[fila][columna] = k ;

    if (is_valid(nuevo_nodo))
      pushBack(list, nuevo_nodo) ;
    else
      free(nuevo_nodo) ;
  }
  //obtenga los nodos adyacentes a n
  //y agréguelos a la lista

  return list ;
}

/*
4.Implemente la función int is_final(Node * n). Esta función retorna 1 si el nodo corresponde a un nodo final (es decir, todos los valores de la matriz son distintos a 0) y 0 en caso contrario.

Ya está listo el grafo implícito, ahora necesitamos construir un método de búsqueda que a partir del estado inicial sea capaz de explorar el grafo de manera sistemática hasta alcanzar un nodo final.
*/
int is_final(Node *n)
{
  return 0 ;
}

/*
5.Implemente la función Node* DFS(Node* n, int* cont). Esta función realiza una búsqueda en profundidad a partir del nodo n. El algoritmo es el siguiente:

Cree un stack S (pila) e inserte el nodo.

Mientras el stack S no se encuentre vacío:

a) Saque y elimine el primer nodo de S.

b) Verifique si corresponde a un estado final, si es así retorne el nodo.

c) Obtenga la lista de nodos adyacentes al nodo.

d) Agregue los nodos de la lista (uno por uno) al stack S.

e) Libere la memoria usada por el nodo.

Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.

Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.

Puede ver un código de ejemplo en las diapos.
Recuerde revisar las operaciones del TDA Stack en el archivo list.h.
*/
Node *DFS(Node *initial, int *cont)
{

  return NULL ;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/

//Compile: gcc sudoku -o sudoku y ejecute: ./sudoku