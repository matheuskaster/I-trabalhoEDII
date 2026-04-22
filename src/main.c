#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/path_utils.h"

#define PATH_LEN 250
#define FILE_NAME_LEN 100

int main(int argc, char *argv[]) {
    char dir_entrada[PATH_LEN] = "./";
    char dir_saida[PATH_LEN] = "";
    char arq_geo[FILE_NAME_LEN] = "";
    char arq_qry[FILE_NAME_LEN] = "";
    char arq_pm[FILE_NAME_LEN] = "";

    FILE *file_geo = NULL;
    FILE *file_pm = NULL;
    FILE *file_qry = NULL;
    FILE *file_svg_geo = NULL;
    FILE *file_svg_qry = NULL;
    FILE *file_txt = NULL;

    int i = 1;
    while (i < argc) {
        switch (argv[i][1]) {
            case 'e':
                if (i + 1 < argc) {
                    i++;
                    trataPath(dir_entrada, PATH_LEN, argv[i]);
                }
                break;
            case 'o':
                if (i + 1 < argc) {
                    i++;
                    trataPath(dir_saida, PATH_LEN, argv[i]);
                }
                break;
            case 'f':
                if (i + 1 < argc) {
                    i++;
                    trataNomeArquivo(arq_geo, FILE_NAME_LEN, argv[i]);
                }
                break;
            case 'q':
                if (i + 1 < argc) {
                    i++;
                    trataNomeArquivo(arq_qry, FILE_NAME_LEN, argv[i]);
                }
                break;
            case 'p':
                if (i + 1 < argc) {
                    i++;
                    trataNomeArquivo(arq_pm, FILE_NAME_LEN, argv[i]);
                }
                break;
        }
        i++;
    }

    if (strlen(arq_geo) == 0 || strlen(dir_saida) == 0) {
        printf("Faltando -f ou -o, parâmetros que são obrigatórios. \n");
        return 1;
    }

    char* path_geo = monta_caminho_completo(dir_entrada, arq_geo);
    file_geo = fopen(path_geo, "r");
    if (!file_geo) {
        printf("[ERRO] não foi possível abrir o .geo: %s\n", path_geo);
        return 1;
    }
    free(path_geo);

    char* path_pm = monta_caminho_completo(dir_entrada, arq_pm);
    file_geo = fopen(path_pm, "r");
    if (!file_pm) {
        printf("[ERRO] não foi possível abrir o .pm: %s\n", path_pm);
        return 1;
    }
    free(path_pm);

    char* path_svg_geo = atualiza_extensao (dir_saida, arq_geo, ".svg");
    file_svg_geo = fopen(path_svg_geo, "w");
    if (!file_svg_geo) {
        fclose(file_geo);
        printf("[ERRO] não foi possível abrir o svg do .geo.\n");
        return 1;
    }
    free(path_svg_geo);

    //geo(file_geo);
    //abre_svg(file_svg_geo);
    //svg(file_svg_geo);
    //fecha_svg(file_svg_geo);

    if (strlen(arq_qry) > 0) {

        char* path_qry = monta_caminho_completo(dir_entrada, arq_qry);
        file_qry = fopen(path_qry, "r");
        if (!file_qry) {
            printf("[ERRO] não foi possível abrir o .qry: %s\n", path_qry);
            return 1;
        }
        free(path_qry);

        char* path_svg_qry = atualiza_extensao(dir_saida, arq_qry, ".svg");
        char* path_txt_qry = atualiza_extensao(dir_saida, arq_qry, ".txt");

        file_svg_qry = fopen(path_svg_qry, "w");
        file_txt     = fopen(path_txt_qry, "w");

        free(path_txt_qry);

        if (file_svg_qry && file_txt) {
            //qry(file_qry, file_svg_qry, file_txt, path_svg_qry);
        }
        free(path_svg_qry);
    }

    if (file_geo)     fclose(file_geo);
    if (file_svg_geo) fclose(file_svg_geo);
    if (file_qry)     fclose(file_qry);
    if (file_svg_qry) fclose(file_svg_qry);
    if (file_txt)     fclose(file_txt);

    return 0;
}