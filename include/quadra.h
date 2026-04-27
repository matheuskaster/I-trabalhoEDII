//
// Created by Matheus on 22/04/2026.
//
#ifndef QUADRA_H
#define QUADRA_H

typedef void* Cores;
typedef void* Quadra;

// TADs relacionados as cores da quadra:

/// @brief Cria o conjunto que compoe as cores que serao atribuidas a uma quadra.
/// @param sw espessura da borda da quadra. Ex.: 1.0 px
/// @param cfill cor de preenchimento da quadra, sendo uma string valida, no padrao do svg, como uma cor.
/// @param cstrk cor de borda da quadra, sendo uma string valida, no padrao svg, como uma cor.
/// @return Retorna uma estrutura que guarda todas as possiveis cores.
Cores cria_cores (char* sw, char* cfill, char* cstrk);

/// @brief O char ponteiro passado por parâmetro na função, torna-se a espessura da borda da quadra.
/// @param cq É um ponteiro para a estrutura que guarda as cores.
/// @param sw É a nova espessura da quadra.
void set_sw (Cores cq, char *sw);

/// @brief Informa qual é a espessura da borda da quadra.
/// @param cq É um ponteiro para a estrutura que guarda as cores.
/// @return Retorna a espessura da quadra.
char* get_sw (Cores cq);

/// @brief O char ponteiro passado por parâmetro na função, torna-se a cor de preenchimento da quadra.
/// @param cq É um ponteiro para a estrutura que guarda as cores.
/// @param cfill É a nova cor de preenchimento da quadra.
void set_cfill (Cores cq, char *cfill);

/// @brief Informa qual é a cor de preenchimento da quadra.
/// @param cq É um ponteiro para a estrutura que guarda as cores.
/// @return Retorna a cor de preenchimento da quadra.
char* get_cfill (Cores cq);

/// @brief O char ponteiro passado por parâmetro na função, torna-se a cor da borda da quadra.
/// @param cq É um ponteiro para a estrutura que guarda as cores.
/// @param cstrk É a nova cor de borda da quadra.
void set_cstrk (Cores cq, char *cstrk);

/// @brief Informa qual é a cor da borda da quadra.
/// @param cq É um ponteiro para a estrutura que guarda as cores.
/// @return Retorna a cor de borda da quadra.
char* get_cstrk (Cores cq);


// TADs relacionados a quadra:

/// @brief Cria uma quadra com os parâmetros informados.
/// @param cep String identificadora para saber a qual quadra que ele está se referindo.
/// @param x É a coordenada no eixo x no qual a âncora do retângulo se encontra (o vértice do canto inferior esquerdo).
/// @param y É a coordenada no eixo y no qual a âncora do retângulo se encontra (o vértice do canto inferior esquerdo).
/// @param w É um número real correspondente a largura do retângulo.
/// @param h É um número real correspondente a altura do retângulo.
/// @return Retorna uma quadra criada com os parâmetros.
Quadra cria_quara (char* cep, double x, double y, double w, double h);

/// @brief O ponteiro para os char, passado por parâmetro na função, torna-se o novo cep da quadra.
/// @param q É um ponteiro que aponta para a quadra.
/// @param cep É o novo cep da quadra.
void set_cep_quadra (Quadra q, char* cep);

/// @brief Informa qual é o cep da quadra.
/// @param q É um ponteiro que aponta para a quadra.
/// @return Retorna o cep da quadra.
char* get_cep_quadra (Quadra q);

/// @brief O número double passado por parâmetro na função indica a coordenada no eixo x onde está localizado a âncora da quadra.
/// @param q É um ponteiro que aponta para a quadra.
/// @param x É a coordenada no eixo x na qual a âncora da quadra se encontra.
void set_x_quadra (Quadra q, double x);

/// @brief Informa qual é a coordenada no ponto x da âncora da quadra.
/// @param q É um ponteiro que aponta para a quadra.
/// @return Retorna qual é a coordenada no ponto x da âncora da quadra.
double get_x_quadra (Quadra q);

/// @brief O número double passado por parâmetro na função indica a coordenada no eixo y onde está localizado a âncora da quadra.
/// @param q É um ponteiro que aponta para a quadra.
/// @param y É a coordenada no eixo y na qual a âncora da quadra se encontra.
void set_y_quadra (Quadra q, double y);

/// @brief Informa qual é a coordenada no ponto y da âncora da quadra.
/// @param q É um ponteiro que aponta para a quadra.
/// @return Retorna qual é a coordenada no ponto y da âncora da quadra.
double get_y_quadra (Quadra q);

/// @brief O número passado por parâmetro na função, torna-se a largura da quadra, também passada por parâmetro.
/// @param q É um ponteiro que aponta para a quadra.
/// @param w É a largura que a quadra possui.
void set_w_quadra (Quadra q, double w);

/// @brief Informa qual é a largura da quadra.
/// @param q É um ponteiro que aponta para a quadra.
/// @return Retorna qual é a largura da quadra.
double get_w_quadra (Quadra q);

/// @brief O número passado por parâmetro na função, torna-se a altura da quadra, também passada por parâmetro.
/// @param q É um ponteiro que aponta para a quadra.
/// @param w É a altura que a quadra possui.
void set_h_quadra (Quadra q, double w);

/// @brief Informa qual é a altura da quadra.
/// @param q É um ponteiro que aponta para a quadra.
/// @return Retorna qual é a altura da quadra.
double get_h_quadra (Quadra q);

/// @brief Libera toda a memória que estava reservada às cores da quadra, disponibilizando a memória novamente para outro uso.
/// @param cq É um ponteiro que aponta para a estrutura de cores, que terá a sua memória liberada.
void libera_cores (Cores cq);

/// @brief Libera toda a memória que estava reservada à quadra, disponibilizando a memória novamente para outro uso.
/// @param q É um ponteiro que aponta para a quadra que terá a sua memória liberada.
void libera_quadra(Quadra q);

#endif
