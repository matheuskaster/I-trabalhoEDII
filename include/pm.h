//
// Created by Matheus on 21/04/2026.
//
#ifndef PM_H
#define PM_H
#include <stdio.h>
#include "hash.h"

/* MODULO PM
Esse modulo visa realizar a parte tudo o que precisa ser feito na leitura do arquivo .pm. Recebe um arquivo com as
informacoes necessarias para a criacao de uma pessoa, e sua classificacao, caso seja um morador tambem.
Cada uma delas sera guardada em uma estrutura de dados localizada atraves do gerenciador.
*/

///@param pessoas Estrutura que tem acesso a todas as informacoes para e alterar os atributos das pessoas.
///@param arq_pm Ponteiro do tipo arquivo, para acessar as informacoes das pessoas.
void pm (Gerenciador pessoas, FILE* arq_pm);

#endif
