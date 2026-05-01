//
// Created by Matheus on 01/05/2026.
//

#ifndef QRY_H
#define QRY_H

/// @brief É uma função feita para poder ler o arquivo de entrada qry e chamar funções que irão executar os comandos.
/// @param quadras É o gerenciador que tem acesso e controle ao hashfile, referente às quadras, do programa.
/// @param pessoas É o gerenciador que tem acesso e controle ao hashfile, referente às pessoas, do programa.
/// @param file_qry É o arquivo de entrada do tipo .qry.
/// @param file_txt É o arquivo de saída, com o relatório final, depois de ter sido processado pelo qry.
/// @param file_svg É o arquivo de saída, com as ilustrações, depois de ter sido processado pelo qry.
void qry (Gerenciador quadras, Gerenciador pessoas, FILE* file_qry, FILE* file_txt, FILE* file_svg);

#endif