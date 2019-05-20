#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grafo.h"

unsigned int n_trilhas_cobertura(grafo g){
  unsigned int n = 0, grau = 0;
  grafo auxGrafo = g;
  vertice auxVertice = NULL;

  while (auxGrafo){
    auxVertice = auxGrafo->verticeAdj;
    grau = 0;
    while (auxVertice){
      ++grau;
      auxVertice = auxVertice->proximo;
    }
    if (!(grau % 2 == 0)){
      ++n;
    }
    auxGrafo = auxGrafo->proxVertice;
  }
  return n;
}

unsigned int cobertura_por_trilhas(grafo g, vertice *cobertura[]){
  unsigned int k;
  vertice trilhaEuleriana = NULL;
  k = n_trilhas_cobertura(g);

  if(k != 0){

    // insere_v_aos_impares(g);
    // encontra_trilha_euleriana(g, trilhaEuleriana);

    return k/2;
  } else {
    return 1;
  }

}


unsigned int n_vertices(grafo g){
  unsigned int n = 0;
  grafo aux = g;
  while (aux){
    ++n;
    aux = aux->proxVertice;
  }
  return n;
}

unsigned int n_arestas(grafo g){
  unsigned int n = 0;
  grafo auxGrafo = g;
  vertice auxVertice = NULL;

  while (auxGrafo){
    auxVertice = auxGrafo->verticeAdj;
    while (auxVertice){
      ++n;
      auxVertice = auxVertice->proximo;
    }
    auxGrafo = auxGrafo->proxVertice;
  }
  return n/2;
}


grafo aloca_grafo (void){
  // Aloca espaço em memoria para a estrutura grafo
  grafo g = (grafo) malloc( sizeof(GrafoS) );
  // Caso sucesso, inicializa a estrutura
  if (g){
    g->verticeAdj = NULL;
    g->proxVertice = NULL;
    strcpy (g->nomeVert, "\0");
  }
  return g;
}


grafo le_grafo(FILE *input){
  grafo cabeca = NULL;
  grafo aux = NULL;
  bool first = true;

  // instancia o inicio do grafo
  cabeca = aloca_grafo();
  aux = cabeca;
  char linha[2048], vert1Linha[1024],vert2Linha[1024];

  //Laço para ler linha por linha do arquivo
  fgets (linha,2055,input);
  while (!feof(input)){

    //ignora linha vazia
    if ( strcmp(linha,"\n")) {

      //Separa os vertices contidos na linha
      processa_linha (linha, vert1Linha, vert2Linha);
      // Na primeira interação o vertice deve ser inserido na cabeca, intancia ja criada
      if (first){
        strcpy(cabeca->nomeVert,vert1Linha);

        // Se houver dois vertices na linha, então aloca a estrutura para o segundo vertice
        // e cria a vizinhança entre eles
        if (strcmp(vert2Linha, "\0")){
          aux = aloca_grafo();
          strcpy(aux->nomeVert,vert2Linha);
          cabeca->proxVertice = aux;
          cria_vizinho (cabeca, vert1Linha, vert2Linha);
          cria_vizinho (cabeca, vert2Linha, vert1Linha);

        }
        first = false;
      }
      // Apos a primeira interação , sao instanciados a estrutura para novos vertices
      // e encadeadas ao final do grafo
      else {

        // Verifica se o vertice ja pertence ao grafo
        if( !busca_nomeVert_no_grafo (cabeca, vert1Linha)){
          aux->proxVertice = aloca_grafo ();
          strcpy(aux->proxVertice->nomeVert,vert1Linha);
          aux = aux->proxVertice;
        }
        // Se houver dois vertices na linha, então aloca a estrutura para o segundo vertice
        // e cria a vizinhança entre eles
        if (strcmp(vert2Linha, "\0")){

          // Verifica se o vertice ja pertence ao grafo
          if( !busca_nomeVert_no_grafo (cabeca, vert2Linha)){
            aux->proxVertice = aloca_grafo ();
            strcpy(aux->proxVertice->nomeVert,vert2Linha);
            aux = aux->proxVertice;
          }

          // Cria a adjacencia entre eles no grafo
          cria_vizinho (cabeca, vert1Linha, vert2Linha);
          cria_vizinho (cabeca, vert2Linha, vert1Linha);
        }
      }
    }
    fgets (linha,2055,input);
  }

  // retorna o inicio do grafo
  return cabeca;
}


vertice aloca_vertice (void){
  // Aloca espaço em memoria para a estrutura vertice
  vertice v = (vertice) malloc( sizeof(VerticeS) );
  // Caso sucesso, inicializa a estrutura
  if (v){
    v->proximo = NULL;
    strcpy (v->nomeVert, "\0");
  }
  return v;
}

void cria_vizinho (grafo cabeca, char *vert1Linha, char *vert2Linha){
  grafo aux = cabeca;
  vertice auxV = NULL;

  while (aux){
    if (!strcmp(aux->nomeVert, vert1Linha)){
      if (aux->verticeAdj){
        auxV = aux->verticeAdj;
        while(auxV->proximo){
          auxV = auxV->proximo;
        }
        auxV->proximo = aloca_vertice ();
        strcpy(auxV->proximo->nomeVert, vert2Linha);
      } else {
        aux->verticeAdj = aloca_vertice ();
        strcpy(aux->verticeAdj->nomeVert, vert2Linha);
      }
    }
    aux = aux->proxVertice;
  }
}

void processa_linha (char *linha,char *vert1,char *vert2){
  int k = 0, j = 0;
  strcpy (vert1, "\0");
  strcpy (vert2, "\0");
  while (linha[k] != ' ' && linha[k] != '\n'){
    vert1[k] = linha[k];
    ++k;
  }
  vert1[k] = '\0';
  ++k;
  while (linha[k + j] != ' ' && linha[k + j] != '\n'){
    vert2[j] = linha[k + j];
    ++j;
  }
  vert2[j] = '\0';
}

int destroi_grafo(grafo g){
  grafo lixoG = g, atualG = g;
  vertice lixoV = NULL, atualV = NULL;
  while (atualG){
    atualV = atualG->verticeAdj;
    while (atualV){
      lixoV = atualV;
      atualV = atualV->proximo;
      free(lixoV);
    }
    lixoG = atualG;
    atualG = atualG->proxVertice;
    free(lixoG);
  }
  if (g){
    return 0;
  }
  return 1;
}

int busca_nomeVert_no_grafo (grafo g, char * vert){
  grafo atual = g;
  while (atual){
    if (!strcmp (atual->nomeVert, vert)){
      return 1;
    }
    atual = atual->proxVertice;
  }
  return 0;
}

void printa_grafo (grafo g){
  grafo aux = g;
  vertice auxV = NULL;
  while (aux){
    printf("%s -> ", aux->nomeVert );
    auxV = aux->verticeAdj;
    while (auxV){
      printf("%s ", auxV->nomeVert);
      auxV = auxV->proximo;
    }
    printf("\n");
    aux = aux->proxVertice;
  }
  printf("\n");
}
