//
// Created by Matheus on 22/04/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"

void abre_svg (FILE* arq_svg) {

    if (arq_svg == NULL) {
        printf("O aquivo não exite. \n");
        return;
    }
    fprintf(arq_svg,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(arq_svg,"<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\">\n");
    fprintf(arq_svg,"<g>\n");
}

void desenha_quadra_svg (FILE* arq_svg, Quadra q) {
    fprintf(arq_svg, "<rect id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" stroke-width=\"%lf\" />\n", get_cep_quadra(q), get_cfill(q), get_cstrk(q), get_h_retangulo(q), get_w_retangulo(q), get_y_retangulo(q), get_x_retangulo(q), 1.0);
}

void fecha_svg(FILE* arq_svg) {
    if (arq_svg == NULL) {
        printf("Não foi possível acessar o arquivo. \n");
        return;
    }
    fprintf(arq_svg, "</g>\n");
    fprintf(arq_svg,"</svg>\n");
}