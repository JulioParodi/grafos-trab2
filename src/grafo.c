#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grafo.h"


// typedef struct _grafo {
//   char nomeVert[1024];           // Armazena nome do vertice existente no grafo
//   struct _vertice *verticeAdj;    // Ponteiro para os vertices adjacentes ao nomeVert
//   struct _grafo *proxVertice;     // Ponteiro para os proximos vertices existentes no grafo
// }GrafoS;
//
// typedef struct _vertice {
//   char nomeVert[1024];           // Nome do vertice adjacente a algum outro vertice ja existente no grafo
//   struct _vertice *proximo;       // Ponteiro para o proximo vizinho do mesmo vertice
//   int visitado;
// }VerticeS;

//


grafo copia_grafo( grafo g){

  if (g == NULL){
    return NULL;
  }
  grafo auxGrafo = g;
  grafo copia = aloca_grafo ();
  strcpy (copia->nomeVert, auxGrafo->nomeVert );
  grafo auxCopia = copia;
  vertice auxVertCopia, auxVert;

  while (auxGrafo){
    auxVert = auxGrafo->verticeAdj;

    if (auxVert){

      auxCopia->verticeAdj = aloca_vertice();
      strcpy (auxCopia->verticeAdj->nomeVert, auxVert->nomeVert );
      auxVertCopia = auxCopia->verticeAdj;
      auxVert = auxVert->proximo;

      while (auxVert) {
        auxVertCopia->proximo = aloca_vertice();
        auxVertCopia = auxVertCopia->proximo;
        strcpy (auxVertCopia->nomeVert, auxVert->nomeVert );
        auxVert = auxVert->proximo;
      }

    }
    auxGrafo = auxGrafo->proxVertice;
    if (auxGrafo){
      auxCopia->proxVertice = aloca_grafo();
      auxCopia = auxCopia->proxVertice;
      strcpy (auxCopia->nomeVert, auxGrafo->nomeVert );
    }
  }
  return copia;
}
grafo escreve_grafo(FILE *output, grafo g){
  grafo auxGrafo = g;
  vertice auxVert;
  inicializa_visitados(g);
  while (auxGrafo){
    auxVert = auxGrafo->verticeAdj;
    while (auxVert) {
      if (!auxVert->visitado){
        fprintf(output, "%s %s\n", auxGrafo->nomeVert, auxVert->nomeVert);
        auxVert->visitado = 1;
        insere_visitado(g,auxVert->nomeVert,auxGrafo->nomeVert);

      }

      auxVert = auxVert->proximo;
    }

    auxGrafo = auxGrafo->proxVertice;
  }
  return g;
}

void insere_visitado (grafo g, char* procurado, char* visitado){
  grafo auxGrafo = g;
  vertice auxVert;
  while (auxGrafo && strcmp(auxGrafo->nomeVert, procurado) != 0){
    auxGrafo = auxGrafo->proxVertice;
  }

  auxVert = auxGrafo->verticeAdj;

  while (auxVert && strcmp(auxVert->nomeVert,visitado) != 0){
    auxVert = auxVert->proximo;
  }
  auxVert->visitado = 1;

}
void printa_grafo (grafo g){
  grafo aux = g;
  vertice auxV = NULL;
  while (aux){
    printf("%s -> ", aux->nomeVert );
    auxV = aux->verticeAdj;

    while (auxV){
      printf("%s ",auxV->nomeVert);
      auxV = auxV->proximo;
    }
    printf("\n");
    aux = aux->proxVertice;
  }
  printf("\n");
}
char *nome(vertice v){
  return v->nomeVert;
}

vertice vertice_nome(grafo g, char *nome){
  grafo auxGrafo = g;
  vertice auxVert = auxGrafo->verticeAdj;

  while (auxGrafo) {
    auxVert = auxGrafo->verticeAdj;
    while (auxVert) {
      if (strcmp(nome, auxVert->nomeVert) == 0){
        return auxVert;
      }
      auxVert = auxVert->proximo;
    }
    auxGrafo = auxGrafo->proxVertice;
  }
  return NULL;
}

vertice aloca_vertice (void){
  // Aloca espaço em memoria para a estrutura vertice
  vertice v = (vertice) malloc( sizeof(VerticeS) );
  // Caso sucesso, inicializa a estrutura
  if (v){
    v->proximo = NULL;
    strcpy (v->nomeVert, "\0");
    v->visitado = 0;
  }
  return v;
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

unsigned int n_vertices_impar(grafo g){
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

int existe_vert_da_trilha_em_G_com_grau_positivo(grafo g,vertice trilhaEuleriana, char* vert){
  vertice auxTrilha = trilhaEuleriana;
  grafo auxGrafo = g;
  strcpy(vert, "\0");
  while (auxTrilha) {
    auxGrafo = g;
    while (auxGrafo){
      if (!strcmp (auxGrafo->nomeVert, auxTrilha->nomeVert)){
        if(auxGrafo->verticeAdj){
          strcpy(vert, auxGrafo->nomeVert);
          return 1;
        }
      }
      auxGrafo = auxGrafo->proxVertice;
    }
    auxTrilha = auxTrilha->proximo;
  }
  return 0;
}

void inicializa_visitados (grafo g){
  grafo auxGrafo = g;
  vertice auxVert;
  while (auxGrafo){
    auxVert = auxGrafo->verticeAdj;
    while (auxVert){
      auxVert->visitado = 0;
      auxVert = auxVert->proximo;
    }
    auxGrafo = auxGrafo->proxVertice;
  }
}

void encontra_circuito_no_grafo(grafo g,char *vert ,vertice circuito){
  grafo auxGrafo = g;
  grafo pai = NULL;
  vertice auxVert = NULL, auxCircuito = NULL;
  int achouCircuito = 1;
  unsigned int cont = 0;
  auxCircuito = circuito;
  inicializa_visitados (g);

  while ( strcmp(auxGrafo->nomeVert, vert) != 0){
    auxGrafo = auxGrafo->proxVertice;
  }
  pai = auxGrafo;
  unsigned int maxInteracoes = n_arestas(g);
  while (achouCircuito && cont < maxInteracoes) {

    strcpy (auxCircuito->nomeVert, auxGrafo->nomeVert);
    auxCircuito->proximo = aloca_vertice();
    auxCircuito = auxCircuito->proximo;

    auxVert = auxGrafo->verticeAdj;
    while (auxVert){
      if (strcmp(auxVert->nomeVert, pai->nomeVert) == 0){
        auxVert->visitado = 1;
      }
      if( strcmp(auxVert->nomeVert, vert) == 0 && !auxVert->visitado){
        if (!(strcmp(pai->nomeVert, vert) == 0)){
          achouCircuito = 0;
          strcpy (auxCircuito->nomeVert, auxVert->nomeVert);
          auxCircuito->proximo = NULL;
        }
      }
      auxVert = auxVert->proximo;
    }

    auxVert = auxGrafo->verticeAdj;
    while (auxVert->visitado && auxVert){
      auxVert = auxVert->proximo;
    }

    if (auxVert == NULL){
      auxGrafo = pai;
    }  else {
      pai = auxGrafo;
      auxVert->visitado = 1;
      auxGrafo = g;
      while ( strcmp(auxGrafo->nomeVert, auxVert->nomeVert) != 0){
        auxGrafo = auxGrafo->proxVertice;
      }
    }
    cont++;
  }

}

void remove_aresta (grafo g, char* vertProcurado, char* vertRemovido){
  grafo auxGrafo = g;
  vertice auxVert = NULL, lixo = NULL;

  while ( strcmp(auxGrafo->nomeVert, vertProcurado) != 0){
    auxGrafo = auxGrafo->proxVertice;
  }

  if (strcmp (auxGrafo->verticeAdj->nomeVert, vertRemovido) == 0){
    lixo = auxGrafo->verticeAdj;
    auxGrafo->verticeAdj = auxGrafo->verticeAdj->proximo;
    free (lixo);
  }else {
    auxVert = auxGrafo->verticeAdj;
    while (auxVert->proximo){
      if (!(strcmp (auxVert->proximo->nomeVert, vertRemovido))){
        lixo = auxVert->proximo;
        auxVert->proximo = auxVert->proximo->proximo;
        free (lixo);
      }
      if (auxVert->proximo != NULL){
        auxVert = auxVert->proximo;
      }
    }
  }
}

void remove_arestas_circuito_do_grafo(grafo g, vertice circuito){
  vertice auxCircuito = circuito;

  while (auxCircuito->proximo){
    remove_aresta (g, auxCircuito->nomeVert ,auxCircuito->proximo->nomeVert );
    remove_aresta (g, auxCircuito->proximo->nomeVert ,auxCircuito->nomeVert );
    auxCircuito = auxCircuito->proximo;
  }
}

void insere_circuito_na_trilha(vertice trilhaEuleriana, vertice circuito){
  vertice auxTrilha = trilhaEuleriana, auxCircuito = circuito, auxTroca = NULL;

  while (strcmp (auxTrilha->nomeVert, circuito->nomeVert) != 0){
    auxTrilha = auxTrilha->proximo;
  }
  auxTroca = auxTrilha->proximo;
  auxTrilha->proximo = circuito->proximo;
  while (auxCircuito->proximo){
    auxCircuito = auxCircuito->proximo;
  }
  auxCircuito->proximo = auxTroca;
}

// Esta função modificará o grafo g,
void encontra_trilha_euleriana(grafo g, vertice trilhaEuleriana){
  vertice circuito =  aloca_vertice();
  char vert[1024];
  strcpy (trilhaEuleriana->nomeVert, g->nomeVert);

  while (existe_vert_da_trilha_em_G_com_grau_positivo(g, trilhaEuleriana, vert)){
    encontra_circuito_no_grafo(g,vert,circuito);
    remove_arestas_circuito_do_grafo(g,circuito);
    insere_circuito_na_trilha(trilhaEuleriana,circuito);
  }
}

void insere_segmentos_da_trilha_no_grafo_vazio(grafo g, vertice trilhaEuleriana){
  grafo auxGrafo = g;
  vertice auxTrilha = trilhaEuleriana, lixo = NULL;

  auxGrafo->verticeAdj = auxTrilha;
  while (auxTrilha->proximo) {
    if (strcmp(auxTrilha->proximo->nomeVert, "InseridoNosImpares") == 0 && (auxTrilha->proximo->proximo != NULL)){
      auxGrafo = auxGrafo->proxVertice;
      auxGrafo->verticeAdj = auxTrilha->proximo->proximo;
      lixo = auxTrilha->proximo;
      auxTrilha->proximo = NULL;
      free(lixo);
      auxTrilha = auxGrafo->verticeAdj;
    }else {
      auxTrilha = auxTrilha->proximo;
    }
  }
}

void junta_segmentos_no_grafo (grafo g){
  grafo auxCabeca = g, auxPercorre;
  vertice cauda;
  unsigned int n = n_vertices(g);
  for (unsigned int i = 0; i < n; ++i){
    if (auxCabeca->verticeAdj){
      auxPercorre = auxCabeca->proxVertice;
      while (auxPercorre){
        if (auxPercorre->verticeAdj){
          cauda = auxPercorre->verticeAdj;
          while (cauda->proximo){
            cauda = cauda->proximo;
          }
          if (strcmp(auxCabeca->verticeAdj->nomeVert, cauda->nomeVert) == 0){
            cauda->proximo = auxCabeca->verticeAdj->proximo;
            free (auxCabeca->verticeAdj);
            auxCabeca->verticeAdj = NULL;
          }
        }
      auxPercorre = auxPercorre->proxVertice;
      }
    }
    auxCabeca = auxCabeca->proxVertice;
  }
}

void insere_segmentos_do_grafo_no_vetor (grafo g,vertice *cobertura[]){
  grafo auxGrafo = g;
  vertice auxVert = NULL;
  unsigned int i = 0 , j = 0;

  while (auxGrafo){
    if (auxGrafo->verticeAdj){
      j = 0;
      auxVert = auxGrafo->verticeAdj;
      while (auxVert){
        ++j;
        auxVert = auxVert->proximo;
      }
      cobertura[i] = (vertice*) malloc ((1 + j) * sizeof(vertice));
      if (cobertura[i] == NULL){
        printf("%s\n", "malloc: FALTA ESPAÇO NA MEMORIA" );
      }

      j = 0;
      auxVert = auxGrafo->verticeAdj;
      while (auxVert ){
        cobertura[i][j] = aloca_vertice();
        strcpy (cobertura[i][j]->nomeVert, auxVert->nomeVert);
        printf("inserido %s\n", cobertura[i][j]->nomeVert);
        ++j;
        auxVert = auxVert->proximo;
      }
      cobertura[i][j] = NULL;
      ++i;
    }
    auxGrafo = auxGrafo->proxVertice;
  }
}

void segmenta_trilha_euleriana(grafo g,vertice trilhaEuleriana,vertice *cobertura[]){

  insere_segmentos_da_trilha_no_grafo_vazio(g, trilhaEuleriana);
  junta_segmentos_no_grafo (g);
  insere_segmentos_do_grafo_no_vetor (g, cobertura);
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

void insere_v_aos_impares(grafo g){
  unsigned int grau = 0;
  grafo auxGrafo = g;
  grafo vertInserido = g;
  vertice auxVertice = NULL;
  vertice pai = NULL;

  while (auxGrafo->proxVertice){
    auxGrafo = auxGrafo->proxVertice;
  }
  vertInserido = aloca_grafo();
  strcpy(vertInserido->nomeVert, "InseridoNosImpares");
  auxGrafo->proxVertice = vertInserido;

  auxGrafo = g;

  while (auxGrafo){
    auxVertice = auxGrafo->verticeAdj;
    grau = 0;
    while (auxVertice){
      ++grau;
      pai = auxVertice;
      auxVertice = auxVertice->proximo;
    }
    if (!(grau % 2 == 0)){
      pai->proximo = aloca_vertice();
      strcpy (pai->proximo->nomeVert, "InseridoNosImpares");
      cria_vizinho (g, vertInserido->nomeVert, auxGrafo->nomeVert);
    }
    auxGrafo = auxGrafo->proxVertice;
  }

}

unsigned int cobertura_por_trilhas(grafo g, vertice **cobertura[]){
  unsigned int k = 0;
  vertice trilhaEuleriana = aloca_vertice();

  k = n_vertices_impar(g);
  *cobertura = (vertice**) malloc ((k/2) * sizeof(vertice*));

  grafo copia = copia_grafo(g);
  if(k != 0){
    // grafo possui mais de uma trilha de cobertura
    insere_v_aos_impares(copia);
    encontra_trilha_euleriana(copia, trilhaEuleriana);
    segmenta_trilha_euleriana(copia,trilhaEuleriana, *cobertura);
    destroi_grafo(copia);
    return k/2;
  } else {
    //grafo é euleriano, logo possui somente uma trilha de cobertura
    encontra_trilha_euleriana(copia, trilhaEuleriana);
    segmenta_trilha_euleriana(copia, trilhaEuleriana, *cobertura);
    destroi_grafo(copia);

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
