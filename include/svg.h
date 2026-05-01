//
// Created by Matheus on 22/04/2026.
//
#ifndef SVG_H
#define SVG_H
#include <stdio.h>
#include "quadra.h"

/// @brief Escreve o cabeçalho do arquivo .svg, ou seja, é a declaração <?xml ...?> e a tag <svg ...> com seus atributos que definem o espaço e as regras para o desenho.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo, já inicializado.
void abre_svg (FILE* arq_svg);

/// @brief Passa as características do retângulo para o svg poder o desenhar.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo.
/// @param q É um ponteiro que aponta para a quadra que será desenhada, no formato de um retângulo.
void desenha_retangulo_svg (FILE* arq_svg, Quadra q);

/// @brief Função que desenha um X vermelha, na âncora da quadra, com os 'x' e 'y' passados por parâmetro.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo, que conterá as ilustrações.
/// @param x Número double, que representa a coordenada que ficará o X, no eixo 'x'.
/// @param y Número double, que representa a coordenada que ficará o X, no eixo 'y'.
void desenha_x_vermelho_svg (FILE* arq_svg, double x, double y);

/// @brief Coloca o número de moradores próximo às faces - de cada face -, e no centro, o total.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo, que conterá as ilustrações.
/// @param x Número double, que representa a coordenada que ficará a âncora do texto, no eixo 'x'.
/// @param y Número double, que representa a coordenada que ficará a âncora do texto, no eixo 'y'.
/// @param txto É a String que carrega o conteúdo que vai ser escrito no svg, no caso, o número.
void desenha_numero_moradores_svg (FILE* arq_svg, double x, double y, char* cor, int tamanho, char* txto);

/// @brief Função que desenha uma cruz vermelha, no endereço do morador que faleceu, com os 'x' e 'y' passados por parâmetro.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo, que conterá as ilustrações.
/// @param x Número double, que representa a coordenada que ficará a âncora do cruz, no eixo 'x'.
/// @param y Número double, que representa a coordenada que ficará a âncora do cruz, no eixo 'y'.
void desenha_cruz_vermelha_svg(FILE* arq_svg, double x, double y);

/// @brief Desenha quadrado vermelho no novo endereço da pessoa que possui esse cpf.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo, que conterá as ilustrações.
/// @param x Número double, que representa a coordenada que ficará a âncora do quadrado, no eixo 'x'.
/// @param y Número double, que representa a coordenada que ficará a âncora do quadrado, no eixo 'y'.
/// @param cpf Número CPF identificador da pessoa, que foi despejada.
void desenha_quadrado_vermelho_svg (FILE* arq_svg, double x, double y, char* cpf);

/// @brief Desenha círculo preto, no endereço da pessoa que, infelizmente, perdeu a sua moradia.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo, que conterá as ilustrações.
/// @param x Número double, que representa a coordenada que ficará o centro do círculo, no eixo 'x'.
/// @param y Número double, que representa a coordenada que ficará o centro do círculo, no eixo 'y'.
void desenha_circulo_preto_svg(FILE* arq_svg, double x, double y);

/// @brief Escreve o rodapé do arquivo .svg, ou seja, é a tag </svg> que fecha o arquivo svg, indicando a realização com sucesso.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo, já inicializado.
void fecha_svg (FILE* arq_svg);

#endif