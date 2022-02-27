#ifndef ABAS_H_INCLUDED
#define ABAS_H_INCLUDED

void aba( const int, const int );

void aba( const int nivel, const int tela ){

    if( nivel == 0 )
        switch( tela ){
            case 0:
                printf ( "\n|----------------| BLACKBANK |----------------|\n"
                         "|                                             |\n"
                         "|                                             |\n"
                         "|          [ 1 ] [  ENTRAR   ]                |\n"
                         "|          [ 2 ] [ CADASTRAR ]                |\n"
                         "|          [ 0 ] [   AJUDA   ]                |\n"
                         "|                                             |\n"
                         "|                                             |\n"
                         "|                                             |\n"
                         "|---------------------------------------------|\n"
                         "-} ");
                break;
            
        }
    if( nivel == 1 )
        switch ( tela ){
            case 0:
            break;
        }

    if( nivel == 2 )
        switch ( tela ){
            case 0:

            break;
        }
}
#endif // ABAS_H_INCLUDED
