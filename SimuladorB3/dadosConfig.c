#include "include/config.h"

bool cria_arquivos( ){
    FILE *arquivo;

    if( ( arquivo = fopen( "arquivos/papeis.txt", "r" ) ) == NULL ){
        if( ( arquivo = fopen( "arquivos/papeis.txt", "w" ) ) == NULL ){}
    }fclose(arquivo);
    if( ( arquivo = fopen( "arquivos/dadosConfig.txt", "r" ) ) == NULL ){
        if( ( arquivo = fopen( "arquivos/dadosConfig.txt", "w" ) ) == NULL ){}
    }fclose(arquivo);
    if( ( arquivo = fopen( "arquivos/historicoTransacao.txt", "r" ) ) == NULL ){
        if( ( arquivo = fopen( "arquivos/historicoTransacao.txt", "w" ) ) == NULL ){}
    }fclose(arquivo);
    if( ( arquivo = fopen( "arquivos/carteiraConfig.txt", "r" ) ) == NULL ){
        if( ( arquivo = fopen( "arquivos/carteiraConfig.txt", "w" ) ) == NULL ){}
    }fclose(arquivo);
    if( ( arquivo = fopen( "arquivos/acoesValorVenda.txt", "r" ) ) == NULL ){
        if( ( arquivo = fopen( "arquivos/acoesValorVenda.txt", "w" ) ) == NULL ){}
    }fclose(arquivo);
    if( ( arquivo = fopen( "arquivos/acoesValorCompra.txt", "r" ) ) == NULL ){
        if( ( arquivo = fopen( "arquivos/acoesValorCompra.txt", "w" ) ) == NULL ){}
    }fclose(arquivo);

    return true;
}
