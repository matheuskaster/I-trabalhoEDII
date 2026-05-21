//
// Created by Matheus on 01/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pessoa.h"
#include "../include/hash.h"
#include "../include/svg.h"

void rq(Gerenciador quadras, Gerenciador pessoas, char* cep, FILE* file_txt, FILE* file_svg) {
    Registro reg_quadra = busca_registro(quadras, cep);
    char* dados_quadra = get_dados_registro(reg_quadra);
    Quadra q = reconstroi_quadra(cep, dados_quadra);

    double x = get_x_quadra(q);
    double y = get_y_quadra(q);
    desenha_x_vermelho_svg(file_svg, x, y);

    remove_registro(quadras, reg_quadra);

    libera_quadra(q);
    libera_registro(reg_quadra);


    int total_pessoas;
    Registro* vetor_pessoas = pega_todos_registros(pessoas, &total_pessoas);

    fprintf(file_txt, "Moradores removidos da quadra %s:\n", cep);

    for (int i = 0; i < total_pessoas; i++) {
        Registro reg_atual = vetor_pessoas[i];
        char* cpf = get_chave_registro(reg_atual);
        char* dados_pessoa = get_dados_registro(reg_atual);

        Pessoa p = reconstroi_pessoa(cpf, dados_pessoa);

        if (eh_morador(p) && strcmp(get_cep(p), cep) == 0) {
            fprintf(file_txt, "Nome: %s %s, CPF: %s\n", get_nome_pessoa(p), get_sobrenome_pessoa(p), cpf);

            char dados_basicos[1024];
            sprintf(dados_basicos, "CPF: %s | Nome: %s %s | Sexo: %c | Nasc: %s | Nao e morador", get_cpf_pessoa(p), get_nome_pessoa(p), get_sobrenome_pessoa(p), get_sexo_pessoa(p), get_nasc_pessoa(p));

            remove_registro(pessoas, reg_atual);
            Registro reg_novo = cria_registro(cpf, dados_basicos);
            insere_registro(pessoas, reg_novo);

            libera_registro(reg_novo);
        }

        libera_pessoa(p);
    }

    if (vetor_pessoas != NULL) {
        for (int i = 0; i < total_pessoas; i++) {
            libera_registro(vetor_pessoas[i]);
        }
        free(vetor_pessoas);
    }
}

void pq (Gerenciador quadras, Gerenciador pessoas, char* cep, FILE* file_svg) {
    Registro reg_quadra = busca_registro(quadras, cep);
    Quadra q = reconstroi_quadra(cep, get_dados_registro(reg_quadra));
    double x = get_x_quadra(q);
    double y = get_y_quadra(q);
    double w = get_w_quadra(q);
    double h = get_h_quadra(q);

    int total_pessoas;
    Registro* vetor_pessoas = pega_todos_registros(pessoas, &total_pessoas);

    int total = 0, face_N = 0, face_S = 0, face_L = 0, face_O = 0;
    for (int i = 0; i < total_pessoas; i++) {
        Registro reg_atual = vetor_pessoas[i];
        char* cpf = get_chave_registro(reg_atual);
        char* dados_pessoa = get_dados_registro(reg_atual);

        Pessoa p = reconstroi_pessoa(cpf, dados_pessoa);

        if (eh_morador(p) && strcmp(get_cep(p), cep) == 0) {
            total++;
            switch (get_face(p)) {
                case 'N': face_N++; break;
                case 'S': face_S++; break;
                case 'L': face_L++; break;
                case 'O': face_O++; break;
            }
        }

        libera_pessoa(p);
    }

    char str_total[10], str_N[10], str_S[10], str_L[10], str_O[10];
    sprintf(str_total, "%d", total);
    sprintf(str_N, "%d", face_N);
    sprintf(str_S, "%d", face_S);
    sprintf(str_L, "%d", face_L);
    sprintf(str_O, "%d", face_O);

    double cx = x + (w / 2.0);
    double cy = y + (h / 2.0);

    desenha_numero_moradores_svg(file_svg, cx, cy, str_total);
    desenha_numero_moradores_svg(file_svg, cx, y + 15, str_N);
    desenha_numero_moradores_svg(file_svg, cx, y + h - 5, str_S);
    desenha_numero_moradores_svg(file_svg, x + w - 15, cy, str_L);
    desenha_numero_moradores_svg(file_svg, x + 15, cy, str_O);

    libera_quadra(q);
    libera_registro(reg_quadra);

    if (vetor_pessoas != NULL) {
        for (int i = 0; i < total_pessoas; i++) {
            libera_registro(vetor_pessoas[i]);
        }
        free(vetor_pessoas);
    }
}

void censo(Gerenciador pessoas, FILE* file_txt) {
    int total_habitantes;
    Registro* vetor_pessoas = pega_todos_registros(pessoas, &total_habitantes);

    int total_moradores = 0, total_sem_teto = 0;
    int total_homens = 0, total_mulheres = 0;
    int moradores_homens = 0, moradores_mulheres = 0;
    int sem_teto_homens = 0, sem_teto_mulheres = 0;

    for (int i = 0; i < total_habitantes; i++) {
        Registro reg_atual = vetor_pessoas[i];
        char* cpf = get_chave_registro(reg_atual);
        char* dados_pessoa = get_dados_registro(reg_atual);

        Pessoa p = reconstroi_pessoa(cpf, dados_pessoa);

        char sexo = get_sexo_pessoa(p);
        bool morador = eh_morador(p);

        if (sexo == 'M') {
            total_homens++;
            if (morador) {
                moradores_homens++;
                total_moradores++;
            } else {
                sem_teto_homens++;
                total_sem_teto++;
            }
        } else if (sexo == 'F') {
            total_mulheres++;
            if (morador) {
                moradores_mulheres++;
                total_moradores++;
            } else {
                sem_teto_mulheres++;
                total_sem_teto++;
            }
        }
        libera_pessoa(p);
    }

    fprintf(file_txt, "--- CENSO DE BITNÓPOLIS ---\n");
    fprintf(file_txt, "Total de Habitantes: %d\n", total_habitantes);
    fprintf(file_txt, "Total de Moradores: %d\n", total_moradores);
    fprintf(file_txt, "Total de Sem-tetos: %d\n", total_sem_teto);

    fprintf(file_txt, "Proporção Moradores/Habitantes: %d/%d \n", total_moradores, total_habitantes);

    fprintf(file_txt, "\n--- ESTATÍSTICAS POR GÊNERO ---\n");
    fprintf(file_txt, "Número de Homens: %d\n", total_homens);
    fprintf(file_txt, "Número de Mulheres: %d\n", total_mulheres);

    fprintf(file_txt, "%% Habitantes Homens: %d/%d\n", total_homens, total_habitantes);
    fprintf(file_txt, "%% Habitantes Mulheres: %d/%d \n", total_mulheres, total_habitantes);

    fprintf(file_txt, "\n--- ESTATÍSTICAS DE MORADORES ---\n");
    if (total_moradores > 0) {
        fprintf(file_txt, "%% Moradores Homens: %d/%d \n", moradores_homens,total_moradores);
        fprintf(file_txt, "%% Moradores Mulheres: %d/%d \n", moradores_mulheres, total_moradores);
    } else {
        fprintf(file_txt, "Não há moradores para calcular a porcentagem.\n");
    }

    fprintf(file_txt, "\n--- ESTATÍSTICAS DE SEM-TETOS ---\n");
    if (total_sem_teto > 0) {
        fprintf(file_txt, "%% Sem-tetos Homens: %d/%d \n", sem_teto_homens, total_sem_teto);
        fprintf(file_txt, "%% Sem-tetos Mulheres: %d/%d \n", sem_teto_mulheres, total_sem_teto);
    } else {
        fprintf(file_txt, "Não há sem-tetos na cidade.\n");
    }

    fprintf(file_txt, "---------------------------\n\n");

    if (vetor_pessoas != NULL) {
        for (int i = 0; i < total_habitantes; i++) {
            libera_registro(vetor_pessoas[i]);
        }
        free(vetor_pessoas);
    }
}

void h (Gerenciador pessoas, char* cpf, FILE* file_txt) {
    Registro reg_pessoa = busca_registro(pessoas, cpf);

    char* dados_banco = get_dados_registro(reg_pessoa);
    Pessoa p = reconstroi_pessoa(cpf, dados_banco);

    fprintf(file_txt, "--- DADOS DO HABITANTE ---\n");
    fprintf(file_txt, "CPF: %s . ", cpf);
    fprintf(file_txt, "Nome Completo: %s %s . ", get_nome_pessoa(p), get_sobrenome_pessoa(p));
    fprintf(file_txt, "Sexo: %c . ", get_sexo_pessoa(p));
    fprintf(file_txt, "Data de Nascimento: %s . ", get_nasc_pessoa(p));

    if (eh_morador(p)) {
        fprintf(file_txt, "Endereço: CEP %s | Face %c | Num: %d | Compl: %s\n", get_cep(p), get_face(p), get_num(p), get_complemento(p));
    } else {
        fprintf(file_txt, "Situação: Sem-teto\n");
    }

    libera_pessoa(p);
    libera_registro(reg_pessoa);
}

void nasc (Gerenciador pessoas, char* cpf, char* nome, char* sobrenome, char* nasc, char sexo) {
    Pessoa p = cria_pessoa(cpf, nome, sobrenome, sexo, nasc);
    char buffer_dados[1024];

    get_dados_completos_pessoa(p, buffer_dados);
    Registro reg = cria_registro(cpf, buffer_dados);
    insere_registro(pessoas, reg);

    libera_pessoa(p);
    libera_registro(reg);
}

void rip (Gerenciador quadras, Gerenciador pessoas, char* cpf, FILE* file_txt, FILE* file_svg) {
    Registro reg_pessoa = busca_registro(pessoas, cpf);
    if (reg_pessoa == NULL) {
        return;
    }
    Pessoa p = reconstroi_pessoa(cpf, get_dados_registro(reg_pessoa));

    fprintf(file_txt, "--- FALECIMENTO ---\n");
    fprintf(file_txt, "Nome: %s %s | CPF: %s\n", get_nome_pessoa(p), get_sobrenome_pessoa(p), cpf);
    fprintf(file_txt, "Nascido em: %s | Sexo: %c\n", get_nasc_pessoa(p), get_sexo_pessoa(p));

    if (eh_morador(p)) {
        char* cep = get_cep(p);
        char face = get_face(p);
        int num = get_num(p);

        fprintf(file_txt, "Endereço: CEP %s, Face %c, Num %d, Compl %s\n", cep, face, num, get_complemento(p));

        Registro reg_q = busca_registro(quadras, cep);
        if (reg_q != NULL) {
            Quadra q = reconstroi_quadra(cep, get_dados_registro(reg_q));
            double qx = get_x_quadra(q);
            double qy = get_y_quadra(q);
            double qw = get_w_quadra(q);
            double qh = get_h_quadra(q);

            double cruz_x, cruz_y;

            switch (face) {
                case 'N':
                    cruz_x = qx + num;
                    cruz_y = qy;
                    break;
                case 'S' :
                    cruz_x = qx + num;
                    cruz_y = qy + qh;
                    break;
                case 'L' :
                    cruz_x = qx + qw;
                    cruz_y = qy + num;
                    break;
                case 'O' :
                    cruz_x = qx;
                    cruz_y = qy + num;
                    break;
            }
            desenha_cruz_vermelha_svg(file_svg, cruz_x, cruz_y);

            libera_quadra(q);
            libera_registro(reg_q);
        }
    } else {
        fprintf(file_txt, "Situação: Sem teto .\n");
    }

    remove_registro(pessoas, reg_pessoa);

    libera_pessoa(p);
    libera_registro(reg_pessoa);
}

void mud (Gerenciador quadras, Gerenciador pessoas, char* cpf, char* cep, char face, int num, char* cmpl, FILE* file_svg) {
    Registro reg_p = busca_registro(pessoas, cpf);
    Pessoa p = reconstroi_pessoa(cpf, get_dados_registro(reg_p));

    set_cep(p, cep);
    set_face(p, face);
    set_num(p, num);
    set_complemento(p, cmpl);

    char buffer_dados[1024];
    get_dados_completos_pessoa(p, buffer_dados);
    Registro novo_reg = cria_registro(cpf, buffer_dados);

    remove_registro(pessoas, reg_p);
    insere_registro(pessoas, novo_reg);


    Registro reg_q = busca_registro(quadras, cep);
    if (reg_q != NULL) {
        Quadra q = reconstroi_quadra(cep, get_dados_registro(reg_q));
        double qx = get_x_quadra(q);
        double qy = get_y_quadra(q);
        double qw = get_w_quadra(q);
        double qh = get_h_quadra(q);

        double x_dest, y_dest;

        switch (face) {
            case 'N':
                x_dest = qx + num;
                y_dest = qy;
                break;
            case 'S' :
                x_dest = qx + num;
                y_dest = qy + qh;
                break;
            case 'L' :
                x_dest = qx + qw;
                y_dest = qy + num;
                break;
            case 'O' :
                x_dest = qx;
                y_dest = qy + num;
                break;
        }
        desenha_quadrado_vermelho_svg(file_svg, x_dest - 1.0, y_dest - 1.0, cpf);

        libera_quadra(q);
        libera_registro(reg_q);
    }

    libera_pessoa(p);
    libera_registro(reg_p);
    libera_registro(novo_reg);
}

void dspj (Gerenciador quadras, Gerenciador pessoas, char* cpf, FILE* file_txt, FILE* file_svg) {
    Registro reg_p = busca_registro(pessoas, cpf);
    Pessoa p = reconstroi_pessoa(cpf, get_dados_registro(reg_p));

    char* cep = get_cep(p);
    char face = get_face(p);
    int num = get_num(p);

    fprintf(file_txt, "--- ORDEM DE DESPEJO EXECUTADA ---\n");
    fprintf(file_txt, "Habitante: %s %s | CPF: %s\n", get_nome_pessoa(p), get_sobrenome_pessoa(p), cpf);
    fprintf(file_txt, "Local do Despejo: CEP %s, Face %c, Num %d\n", cep, face, num);
    fprintf(file_txt, "Situação Atual: O habitante agora é considerado SEM-TETO.\n");
    fprintf(file_txt, "----------------------------------\n\n");

    Registro reg_q = busca_registro(quadras, cep);
    if (reg_q != NULL) {
        Quadra q = reconstroi_quadra(cep, get_dados_registro(reg_q));
        double qx = get_x_quadra(q);
        double qy = get_y_quadra(q);
        double qw = get_w_quadra(q);
        double qh = get_h_quadra(q);

        double cx, cy;

        switch (face) {
            case 'N':
                cx = qx + num;
                cy = qy;
                break;
            case 'S' :
                cx = qx + num;
                cy = qy + qh;
                break;
            case 'L' :
                cx = qx + qw;
                cy = qy + num;
                break;
            case 'O' :
                cx = qx;
                cy = qy + num;
                break;
        }

        desenha_circulo_preto_svg(file_svg, cx, cy);

        libera_quadra(q);
        libera_registro(reg_q);
    }
    set_eh_morador(p, false);
    char buffer_dados[1024];
    get_dados_completos_pessoa(p, buffer_dados);
    Registro novo_reg = cria_registro(cpf, buffer_dados);

    remove_registro(pessoas, reg_p);
    insere_registro(pessoas, novo_reg);

    libera_pessoa(p);
    libera_registro(reg_p);
    libera_registro(novo_reg);
}
