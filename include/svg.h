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

/// @brief Escreve o rodapé do arquivo .svg, ou seja, é a tag </svg> que fecha o arquivo svg, indicando a realização com sucesso.
/// @param arq_svg É um arquivo do tipo FILE* para acessar o arquivo, já inicializado.
void fecha_svg (FILE* arq_svg);

#endif