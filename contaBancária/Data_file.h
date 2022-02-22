#ifndef DATA_FILE_H_INCLUDED
#define DATA_FILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define bool _Bool
#define true 1
#define false 0

#define TAMANHO_NOME_COMP 61
#define TAMANHO_NOME_PREF 31
#define TAMANHO_EMAIL 31
#define TAMANHO_TELEFONE 12
#define TAMANHO_CPF 20
#define TAMANHO_SENHA 7
#define TAMANHO_RENDA 8
#define TAMANHO_DATA_NASCIMENTO 9

#define CLEAN system ("cls");
#define DLAY getchar ( );

struct dados{
    char nomeCompleto[ TAMANHO_NOME_COMP ],
         nomePreferencial[ TAMANHO_NOME_PREF ],
         email[ TAMANHO_EMAIL ],
         telefone[ TAMANHO_TELEFONE ],
         cpf[ TAMANHO_CPF ],
         senha[ TAMANHO_SENHA ],
         renda[ TAMANHO_RENDA ],
         dataNascimento[ TAMANHO_DATA_NASCIMENTO ];
};
typedef struct dados Dados;

bool cadastrarCliente( Dados* );
char *validaCpf( char* );
char *validaNomes( char* );
char *validaEmail( char* );
char *validaTelefone( char* );
char *validaRenda( char* );
char *validaSenha( char* );
char *validaDataNascimento( char* );

bool solicitaEmail( Dados* );
bool solicitaNomePreferencial( Dados* );
bool solicitaNomeCompleto( Dados* );
bool solicitaTelefone( Dados* );
bool solicitaRenda( Dados* );
bool solicitaSenha( Dados* );
bool solicitaCpf( Dados* );
bool solicitaData_De_Nascimento( Dados* );

bool cadastrarCliente( Dados *Cliente ){
    if( solicitaCpf( Cliente ) ){

        //if( solicitaData_De_Nascimento( Cliente ) ){
            //if( solicitaNomeCompleto(Cliente ) ){
               // if( solicitaEmail( Cliente ) ){
                   // if( solicitaTelefone( Cliente ) ){
                       // if( solicitaRenda( Cliente ) ){
                          //  if( solicitaNomePreferencial( Cliente ) ){
                              //  if( solicitaSenha( Cliente ) ){
                                    ///return true;
                                    ///arquivamento;
                               // }else return false;
                           // }else return false;
                       // }else return false;
                   // }else return false;
               // }else return false;
           // }else return false;
       // }else return false;
    }else return false;
}

bool solicitaCpf( Dados *cliente ){
    char *mensagemDeErro = NULL;

    do{
        printf("-> Insira seu CPF [xxx.xxx.xxx-xx]\n   <- ");
        fgets( cliente->cpf, TAMANHO_CPF, stdin );
        mensagemDeErro = validaCpf( cliente->cpf );
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL );

    return true;
}
char *validaCpf( char*cpf ){
    static char *erro = NULL;
    /// 0 0 0 . 0 0 0 . 0 0 0 - 0 0
    /// 0 1 2 3 4 5 6 7 8 9 0 1 2 3

    if( !(cpf[3] == '.') || !(cpf[7] == '.') || !(cpf[11] == '-') ){
        erro = "\t^ Formato invalido!\n";
    }else{
        for( int digito = 0; cpf[digito] != '\0'; digito++ ){
            if( isdigit( cpf[digito] ) != 0 && cpf[digito] != '\n' ){
                erro = "\t^ Utilize apenas numeros!\n";
                break;}}
        erro = NULL;}
    return erro;
}
#endif // DATA_FILE_H_INCLUDED
