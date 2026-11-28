#include "test.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
    * @LucasAPV
    * Funcao para alocar a matriz adjacente
*/


static int** alloc_adj_matrix(int n, const int flat[]) {
    int **mtx = malloc(sizeof(int*) * (size_t)n);
    if (!mtx) return NULL;

    for (int i = 0; i < n; ++i) {
        mtx[i] = malloc(sizeof(int) * (size_t)n);
        if (!mtx[i]) {
            for (int k = 0; k < i; ++k) {
                free(mtx[k]);
            }
            free(mtx);
            return NULL;
        }
        for (int j = 0; j < n; ++j) {
            mtx[i][j] = flat[i * n + j];
        }
    }
    return mtx;
}

static void free_adj_matrix(int **mtx, int n) {
    if (!mtx) return;
    for (int i = 0; i < n; ++i) {
        free(mtx[i]);
    }
    free(mtx);
}

/*
    * @LucasAPV
    * Bateria de testes de todas as funcoes cridas. 
    * Se tudo funcionar como esperado, essa funcao deve executar sem problemas algum
*/


void run_test(int *adj_mtx[], int qty_cols, int qty_nodes) {
    printf("=== INICIANDO TESTES ===\n");

    /* Teste 1: is_argc_correct */
    assert(is_argc_correct(4) == 1);
    assert(is_argc_correct(2) == 0);

    /* Teste 2: init_arr_with_zeros */
    int check_arr[4] = {5, 6, 7, 8};
    init_arr_with_zeros(check_arr, 4);
    for (int i = 0; i < 4; ++i) {
        assert(check_arr[i] == 0);
    }

    /* Se matriz e nos forem passados pela main, testa diretamente neles */
    if (adj_mtx != NULL && qty_cols > 0 && qty_nodes > 0) {
        int top_node = find_biggest_conn(adj_mtx, qty_cols);
        assert(top_node >= 0 && top_node < qty_cols);

        int *dom = guha_keller_heuristic_cds_solve(adj_mtx, qty_cols, qty_nodes);
        assert(dom != NULL);
        for (int i = 0; i < qty_nodes; ++i) {
            printf("No -> estado: %d\n", dom[i]);
        }
        free(dom);
    } else {
        /* Fallback com grafo estrela padrao de 4 nos (no 0 conectado a 1, 2, 3) */
        const int n = 4;
        const int flat_graph[16] = {
            0, 1, 1, 1,
            1, 0, 0, 0,
            1, 0, 0, 0,
            1, 0, 0, 0
        };
        int **sample_adj = alloc_adj_matrix(n, flat_graph);
        int sample_nodes[4] = {0, 1, 2, 3};

        assert(sample_adj != NULL);
        assert(does_make_connection(sample_adj, 0, 1) == 1);
        assert(does_make_connection(sample_adj, 1, 2) == 0);
        assert(find_biggest_conn(sample_adj, n) == 0);

        int *dom = guha_keller_heuristic_cds_solve(sample_adj, n, n);
        assert(dom != NULL);
        assert(dom[0] == 2);
        for (int i = 0; i < n; ++i) {
            printf("No %d -> estado: %d\n", sample_nodes[i], dom[i]);
        }

        free(dom);
        free_adj_matrix(sample_adj, n);
    }

    printf("=== TESTES CONCLUIDOS ===\n");
}