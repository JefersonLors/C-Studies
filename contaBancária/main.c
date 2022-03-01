#include "cadastro.h"
#include "login.h"

int main( ){
    void cadastrarCliente( Dados );
    int login( void );
    
    char resposta = {'\0'};
    enum MENU { ENTRAR = '1', CADASTRAR = '2', AJUDA = '3', SAIR = '0' };

    do{
        do{ 
            aba( 0, 0);
            resposta = getchar( ); getchar( );
        }while( resposta != ENTRAR && resposta != CADASTRAR && resposta != AJUDA && resposta != SAIR );
        
        if( resposta == ENTRAR ){ 
            login();
        }else if( resposta == CADASTRAR ){
            cadastrarCliente( cliente );
            FILE *dadosClienteCadastrado = fopen( ARQUIVO_CADASTRO_CLIENTE, "r" );
            FILE *dadosGerais = fopen( DADOS_ARQUIVO_CADASTRO, "r" );
            
            if( dadosClienteCadastrado == NULL ){
                puts( "\n\nOps! Cliente não encontrado!\n\n" );
            }else{ 
                fscanf( dadosGerais, "%d", &quantidadeDeContas );
                fseek( dadosClienteCadastrado, (quantidadeDeContas-1)*(sizeof(Dados)), SEEK_SET );
                fread( &cliente, sizeof( Dados ), 1, dadosClienteCadastrado ); 
                printf( "\n\n\t    CADASTRO REALIZADO!\n"
                         "\tSeja bem-vindo ao BLACKBANK, %s\n", cliente.nomePreferencial ); }
    
        }else if( resposta == AJUDA ){
            printf( "\n--------------------AJUDA--------------------\n"
                    " - DIGITE \"SAIR\" PARA SAIR A QUALQUER MOMENTO.\n\n" ); 
        }else
            if( !sairConfirma( ) )
                resposta = -1;
    }while( resposta != SAIR );
    puts( "\n\t\t\tSEE YOU SOON!\n" );

    return 0;
}
