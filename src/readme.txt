
EXECUTANDO O PROGRAMA
-------------------------------------------
  Após compilação, executar :

  ./teste < arquivo-entrada.txt , onde:

  ./teste é o produto da compilação e
  arquivo-entrada.txt é o arquivo de entrada contendo o grafo representado de acordo com a especificação.


ESTRUTURA E LEITURA
------------------------------------------
	O trabalho de implementação 2 , tem como objetivo criar uma função que encontra um conjunto minimal de trilhas que percorrem um grafo passado como entrada e retorna o numero mínimo k de trilhas. Chamada de cobertura_por_trilhas() tem como parâmetros a estrutura grafo já preenchida com a função le_grafo(), e a matriz de ponteiros "*cobertura[]", que conterá o conjunto das trilhas.
	A estrutura utilizada no trabalho 2 é a mesma do trabalho 1, tendo como representação do grafo uma lista de adjacência, logo teremos a struct _grafo representando cada vértice "v" e a struct _vertice, cada vizinho conectado a "v", segue as estruturas:

	typedef struct _grafo {
	  char nomeVert[1024];           // Armazena nome do vertice existente no grafo
	  struct _vertice *verticeAdj;    // Ponteiro para a lista dos vertices adjacentes ao nomeVert
	  struct _grafo *proxVertice;     // Ponteiro para os proximos vertices existentes no grafo
	} GrafoS;


	typedef struct _vertice {
	  char nomeVert[1024];           // Nome do vertice adjacente a algum outro vertice ja existente no grafo
	  struct _vertice *proximo;       // Ponteiro para o proximo vizinho do mesmo vertice
	  int visitado;
	} VerticeS;

	Por questões de busca no grafo a variável visitado foi adicionada a struct _vertice.
	Como a leitura é a mesma do trabalho 1, a função le_grafo() foi copiada juntamente com suas dependências que são processa_linha(), cria_vizinho(), busca_nomeVert_no_grafo().



FUNCIONAMENTO DO ALGORITMO
------------------------------------------------
	O algoritmo implementado para obter as trilhas segue com o pseudo-codigo apresentado na especificação do trabalho, sendo ele:

		1 - Seja I o conjunto de vértices de grau ímpar de G.
		2 - Se I não é vazio, acrescente um novo vértice v a G e acrescente arestas de forma que v seja vizinho de todos os vértices de I. Observe que agora o grafo G é euleriano.
		3 - Encontre uma trilha euleriana fechada T em G.
		4 - Devolva o conjunto dos segmentos maximais de T que não contém o vértice v.

		Uma trilha euleriana fechada em um grafo euleriano conexo G pode ser encontrada da seguinte maneira.

		 	1 - Seja v um vértice de G e seja T a trilha T=(v).

			2 - Enquanto existir em V(T) um vértice u de grau positivo em G,

				2.1 - encontre um ciclo C em G contendo o vértice u,
				2.2 - incorpore o ciclo C na trilha T, e
				2.3 - remova de G as arestas de C.
			3 - Devolva T

	Logo funções foram criadas para tirar do abstrato fazendo operações com ponteiros na estrutura escolhida, com isso o codigo que obtem as trilhas ficou da seguinte forma:

	unsigned int cobertura_por_trilhas(){
	 	k = n_vertices_impar();
	  	if(k != 0){
		    // grafo possui mais de uma trilha de cobertura
		    insere_v_aos_impares();
		    encontra_trilha_euleriana();
		    segmenta_trilha_euleriana();
		    return k/2;
		} else {
		    //grafo é euleriano, logo possui somente uma trilha de cobertura
		    encontra_trilha_euleriana();
		    segmenta_trilha_euleriana();
		    return 1;
		  }
	}
	
	Assim temos as funções insere_v_aos_impares(), encontra_trilha_euleriana(),segmenta_trilha_euleriana() sendo implementações dos comandos 2, 3, 4 do pseudo-código respectivamente.
	Foi necessário inserir um if (k != 0) , sendo k o número de vértices de grau ímpar no grafo, pois se k for 0 então o grafo será euleriano, assim não precisa inserir um vértice v aos vértices de grau ímpar, como manda o algoritmo.
	O código que encontra as trilhas eulerianas no grafo segue abaixo.

	void encontra_trilha_euleriana(){
		while (existe_vert_da_trilha_em_G_com_grau_positivo()){
		  encontra_circuito_no_grafo();
		  remove_arestas_circuito_do_grafo();
		  insere_circuito_na_trilha();
		}
	}
	
	Também teremos as funções existe_vert_da_trilha_em_g_com_grau_positivo(), encontra_circuito_no_grafo(), remove_arestas_circuito_do_grafo() e insere_circuito_na_trilha() relacionados com os comandos 2, 2.1, 2.3, 2.2, respectivamente com o peseudo_código de como encontrar uma trilha euleriana. Foi necessário remover as arestas do garfo de acordo com o circuito antes de inserir o circuito na trilha, pois quando o ciclo é incorporado a trilha a função remove_arestas_circuito_grafo() acaba tentando eliminar as arestas na trilha T, chamada no trabalho de trilhaEuleriana.
	Agora que foi passado o modulo principal de como obter o conjunto de trilhas, subfunções foram criadas para que as operações pudessem ocorrer, então segue a abaixo uma árvore das funções presentes no trabalho para que haja um entendimento das dependências e relações entre as funções.
               
-cobertura_por_trilhas()
	|
	|-n_vertices_impar()
	|-insere_v_aos_impares()
		|
		|-aloca_grafo()
		|-cria_vizinho()
	|
	|-encontra_trilha_euleriana()
		|
		|-existe_vert_da_trilha_em_G_com_grau_positivo()
		|-encontra_circuito_no_grafo()
			|
			|-inicializa_visitados ()
			|-n_arestas()
			|-aloca_vertice()
		|
		|-remove_arestas_circuito_do_grafo()
			|
			|-remove_aresta()
		|
		|-insere_circuito_na_trilha()
	|
	|-segmenta_trilha_euleriana()
		|
		|-insere_segmentos_da_trilha_no_grafo_vazio()
  		|-junta_segmentos_no_grafo ()
			|
			|-n_vertices()
		|
  		|-insere_segmentos_do_grafo_no_vetor ()
			|
			|-aloca_vertice()

	Ainda teremos a árvore da função le_grafo():
-le_grafo()
	|
	|-aloca_grafo()
	|-processa_linha()
    |-cria_vizinho()
    |-busca_nomeVert_no_grafo()
    |-cria_vizinho()
	

DESCRIÇÃO DAS FUNÇÕES
-----------------------------------------
    As funções da árvore le_grafo já foram apresentadas no primeiro trabalho, logo faremos as descrições as funções relevantes ao problema, explicitando agora seus parâmetros e as operações feitas.

    1) unsigned int cobertura_por_trilhas(grafo g, vertice *cobertura[])
        - Principal função do trabalho, tem como objetivo retornar número mínimo k de trilhas que percorrem o grafo, e também obter o conjunto das trilhas sendo a variável *cobertura[] do tipo vertice. Quando executada ela modifica o grafo g passado por parametro. Está função basicamente segue o pseudo-codigo. 

    2) unsigned int n_vertices_impar(grafo g)
        - Está retorna um inteiro n , sendo n o número de vértices de grau ímpar presentes no grafo g, este passado por parametro.
    
    3) void insere_v_aos_impares(grafo g)
        - Está insere um novo vértice chamado InseridoAosImpares na estrutura do grafo, conectado a todos os outros vértices de grau ímpar, então a função modifica o grafo g. A função só é chamada quando o grafo de entrada possui vértices ímpares.

    4) void encontra_trilha_euleriana(grafo g, vertice trilhaEuleriana)
        - Está tem como objetivo encontrar uma trilha euleriana no grafo g, ambos passados por parametro, a variável trilhaEuleriana é a cabeça de uma lista encadeada dos vértices da trilha.

    5) int existe_vert_da_trilha_em_G_com_grau_positivo(grafo g,vertice trilhaEuleriana, char *vert)
        - Está verifica se existe algum vértice em trilhaEuleriana presento no grafo g de grau positivo, se sim retorna 1, se não 0. Se existir o nome do vértice é copiado para a variável vert passada por parametro.
 
    6) void encontra_circuito_no_grafo(grafo g,char* vert, vertice circuito);
        - Com o objetivo de encontrar um circuito partindo do vertice de nome vert no grafo g, o caminho é gravado na variavel circuito, sendo uma lista encadeada dos vértices.

    7) void inicializa_visitados (grafo g)
        - Está inicializa em 0 o atributo visitado nas estruturas vertices no grafo.

    8) void remove_arestas_circuito_do_grafo(grafo g, vertice circuito)
        - Remove todas as conexões presentes no circuito do grafo g.

    9) void remove_aresta (grafo g, char* vertProcurado, char* vertRemovido)
        - Está remove na estrutura grafo a aresta dos vertices passados por parametro, a função vai ate a estrutura grafo com nome vertProcurado e remove da lista encadeada a estrutura vertice corespondente ao nome de vertRemovido.

    10) void insere_circuito_na_trilha(vertice trilhaEuleriana, vertice circuito)
        - A função insere a lista circuito na lista trilhaEuleriana, se acordo com o vertice que fecha o circuito, aqui basicamente ocorre uma troca de ponteiros. 
    
    11) void segmenta_trilha_euleriana(grafo g,vertice trilhaEuleriana,vertice *cobertura[])
        - Após obter a trilha euleriana é necessário encontrar os segmentos maximais nela, para isso a estrutura grafo já sem arestas devido a operações anteriores será utilizado para a segmentação. os segmentos divididos pelo vértice inserido serão colocados separamente na lista, apos isso segmentos que podem ser unidos serão e por fim os segmentos são copiados para a cobertura.

    12) void insere_segmentos_da_trilha_no_grafo_vazio(grafo g, vertice trilhaEuleriana)
        - Aqui os segmentos na trilhaEuleriana, separados pelo vertice anteriormente inserido aos impares serão postos separadamente no grafo g que está vazio, cada segmento será conectada a um vértice do grafo.

    13) void junta_segmentos_no_grafo (grafo g)
        - Os segmentos ja separados no grafo podem não ser maximais existindo possiveis conexões entre eles, está função junta esses segmentos se existirem.


    14) void insere_segmentos_do_grafo_no_vetor (g grafo g,vertice *cobertura[])
        - Está por fim, insere os segmentos separados na estrutura do grafo em cobertura, seguindo especificação.





	


