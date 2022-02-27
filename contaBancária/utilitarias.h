#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "abas.h"

#define bool _Bool
#define true 1
#define false 0

bool validaTamanho( const char *dado, const int tamanhoDoDado );
bool sairConfirma( );
bool sair( char *respostaInserida );
char *padronizaDado( char *dadoInserido );
void limpaDado( char *dadoBruto );

bool validaTamanho( const char *dado, const int tamanho ){
    for( int digito = 0; dado[digito] != '\0'; digito++ )
        if( dado[digito+1] == '\0' && (digito+3) < tamanho )
            return false;
    return true;
}
bool sair( char *resposta ){
    char *sair = "sair",
         respostaBackUp[5] = {};
    strncpy(respostaBackUp, resposta, 4);
    strcpy(respostaBackUp, (padronizaDado(respostaBackUp)));
    if( strcmp(respostaBackUp, sair ) == 0 )
        return true;
    return false;
}
char *padronizaDado( char *dadoForaDoPadrao ){
    char *dadoBackUp = (char*)malloc( sizeof dadoForaDoPadrao );
    strcpy( dadoBackUp, dadoForaDoPadrao );
    for( int caracter = 0; dadoBackUp[caracter] != '\0'; caracter++ ){
        dadoBackUp[caracter] = tolower( dadoBackUp[caracter] );}
    return dadoBackUp;
}
void limpaDado( char *dado ){
    for( int caracter = 0; dado[caracter] != '\0'; caracter++ )
        if( dado[caracter+1] == '\0' )
            dado[caracter] = '\0'; 
}
bool sairConfirma(  ){
    char resposta = '\0';
    do{    
        printf ( "\n|----------------| BLACKBANK |----------------|\n"
                   "|                                             |\n"
                   "|                                             |\n"
                   "|                                             |\n"
                   "|               CONFIRMA SAÍDA?               |\n"
                   "|                                             |\n"
                   "|         [1] [ SIM ]     [0] [ NÃO ]         |\n"
                   "|                                             |\n"
                   "|                                             |\n"
                   "|---------------------------------------------|\n"
                   "-} ");
        resposta = getchar( ); getchar( ); 
    }while( resposta != '1' && resposta != '0' );
    return (resposta == '1' ? true : false );    
}
///DEFINIR FUNÇÃO QUE FAZ A LIMPEZA DO BUFFER


#endif // UTILITARIAS_H_INCLUDED