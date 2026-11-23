/*
    Trabalho Pratico Matematica Discreta
    
    Alunos:
        @LucasVilela
        @AnaClara
        @RafaelaLarissa
        @PedroLucas
*/

#include <stdio.h>
#include <stdlib.h>

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