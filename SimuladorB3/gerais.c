#include "includes/config.h"

void formata_texto( char* );
void tira_espacos_vazios( char * );
void DELAY( );

void formata_texto( char *texto ){
    for( int caracter = 0; texto[caracter] != '\0'; caracter++ ){
        texto[caracter] = toupper( texto[caracter] );
        if( texto[caracter+1] == '\0' )
            texto[caracter] = '\0';
        if( texto[caracter] == ' ' )
            texto[caracter] = '_';
        if( ( isalnum( texto[caracter] ) ) == 0 && texto[caracter] != '\0' )
            texto[caracter] = '_';
    }
}
void tira_espacos_vazios( char *data ){
    for( int caracter = 0; data[caracter] != '\0'; caracter++ ){
        if( data[caracter] == ' ' )
            data[caracter] = '_';
    }
}
void DELAY(  ){
   Sleep(1000);
}
