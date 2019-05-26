#include <stdio.h>

#include "grafo.h"


//------------------------------------------------------------------------------

int main(void) {

  grafo g = NULL;
  unsigned int i = 0, j =0;
  g = le_grafo(stdin);
  printa_grafo(g);
  // grafo copia = copia_grafo (g);
  // printa_grafo(copia);
  g = escreve_grafo(stdout, g);
  unsigned int n = n_vertices_impar(g)/2 ;
  // printf("%d\n", n);


  vertice **cobertura;
  printf("numero de trilhas %u\n", n_vertices_impar(g)/2);
  if ( !g ) printf("%s\n","Grafo Vazio" );
  // printa_grafo (g);
  printf ("O grafo possui %u vertices e %u arestas\n", n_vertices(g), n_arestas(g));
  unsigned int k = cobertura_por_trilhas(g, &cobertura);
  printa_grafo(g);
  printf("O grafo possui %u trilhas de cobertura\n", k);
  // printf("%s\n", cobertura[0][2]->nomeVert);
  // printf("%d\n", n);

  if (k == 1){
    while (cobertura[0][j]){
      printf("cobertura [0][%d] = %s\n", j, cobertura[i][j]->nomeVert);
      ++j;
    }
    printf("cobertura [0][%d] = %s\n", j, cobertura[i][j]->nomeVert);

  }else {
    for (i = 0 , j = 0 ; i < n; ++i, j = 0) {
      while (cobertura[i][j]){
        printf("cobertura [%d][%d] = %s\n", i,j, cobertura[i][j]->nomeVert);
        ++j;
        // free(cobertura[i][j]);
      }
      printf("cobertura [%d][%d] = %s\n",i, j, cobertura[i][j]->nomeVert);
      // free(cobertura[i]);
    }
    // free(cobertura);
  }


  return ! destroi_grafo(g);

}
