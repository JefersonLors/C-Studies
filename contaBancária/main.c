#include "cadastro.h"

int main ( ){
    FILE *cadastrarCliente( Dados );
    char resposta[5] = {'\0'};
    enum MENU { ENTRAR = '1', CADASTRAR = '2', AJUDA = '0' };
    do{ 
        aba( 0, 0);
        fgets( resposta, 5, stdin );
        if( (sair(resposta)) && (sairConfirma( )) ){
            exit( EXIT_SUCCESS );}
    }while( resposta[0] != ENTRAR && resposta[0] != CADASTRAR && resposta[0] != AJUDA );

    if( resposta[0] == ENTRAR ){ 
        printf( "\n\n\t    NÃO ESTÁ PRONTO!\n");
    }else if( resposta[0] == CADASTRAR ){
        FILE *clienteCadastro = cadastrarCliente( clienteDado );
        
        if( clienteCadastro != NULL ){
            fopen( "arquivoClienteCadastro.dat", "r" );
            fread( &clienteDado, sizeof( Dados ), 1, clienteCadastro); 
            printf( "\n\n\t    CADASTRO REALIZADO!\n"
                     "\tSeja bem-vindo ao BLACKBANK, %s\n", clienteDado.nomePreferencial );
        
        }else{
            printf( "\tOps! Alguma coisa aconteceu!!\n"
                     "Nao conseguimos finalizar o seu cadastro...\n\n");
        }
    }else if( resposta[0] == AJUDA ){
        printf( "\n--------------------AJUDA--------------------\n"
                " - DIGITE \"SAIR\" PARA SAIR A QUALQUER MOMENTO.\n" );
    }
    



    return 0;
}
