//
// Created by Matheus on 22/04/2026.
//
#include "../include/pessoa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cpf[15];
    char nome[32];
    char sobrenome[32];
    char sexo;
    char nasc[12];
    bool m;
    char cep[10];
    char face;
    int num;
    char compl[10];
} StrPessoa;

void set_cep (Pessoa p, char *cep) {
    if ( ((StrPessoa*)p)->m == false) {
        ((StrPessoa*)p)->m = true;
    }
    strcpy (((StrPessoa*)p)->cep, cep);
}

char* get_cep (Pessoa p) {
    return ((StrPessoa*)p)->cep;
}

void set_face (Pessoa p, char face) {
    if ( ((StrPessoa*)p)->m == false) {
        ((StrPessoa*)p)->m = true;
    }
    ((StrPessoa*)p)->face = face;
}

char get_face (Pessoa p) {
    return ((StrPessoa*)p)->face;
}

void set_num (Pessoa p, int num) {
    if ( ((StrPessoa*)p)->m == false) {
        ((StrPessoa*)p)->m = true;
    }
    ((StrPessoa*)p)->num = num;
}

int get_num (Pessoa p) {
    return ((StrPessoa*)p)->num;
}

void set_complemento (Pessoa p, char *compl) {
    if ( ((StrPessoa*)p)->m == false) {
        ((StrPessoa*)p)->m = true;
    }
    strcpy (((StrPessoa*)p)->compl, compl);
}

char* get_complemento (Pessoa p) {
    return ((StrPessoa*)p)->compl;
}



Pessoa cria_pessoa (char* cpf, char* nome, char* sobrenome, char sexo, char* nasc) {
    StrPessoa *p = malloc(sizeof(StrPessoa));
    strcpy(p->cpf, cpf);
    strcpy(p->nome, nome);
    strcpy(p->sobrenome, sobrenome);
    p->sexo = sexo;
    strcpy(p->nasc, nasc);
    p->m = false;
    return ((StrPessoa*) p);
}

void set_cpf_pessoa (Pessoa p, char* cpf) {
    strcpy (((StrPessoa*)p)->cpf, cpf);
}

char* get_cpf_pessoa (Pessoa p) {
    return ((StrPessoa*)p)->cpf;
}

void set_nome_pessoa (Pessoa p, char* nome) {
    strcpy (((StrPessoa*)p)->nome, nome);
}

char* get_nome_pessoa (Pessoa p) {
    return ((StrPessoa*)p)->nome;
}

void set_sobrenome_pessoa (Pessoa p, char* sobrenome) {
    strcpy (((StrPessoa*)p)->sobrenome, sobrenome);
}

char* get_sobrenome_pessoa (Pessoa p) {
    return ((StrPessoa*)p)->sobrenome;
}

void set_sexo (Pessoa p, char sexo) {
    ((StrPessoa*)p)->sexo = sexo;
}

char get_sexo (Pessoa p) {
    return ((StrPessoa*)p)->sexo;
}

void set_nasc_pessoa (Pessoa p, char* nasc) {
    strcpy (((StrPessoa*)p)->nasc, nasc);
}

char* get_nasc_pessoa (Pessoa p) {
    return ((StrPessoa*)p)->nasc;
}

bool eh_morador (Pessoa p) {
    return ((StrPessoa*)p)->m;
}

void libera_pessoa (Pessoa p) {
    if (p == NULL) return;
    StrPessoa* _p = (StrPessoa*) p;
    free(_p);
}
