//
// Created by Matheus on 21/04/2026.
//
#include "../include/pm.h"
#include "../include/pessoa.h"
#include <string.h>
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
            case 'p': {
                char cpf[32], nome[128], sobrenome[128], dataNascimento[32];
                char sexo;
                sscanf (linha, "p %s %s %s %c %s", cpf, nome, sobrenome, &sexo, dataNascimento);
                Pessoa p = cria_pessoa(cpf, nome, sobrenome, sexo, dataNascimento);

                char dados_pessoa[1024];
                get_dados_completos_pessoa(p, dados_pessoa);
                Registro reg = cria_registro(cpf, dados_pessoa);

                insere_registro(pessoas, reg);

                libera_registro(reg);
                libera_pessoa(p);
                break;
            }
            case 'm': {
                char cpf[32], cep[32], complemento[16];
                char face;
                int numeroCasa;
                sscanf (linha, "m %s %s %c %d %s", cpf, cep, &face, &numeroCasa, complemento);


                // Passo 1: Busca a pessoa no Hash
                Registro reg_existente = busca_registro(pessoas, cpf);

                if (reg_existente != NULL) {
                    char* dados_antigos = get_dados_registro(reg_existente);
                    char novos_dados[2048];
                    char copia_dados[1024];

                    strcpy(copia_dados, dados_antigos);

                    char* pos = strstr(copia_dados, " | Nao e morador");

                    if (pos != NULL) {
                        *pos = '\0';
                    }

                    snprintf(novos_dados, sizeof(novos_dados), "%s | CEP: %s | Face: %c | Num: %d | Compl: %s", copia_dados, cep, face, numeroCasa, complemento);

                    remove_registro(pessoas, reg_existente);

                    Registro reg_novo = cria_registro(cpf, novos_dados);
                    insere_registro(pessoas, reg_novo);

                    libera_registro(reg_novo);
                    libera_registro(reg_existente);
                } else {
                    printf("Aviso: Tentativa de adicionar moradia a um CPF inexistente (%s)\n", cpf);
                }
                break;
            }
        }
    }
}