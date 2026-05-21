//
// Created by Matheus on 21/04/2026.
//
#ifndef GEO_H
#define GEO_H
#include <stdio.h>
#include "hash.h"
#include "quadra.h"

/* MODULO GEO
Esse modulo visa realizar a parte tudo o que precisa ser feito na leitura do arquivo .geo. Recebe um arquivo com as
informacoes necessarias para a criacao e ilustracao de uma quadra, cada uma delas sera guardada em uma estrutura
de dados localizada atraves do gerenciador.
*/

///@param quadras Estrutura que tem acesso a todas as informacoes para alterar os atributos das quadras.
///@param arq_geo Ponteiro do tipo arquivo, para acessar as informacoes das quadras.
///@param arq_svg Ponteiro do tipo arquivo, para poder desenhar as quadras.
void geo (Gerenciador quadras, FILE* arq_geo, FILE* arq_svg, Cores cq);

#endif