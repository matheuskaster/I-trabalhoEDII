//
// Created by Matheus on 21/04/2026.
//
#include "../include/pm.h"
#include <stdlib.h>

void pm (Gerenciador pessoas, FILE* arq_pm) {

    if(arq_pm == NULL){
        printf("Arquivo .pm não encontrado. \n");
        exit(1);
    }

    char linha[256];
    char comando[3];

    while (fgets(linha, sizeof(linha), arq_pm) != NULL) {
        if (linha[0] == '\n' || linha[0] == '#'){
            continue;
        }

        sscanf(linha, "%s", comando);

        switch (comando[0]) {
            case 'p':
                char cpf[16], nome[32], sobrenome[32], dataNascimento[16];
                char sexo;
                sscanf (linha, "%s %s %s %c %s", cpf, nome, sobrenome, sexo, dataNascimento);
                Pessoa p = cria_pessoa(cpf, nome, sobrenome, sexo, dataNascimento);
                insere_registro(pessoas, ??);
                break;
            case 'm':
                char cpf[16], cep[16], complemento[16];
                char face;
                double numeroCasa;
                sscanf (linha, "%s %s %c %lf %s", cpf, cep, face, &numeroCasa, complemento);
                recebe_moradia(Pessoa, p, cpf, cep, complemento, numeroCasa);
                break;
        }
    }
}