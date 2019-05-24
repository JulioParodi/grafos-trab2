#include <stdio.h>

#include "grafo.h"


//------------------------------------------------------------------------------

int main(void) {

  grafo g = NULL;

  g = le_grafo(stdin);
  int n = n_vertices_impar(g)/2 ;
  vertice *cobertura [n];
  printf("numero de trilhas %u\n", n_vertices_impar(g)/2);
  if ( !g ) printf("%s\n","Grafo Vazio" );
  // printa_grafo (g);

  printf ("O grafo possui %u vertices e %u arestas\n", n_vertices(g), n_arestas(g));
  printf("O grafo possui %u trilhas de cobertura\n", cobertura_por_trilhas(g, cobertura));
  for (int i = 0 , j = 0 ; i < n; ++i, j = 0) {
    while (cobertura[i][j]){
      printf("cobertura [%d][%d] = %s\n", i,j, cobertura[i][j]->nomeVert);
      ++j;
    }
  }
  printf("%s\n", "FIM");
  return 0; //destroi_grafo(g);
}
