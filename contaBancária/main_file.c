#include <stdio.h>
#include <stdlib.h>
#include "Display_file.h"
#include "Data_file.h"

main ( ){
    Dados Lucas;

    if( cadastrarCliente( &Lucas ) ){
        printf( "\t    CADASTRO REALIZADO!\n"
                 "\tSeja bem-vindo ao BLACKBANK, %s\n", Lucas.nomePreferencial );
    }
    else{
        printf( "\tOps! Alguma coisa aconteceu!!\n"
                 "Nao conseguimos finalizar o seu cadastro...\n\n");
    }


}
