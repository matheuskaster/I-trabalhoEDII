//
// Created by Matheus on 22/04/2026.
//

#include "../include/quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sw[16];
    char cfill[16];
    char cstrk[16];
} StrCores;

typedef struct {
    char cep[10];
    double x, y, w, h;
} StrQuadra;

Cores cria_cores (char* sw, char* cfill, char* cstrk) {
    StrCores *cq = (StrCores*) malloc (sizeof(StrCores));
    strcpy (cq->sw, sw);
    strcpy (cq->cfill, cfill);
    strcpy (cq->cstrk, cstrk);
    return ((StrCores*)cq);
}

void set_sw (Cores cq, char *sw) {
    strcpy (((StrCores*)cq)->sw, sw);
}

char* get_sw (Cores cq) {
    return ((StrCores*)cq)->sw;
}

void set_cfill (Cores cq, char *cfill) {
    strcpy (((StrCores*)cq)->cfill, cfill);
}

char* get_cfill (Cores cq) {
    return ((StrCores*)cq)->cfill;
}

void set_cstrk (Cores cq, char *cstrk) {
    strcpy (((StrCores*)cq)->cstrk, cstrk);
}

char* get_cstrk (Cores cq) {
    return ((StrCores*)cq)->cstrk;
}



Quadra cria_quadra (char* cep, double x, double y, double w, double h, Cores cq) {
    StrQuadra *q = malloc(sizeof(StrQuadra));
    strcpy(q->cep, cep);
    q->x = x;
    q->y = y;
    q->w = w;
    q->h = h;
    return ((StrQuadra*) q);
}

void set_cep_quadra (Quadra q, char* cep) {
    strcpy (((StrQuadra*)q)->cep, cep);
}

char* get_cep_quadra (Quadra q) {
    return ((StrQuadra*)q)->cep;
}

void set_x_quadra (Quadra q, double x) {
    ((StrQuadra*)q)->x = x;
}

double get_x_quadra (Quadra q) {
    return ((StrQuadra*)q)->x;
}

void set_y_quadra (Quadra q, double y) {
    ((StrQuadra*)q)->y = y;
}

double get_y_quadra (Quadra q) {
    return ((StrQuadra*)q)->y;
}

void set_w_quadra (Quadra q, double w) {
    ((StrQuadra*)q)->w = w;
}

double get_w_quadra (Quadra q) {
    return ((StrQuadra*)q)->w;
}

void set_h_quadra (Quadra q, double h) {
    ((StrQuadra*)q)->h = h;
}

double get_h_quadra (Quadra q) {
    return ((StrQuadra*)q)->h;
}

void libera_cores (Cores cq) {
    if (cq == NULL) return;
    StrCores* _cq = (StrCores*)cq;
    free(_cq);
}

void libera_quadra (Quadra q) {
    if (q == NULL) return;
    StrQuadra* _q = (StrQuadra*) q;
    free(_q);
}