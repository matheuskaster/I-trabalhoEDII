#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hash.h"
#include "hash.h"

#define TAM_BUCKET 3


typedef struct {
    char chave[32];
    char dados[1024];
} StrRegistro;

typedef struct {
    int profundidade_local;
    int countagem;
    StrRegistro registros[TAM_BUCKET];
} StrBucket;

typedef struct {
    FILE* dir_file;
    FILE* bucket_file;
    FILE* txt_file;
    int profundidade_global;
} StrGerenciador;


void set_chave_registro(Registro r, char* chave) {
    strcpy (((StrRegistro*)r)->chave, chave);
}

char* get_chave_registro(Registro r) {
    return ((StrRegistro*)r)->chave;
}

void set_dados_registro(Registro r, char* dados) {
    strcpy (((StrRegistro*)r)->dados, dados);
}

char* get_dados_registro(Registro r) {
    return ((StrRegistro*)r)->dados;
}

int hash_function() {}

static void set_bucket_offset(StrGerenciador* hash, int dir_index, long offset) {
    fseek(hash->dir_file, sizeof(int) + (dir_index * sizeof(long)), SEEK_SET);
    fwrite(&offset, sizeof(long), 1, hash->dir_file);
    fflush(hash->dir_file);
}

static long get_bucket_offset(StrGerenciador* hash, int dir_index) {
    long offset;
    fseek(hash->dir_file, sizeof(int) + (dir_index * sizeof(long)), SEEK_SET);
    fread(&offset, sizeof(long), 1, hash->dir_file);
    return offset;
}

Gerenciador cria_hash(const char *dir_filename, const char *bucket_filename) {
    StrGerenciador* hash = (StrGerenciador*)malloc(sizeof(StrGerenciador));
    hash->dir_file = fopen(dir_filename, "r+b");
    hash->bucket_file = fopen(bucket_filename, "r+b");
    if (hash->dir_file == NULL || hash->bucket_file == NULL) {
        if (hash->dir_file) fclose(hash->dir_file);
        if (hash->bucket_file) fclose(hash->bucket_file);

        hash->dir_file = fopen(dir_filename, "w+b");
        hash->bucket_file = fopen(bucket_filename, "w+b");

        hash->profundidade_global = 0;
        fwrite(&(hash->profundidade_global), sizeof(int), 1, hash->dir_file);

        StrBucket bucket;
        bucket.profundidade_local = 0;
        bucket.countagem = 0;

        fseek(hash->bucket_file, 0, SEEK_SET);
        long initial_offset = ftell(hash->bucket_file);
        fwrite(&bucket, sizeof(StrBucket), 1, hash->bucket_file);
        fflush(hash->bucket_file);

        set_bucket_offset(hash, 0, initial_offset);
    } else {
        fseek(hash->dir_file, 0, SEEK_SET);
        fread(&(hash->profundidade_global), sizeof(int), 1, hash->dir_file);
    }
    return (Gerenciador) hash;
}

Registro cria_registro(char* chave, char* dados) {
    StrRegistro* r = (StrRegistro*)malloc(sizeof(StrRegistro));
    strcpy (((StrRegistro*)r)->chave, chave);
    strcpy (((StrRegistro*)r)->dados, dados);
    return (Registro) r;
}

Registro busca_registro(Gerenciador hash, char* chave) {
    StrGerenciador* h = (StrGerenciador*)hash;
    int dir_index = hash_function(chave, h->profundidade_global);
    long bucket_offset = get_bucket_offset(h, dir_index);

    StrBucket b;
    fseek(h->bucket_file, bucket_offset, SEEK_SET);
    fread(&b, sizeof(StrBucket), 1, h->bucket_file);
    for (int i = 0; i < TAM_BUCKET; i++){
        if (b.registros[i].chave == chave) {
            StrRegistro* r = (StrRegistro*)malloc(sizeof(StrRegistro));
            *r = b.registros[i];
            return (Registro) r;
        }
    }
    return NULL;
}

void insere_registro(Gerenciador hash, Registro r) {
    StrGerenciador* h = (StrGerenciador*) hash;
    StrRegistro* reg = (StrRegistro*) r;
    int chave = get_chave_registro(r);
    int dir_index = hash_function(chave, h->profundidade_global);
    long bucket_offset = get_bucket_offset(h, dir_index);

    StrBucket b;
    fseek(h->bucket_file, bucket_offset, SEEK_SET);
    fread(&b, sizeof(StrBucket), 1, h->bucket_file);
    if (b.countagem < TAM_BUCKET) {
        b.registros[b.countagem] = *reg;
        b.countagem++;
        fseek(h->bucket_file, bucket_offset, SEEK_SET);
        fwrite(&b, sizeof(StrBucket), 1, h->bucket_file);
        fflush(h->bucket_file);
    } else {
        int inserido_com_sucesso = 0;
        while (!inserido_com_sucesso) {
            if (b.profundidade_local == h->profundidade_global) {
                int tamanho_diretorio_atual = 1 << h->profundidade_global;
                h->profundidade_global++;
                fseek(h->dir_file, 0, SEEK_SET);
                fwrite(&(h->profundidade_global), sizeof(int), 1, h->dir_file);

                for (int i = 0; i < tamanho_diretorio_atual; i++) {
                    long offset_existente = get_bucket_offset(h, i);
                    set_bucket_offset(h, i + tamanho_diretorio_atual, offset_existente);
                }
            }

            int profundidade_local = b.profundidade_local;
            int nova_profundidade_local = profundidade_local + 1;

            StrBucket b_atual, b_novo;
            b_atual.profundidade_local = nova_profundidade_local;
            b_atual.countagem = 0;
            b_novo.profundidade_local = nova_profundidade_local;
            b_novo.countagem = 0;

            fseek(h->bucket_file, 0, SEEK_END);
            long new_offset = ftell(h->bucket_file);

            StrRegistro temp_registros[TAM_BUCKET + 1];
            for (int i = 0; i < TAM_BUCKET; i++) {
                temp_registros[i] = b_atual.registros[i];
            }
            temp_registros[TAM_BUCKET] = *reg;

            int bit_significativo = 1 << profundidade_local; 

            for (int i = 0; i <= TAM_BUCKET; i++) {
                int hash_val = hash_function(temp_registros[i].chave, nova_profundidade_local);
                if (hash_val & bit_significativo) {
                    b_novo.registros[b_novo.countagem++] = temp_registros[i];
                } else {
                    b.registros[b_atual.countagem++] = temp_registros[i];
                }
            }
            int novo_tamanho_diretorio = 1 << h->profundidade_global;
            for (int i = 0; i < novo_tamanho_diretorio; i++) {
                if (get_bucket_offset(h, i) == bucket_offset) {
                    if (i & bit_significativo) {
                        set_bucket_offset(h, i, new_offset);
                    }
                }
            }

            fseek(h->bucket_file, bucket_offset, SEEK_SET);
            fwrite(&b_atual, sizeof(StrBucket), 1, h->bucket_file);

            fseek(h->bucket_file, new_offset, SEEK_SET);
            fwrite(&b_novo, sizeof(StrBucket), 1, h->bucket_file);

            fflush(h->dir_file);
            fflush(h->bucket_file);

            if (b.countagem > TAM_BUCKET) {
                b = b_atual;
            } 
            else if (b_novo.countagem > TAM_BUCKET) {
                b = b_novo;
                bucket_offset = new_offset;
            } 
            else {
                inserido_com_sucesso = 1;
            }
        }
    }
}

int remove_registro (Gerenciador hash, Registro r) {
    StrGerenciador* h = (StrGerenciador*) hash;
    int chave = get_chave_registro(r);
    int dir_index = hash_function(chave, h->profundidade_global);
    long bucket_offset = get_bucket_offset(h, dir_index);

    StrBucket b;
    fseek(h->bucket_file, bucket_offset, SEEK_SET);
    fread(&b, sizeof(StrBucket), 1, h->bucket_file);
    for (int i = 0; i < TAM_BUCKET; i++){
        if (b.registros[i].chave == chave) {
            b.registros[i] = b.registros[b.countagem - 1];
            b.countagem--;
            fseek(h->bucket_file, bucket_offset, SEEK_SET);
            fwrite(&b, sizeof(StrBucket), 1, h->bucket_file);
            fflush(h->bucket_file);
            return 1;
        }
    }
    return 0;
}

void libera_registro(Registro r) {
    if (r) free((StrRegistro*) r);
}

void libera_hash(Gerenciador hash) {
    StrGerenciador* h = (StrGerenciador*) hash;
    if (h) {
        if (h->dir_file) fclose(h->dir_file);
        if (h->bucket_file) fclose(h->bucket_file);
    }
    free(h);
}