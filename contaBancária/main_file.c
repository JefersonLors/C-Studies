#include <stdio.h>
#include <stdlib.h>
#include "Display_file.h"
#include "Data_file.h"

int main ( ){
    FILE * cadastrarCliente( Dados );
    
    Dados cliente;
    FILE *clienteCadastro = cadastrarCliente( cliente );

    if( clienteCadastro != NULL  ){
        fopen( "arquivoClienteCadastro.dat", "r" );
        fread( &cliente, sizeof( Dados ), 1, clienteCadastro); 
        printf( "\n\t    CADASTRO REALIZADO!\n"
                 "\tSeja bem-vindo ao BLACKBANK, %s\n", cliente.nomePreferencial );
        
    }
    else{
        printf( "\tOps! Alguma coisa aconteceu!!\n"
                 "Nao conseguimos finalizar o seu cadastro...\n\n");
    }

    return 0;
}
