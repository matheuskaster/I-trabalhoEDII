#ifndef PATH_UTIL
#define PATH_UTIL

/// @brief Recebe um caminho para um arquivo, com o último caractere sendo uma barra, e remove essa última barra.
/// @param path É o ponteiro para onde será salvo o caminho para o arquivo, sem essa barra no final, indesejada.
/// @param tamMax Número inteiro que representa, o tamanho do espaço disponível para armazenar o texto.
/// @param arg É o ponteiro para o caminho original, que terá a última barra removida.
void trataPath(char *path, int tamMax, char *arg);

/// @brief Copia o nome de um arquivo com espaços sobrando no vetor, para encaixar uma extensão, como por exemplo, um ".geo" no final.
/// @param path É o ponteiro para onde será salvo o nome do arquivo, com esses espaços sobrando.
/// @param tamMax Número inteiro que representa, o tamanho do espaço disponível para armazenar o texto.
/// @param arg É o ponteiro para o nome do arquivo original, que será copiado, com seu tamanho aumentado.
void trataNomeArquivo(char *path, int tamMax, char *arg);

/// @brief Remove todo o caminho para chegar em um arquivo e sua possível extensão e deixa só o nome do arquivo puro.
/// @param arq É o ponteiro para o caminho completo para um arquivo.
/// @param nome_base É a parte já extraída, tem só o nome do arquivo.
void extrai_nome_base(char *arq, char *nome_base);

/// @brief Recebe o caminho de um diretório, e junta através de uma '/' com o nome do arquivo que se pretende criar.
/// @param dir É o ponteiro para a pasta, onde estará localizado o novo arquivo a ser criado.
/// @param file É o nome do arquivo que se localizará nessa pasta.
/// @return Retorna o arquivo com seu caminho.
char *monta_caminho_completo(const char *dir, const char *file);

/// @brief Recebe um arquivo, em uma pasta de entrada, e passa ele para uma pasta de saída com outra extensão.
/// @param dir_saida É o ponteiro para a nova pasta, que esse novo arquivo criado se localizará.
/// @param nome_arq_entrada É o ponteiro para o arquivo original, para montar com os arquivos com o mesmo nome puro.
/// @param nova_extensao É o ponteiro para como será a nova extensão. Ex.: ".geo" -> ".qry"
/// @return Retorna o ponteiro para o novo arquivo, com seu novo diretório, e sua nova extensão.
char *atualiza_extensao(const char *dir_saida, const char *nome_arq_entrada, const char *nova_extensao);

#endif