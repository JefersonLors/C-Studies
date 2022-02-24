#ifndef DATA_FILE_H_INCLUDED
#define DATA_FILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define bool _Bool
#define true 1
#define false 0

#define TAMANHO_NOME_COMP 61
#define TAMANHO_NOME_PREF 31
#define TAMANHO_EMAIL 82
#define TAMANHO_TELEFONE 16
#define TAMANHO_CPF 20
#define TAMANHO_SENHA 10
#define TAMANHO_RENDA 10
#define TAMANHO_DATA_NASCIMENTO 15

#define CLEAN system ("cls");
#define DLAY getchar ( );

struct dados{
    char nomeCompleto[ TAMANHO_NOME_COMP ],
         nomePreferencial[ TAMANHO_NOME_PREF ],
         email[ TAMANHO_EMAIL ],
         telefone[ TAMANHO_TELEFONE ],
         cpf[ TAMANHO_CPF ],
         senha[ TAMANHO_SENHA ],
         renda[ TAMANHO_RENDA ],
         nascimento[ TAMANHO_DATA_NASCIMENTO ];
};
typedef struct dados Dados;

FILE *cadastrarCliente( Dados cliente ){
    bool solicitaEmail( Dados* );
    bool solicitaNomePreferencial( Dados* );
    bool solicitaNomeCompleto( Dados* );
    bool solicitaTelefone( Dados* );
    bool solicitaRenda( Dados* );
    bool solicitaSenha( Dados* );
    bool solicitaCpf( Dados* );
    bool solicitaData_De_Nascimento( Dados* );
    
    static FILE *arquivoClienteCadastro;
    static int id = 0;
    
    if( (arquivoClienteCadastro = fopen( "arquivoClienteCadastro.dat", "a" )) == NULL ){
        return NULL;
    }else{
        if( solicitaCpf( &cliente ) ){
            if( solicitaData_De_Nascimento( &cliente ) ){
                if( solicitaNomeCompleto( &cliente ) ){
                    if( solicitaEmail( &cliente ) ){
                        if( solicitaTelefone( &cliente ) ){
                            if( solicitaRenda( &cliente ) ){
                                if( solicitaNomePreferencial( &cliente ) ){
                                    if( solicitaSenha( &cliente ) ){
                                        fseek( arquivoClienteCadastro, id*sizeof( Dados ), SEEK_SET ); 
                                        fwrite( &cliente, sizeof( Dados ), 1, arquivoClienteCadastro );
                                        fclose( arquivoClienteCadastro );
                                        id++;
                                        return arquivoClienteCadastro;
                                    }else return NULL;
                                }else return NULL;
                            }else return NULL;
                        }else return NULL;
                    }else return NULL;
                }else return NULL;
            }else return NULL;
        }else return NULL;
    }
}

bool solicitaCpf( Dados *cliente ){
    char *validaCpf( char* );
    char *mensagemDeErro = NULL;

    do{
        printf("\n-> Insira seu CPF [xxx.xxx.xxx-xx]\n   <- ");
        fgets( cliente->cpf, TAMANHO_CPF, stdin );
        mensagemDeErro = validaCpf( cliente->cpf );
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL );

    return true;
}
char *validaCpf( char *cpf ){
    static char *erro = NULL;

    if( !(cpf[3] == '.') || !(cpf[7] == '.') || !(cpf[11] == '-') ){
        erro = "\t^ Formato invalido!";
    }else{
        for( int digito = 0; cpf[digito] != '\0'; digito++ ){
            if( isdigit( cpf[digito] ) != 0 && cpf[digito] != '\n' ){
                erro = "\t^ Utilize apenas numeros!";
                break;}}
        erro = NULL;}
    return erro;
}
bool solicitaData_De_Nascimento( Dados *cliente ){
    char *validaData_De_Nascimento( char* );
    char *mensagemDeErro = NULL;

    do{
        printf("\n-> Insira sua data de nascimento [dd/mm/aaaa]\n   <- ");
        fgets( cliente->nascimento, TAMANHO_DATA_NASCIMENTO, stdin );
        mensagemDeErro = validaData_De_Nascimento( cliente->nascimento );
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL );

    return true;
}
char *validaData_De_Nascimento( char *data ){
    static char *erro = NULL;

    if( !(data[2] == '/') || !(data[5] == '/') ){
        erro = "\t^ Formato invalido!"; 
    }else{
        if( (data[0] > '3') || (data[0] == '3' && data[1] > '1') || 
            ((data[0] == '0') && (data[1] == '0')) ) {
            erro = "\t^ Dia inválido!";
        }else if( (data[3] > '1') || (data[3] == '1' && data[4] > '2') || 
                  ((data[3] == '0') && (data[4] == '0')) ){
            erro = "\t^ Mês inválido!";
        }else if( (data[6] > '2') || (data[8] == '2' && data[9] > '2') || 
                  ((data[6] == '2') && (data[7] > '0')) || ((data[7] == '0') && (data[8] > '2')) ){
             erro = "\t^ Ano inválido!";
        }else if( (data[6] < '1') || (data[6] == '1' && data[7] < '9') ){
             erro = "\t^ Ano inválido!";
        }else{
            for( int digito = 0; data[digito] != '\0'; digito++ ){
                if( isdigit( data[digito] ) != 0 && data[digito] != '\n' ){
                    erro = "\t^ Utilize apenas numeros!";
                    break;}}
            erro = NULL;}}
    return erro;
}
bool solicitaNomeCompleto( Dados *cliente ){
    char *validaNomes( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira seu nome completo (MÁX %d carac.)\n   <- ", (TAMANHO_NOME_COMP - 2 ));
        fgets( cliente->nomeCompleto, TAMANHO_NOME_COMP, stdin );
        mensagemDeErro = validaNomes( cliente->nomeCompleto );
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL);
    return true;
}
bool solicitaNomePreferencial( Dados *cliente ){
    char *validaNomes( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira seu nome preferencial (MÁX %d carac.)\n   <- ", (TAMANHO_NOME_PREF - 2) );
        fgets( cliente->nomePreferencial, TAMANHO_NOME_PREF, stdin );
        mensagemDeErro =  validaNomes( cliente->nomePreferencial );
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL);
    return true;
}
char *validaNomes( char *nome ){
    static char *erro = NULL;

    for( int letra = 0; nome[letra] != '\0'; letra++ ){
        if( ( isalpha( nome[letra] ) == 0) && (nome[letra] != '\n') && (nome[letra] != ' ') ){
            erro = "\t^ Utilize apenas letras!";
            break;}
        erro = NULL;}
}
bool solicitaEmail( Dados *cliente ){
    char *validaEmail( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira seu melhor e-mail [fulano@gmail.com - MÁX %d carac.]\n   <- ", (TAMANHO_EMAIL - 2) );
        fgets( cliente->email, TAMANHO_EMAIL, stdin );
        mensagemDeErro = validaEmail( cliente->email );
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL);
    return true;
}
char *validaEmail( char *email  ){
    void padronizaEmail( char* );

    int tamanhoMin = 5;
    static char *erro = NULL;
    const int quantidadeDominios = 5;
    char *dominios[] = { "@gmail.com\n", "@outlook.com\n", "@hotmail.com\n", "@live.com\n", "@yahoo.com\n" };
    
    padronizaEmail( email );
    for( int caracter = 0; email[caracter] != '\0'; caracter++ ){
        if( email[caracter] == '@' ){
            if( caracter < tamanhoMin ){
                erro = "\t^ É necessário pelo menos 5 caracteres de endereço.";
                break;}
            for( int dominio = 0; dominio < quantidadeDominios; dominio++ ){
                if( (strcmp( &email[caracter], dominios[dominio] )) == 0 ){
                    erro = NULL;
                    break;}
                erro = "\t^ Dominio inválido!";}
            break;
        }else if( isalnum( email[caracter] ) == 0 &&  email[caracter] != '.' && email[caracter] != '_' ){
            erro = "\t^ Email inválido! Utilize caracteres de A - Z, de 0 - 9, ( _ ), ( . ), sem espaço, sem acentuação e sem caracteres especiais além dos já citados!";
            break;
        }else if( email[caracter+1] == '\0' ){
            erro = "\t^ Email inválido!";}
    }
    return erro;
}
void padronizaEmail( char *emailForaDoPadrao ){
    for( int caracter = 0; emailForaDoPadrao[caracter] != '\0'; caracter++ ){
        emailForaDoPadrao[caracter] = tolower( emailForaDoPadrao[caracter] );}
}
bool solicitaSenha( Dados *cliente ){
    char *validaSenha( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf( "\n-> Crie uma senha segura de até %d caracteres [jw3h_7Da]\n"
                "   - Pelo menos uma letra maiúscula;\n"
                "   - Pelo menos uma letra minúscula;\n"
                "   - Pelo menos um caracter especia;\n"
                "   - Pelo menos um número;\n\n   -", (TAMANHO_SENHA -2) );
        fgets( cliente->senha, TAMANHO_SENHA, stdin );
        mensagemDeErro = validaSenha( cliente->senha);
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL);
    return true;
}
char *validaSenha( char *senha ){
    static char *erro = NULL;

    for( int digito = 0; senha[digito] != '\0'; digito++ ){
        if( (islower(senha[digito]) > 0 ) ){
            for( int digito = 0; senha[digito] != '\0'; digito++ ){
                if( (isupper(senha[digito]) > 0) ){
                    for( int digito = 0; senha[digito] != '\0'; digito++ ){
                        if( (isdigit(senha[digito]) > 0) ){
                            for( int digito = 0; senha[digito] != '\0'; digito++ ){
                                if( (isalnum(senha[digito] )) == 0 ){
                                    erro = NULL;
                                }else if( senha[digito+1] == '\0'){
                                    erro = "\t^ Falta pelo menos um caracter especial!";}}
                            break;
                        }else if( senha[digito+1] == '\0'){
                            erro = "\t^ Falta pelo menos um número!";}}
                    break;
                }else if( senha[digito+1] == '\0'){
                    erro = "\t^ Falta pelo menos uma letra MAIÚSCULA!";}}
            break;
        }else if( senha[digito+1] == '\0'){
            erro = "\t^ Falta pelo menos uma letra minúscula!";}
    }
    return erro;
}
bool solicitaTelefone( Dados *cliente ){
    char *validaTelefone( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira seu telefone [xx xxxxx-xxxx]\n   <- ");
        fgets( cliente->telefone, TAMANHO_TELEFONE, stdin );
        mensagemDeErro = validaTelefone( cliente->telefone );
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL);
    return true;
}
char *validaTelefone( char *telefone  ){
    static char *erro = NULL;

    if( !(telefone[2] == ' ') || !(telefone[8] == '-') ){
        erro = "\t^ Formato inválido.";
    }else if( !(telefone[3] == '9') ){
        erro = "\t^ Inclua o 9";
    }else{
        erro = NULL;}
    return erro;
}
bool solicitaRenda( Dados *cliente ){
    char *validaRenda( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira sua renda mensal [R$ 1234 - MÁX %d carac.]\n   <- R$ ", (TAMANHO_RENDA -2) );
        fgets( cliente->renda, TAMANHO_RENDA, stdin );
        mensagemDeErro = validaRenda( cliente->renda );
        if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}
    }while( mensagemDeErro != NULL);
    return true;
}
char *validaRenda( char *renda ){
    static char *erro = NULL;

    for( int digito = 0; renda[digito] != '\0'; digito++ ){
        if( (isdigit(renda[digito])) == 0 && renda[digito] != '\n'){
            erro = "\t^ Utilize apenas números!";
            break;
        }else if( renda[digito+1] == '\0' ){ 
            erro = NULL;}}
    return erro;
}
    
#endif // DATA_FILE_H_INCLUDED


                    