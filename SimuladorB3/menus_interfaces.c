#include "include/config.h"

unsigned MENU_PRINCIPAL(  ){
    unsigned resposta;
    printf( "============================================================"
            "\t\t\tSIMULADOR B3\n"
            "============================================================\n"
            "[1] OFERTAS\n"
            "[2] COMPRAR\n"
            "[3] VENDER\n"
            "[4] CARTEIRA\n"
            "[5] PAPEIS\n"
            "[0] SAIR\n\n"
            "[ ] <- "
        );
    scanf( "%d", &resposta ); getchar( );
    while( resposta < 0 || resposta > 5 ){
        printf( "\t\t<<<<< OPÇÃO INVÁLIDA >>>>>\n\n"
              "[ ] <- " );
        scanf( "%d", &resposta ); getchar( );}
    printf("[%d] ", resposta );
    switch( resposta ){
        case 0: puts( "SAIR\n" ); break;
        case 1: puts( "OFERTAS\n" ); break;
        case 2: puts( "COMPRAR\n" ); break;
        case 3: puts( "VENDER\n" ); break;
        case 4: puts( "CARTEIRA\n" ); break;
        case 5: puts( "PAPEIS\n" ); break;}
    return resposta;
}
unsigned MENU_PAPEL( ){
    unsigned resposta;
    printf( "============================================================\n"
            "[1] ADICIONAR\n"
            "[2] RETIRAR\n"
            "[0] SAIR\n\n"
            "[ ] <- "
            );
        scanf( "%d", &resposta ); getchar( );
        while( resposta < 0 || resposta > 2 ){
            printf( "\t\t<<<<< OPÇÃO INVÁLIDA >>>>>\n\n"
                  "[ ] <- " );
            scanf( "%d", &resposta ); getchar( );}
        printf("[%d] ", resposta );
        switch( resposta ){
            case 0: puts( "SAIR\n" ); break;
            case 1: puts( "ADICIONAR\n" ); break;
            case 2: puts( "RETIRAR\n" ); break;}
    return resposta;
}
int MENU_COTACOES(  ){
    unsigned resposta;

    if( listar_papeis( ) ){
        printf( "============================================================\n"
                "[0] SAIR\n\n"
                "[ ] <- "
              );
        scanf( "%d", &resposta ); getchar( );
        while( resposta < 0 || resposta > dados.quantidade_de_papel ){
            printf( "\t\t<<<<< OPÇÃO INVÁLIDA >>>>>\n\n"
                  "[ ] <- " );
            scanf( "%d", &resposta ); getchar( );}
        printf("[%d] ", resposta );
        switch( resposta ){
            case 0: puts( "SAIR\n" ); break;
            default: puts( "ESCOLHIDA\n" ); break;}
        return resposta;
    }return -1;
}
unsigned SUB_MENU_COTACOES(  ){
    unsigned resposta;

    printf( "[0] SAIR\n"
            "[1] ATUALIZAR\n\n"
            "[ ] <- "
            );
    scanf( "%d", &resposta ); getchar( );
    while( resposta != 0 && resposta != 1 ){
        printf( "\t\t<<<<< OPÇÃO INVÁLIDA >>>>>\n\n"
              "[ ] <- " );
        scanf( "%d", &resposta ); getchar( );}
    printf("[%d] ", resposta );
    switch( resposta ){
        case 0: puts( "SAIR\n" ); break;
        case 1: puts( "ATUALIZAR\n" ); break;}
    return resposta;
}
void CARTEIRA_INTERFACE( ){
     printf( "============================================================"
             "\t\t\t  CARTEIRA\n"
             "============================================================"
             );
    if( listar_carteira( true ) < 0 ){
        puts("\n\t    <<<<< NÃO HÁ AÇÕES COMPRADAS! >>>>> \n");
    }else{
        printf( "============================================================\n"  );}
}
void PAPEL_INTERFACE( ){
    enum OPCOES{ SAIR = 0, ADICIONAR = 1, RETIRAR = 2, LISTAR = 3 };

    int resposta,
        subResposta;

    do{ printf( "============================================================"
                "\t\t\tPAPEIS ATIVOS\n"
                "============================================================\n" );
        if( !listar_papeis(  ) ){
            puts("\t   <<<<< NÃO HÁ PAPEIS PARA NEGOCIAR! >>>>> \n");}

        subResposta = MENU_PAPEL( );

        switch( subResposta ){
            case ADICIONAR:
                printf( "============================================================"
                        "\t\t     ADICIONAR PAPEL\n"
                        "============================================================\n"
                        "DIGITE [0 PARA SAIR]:\n\n");
                if( adiciona_papel( ) ){
                    puts( "\t\tBuscando cotações do papel...\n" );
                    if( gerador_de_ofertas( ) ){
                        printf( "============================================================\n"
                                "\t  <<<<< PAPEL ADICIONADO COM SUCESSO! >>>>>\n\n" );
                    }else{
                        printf( "============================================================\n"
                                "     <<<<< OPS! AS COTAÇÕES NÃO FORAM ENCONTRADAS >>>>> \n\n");
                    }
                }else{
                    printf( "============================================================\n"
                            "\t<<<<< OPS! O PAPEL NÃO FOI ADICIONADO >>>>> \n\n");
                }break;
            case RETIRAR:
                printf( "============================================================"
                        "\t\t       RETIRAR PAPEL\n"
                        "============================================================\n"
                        "DIGITE [0 PARA SAIR]:\n\n");
                if( retira_papel( ) ){
                    if( retira_oferta( ) ){
                        printf( "============================================================\n"
                                "\t  <<<<< PAPEL RETIRADO COM SUCESSO! >>>>>\n\n" );
                    }else{
                        printf( "============================================================\n"
                                "\t <<<<< OPS! O PAPEL NÃO FOI RETIRADO >>>>> \n\n");}
                }else{
                    printf( "============================================================\n"
                            "\t <<<<< OPS! O PAPEL NÃO FOI RETIRADO >>>>> \n\n"); }
            break;}
    }while( subResposta != SAIR );
}
void OFERTA_INTERFACE( ){
    enum OPCOES{ SAIR = 0 };

    int resposta,
        subResposta;

    do{ printf( "============================================================"
                "\t\t     SELECIONA A AÇÃO\n"
                "============================================================\n" );
        subResposta = MENU_COTACOES( );
        if( subResposta != SAIR ){
            if( subResposta != -1 ){
                gerador_de_cotacao( subResposta );
                visualizar_ofertas_acao( subResposta );

                if( transacao( subResposta ) ){
                    puts( "\n\t\t<<<<< TRANSAÇÃO REALIZADA >>>>>\n" );
                    gerador_de_cotacao( subResposta );
                    visualizar_ofertas_acao( subResposta );}

                while( SUB_MENU_COTACOES(  ) ){
                    printf( "\t\tCarregando novas ofertas...\n\n");
                    atualiza_ofertas( subResposta );
                    gerador_de_cotacao( subResposta );
                    visualizar_ofertas_acao( subResposta );
                    if( transacao( subResposta ) ){
                        puts( "\n\t\t<<<<< TRANSAÇÃO REALIZADA >>>>>\n" );
                        gerador_de_cotacao( subResposta );
                        visualizar_ofertas_acao( subResposta );}}
            }else{
                puts( "\t\t<<<<< OPS! NÃO HÁ OFERTAS >>>>>\n");
                break; }
        }else{ break; }
    }while( true );
}
void COMPRA_INTERFACE( ){
    int resposta;
    printf( "============================================================"
            "\t\t      OFERTA DE COMPRA\n"
            "============================================================");

    resposta = MENU_COTACOES( );

    if( resposta > 0 ){
        int respostaBackup = resposta,
            quantidadeTemp = 0;
        float valorTemp = 0.0;

        papel *inicio = NULL;

        recupera_papeis( &inicio );

        while( resposta > 1 ){ inicio = inicio->next; resposta--; }

        printf( "============================================================"
                "\t\t      OFERTA DE COMPRA\n"
                "============================================================");
        printf( "Acão: %s - %s\n", inicio->codigo, inicio->nomeDePregao );
        printf( "\nPreço: R$" );

        scanf( "%f", &valorTemp );
        if( valorTemp != 0 ){
            while( valorTemp < 0 ){
                puts( "\t\t<<<<< VALOR INVÁLIDO >>>>>" );
                printf( "\nPreço: R$" );
                scanf( "%f", &valorTemp );
            }
            printf( "Quantidade: " );
            scanf("%d", &quantidadeTemp );
            while( quantidadeTemp < 0 ){
                puts( "\t\t<<<<< VALOR INVÁLIDO >>>>>" );
                printf( "\nQuantidade: " );
                scanf( "%d", &quantidadeTemp );
            }
            acao *nova = (acao*)malloc( sizeof(acao) );

            strcpy( nova->identificacao.codigo, inicio->codigo );
            strcpy( nova->identificacao.nomeDePregao, inicio->nomeDePregao );

            nova->quantidadeOfertado = 1;
            (nova->valor) = (oferta*)malloc( sizeof(oferta) );
            (nova->valor)->quantidade = quantidadeTemp;
            (nova->valor)->valor = valorTemp;
            nova->next = NULL;
            nova->prev = NULL;
            nova->valor->user = true;
            (nova->valor)->next = NULL;
            (nova->valor)->prev = NULL;

            limpa_lista_de_papeis( &inicio );
            if( incluir_oferta_de_compra( nova ) ){
                printf( "\n============================================================"
                        "\n\t   <<<<< OFERTA INCLUIDA COM SUCESSO! >>>>> \n\n" );
            }else{
                printf( "\n============================================================"
                        "\n\t<<<<< NÃO FOI POSSÍVEL INSERIR A OFERTA  \n" );
            }
        }
    }else if ( resposta == -1 ){
        puts("\n\t  <<<<< NÃO HÁ PAPEIS PARA NEGOCIAR! >>>>> \n");}
}
void VENDA_INTERFACE( ){
    char codigoTemp[TAM_CODIGO];
    int resposta = 0;
    printf( "============================================================"
            "\t\t      OFERTA DE VENDA\n"
            "============================================================" );

    resposta = listar_carteira( false );
    if( resposta > -1 ){
        int quantidadeTemp = 0;
        float valorTemp = 0.0;

        carteira *inicio = NULL;

        recupera_carteira( &inicio );

        while( resposta > 1 ){
            inicio = inicio->next;
            resposta--;}

        printf( "============================================================"
                "\t\t      OFERTA DE VENDA\n"
                "============================================================");

        printf( "Acão: %s - %s\n", inicio->identificacao.codigo,
                inicio->identificacao.nomeDePregao );
        printf( "\nPreço: R$" );

        scanf( "%f", &valorTemp );
        if( valorTemp != 0 ){
            while( valorTemp < 0 ){
                puts( "\t\t<<<<< VALOR INVÁLIDO >>>>>\n\n" );
                printf( "\nPreço: R$" );
                scanf( "%f", &valorTemp );
            }
            printf( "Quantidade: " );
            scanf("%d", &quantidadeTemp );
            while( quantidadeTemp < 0 || quantidadeTemp > inicio->quantidade ){
                puts( "\t\t<<<<< VALOR INVÁLIDO >>>>>\n\n" );
                printf( "\nQuantidade: " );
                scanf( "%d", &quantidadeTemp );
            }
            acao *nova = (acao*)malloc( sizeof(acao) );

            strcpy( nova->identificacao.codigo, inicio->identificacao.codigo );
            strcpy( nova->identificacao.nomeDePregao, inicio->identificacao.nomeDePregao );

            nova->quantidadeOfertado = 1;
            (nova->valor) = (oferta*)malloc( sizeof(oferta) );
            (nova->valor)->quantidade = quantidadeTemp;
            (nova->valor)->valor = valorTemp;
            nova->next = NULL;
            nova->prev = NULL;
            nova->valor->user = true;
            (nova->valor)->next = NULL;
            (nova->valor)->prev = NULL;

            if( incluir_oferta_de_venda( nova ) ){
                printf( "\n============================================================"
                        "\n\t   <<<<< OFERTA INCLUIDA COM SUCESSO! >>>>> \n\n" );
            }else{
                printf( "\n============================================================"
                        "\n\t<<<<< NÃO FOI POSSÍVEL INSERIR A OFERTA  \n" );}
            limpa_lista_de_acoes_na_carteira( inicio );
        }
    }else{
        puts("\n\t   <<<<< NÃO HÁ AÇÕES NA CARTEIRA! >>>>>\n" );}
}

