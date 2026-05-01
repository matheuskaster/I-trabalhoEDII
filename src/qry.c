//
// Created by Matheus on 01/05/2026.
//

#include "../include/hash.h"
#include "../include/qry.h"
#include "../include/svg.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void qry (Gerenciador quadras, Gerenciador pessoas, FILE* file_qry, FILE* file_txt, FILE* file_svg) {

    char linha[512];
    char comando[6];

    while (fgets(linha, sizeof(linha), file_qry) != NULL) {
        if(linha[0] == '\n' || linha[0] == '\r'){
            continue;
        }

        sscanf(linha, "%s", comando);

        if (strcmp(comando, "rq") == 0) {
            char cep[10];
            sscanf(linha, "rq %s", cep);
            rq(quadras, pessoas, cep, file_txt, file_svg);
        }
        else if (strcmp(comando, "pq") == 0) {
            char cep[10];
            sscanf(linha, "pq %s", cep);
            pq(quadras, pessoas, cep, file_svg);
        }
        else if (strcmp(comando, "censo") == 0) {
            censo(quadras, pessoas, file_txt);
        }
        else if (strcmp(comando, "h?") == 0) {
            char cpf[15];
            sscanf(linha, "h? %s", cpf);
            h(pessoas, cpf, file_txt);
        }
        if (strcmp(comando, "nasc") == 0) {
            char cpf[15], nome[32], sobrenome[32], nasc[12];
            char sexo;
            sscanf(linha, "nasc %s %s %s %s %c", cpf, nome, sobrenome, nasc, sexo);
            nasc(pessoas, cpf, nome, sobrenome, nasc, sexo);
        }
        else if (strcmp(comando, "rip") == 0) {
            char cpf[15];
            sscanf(linha, "rip %s", cpf);
            rip(pessoas, cpf, file_txt, file_svg);
        }
        else if (strcmp(comando, "mud") == 0) {
            char cpf[15], cep[10], cmpl[10];
            char face;
            int num;

            sscanf(linha,"mud %s %s %s %c, %i", cpf, cep, &face, &num, cmpl);
            mud(pessoas, cpf, cep, face, num, cmpl, file_svg);
        }
        else if (strcmp(comando, "dspj") == 0) {
            char cpf[15];
            sscanf(linha,"dspj %s", cpf);
            dspj(pessoas, cpf, file_txt, file_svg);
        }
    }
}