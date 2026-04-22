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

void desenha_retangulo_svg (FILE* arq_svg, Retangulo r) {
    fprintf(arq_svg, "<rect id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" stroke-width=\"%lf\" />\n", get_id_retangulo(r), get_corp_retangulo(r), get_corb_retangulo(r), get_h_retangulo(r), get_w_retangulo(r), get_y_retangulo(r), get_x_retangulo(r), 1.0);
}

void fecha_svg(FILE* arq_svg) {
    if (arq_svg == NULL) {
        printf("Não foi possível acessar o arquivo. \n");
        return;
    }
    fprintf(arq_svg, "</g>\n");
    fprintf(arq_svg,"</svg>\n");
}