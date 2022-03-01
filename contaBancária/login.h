#include "utilitarias.h"

#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

int login( void ){
    char *solicitaSenhaLogin(  );
    char *solicitaCpfLogin(  );

    char cpfLogin[TAMANHO_CPF];

    FILE *clienteCadastrados = fopen( ARQUIVO_CADASTRO_CLIENTE, "r") ;
    FILE *dadosDosArquivos = NULL;

    if( clienteCadastrados == NULL ){
        puts( "\n\n\tNÃO HÁ CLIENTES NA BASE AINDA!\n\n");
    }else{
        do{
            strcpy( cpfLogin, (solicitaCpfLogin( )) ); ///verificar a string de saída
            dadosDosArquivos = fopen( DADOS_ARQUIVO_CADASTRO, "r" );
            fscanf( dadosDosArquivos, "%d", &quantidadeDeContas );
            fclose( dadosDosArquivos );
        
            for( int id = 0; id <= quantidadeDeContas-1; id++ ){
                fseek( clienteCadastrados, id, SEEK_SET );
                fread( &cliente, sizeof(Dados), 1, clienteCadastrados );
                
                if( strcmp( cpfLogin, cliente.cpf ) == 0 ){
                    for( int tentativas = 3; tentativas > 0; tentativas-- ){
                        if( strcmp( (solicitaSenhaLogin( )), cliente.senha) == 0 ){
                            printf( "\n\n >>>>>> BEM-VINDO DE VOLTA, senhor %s! <<<<<\n\n", cliente.nomePreferencial );
                            cpfLogin[0] = '\0';
                            break;
                        }else if( tentativas == 0 ){
                            puts( "\t  ^ Desculpe! Excesso de tentativas.\nTente novamente mais tarde!\n" );
                        }else{
                            puts( "\t  ^ Senha incorreta!" );
                        }
                    }
                    break;
                }else if( id == quantidadeDeContas-1 ){
                    puts( "\t  ^ CPF inválido!");
                }
            }
        }while( cpfLogin != NULL && cpfLogin[0] != '\0');
    }
}
char *solicitaCpfLogin( ){
    char **validaCpfLogin( char* );
    char **mensagemDeErro = NULL;
    static char cpfTemp[TAMANHO_CPF] = { };
    
    do{
        printf("\n-> Insira seu CPF [xxx.xxx.xxx-xx]\n   <- ");
        fgets( cpfTemp, TAMANHO_CPF, stdin );
        limpaDado( cpfTemp );
        if( sair(cpfTemp) && (sairConfirma(  )) ){
            return NULL;
        }else{
            mensagemDeErro = validaCpf( cpfTemp );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor]);}}
    }while( mensagemDeErro[0] != NULL );

    return cpfTemp;
}
char **validaCpfLogin( char *cpf ){
    static char *mensagem[3] = {NULL};
    int erro = 0; 
 
    if( !(validaTamanho(cpf, TAMANHO_CPF)) ){
        mensagem[erro++] = "\t^ Dado incompleto"; }
    if( !(cpf[3] == '.') || !(cpf[7] == '.') || !(cpf[11] == '-') ){
        mensagem[erro++] = "\t^ Formato invalido!";}
    for( int digito = 0; cpf[digito] != '\0'; digito++ ){
        if( (isdigit( cpf[digito] )) == 0 && cpf[digito] != '.' && cpf[digito] != '-' ){
            mensagem[erro++] = "\t^ Utilize apenas numeros!";
            break;}}
    mensagem[erro] = NULL;
    return mensagem;
}
char *solicitaSenhaLogin(  ){
    static char senhaTemp[TAMANHO_SENHA] = { };

    printf( "\n-> Insira sua senha\n   <- " );
    fgets( senhaTemp, TAMANHO_SENHA, stdin );
    limpaDado( senhaTemp );
    if( sair(senhaTemp) && (sairConfirma(  )) ){
        return NULL;
    }else{
        return senhaTemp;}
}

#endif //LOGIN_H_INCLUDED