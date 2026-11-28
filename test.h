#ifndef __TEST__
#define __TEST__

#include <assert.h>

/*
    * @LucasAPV
    * Arquivo criado para fazer testes para quando eu estou sem
    * matrix oferecida. Portanto passo uma matriz menor para fazer os testes.
*/


int is_argc_correct(int argc);
int find_biggest_conn(int *adj_mtx[], int qty_cols);
int does_make_connection(int *adj_mtx[], int line, int col);
void init_arr_with_zeros(int *arr, int size);

int* guha_keller_heuristic_cds_solve(int *adj_mtx[], int qty_cols, int qty_nodes);

void run_test(int *adj_mtx[], int qty_cols, int qty_nodes);
#endif