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
    fprintf(arq_svg,"<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" width=\"10000\" height=\"10000\">\n");
    fprintf(arq_svg,"<g>\n");
}

void desenha_quadra_svg (FILE* arq_svg, Quadra q, Cores cq) {
    fprintf(arq_svg, "<rect cep=\"%s\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" stroke-width=\"%s\" />\n", get_cep_quadra(q), get_cfill(cq), get_cstrk(cq), 0.6*get_h_quadra(q), 0.6*get_w_quadra(q), 0.6*get_y_quadra(q), 0.6*get_x_quadra(q), get_sw(cq));
    fprintf(arq_svg, "<text x=\"%lf\" y=\"%lf\" fill=\"black\" font-family=\"Arial\" font-size=\"10\" font-weight=\"bold\">%s</text>\n", (0.6 * get_x_quadra(q)) + 4.0, (0.6 * get_y_quadra(q)) + 24.0, get_cep_quadra(q));
}

void desenha_x_vermelho_svg (FILE* arq_svg, double x, double y) {
    double tamanho = 2.0;
    fprintf(arq_svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"%lf\" />\n", 0.6*(x - tamanho), 0.6*(y - tamanho), 0.6*(x + tamanho), 0.6*(y + tamanho), 2.0);
    fprintf(arq_svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"%lf\" />\n", 0.6*(x + tamanho), 0.6*(y - tamanho), 0.6*(x - tamanho), 0.6*(y + tamanho), 2.0);
}

void desenha_numero_moradores_svg (FILE* arq_svg, double x, double y, char* txto) {
    fprintf(arq_svg, "<text x=\"%lf\" y=\"%lf\" fill=\"black\" font-family=\"Arial\" font-size=\"10\" font-weight=\"bold\">%s</text>\n", 0.6*x, 0.6*y, txto);
}

void desenha_cruz_vermelha_svg(FILE* arq_svg, double x, double y) {
    double tamanho = 2.0;
    fprintf(arq_svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"%lf\" />\n", 0.6*x, 0.6*(y - tamanho), 0.6*x, 0.6*(y + tamanho), 1.5);
    fprintf(arq_svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"%lf\" />\n", 0.6*(x - tamanho), 0.6*y, 0.6*(x + tamanho), 0.6*y, 1.5);
}

void desenha_quadrado_vermelho_svg (FILE* arq_svg, double x, double y, char* cpf) {
    double altura_largura = 2.0;
    fprintf(arq_svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill=\"none\" opacity=\"%lf\" stroke-width=\"%lf\" />\n", 0.6*x, 0.6*y, 0.6*altura_largura, 0.6*altura_largura, 4.0, 1.5);
    fprintf(arq_svg, "\t<text x=\"%lf\" y=\"%lf\" fill=\"red\" font-size=\"3px\" text-anchor=\"middle\" >%s</text>\n", 0.6*x + 0.6*2.0, 0.6*y + 0.6*(altura_largura - 2.0), cpf);
}

void desenha_circulo_preto_svg(FILE* arq_svg, double x, double y) {
    fprintf(arq_svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"black\" fill=\"black\" opacity=\"%lf\" stroke-width=\"%lf\" />\n", 0.6*x, 0.6*y, 0.6*2.0, 4.0, 1.5);
}

void fecha_svg(FILE* arq_svg) {
    if (arq_svg == NULL) {
        printf("Não foi possível acessar o arquivo. \n");
        return;
    }
    fprintf(arq_svg, "</g>\n");
    fprintf(arq_svg,"</svg>\n");
}