#ifndef DISPLAY_FILE_H_INCLUDED
#define DISPLAY_FILE_H_INCLUDED

void DISPLAY( int, int );

void DISPLAY( int nivel, int tela ){

    if ( nivel == 0 )
        switch ( tela ){
            case 0:
                printf ( "|----------------| BLACKBANK |----------------|"
                         "|                                             |"
                         "|                                             |"
                         "|          [ 1 ] [  ENTRAR   ]                |"
                         "|          [ 2 ] [ CADASTRAR ]                |"
                         "|          [ 0 ] [   SAIR    ]                |"
                         "|                                             |"
                         "|                                             |"
                         "|                                             |"
                         "|---------------------------------------------|"
                         "-} ");
                break;
        }
    if ( nivel == 1 )
        switch ( tela ){
            case 0:
            break;
        }

    if ( nivel == 2 )
        switch ( tela ){
            case 0:

            break;
        }
}
#endif // DISPLAY_FILE_H_INCLUDED
