#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/path_utils.h"

void trataPath(char *path, int tamMax, char *arg) {
    int argLen = strlen(arg);
    assert(argLen < tamMax);
    if (arg[argLen - 1] == '/') arg[argLen - 1] = '\0';
    strcpy(path, arg);
}

void trataNomeArquivo(char *path, int tamMax, char *arg) {
    int argLen = strlen(arg);
    assert((argLen + 4) < tamMax);
    sprintf(path, "%s", arg);
}

void extrai_nome_base(char* arq, char* nome_base) {
    if (arq == NULL || nome_base == NULL) {
        printf("Erro ao tentar acessar os parâmetros. \n");
        return;
    }

    char nome_base_tmp[strlen(arq) + 1]; 
    char* ultimo_ponto = strrchr(arq, '.');
    int len_ent;

    if (ultimo_ponto == NULL || ultimo_ponto == arq) {
        strcpy(nome_base_tmp, arq);
    } 
    else {
        len_ent = ultimo_ponto - arq;
        strncpy(nome_base_tmp, arq, len_ent);
        nome_base_tmp[len_ent] = '\0';
    }
    char* ultima_barra = strrchr(nome_base_tmp, '/');
    if (ultima_barra == NULL || ultima_barra == arq) {
        strcpy(nome_base, nome_base_tmp);
    } 
    else {
        strcpy(nome_base, ultima_barra + 1);
    }
}

char* monta_caminho_completo (const char* dir, const char* file) {
    int len = strlen(dir) + strlen(file) + 2;
    char* path = (char*)malloc(len * sizeof(char));
    
    if (dir[strlen(dir) - 1] == '/') {
        sprintf(path, "%s%s", dir, file);
    } else {
        sprintf(path, "%s/%s", dir, file);
    }
    return path;
}

char* atualiza_extensao (const char* dir_saida, const char* nome_arq_entrada, const char* nova_extensao) {

    char* nome_base = (char*)malloc(strlen(nome_arq_entrada) + 1);
    extrai_nome_base((char*)nome_arq_entrada, nome_base);

    char* nome_com_ext = (char*)malloc(strlen(nome_base) + strlen(nova_extensao) + 1);
    sprintf(nome_com_ext, "%s%s", nome_base, nova_extensao);

    char* path_final = monta_caminho_completo (dir_saida, nome_com_ext);

    free(nome_base);
    free(nome_com_ext);

    return path_final;
}