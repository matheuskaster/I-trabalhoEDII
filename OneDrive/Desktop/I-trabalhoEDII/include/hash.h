#ifndef HASH_H
#define HASH_H

typedef void* Registro;
typedef void* Gerenciador;

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
Registro cria_registro(int chave, int dados);

/// @brief Troca a chave do registro desejado.
/// @param r É o ponteiro para o registro que terá sua chave alterada.
/// @param chave É a chave identificadora, específica de cada registro.
void set_chave_registro(Registro r, int chave);

/// @brief Informa a chave do registro desejado.
/// @param r É o ponteiro para o registro que guarda a informação.
/// @return Retorna o número inteiro, que representa a chave do registro passado por parâmetro.
int get_chave_registro(Registro r);

/// @brief Troca os dados do registro desejado.
/// @param r É o ponteiro para o registro que terá seus dados alterados.
/// @param dados São as informações gerais referentes à esse registro.
void set_dados_registro(Registro r, int dados);

/// @brief Informa os dados do registro desejado.
/// @param r É o ponteiro para o registro que guarda a informação.
/// @return Retorna o número inteiro, que representa os dados do registro passado por parâmetro.
int get_dados_registro(Registro r);

/// @brief Busca dentro do arquivo um registro que está inserido na hash. 
/// @param hash É o gerenciador para acessar e controlar os arquivos.
/// @param chave É a chave identificadora, específica de cada registro.
/// @return Retorna um ponteiro para o registro encontrado.
Registro busca_registro(Gerenciador hash, int chave);

/// @brief Insere um novo registro no arquivo.
/// @param hash É o gerenciador para acessar e controlar os arquivos.
/// @param r É o ponteiro para o registro que será inserido.
void insere_registro(Gerenciador hash, Registro r);

/// @brief Libera a memória do registro.
/// @param r É o ponteiro para o registro que terá sua memória liberada.
void libera_registro(Registro r);

/// @brief Fecha os arquivos e libera a memória do gerenciador.
/// @param hash É o ponteiro para o gerenciador, estrutura que contém os arquivos, que será liberado.
void libera_hash(Gerenciador hash);

#endif