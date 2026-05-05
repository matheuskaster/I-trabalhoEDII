//
// Created by Matheus on 22/04/2026.
//
#ifndef PESSOA_H
#define PESSOA_H
#include <stdbool.h>

typedef void* Pessoa;

// TADs relacionados a moradia, que uma pessoa pode ter.

/// @brief O char ponteiro passado por parâmetro na função, torna-se o cep em que está localizada a moradia passada por parâmetro.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param cep É o número cep da moradia.
void set_cep (Pessoa p, char* cep);

/// @brief Informa qual é o cep da moradia passada por parâmetro.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna o cep da moradia.
char* get_cep (Pessoa p);

/// @brief O char passado por parâmetro na função, torna-se a nova face em que está localizada a quadra.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param face É a nova face da quadra.
void set_face (Pessoa p, char face);

/// @brief Informa qual é a face da quadra.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna a face da quadra.
char get_face (Pessoa p);

/// @brief O int passado por parâmetro na função, torna-se o novo número da quadra.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param num É a novo número da quadra.
void set_num (Pessoa p, int num);

/// @brief Informa qual é o número da quadra.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna o número da quadra.
int get_num (Pessoa p);

/// @brief O char passado por parâmetro na função, torna-se o novo complemento da quadra.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param compl É o novo complemento da quadra.
void set_complemento(Pessoa p, char* compl);

/// @brief Informa qual é o complemento da quadra.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna o complemento da quadra.
char* get_complemento (Pessoa p);

/// Função prática para definir todos os dados de endereço de uma só vez.
void recebe_moradia (Pessoa p, char* cep, char face, int num, char* compl);

// TADs relacionados a pessoa:

/// @brief Cria uma pessoa com os parâmetros informados.
/// @param cpf String identificadora para saber a qual pessoa que ele está se referindo.
/// @param nome String que contém o nome da pessoa.
/// @param sobrenome String que contém o sobrenome da pessoa.
/// @param sexo Char para caracterizar se é do sexo masculino 'm' ou feminino 'f'.
/// @param nasc String para indicar qual é a data do nascimento de uma pessoa, do padrão DD/MM/AAAA.
/// @return Retorna a pessoa criada com os parâmetros.
Pessoa cria_pessoa (char* cpf, char* nome, char* sobrenome, char sexo, char* nasc);

/// Função para gerar uma string única com todos os dados da pessoa.
void get_dados_completos_pessoa(Pessoa p, char* buffer);

/// Função para ler a string do hash e recriar a struct Pessoa.
Pessoa reconstroi_pessoa(char* cpf, char* dados_do_hash);

/// @brief O ponteiro para os char, passado por parâmetro na função, torna-se o novo cpf da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param cpf É o novo cpf da pessoa.
void set_cpf_pessoa (Pessoa p, char* cpf);

/// @brief Informa qual é o cpf da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna o cpf da pessoa.
char* get_cpf_pessoa (Pessoa p);

/// @brief O ponteiro para os char, passado por parâmetro na função, torna-se o novo nome da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param nome É o novo nome da pessoa.
void set_nome_pessoa (Pessoa p, char* nome);

/// @brief Informa qual é o nome da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna o nome da pessoa.
char* get_nome_pessoa (Pessoa p);

/// @brief O ponteiro para os char, passado por parâmetro na função, torna-se o novo sobrenome da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param sobrenome É o novo sobrenome da pessoa.
void set_sobrenome_pessoa (Pessoa p, char* sobrenome);

/// @brief Informa qual é o sobrenome da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna o sobrenome da pessoa.
char* get_sobrenome_pessoa (Pessoa p);

/// @brief O char, passado por parâmetro na função, torna-se o novo sexo da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param sexo É o novo sexo da pessoa.
void set_sexo_pessoa (Pessoa p, char sexo);

/// @brief Informa qual é o sexo da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna o sexo da pessoa.
char get_sexo_pessoa (Pessoa p);

/// @brief O ponteiro para os char, passado por parâmetro na função, torna-se a nova data de nascimento da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param nasc É a nova data de nascimento da pessoa.
void set_nasc_pessoa (Pessoa p, char* nasc);

/// @brief Informa qual é a data de nascimento da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna a data de nascimento da pessoa.
char* get_nasc_pessoa (Pessoa p);

/// @brief O boolean passado por parâmetro na função, torna-se o novo status (relação a moradia) da pessoa.
/// @param p É o ponteiro que aponta para a pessoa.
/// @param status É a novo status de moradia da pessoa.
void set_eh_morador (Pessoa p, bool status);

/// @brief Responde, quando questionado, se uma determinada pessoa possui moradia.
/// @param p É o ponteiro que aponta para a pessoa.
/// @return Retorna true, se tiver moradia, ou false, caso contrário.
bool eh_morador (Pessoa p);

/// @brief Libera toda a memória que estava reservada à pessoa, disponibilizando a memória novamente para outro uso.
/// @param p É o ponteiro que aponta para a pessoa que terá a sua memória liberada.
void libera_pessoa(Pessoa p);


#endif