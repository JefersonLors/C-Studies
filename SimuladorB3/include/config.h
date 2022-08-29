#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

#define TAM_NOME_PREGAO 20
#define TAM_CODIGO 8
#define TAM_COT 8

#define teste puts("teste");
#define aqui puts( "aqui" );

#define delay getchar( );

struct{
    unsigned quantidade_de_papel,
             quantidade_de_acoes,
             quantidade_de_transacoes,
             acoes_diferentes_na_carteira;
}dados;

bool cria_arquivos( );
bool salva_dados( );

typedef struct papel{
    char nomeDePregao[TAM_NOME_PREGAO],
         codigo[TAM_CODIGO];
    float cotacao;
    struct papel *next;
}papel;

bool adiciona_papel( void );
bool salva_papeis( papel* );
bool recupera_papeis( papel** );

bool listar_papeis( void );
bool retira_papel( void );
void limpa_lista_de_papeis( papel** );


typedef struct oferta{
    int quantidade;
    float valor;
    bool user;
    struct oferta *prev;
    struct oferta *next;
}oferta;

typedef struct acoes{
    papel identificacao;
    oferta *valor;
    unsigned quantidadeOfertado;
    struct acoes *prev;
    struct acoes *next;
}acao;

bool gerador_de_ofertas( void );
bool gerador_de_lista_de_oferta( oferta**, acao* );
bool gerador_de_quantidade_de_acoes( oferta* );
bool gerador_de_valor_de_venda( oferta* );
bool gerador_de_valor_de_compra( oferta* );
bool gerador_de_cotacao( unsigned );
unsigned gerador_de_quantidade_de_oferta( void );
void ordena_ofertas_de_venda( oferta*, unsigned );
void ordena_ofertas_de_compra( oferta*, unsigned );
bool preenche_ofertas( acao**, bool );
bool obtem_nome_e_codigo( acao* );
bool recupera_ofertas( acao**, acao** );
bool recupera_lista_de_oferta( oferta**, unsigned, FILE* );
bool atualiza_ofertas( unsigned );
bool retira_oferta( void );
bool exclui_lista_de_oferta( oferta** );
void limpa_lista_de_acoes( acao** );
bool salva_ofertas( acao**, acao** );
bool visualizar_ofertas_acao( unsigned );

bool transacao( unsigned );
bool valida_transacao( oferta*, oferta* );
void ajusta_lista_de_ofertas( oferta**, oferta**, acao*, acao* );
bool realiza_transacao( oferta*, oferta*, papel*, bool );
void registra_transacao_usuario( float, float, int, char*, char*, bool );

bool incluir_oferta_de_compra( acao* );

typedef struct movimentacao{
    papel identificacao;
    unsigned quantidade;
    float valor;
    char dataHoraCompra[30];
    bool operacao;
    struct movimentacao *next;
    struct movimentacao *prev;
}movimentacao;

typedef struct carteira{
    papel identificacao;
    unsigned quantidade;
    struct carteira *next;
    struct carteira *prev;
}carteira;

int listar_carteira( bool );
void limpa_lista_de_movimentacoes( movimentacao* );
void limpa_lista_de_acoes_na_carteira( carteira* );
bool cria_carteira( carteira** );
bool salva_carteira( carteira* );
bool recupera_carteira( carteira** );
void historico_de_transacao( char*, char* );
bool recupera_historico_de_transacao( movimentacao** );
void ajusta_carteira( carteira** );
int MENU_CARTEIRA( void );

unsigned MENU_PRINCIPAL( void );
unsigned MENU_PAPEL( void );
int MENU_COTACOES( void );
unsigned SUB_MENU_COTACOES( void );
void VENDA_INTERFACE( void );
void OFERTA_INTERFACE( void );
void PAPEL_INTERFACE( void );
void CARTEIRA_INTERFACE( void );
void VENDA_INTERFACE( void );
void COMPRA_INTERFACE( void );

#endif // CONFIG_H_INCLUDED
