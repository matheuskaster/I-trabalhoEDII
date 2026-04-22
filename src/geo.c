//
// Created by Matheus on 21/04/2026.
//
#include "../include/geo.h"
#include "../include/svg.h"
#include <stdlib.h>
#include <string.h>

void geo (Gerenciador quadras, FILE* arq_geo) {

    if(arq_geo == NULL){
        printf("Arquivo .geo não encontrado. \n");
        exit(1);
    }

    char linha[256];
    char comando[3];
    Cores cq = NULL;

    while (fgets(linha, sizeof(linha), arq_geo) != NULL) {
        if (linha[0] == '\n' || linha[0] == '#'){
            continue;
        }

        sscanf(linha, "%s", comando);

        if (strcmp(comando, "q") == 0) {
            char cep[16];
            double x, y, w, h;
            if (cq == NULL) {
                //settando cores padroes, pois não foi informado quais sao as cores desejadas.
                cq = criaCores( "1.0px", "steelblue" , "MistyRose");
            }
            sscanf (linha, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            Quadra q = cria_quadra(cep, x, y, w, h, cq);
            desenha_retangulo_svg(arq_geo, q);
            insere_registro (quadras, ??);
        } else {
            char sw[6], cfill[8], cstrk[8];
            sscanf (linha, "%%s %s %s", sw, cfill, cstrk);
            setSwCores(cq, sw);
            setCfillCores(cq, cfill);
            setCstrkCores(cq, cstrk);
        }
    }
}