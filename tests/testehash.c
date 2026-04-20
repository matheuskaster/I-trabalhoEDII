#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../unity/unity.h" 
#include "../include/hash.h"

#define TEST_DIR_FILE "test_dir.bin"
#define TEST_BKT_FILE "test_bkt.bin"

Gerenciador hash = NULL;

void setUp(void) {
    remove(TEST_DIR_FILE);
    remove(TEST_BKT_FILE);
    hash = cria_hash(TEST_DIR_FILE, TEST_BKT_FILE);
}

void tearDown(void) {
    libera_hash(hash);
    remove(TEST_DIR_FILE);
    remove(TEST_BKT_FILE);
}

void test_cria_hash(void) {
    TEST_ASSERT_NOT_NULL(hash);
}

void test_cria_e_altera_registro(void) {
    Registro r = cria_registro(10, 100);
    TEST_ASSERT_NOT_NULL(r);
    TEST_ASSERT_EQUAL_INT(10, get_chave_registro(r));
    TEST_ASSERT_EQUAL_INT(100, get_dados_registro(r));

    set_chave_registro(r, 99);
    set_dados_registro(r, 500);
    TEST_ASSERT_EQUAL_INT(99, get_chave_registro(r));
    TEST_ASSERT_EQUAL_INT(500, get_dados_registro(r));

    libera_registro(r);
}

void test_insere_e_procura_registro(void) {
    Registro r = cria_registro(42, 2048);
    insere_registro(hash, r);
    libera_registro(r);
    Registro r_encontrado = busca_registro(hash, 42);
    
    TEST_ASSERT_NOT_NULL(r_encontrado);
    TEST_ASSERT_EQUAL_INT(42, get_chave_registro(r_encontrado));
    TEST_ASSERT_EQUAL_INT(2048, get_dados_registro(r_encontrado));

    libera_registro(r_encontrado);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_cria_hash);
    RUN_TEST(test_cria_e_altera_registro);
    RUN_TEST(test_insere_e_procura_registro);
    
    return UNITY_END();
}