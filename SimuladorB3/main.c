#include "include/config.h"

int main( ){
    setlocale( LC_ALL, "Portuguese" );

    enum OPCOES{ SAIR = 0, OFERTAS = 1, COMPRAR = 2, VENDER = 3, CARTEIRA = 4, PAPEIS = 5 };

    int resposta;

    if( cria_arquivos( ) ){
        do{ resposta = MENU_PRINCIPAL( );
            switch( resposta ){
                case OFERTAS:
                    OFERTA_INTERFACE( );
                    break;

                case COMPRAR:
                    COMPRA_INTERFACE( );
                    break;

                case VENDER:
                    VENDA_INTERFACE( );
                break;

                case CARTEIRA:
                     CARTEIRA_INTERFACE( );
                    break;
                case PAPEIS:
                    PAPEL_INTERFACE( );
            }
        }while( resposta != SAIR );
    }else{
        puts( "\t<<<<< NÃO FOI POSSÍVEL INICIALIZAR :( >>>>>\n\n" ); }

    printf( "============================================================\n"
            "\t       <<<<< PREGÃO ENCERRADO >>>>>\n\n" );
    return 0;
}
