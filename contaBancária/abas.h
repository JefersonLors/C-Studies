#ifndef ABAS_H_INCLUDED
#define ABAS_H_INCLUDED
#include "cadastro.h"

void abasLogin( const int );
void menus( const int );
void abasCadastro( const int );
void abaConfirmaSaida( );
    
void abasCadastro( const int etapa ){
    enum CADASTRO { CPF = 1, SENHA = 2, NOME_COMPLETO = 3, NOME_PREFERENCIAL = 4,
                    EMAIL = 5, RENDA = 6, NASCIMENTO = 7, TELEFONE = 8 }; 
    
    switch( etapa ){
        case CPF:
            printf ( "\n|=========================================|\n"
                       "|==============| CADASTRO |===============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Digite o seu CPF                        \n"
                       "      xxx.xxx.xxx-xx                       \n"
                       "   <| " );
            break;
        
        case NOME_COMPLETO:
            printf ( "\n|=========================================|\n"
                       "|==============| CADASTRO |===============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Digite o seu nome completo              \n"
                       "   <| " );
            break;
        
        case NASCIMENTO:
            printf ( "\n|=========================================|\n"
                       "|==============| CADASTRO |===============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Digite sua data de nascimento           \n"
                       "      dd/mm/aaaa                           \n"
                       "   <| " );
            break;
        
        case NOME_PREFERENCIAL:
            printf ( "\n|=========================================|\n"
                       "|==============| CADASTRO |===============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Digite seu nome preferencial            \n"
                       "   <| " );
            break;
        
        case RENDA:
            printf ( "\n|=========================================|\n"
                       "|==============| CADASTRO |===============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Digite a sua renda                      \n"
                       "   <| R$" );
            break;
        
        case SENHA:
            printf ( "\n|=========================================|\n"
                       "|==============| CADASTRO |===============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Agora crie uma senha de até %d digitos  \n"
                       "   - Pelo menos uma letra maiúscula;       \n"
                       "   - Pelo menos uma letra minúscula;       \n"
                       "   - Pelo menos um caracter especia;       \n"
                       "   - Pelo menos um número;               \n\n"
                       "   <| ", 8);
            break;

        
        case EMAIL:
            printf ( "\n|=========================================|\n"
                       "|==============| CADASTRO |===============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Digite seu melhor e-mail                \n"
                       "   <| " );
            break;
        
        case TELEFONE:
            printf ( "\n|=========================================|\n"
                       "|==============| CADASTRO |===============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Digite seu telefone                     \n"
                       "      xx xxxxx-xxxx                        \n"
                       "   <| " );
            break;
        
        default:
            puts( "\n\tOps! Tela não encontrada!\n" );
            break;
    }

}
void abasLogin( const int etapa ){
    enum ABA { CPF = 1, SENHA = 2 };
    
    switch( etapa ){
        case CPF:
            printf ( "\n|=========================================|\n"
                       "|================| LOGIN |================|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Insira o seu CPF                        \n"
                       "      xxx.xxx.xxx-xx                       \n"
                       "   <| " );
            break;
        
        case SENHA:
            printf ( "\n|=========================================|\n"
                       "|================| LOGIN |================|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "|> Insira sua senha                        \n"
                       "   <| " );
            break;
        
        default:
            puts( "\n\tOps! Tela não encontrada!\n" );
            break;
    }
}
void menus( const int menu ){
    enum MENUS { INICIAL = 1 };
    
    switch( menu ){
        case INICIAL:
            printf ( "\n|=========================================|\n" 
                       "|==============| BLACKBANK |==============|\n"
                       "|=========================================|\n"
                       "                                           \n"
                       "              [ 1 ] ENTRAR                 \n"
                       "              [ 2 ] CADASTRAR              \n"
                       "              [ 3 ] AJUDA                  \n"
                       "              [ 0 ] SAIR                   \n"
                       "                                           \n"
                       " <| ");
            break;

        default: 
            puts( "\n\tOps! Tela não encontrada!\n" );
            break;
    }   
}
void abaConfirmaSaida( ){
    printf ( "\n|=========================================|\n" 
               "|==============| BLACKBANK |==============|\n"
               "|=========================================|\n"
               "                                           \n"
               "              CONFIRMA SAÍDA?              \n"
               "                                           \n"
               "        [1] [ SIM ]     [0] [ NÃO ]        \n"
               "                                           \n"
               " <| ");
    
}
#endif // ABAS_H_INCLUDED
