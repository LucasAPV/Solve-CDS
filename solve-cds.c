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

int find_biggest_conn(int *adj_mtx[], qty_cols){
    int biggest = adj_mtx[0][0];
    
    for(int i = 0; i < qty_cols; ++i){
        int sum = 0;
        for(int j = 0; j < qty_cols; ++j){
            sum += adj_mtx[i][j];
        }
        
        if(sum > biggest) {
            biggest = i;
        }
    }
    
    return biggest;
}

int make_connection(int *adj_mtx[], int line, int col){
        return adj_mtx[line][col];
}

void diff_of_sets(int *set, int size_set, ){
    
}

int* guha_keller_heuristic_cds_solve(int *adj_mtx[], int qty_cols, int *nodes, int qty_nodes){
    int *dom_conx = malloc(sizeof(int) * qty_nodes);
    int *uncovered_and_uncovered_nodes = malloc(sizeof(int) * qty_nodes);
    int biggest_conn = find_biggest_conn(adj_mtx, qty_cols);
    
    dom_conx[0] = biggest_conn;
    diff_of_sets(uncovered_and_uncovered_nodes, make_connection);
    
    
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
    
    
    printf("Hello World!!\n");
}