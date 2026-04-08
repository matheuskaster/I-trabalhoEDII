#ifndef HASH_H
#define HASH_H

typedef void* Registro;
typedef void* Gerenciador;

/* MODULO HASH
Esse modulo utiliza da estrutura de dados hash para guardar registros e ter um tempo de busca linear, utilizando a mesma ideia de um
vetor, que sabe exatamente onde esta guardado o registro e utiliza ele, sem precisar percorrer os elementos ate encontrar o desejado.
Para acessar qualquer arquivo e utilizado um gerenciador que possui os ponteiros em sua estrutura para localizar os arquivos do
diretorio (analogo ao vetor), do bucket (onde sera efetivamente guardado o registro) e o do texto (onde sera guardado as informacoes
importantes, como o deslocamento de cada bucket em relacao ao primeiro endereco do arquivo e tamanho de cada bucket).
*/

/// @brief Cria um sistema "hash", responsável por acessar aos dois arquivos, o hf e o hfc e ele cuida da necessitade de expandir o
/// arquivo do diretório. Ela cria os arquivos dentro da função, com o nome de cada um sendo informado.
/// @param dir_filename É o ponteiro para o nome do arquivo do diretório.
/// @param bucket_filename É o ponteiro para o nome do arquivo do bucket. 
/// @return Retorna um ponteiro para o gerenciador do hash.
Gerenciador cria_hash(const char* dir_filename, const char* bucket_filename);

/// @brief Cria um novo registro.
/// @param chave É a chave para identificá-lo.
/// @param dados São as outras informações referentes à esse registro.
/// @return Retorna um ponteiro para o registro recém-criado.
Registro cria_registro(char* chave, int dados);

/// @brief Troca a chave do registro desejado.
/// @param r É o ponteiro para o registro que terá sua chave alterada.
/// @param chave É a chave identificadora, específica de cada registro.
void set_chave_registro(Registro r, char* chave);

/// @brief Informa a chave do registro desejado.
/// @param r É o ponteiro para o registro que guarda a informação.
/// @return Retorna o número inteiro, que representa a chave do registro passado por parâmetro.
int get_chave_registro(Registro r);

/// @brief Troca os dados do registro desejado.
/// @param r É o ponteiro para o registro que terá seus dados alterados.
/// @param dados São as informações gerais referentes à esse registro.
void set_dados_registro(Registro r, char* dados);

/// @brief Informa os dados do registro desejado.
/// @param r É o ponteiro para o registro que guarda a informação.
/// @return Retorna o número inteiro, que representa os dados do registro passado por parâmetro.
int get_dados_registro(Registro r);

/// @brief Busca dentro do arquivo um registro que está inserido na hash. 
/// @param hash É o gerenciador para acessar e controlar os arquivos.
/// @param chave É a chave identificadora, específica de cada registro.
/// @return Retorna um ponteiro para o registro encontrado.
Registro busca_registro(Gerenciador hash, char* chave);

/// @brief Insere um novo registro no arquivo.
/// @param hash É o gerenciador para acessar e controlar os arquivos.
/// @param r É o ponteiro para o registro que será inserido.
void insere_registro(Gerenciador hash, Registro r);

/// @brief Função que remove um registro de um bucket.
/// @param hash É o gerenciador para acessar e controlar os arquivos.
/// @param chave É o ponteiro para o registro que terá seus dados alterados.
/// @return Retorna 1, se tiver removido e 0 se não tiver encontrado a chave do registro a ser removido.
int remove_registro(Gerenciador hash, Registro r);

/// @brief Libera a memória do registro.
/// @param r É o ponteiro para o registro que terá sua memória liberada.
void libera_registro(Registro r);   

/// @brief Fecha os arquivos e libera a memória do gerenciador.
/// @param hash É o ponteiro para o gerenciador, estrutura que contém os arquivos, que será liberado.
void libera_hash(Gerenciador hash);

#endif