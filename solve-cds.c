/*
    Trabalho Pratico Matematica Discreta

    Sistema: Solve CDS

    Modo de compilacao [PARA A PRODUCAO [!!!APAGAR ANTES DE ENVIAR O PROJETO]]:
        * gcc nob.c -o nob    # A aplicacao que ira buildar o projeto
        * ./nob               # Compilcacao do projeto atual, usando o builder
        * ./output/solve-cds  # Execucao do projeto atual

    Modo de compilacao [PARA O DIEGO]: gcc solve-cds.c -o solve-cds.bin -lm

    Alunos:
        @LucasAPV
        @AnaClara
        @RafaelaLarissa
        @PedroLucas
        @CristianoEDS
*/

#include <stdio.h>
#include <stdlib.h>
#include "test.h"
/*
    * @LucasAPV

    * Para podermos dar mensagem de erro e relatorios de forma mais bem apresentada, criei funcoes para mudar a cor do texto apresentado

    * O modo de uso e simples, basta chamar a cor desejada antes do print que deseja fazer, e apos isso, de o reset das cores

    * Exemplo:
        * yellow(stdout);
        * printf("ESSE TEXTO SERA EM AMARELO!\n");
        * reset(stdout); // Volta as cores normais do terminal
    * O stream nada mais e onde o texto sera colocado:
        * stdout => Saida padrao
        * stderr => Saida de erro
        * FILE   => Um arquivo desejado
*/

void red(FILE *stream){
    fprintf(stream, "\033[1;31m");
}

void green(FILE *stream){
    fprintf(stream, "\033[1;32m");
}

void yellow(FILE *stream){
    fprintf(stream, "\033[1;33m");
}

void reset(FILE *stream){
    fprintf(stream, "\033[0m");
}

/*
    * @LucasAPV
    * Um macro que criei para poder ajudar no DEBUG do sistema.

    * Para usar, basta chamar o macro passando somente a variavel que quer, assim o output sera:
        * [DEBUG] nome_da_variavel = valor_da_variavel

    * Exemplo:
        * int idade = 10;
        * DBG(idade); // out: [DEBUG] idade = 10
*/

#define DBG(x) do { \
    yellow(stdout); \
    fprintf(stdout, "[DEBUG] %s = ", #x); \
    reset(stdout); \
    green(stdout); \
    _Generic((x), \
        int: fprintf(stdout, "%d", x), \
        float: fprintf(stdout, "%f", x), \
        double: fprintf(stdout, "%lf", x), \
        char*: fprintf(stdout, "\"%s\"", x), \
        char: fprintf(stdout, "'%c'", x), \
        default: fprintf(stdout, "%p", (void*)(x)) \
    ); \
    reset(stdout);\
    fprintf(stdout, "\n"); \
} while (0)



void usage(){
    yellow(stderr);
    fprintf(stderr, "[USAGE]");
    reset(stderr);
    fprintf(stderr, " ./solve-cdn.bin");
    green(stderr);
    fprintf(stderr, " <arq-dist>");
    fprintf(stderr, " <limite>");
    fprintf(stderr, " <arq-saida.dot>\n");
    reset(stderr);
}

void error(FILE *stream){
    red(stream);
    fprintf(stream, "\n[ERROR]");
    reset(stream);
}

/*
    * @LucasAPV

    * Funcao auxiliar para conferir se o numero de argumentos passados foi a quantidade correta.
*/

int is_argc_correct(int argc){
    if(argc != 4){
        error(stderr);
        fprintf(stderr, " QUANTIDADE DE PARAMENTROS INCORRETO!\n");
        usage();
        printf("\n");
        return 0;
    }

    return 1;
}

/*
    * @LucasAPV
    * Funcao auxiliar para encontrar o no com a maior quantidade de conexoes, no caso da heurisca seria o v_0.
    * Podemos usar o qty_cols tanto para as colunas e linhas pois a matriz adj_mtx e quadrada
*/

typedef struct {
    int line;
    int col;
} LineCol;

/*
    * @LucasAPV
    * Retorno qual no tem a maior quntidade de conexoes. Esse no e representado pela linha matriz
*/

int find_biggest_conn(int *adj_mtx[], int qty_cols){
    if(qty_cols <= 0) return -1;

    int best_node = 0;
    int max_conn = -1;

    for(int i = 0; i < qty_cols; ++i){
        int sum = 0;
        int j = 0;
        for(j = 0; j < qty_cols; ++j){
            if(i != j && adj_mtx[i][j] == 1)
                sum += adj_mtx[i][j];
        }

        if(sum > max_conn) {
            best_node = i;
            max_conn = sum;
        }
    }

    return best_node;
}

int does_make_connection(int *adj_mtx[], int line, int col){
        return adj_mtx[line][col];
}

int greed_most_gain(int *adj_mtx[], int *node_state, int qty_nodes){
    int best_node = 0;
    int max_gain = 0;
    for (int i = 0; i < qty_nodes; ++i) {
        if(node_state[i] == 2){
            continue;
        }

        int gain = 0;

        if(node_state[i] == 0){
            gain += 1;
        }

        for (int j = 0; j < qty_nodes; ++j) {
            if(i != j && adj_mtx[i][j] == 1 && node_state[j] == 0){
                gain += 1;
            }
        }

        if(gain > max_gain){
            max_gain = gain;
            best_node = i;
        }
    }

    return best_node;
}


void find_neighbors(int *adj_mtx[], int mtx_size, int *node_state, int node, int* not_covered_qty){
    /*
        * Se na matrix ha a conexao no no que o nosso node toca, entao marcaremos como covered (1)
    */

    if(node < 0 || node >= mtx_size) return;

    if(node_state[node] != 2) {
        if(node_state[node] == 0 && *not_covered_qty > 0) {
            *not_covered_qty -= 1;
        }

        node_state[node] = 2;
    }

    for(int i = 0; i < mtx_size; ++i){
        if (node != i && adj_mtx[node][i] == 1 && node_state[i] == 0) {
            node_state[i] = 1;
            if (*not_covered_qty > 0) {
                *not_covered_qty -= 1;
            }
        }
    }
}

/*
    * @LucasAPV
    * Como forma de garantir que o array nao tera posicoes nulas, colocarei todas as suas posicoes como zero
*/

void init_arr_with_zeros(int *arr, int size){
    for (int i = 0; i < size; ++i ) {
        arr[i] = 0;
    }
}


/*
    *@LucasAPV

    * int qty_nodes ~> quantiade max de nos, representado no texto por MAX.
*/

int* guha_keller_heuristic_cds_solve(int *adj_mtx[], int qty_cols, int qty_nodes){

    if(qty_nodes <= 0 || qty_cols <= 0){
        return NULL;
    }


    int *dom_conx = malloc(sizeof(int) * qty_nodes);
    int *node_state = malloc(sizeof(int) * qty_nodes);

    if(!node_state || !dom_conx){
        free(node_state);
        free(dom_conx);
        return NULL;
    }

    init_arr_with_zeros(dom_conx, qty_nodes);
    init_arr_with_zeros(node_state, qty_nodes);

    /*
        * No atual com a maior quantiade de conexoes
    */
    int current_node = find_biggest_conn(adj_mtx, qty_cols);
    int not_covered_qty = qty_nodes;

    while (not_covered_qty > 0 && current_node != -1) {
        /*
            * @LucasAPV
            * Vou selecinar todos que o atual toca, e ja atualizar a quantidade de nao cobertos
        */

        find_neighbors(adj_mtx, qty_cols, node_state, current_node, &not_covered_qty);
        dom_conx[current_node] = 2;

        if(not_covered_qty <= 0) {
            break;
        }

        current_node = greed_most_gain(adj_mtx, node_state , qty_nodes);

        /*
            * @LucasAPV
            * O loop continuara ate que acabe a quantiade de nos nao tocados seja zero.
            * E assim, garantimos que pegaremos os nos com maior qtd de vizinhos, a metodologia gulosa
        */
    }

    free(node_state);
    return dom_conx;
}



/*Primeiro de tudo, temos que tentar carregar o arquivo aqui dentro*/
int main(int argc, char *argv[]){
    if(!is_argc_correct(argc)) return 1;

    char* distances_file = argv[1];
    float reach          = atof(argv[2]);
    char* output_file    = argv[3];

    /*PROCESSAMENTO A SE FAZER*/

    /*Criacao do arquivo final*/
    
    //////////////////////////////////////
    /*
        * @LucasAPV
        * Fiz uma funcao para testar o que eu criei, e funcionou como esperado. 
        * Portanto, ao finalizarmos o projeto, 
        * iremos retirar tudo o que for de teste para garantir a boa execucao geral 
    */
    int n = 4;
        int r0[4] = {0, 1, 1, 1};
        int r1[4] = {1, 0, 0, 0};
        int r2[4] = {1, 0, 0, 0};
        int r3[4] = {1, 0, 0, 0};
        int *adj[4] = {r0, r1, r2, r3};

        run_test(adj, n, n);

    printf("Hello World!!\n");
}