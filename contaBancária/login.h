#include "utilitarias.h"

#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

int login( void ){
    char *solicitaSenhaLogin(  );
    char *solicitaCpfLogin(  );

    char cpfLogin[TAMANHO_CPF],
         senhaLogin[TAMANHO_SENHA];
    FILE *clienteCadastrado = fopen( ARQUIVO_CADASTRO_CLIENTE, "r") ;
    FILE *dadosDosArquivos = fopen( DADOS_ARQUIVO_CADASTRO, "r" );
    
    fscanf( dadosDosArquivos, "%3d", &quantidadeDeContas );
    fclose( dadosDosArquivos );
    
    if( clienteCadastrado == NULL ){
        puts( "\n\n\tNÃO HÁ CLIENTES NA BASE AINDA!\n\n");
    }else{
        do{
            strcpy( cpfLogin, (solicitaCpfLogin( )) ); 
            
            if ( cpfLogin[0] != ' ' ){
                for( int id = 0; id <= quantidadeDeContas; id++ ){
                    fseek( clienteCadastrado, id*sizeof(Dados), SEEK_SET );
                    fread( &cliente, sizeof(Dados), 1, clienteCadastrado );
                    if( strcmp( cpfLogin, cliente.cpf ) == 0 ){
                        for( int tentativas = 3; tentativas > 0; tentativas-- ){
                            strcpy( senhaLogin, (solicitaSenhaLogin( )));
                            if( senhaLogin[0] != ' ' ){
                                if( strcmp( senhaLogin, cliente.senha) == 0 ){
                                    return id;
                                }else if( (tentativas-1) == 0 ){
                                    puts( "\t  ^ Desculpe! Excesso de tentativas.\n\t      Tente novamente mais tarde!\n" );
                                    return -1;
                                }else{
                                    puts( "\t  ^ Senha incorreta!" );}
                            }else{
                                if( sairConfirma(  ) ){
                                    return -1;}
                                else{cpfLogin[0] = '\0';}}}
                        break;
                    }else if( id == quantidadeDeContas ){
                        puts( "\t  ^ CPF inválido!");}}
            }else{
                if( sairConfirma(  ) ){
                    return -1;}
                else{cpfLogin[0] = '\0';}}
        }while( cpfLogin[0] != ' ' ); 
    }
}
char *solicitaCpfLogin( ){
    char **mensagemDeErro = NULL;
    static char cpfTemp[TAMANHO_CPF] = { };
    
    do{
        abasLogin(1);
        fgets( cpfTemp, TAMANHO_CPF, stdin );
        limpaDado( cpfTemp );
        if( sair(cpfTemp) ){
            return " ";
        }else{
            mensagemDeErro = validaCpf( cpfTemp );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor]);}}
    }while( mensagemDeErro[0] != NULL );

    return cpfTemp;
}
char *solicitaSenhaLogin(  ){
    static char senhaTemp[TAMANHO_SENHA] = { };

    abasLogin(2);
    fgets( senhaTemp, TAMANHO_SENHA, stdin );
    limpaDado( senhaTemp );
    if( sair(senhaTemp) ){
        return " ";
    }else{
        return senhaTemp;}
}

#endif //LOGIN_H_INCLUDED