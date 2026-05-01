#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hash.h"

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
    int numBuckets;
    int sizeRecord;
    int sizeBlock;
    int offsetKey;
    int sizeKey;
    long offsetTable;
    long offsetBuckets;
    int profundidade_global;
} StrCabecalho;

typedef struct {
    FILE* dir_file;
    FILE* bucket_file;
    FILE* txt_file;
    StrCabecalho cabecalho;
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

// Função DJB2 adaptada para Hash Extensível
int hash_function(const char* str, int profundidade) {
    // 5381 é o valor inicial mágico clássico do DJB2
    unsigned long hash = 5381;
    int c;

    // Percorre cada caractere da string (chave)
    while ((c = *str++)) {
        // hash * 33 + c
        // (hash << 5) é uma forma ultrarrápida de fazer hash * 32.
        // Somando 'hash' de novo, temos hash * 33.
        hash = ((hash << 5) + hash) + c;
    }

    // Se a profundidade for 0, o índice no diretório é sempre 0
    if (profundidade == 0) {
        return 0;
    }

    // Máscara para pegar apenas os bits referentes à profundidade
    // Exemplo: se profundidade for 3, (1 << 3) é 8 (binário 1000).
    // 8 - 1 = 7 (binário 0111).
    // O operador '&' vai cortar o hash gigante e deixar só os 3 últimos bits!
    int mascara = (1 << profundidade) - 1;

    return hash & mascara;
}

static void set_bucket_offset(StrGerenciador* hash, int dir_index, long offset) {
    fseek(hash->dir_file, sizeof(StrCabecalho) + (dir_index * sizeof(long)), SEEK_SET);
    fwrite(&offset, sizeof(long), 1, hash->dir_file);
    fflush(hash->dir_file);
}

static long get_bucket_offset(StrGerenciador* hash, int dir_index) {
    long offset;
    fseek(hash->dir_file, sizeof(StrCabecalho) + (dir_index * sizeof(long)), SEEK_SET);
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

        hash->cabecalho.numBuckets = 1;
        hash->cabecalho.sizeRecord = sizeof(StrRegistro);
        hash->cabecalho.sizeBlock = sizeof(StrBucket);
        hash->cabecalho.offsetKey = 0;
        hash->cabecalho.sizeKey = 32;
        hash->cabecalho.offsetTable = sizeof(StrCabecalho);
        hash->cabecalho.offsetBuckets = 0;
        hash->cabecalho.profundidade_global = 0;

        fseek(hash->dir_file, 0, SEEK_SET);
        fwrite(&(hash->cabecalho), sizeof(StrCabecalho), 1, hash->dir_file);

        StrBucket bucket;
        memset(&bucket, 0, sizeof(StrBucket));
        bucket.profundidade_local = 0;
        bucket.countagem = 0;

        fseek(hash->bucket_file, 0, SEEK_SET);
        long initial_offset = ftell(hash->bucket_file);
        fwrite(&bucket, sizeof(StrBucket), 1, hash->bucket_file);
        fflush(hash->bucket_file);

        set_bucket_offset(hash, 0, initial_offset);
    } else {
        fseek(hash->dir_file, 0, SEEK_SET);
        fread(&(hash->cabecalho), sizeof(StrCabecalho), 1, hash->dir_file);
    }
    return (Gerenciador) hash;
}

Registro cria_registro(char* chave, char* dados) {
    StrRegistro* r = (StrRegistro*)malloc(sizeof(StrRegistro));
    memset(r, 0, sizeof(StrRegistro));

    strcpy (((StrRegistro*)r)->chave, chave);
    strcpy (((StrRegistro*)r)->dados, dados);
    return (Registro) r;
}

Registro busca_registro(Gerenciador hash, char* chave) {
    StrGerenciador* h = (StrGerenciador*)hash;
    int dir_index = hash_function(chave, h->cabecalho.profundidade_global);
    long bucket_offset = get_bucket_offset(h, dir_index);

    StrBucket b;
    fseek(h->bucket_file, bucket_offset, SEEK_SET);
    fread(&b, sizeof(StrBucket), 1, h->bucket_file);
    for (int i = 0; i < b.countagem; i++){
        if (strcmp(b.registros[i].chave, chave) == 0) {
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
    char* chave = get_chave_registro(r);

    Registro existente = busca_registro(hash, chave);
    if (existente != NULL) {
        libera_registro(existente);
        return;
    }

    int dir_index = hash_function(chave, h->cabecalho.profundidade_global);
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
            if (b.profundidade_local == h->cabecalho.profundidade_global) {
                int tamanho_diretorio_atual = 1 << h->cabecalho.profundidade_global;
                h->cabecalho.profundidade_global++;
                fseek(h->dir_file, 0, SEEK_SET);
                fwrite(&(h->cabecalho.profundidade_global), sizeof(StrCabecalho), 1, h->dir_file);

                for (int i = 0; i < tamanho_diretorio_atual; i++) {
                    long offset_existente = get_bucket_offset(h, i);
                    set_bucket_offset(h, i + tamanho_diretorio_atual, offset_existente);
                }
            }

            int profundidade_local = b.profundidade_local;
            int nova_profundidade_local = profundidade_local + 1;

            StrBucket b_atual, b_novo;
            memset(&b_atual, 0, sizeof(StrBucket));
            memset(&b_novo, 0, sizeof(StrBucket));

            b_atual.profundidade_local = nova_profundidade_local;
            b_atual.countagem = 0;
            b_novo.profundidade_local = nova_profundidade_local;
            b_novo.countagem = 0;

            fseek(h->bucket_file, 0, SEEK_END);
            long new_offset = ftell(h->bucket_file);

            h->cabecalho.numBuckets++;

            StrRegistro temp_registros[TAM_BUCKET + 1];
            for (int i = 0; i < TAM_BUCKET; i++) {
                temp_registros[i] = b.registros[i];
            }
            temp_registros[TAM_BUCKET] = *reg;

            int bit_significativo = 1 << profundidade_local; 

            for (int i = 0; i <= TAM_BUCKET; i++) {
                int hash_val = hash_function(temp_registros[i].chave, nova_profundidade_local);
                if (hash_val & bit_significativo) {
                    b_novo.registros[b_novo.countagem++] = temp_registros[i];
                } else {
                    b_atual.registros[b_atual.countagem++] = temp_registros[i];
                }
            }
            int novo_tamanho_diretorio = 1 << h->cabecalho.profundidade_global;
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

            fseek(h->dir_file, 0, SEEK_SET);
            fwrite(&(h->cabecalho), sizeof(StrCabecalho), 1, h->dir_file);

            fflush(h->dir_file);
            fflush(h->bucket_file);

            if (b_atual.countagem > TAM_BUCKET) {
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
    char* chave = get_chave_registro(r);
    int dir_index = hash_function(chave, h->cabecalho.profundidade_global);
    long bucket_offset = get_bucket_offset(h, dir_index);

    StrBucket b;
    fseek(h->bucket_file, bucket_offset, SEEK_SET);
    fread(&b, sizeof(StrBucket), 1, h->bucket_file);
    for (int i = 0; i < b.countagem; i++){
        if (strcmp(b.registros[i].chave, chave) == 0) {
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

void gera_dump(Gerenciador hash, const char* file_hfd_hash) {
    StrGerenciador* h = (StrGerenciador*) hash;

    FILE* out = fopen(file_hfd_hash, "w");
    if (!out) {
        printf("Erro ao criar o arquivo de dump.\n");
        return;
    }

    fprintf(out, "DUMP\n");
    fprintf(out, "*Dump cabecalho\n");
    fprintf(out, "numBuckets %d\n", h->cabecalho.numBuckets);
    fprintf(out, "sizeRecord %d\n", h->cabecalho.sizeRecord);
    fprintf(out, "sizeBlock %d\n", h->cabecalho.sizeBlock);
    fprintf(out, "offsetKey %d\n", h->cabecalho.offsetKey);
    fprintf(out, "sizeKey %d\n", h->cabecalho.sizeKey);
    fprintf(out, "offsetTable %ld\n", h->cabecalho.offsetTable);
    fprintf(out, "offsetBuckets %ld\n", h->cabecalho.offsetBuckets);

    fprintf(out, "* Dump table\n");

    int tamanho_diretorio = 1 << h->cabecalho.profundidade_global;

    for (int i = 0; i < tamanho_diretorio; i++) {
        long offset = get_bucket_offset(h, i);
        fprintf(out, "[%d] %ld\n", i, offset);
    }

    fprintf(out, "*Dump buckets\n");

    fseek(h->bucket_file, 0, SEEK_SET);

    StrBucket b;
    int contador_bloco = 0;
    while (fread(&b, sizeof(StrBucket), 1, h->bucket_file) == 1) {
        fprintf(out, "BLOCO: %d\n", contador_bloco);
        for (int i = 0; i < b.countagem; i++) {
            fprintf(out, "1 | %s | %s |\n", b.registros[i].chave, b.registros[i].dados);
        }
        contador_bloco++;
    }

    fclose(out);
}

Registro* pega_todos_registros(Gerenciador hash, int* qtd_retornada) {
    StrGerenciador* h = (StrGerenciador*) hash;
    int total_registros = 0;

    fseek(h->bucket_file, 0, SEEK_SET);

    StrBucket b;
    while (fread(&b, sizeof(StrBucket), 1, h->bucket_file) == 1) {
        total_registros += b.countagem;
    }
    if (total_registros == 0) {
        *qtd_retornada = 0;
        return NULL;
    }

    Registro* lista = malloc(total_registros * sizeof(Registro));

    fseek(h->bucket_file, 0, SEEK_SET);
    int indice_vetor = 0;

    while (fread(&b, sizeof(StrBucket), 1, h->bucket_file) == 1) {
        for (int i = 0; i < b.countagem; i++) {
            StrRegistro* copia = (StrRegistro*)malloc(sizeof(StrRegistro));
            *copia = b.registros[i]; // Copia os dados do bloco pra RAM
            lista[indice_vetor] = (Registro) copia;
            indice_vetor++;
        }
    }
    *qtd_retornada = total_registros;
    return lista;
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