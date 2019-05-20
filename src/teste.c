#include <stdio.h>

#include "grafo.h"


//------------------------------------------------------------------------------

int main(void) {

  grafo g = NULL;

  g = le_grafo(stdin);

  vertice *cobertura [n_trilhas_cobertura(g)];
  if ( !g ) printf("%s\n","Grafo Vazio" );
  printa_grafo (g);

  printf ("O grafo possui %u vertices e %u arestas\n", n_vertices(g), n_arestas(g));
  printf("O grafo possui %u trilhas de cobertura\n", cobertura_por_trilhas(g, cobertura));
  return ! destroi_grafo(g);
}
