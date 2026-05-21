//
// Created by Matheus on 01/05/2026.
//

#include "../include/hash.h"
#include "../include/qry.h"
#include "../include/svg.h"
#include "../include/relatorio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void qry (Gerenciador quadras, Gerenciador pessoas, FILE* file_qry, FILE* file_txt, FILE* file_svg, Cores cq) {

    char linha[512];
    char comando[6];

    abre_svg(file_svg);

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
            censo(pessoas, file_txt);
        }
        else if (strcmp(comando, "h?") == 0) {
            char cpf[15];
            sscanf(linha, "h? %s", cpf);
            h(pessoas, cpf, file_txt);
        }
        if (strcmp(comando, "nasc") == 0) {
            char cpf[15], nome[32], sobrenome[32], dataNascimento[12];
            char sexo;
            sscanf(linha, "nasc %s %s %s %s %c", cpf, nome, sobrenome, dataNascimento, &sexo);
            nasc(pessoas, cpf, nome, sobrenome, dataNascimento, sexo);
        }
        else if (strcmp(comando, "rip") == 0) {
            char cpf[15];
            sscanf(linha, "rip %s", cpf);
            rip(quadras, pessoas, cpf, file_txt, file_svg);
        }
        else if (strcmp(comando, "mud") == 0) {
            char cpf[15], cep[10], cmpl[10];
            char face;
            int num;

            sscanf(linha,"mud %s %s %c %i %s", cpf, cep, &face, &num, cmpl);
            mud(quadras, pessoas, cpf, cep, face, num, cmpl, file_svg);
        }
        else if (strcmp(comando, "dspj") == 0) {
            char cpf[15];
            sscanf(linha,"dspj %s", cpf);
            dspj(quadras, pessoas, cpf, file_txt, file_svg);
        }
    }
    int total;
    Registro* vetor_quadras = pega_todos_registros(quadras, &total);
    for (int i = 0; i < total; i++) {
        Registro r = vetor_quadras[i];

        char* cep = get_chave_registro(r);
        char* dados = get_dados_registro(r);
        Quadra q = reconstroi_quadra(cep, dados);
        desenha_quadra_svg(file_svg, q, cq);

        libera_registro(r);
        libera_quadra(q);
    }
    free(vetor_quadras);
    fecha_svg(file_svg);
}