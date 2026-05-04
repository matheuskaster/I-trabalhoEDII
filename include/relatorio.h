//
// Created by Matheus on 01/05/2026.
//

#ifndef RELATORIO_H
#define RELATORIO_H

#include <stdio.h>
#include "../include/hash.h"

/* MODULO RELATORIO
Esse modulo foi criado com a intencao de deixar o modulo que cuida e controla as acoes descritas no arquivo do qry
mais organizado. Ou seja, o qry faz so a leitura do que e o comando que o programa deseja executar, mas para deixar
ambos, tanto esse quanto o outro, mais compactos e legiveis. Aqui estara a implementacao do que deve acontecer apos
cada um dos comandos. Que foi descrito no documento do projeto.
*/

/// @brief Remove quadra cujo cep é cep. Moradores da quadra passam a ser sem-tetos.
/// @param quadras Estrutura que tem acesso a todas as informacoes para alterar os atributos das quadras.
/// @param pessoas Estrutura que tem acesso a todas as informacoes para alterar os atributos das pessoas.
/// @param cep É o cep específico de cada quadra, para identificar qual é a quadra desejada.
/// @param file_txt Arquivo onde será reportado o cpf e nome dos moradores, que se tornaram sem-tetos.
/// @param file_svg Arquivo que será ilustrará um pequeno X vermelho no local da âncora da quadra removida.
void rq (Gerenciador quadras, Gerenciador pessoas, char* cep, FILE* file_txt, FILE* file_svg);

/// @brief Calcula o número de moradores da quadra (por face e total).
/// @param quadras Estrutura que tem acesso a todas as informacoes para alterar os atributos das quadras.
/// @param pessoas Estrutura que tem acesso a todas as informacoes para alterar os atributos das pessoas.
/// @param cep É o cep específico de cada quadra, para identificar qual é a quadra desejada.
/// @param file_svg Arquivo que será ilustrará número de moradores de cada face e, o número total de da quadra.
void pq (Gerenciador quadras, Gerenciador pessoas, char* cep, FILE* file_svg);

/// @brief Produz várias estatísticas sobre habitantes de Bitnópolis.
/// @param pessoas Estrutura que tem acesso a todas as informacoes para alterar os atributos das pessoas.
/// @param file_txt Arquivo onde será reportado todos os dados sobre Bitnópolis, e todas suas estatísticas.
void censo (Gerenciador pessoas, FILE* file_txt);

/// @brief Reporta os dados sobre habitante identificado por cpf.
/// @param pessoas Estrutura que tem acesso a todas as informacoes para alterar os atributos das pessoas.
/// @param cpf É o cpf específico de cada pessoa, para identificar qual é a pessoa desejada.
/// @param file_txt Arquivo onde será reportado todos os dados sobre a respectiva pessoa.
void h (Gerenciador pessoas, char* cpf, FILE* file_txt);

/// @brief Faz com que o programa registre que uma nova pessoa nasceu em Bitnópolis.
/// @param pessoas Estrutura que tem acesso a todas as informacoes para alterar os atributos das pessoas.
/// @param cpf É o cpf específico de cada pessoa, para identificar qual é a pessoa desejada.
/// @param nome É o nome que será atribuido a pessoa que irá nascer.
/// @param sobrenome É o sobrenome que a pessoa que vai nascer receberá.
/// @param nasc É onde está guardado a data de nascimento da pessoa que vai nascer (data do dia do acontecimento).
/// @param sexo É um char para identificar qual é o sexo da pessoa que acabou de nascer.
void nasc (Gerenciador pessoas, char* cpf, char* nome, char* sobrenome, char* nasc, char sexo);

/// @brief Faz com que o programa registre que uma pessoa de Bitnópolis faleceu.
/// @param pessoas Estrutura que tem acesso a todas as informacoes para alterar os atributos das pessoas.
/// @param cpf É o cpf específico de cada pessoa, para identificar qual é a pessoa desejada.
/// @param file_txt Arquivo onde será reportado todos os dados sobre a pessoa falecida.
/// @param file_svg Arquivo que será ilustrará Colocar uma pequena cruz vermelha no local do endereço (se morador).
void rip (Gerenciador pessoas, char* cpf, FILE* file_txt, FILE* file_svg);

/// @brief Faz com que o programa registre que o morador identificado por cpf se mudou para um novo endereço.
/// @param quadras Estrutura que tem acesso a todas as informacoes para alterar os atributos das quadras.
/// @param pessoas Estrutura que tem acesso a todas as informacoes para alterar os atributos das pessoas.
/// @param cpf É o cpf específico de cada pessoa, para identificar qual é a pessoa desejada.
/// @param cep É o cep específico de cada quadra, para identificar qual é a quadra desejada.
/// @param face É um char, para mostrar em qual canto da quadra fica a moradia.
/// @param num É um número inteiro, para dizer qual é o número do endereço do local (distância da borda).
/// @param cmpl É uma String para dizer qual é o complemento do lugar, ex.: apartamento, e o número.
/// @param file_svg Arquivo que será ilustrará o endereço de destino com um pequeno quadrado vermelho no local.
void mud (Gerenciador quadras, Gerenciador pessoas, char* cpf, char* cep, char face, int num, char* cmpl, FILE* file_svg);

/// @brief Faz com que o programa registre que o morador identificado por cpf foi despejado.
/// @param quadras Estrutura que tem acesso a todas as informacoes para alterar os atributos das quadras.
/// @param pessoas Estrutura que tem acesso a todas as informacoes para alterar os atributos das pessoas.
/// @param cpf É o cpf específico de cada pessoa, para identificar qual é a pessoa desejada.
/// @param file_txt Arquivo onde será reportado os dados do habitante e endereço onde ocorreu o despejo.
/// @param file_svg Arquivo que será ilustrará um pequeno círculo preto no local do despejo.
void dspj (Gerenciador quadras, Gerenciador pessoas, char* cpf, FILE* file_txt, FILE* file_svg);

#endif
