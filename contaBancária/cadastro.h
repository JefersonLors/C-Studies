#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED

#include "utilitarias.h"

#define TAMANHO_NOME_COMP 61
#define TAMANHO_NOME_PREF 31
#define TAMANHO_EMAIL 81
#define TAMANHO_TELEFONE 15
/// 7 1 ' ' 9 8 7 8 0 - 1 5 3 5 '\0' 
/// 0 1  2  3 4 5 6 7 8 9 0 1 2   3    
#define TAMANHO_CPF 16         
/// 0 0 0 . 0 0 0 . 0 0 0 - 0 0 '\0'  
/// 0 1 2 3 4 5 6 7 8 9 0 1 2 3   4    
#define TAMANHO_SENHA 10
#define TAMANHO_RENDA 10
/// 0 0 / 0 0 / 0 0 0 0 '\0' 
/// 0 1 2 3 4 5 6 7 8 9   0   
#define TAMANHO_DATA_NASCIMENTO 12

struct dados{
    char nomeCompleto[ TAMANHO_NOME_COMP ],
         nomePreferencial[ TAMANHO_NOME_PREF ],
         email[ TAMANHO_EMAIL ],
         telefone[ TAMANHO_TELEFONE ],
         cpf[ TAMANHO_CPF ],
         senha[ TAMANHO_SENHA ],
         renda[ TAMANHO_RENDA ],
         nascimento[ TAMANHO_DATA_NASCIMENTO ];
}clienteDado;
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
                                        fwrite( &cliente, sizeof( Dados ), id++, arquivoClienteCadastro );
                                        fclose( arquivoClienteCadastro );
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
    char **validaCpf( char* );
    char **mensagemDeErro = NULL;

    do{
        printf("\n-> Insira seu CPF [xxx.xxx.xxx-xx]\n   <- ");
        fgets( cliente->cpf, TAMANHO_CPF, stdin );
        limpaDado( cliente->cpf );
        if( sair(cliente->cpf) && (sairConfirma(  )) ){
            return false;
        }else{
            mensagemDeErro = validaCpf( cliente->cpf );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor]);}}
    }while( mensagemDeErro[0] != NULL );

    return true;
}
char **validaCpf( char *cpf ){
    static char *mensagem[3] = {NULL};
    int erro = 0; 
 
    ///incluir funcao de busca no banco de dados se o email já encontra-se cadastrado
    if( !(validaTamanho(cpf, TAMANHO_CPF)) ){
        mensagem[erro++] = "\t^ Dado incompleto"; }
    if( !(cpf[3] == '.') || !(cpf[7] == '.') || !(cpf[11] == '-') ){
        mensagem[erro++] = "\t^ Formato invalido!";}
    for( int digito = 0; cpf[digito] != '\0'; digito++ ){
        if( (isdigit( cpf[digito] )) == 0 && cpf[digito] != '.' && cpf[digito] != '-' ){
            mensagem[erro++] = "\t^ Utilize apenas numeros!";
            break;}}
    mensagem[erro] = NULL;
    return mensagem;
}
bool solicitaData_De_Nascimento( Dados *cliente ){
    char **validaData_De_Nascimento( char* );
    char **mensagemDeErro = NULL;

    do{
        printf("\n-> Insira sua data de nascimento [dd/mm/aaaa]\n   <- ");
        fgets( cliente->nascimento, TAMANHO_DATA_NASCIMENTO, stdin );
        limpaDado( cliente->nascimento );
        if( sair(cliente->nascimento) && (sairConfirma(  )) ){ 
            return false;
        }else{ 
            mensagemDeErro = validaData_De_Nascimento( cliente->nascimento );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor] );}}
    }while( mensagemDeErro[0] != NULL );

    return true;
}
char **validaData_De_Nascimento( char *data ){
    static char *mensagem[7] = {NULL};
    int erro = 0;

    if( !(validaTamanho(data, TAMANHO_DATA_NASCIMENTO)) ){
        mensagem[erro++] = "\t^ Dado incompleto";}
    if( !(data[2] == '/') || !(data[5] == '/') ){
        mensagem[erro++] = "\t^ Formato invalido!";}
    for( int digito = 0; data[digito] != '\0'; digito++ ){
        if( (isdigit( data[digito] )) == 0 && data[digito] != '/' ){
            mensagem[erro++] = "\t^ Utilize apenas numeros!";
            break;}}
    if( mensagem[0] == NULL ){
        if( (data[0] > '3') || (data[0] == '3' && data[1] > '1') || ((data[0] == '0') && (data[1] == '0')) ) {
            mensagem[erro++] = "\t^ Dia inválido!";}
        if( (data[3] > '1') || (data[3] == '1' && data[4] > '2') || ((data[3] == '0') && (data[4] == '0')) ){
            mensagem[erro++] = "\t^ Mês inválido!";}
        if( (data[6] > '2') || (data[8] == '2' && data[9] > '2') || ((data[6] == '2') && (data[7] > '0')) || ((data[7] == '0') && (data[8] > '2')) ){
            mensagem[erro++] = "\t^ Ano inválido!";}
        if( (data[6] < '1') || (data[6] == '1' && data[7] < '9') ){
            mensagem[erro++] = "\t^ Ano inválido!";}}
    if( mensagem[0] == NULL && (data[6] == '2') && (data[0] == '0') && (data[9] > '4') ){
        mensagem[erro++] = "\t^ Ops!! Você não tem idade para fazer o cadastro!";}
    mensagem[erro] = NULL;
    return mensagem;
}
bool solicitaNomeCompleto( Dados *cliente ){
    char *validaNomes( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira seu nome completo (MÁX %d carac.)\n   <- ", (TAMANHO_NOME_COMP - 1));
        fgets( cliente->nomeCompleto, TAMANHO_NOME_COMP, stdin );
        limpaDado( cliente->nomeCompleto );
        if( sair( cliente->nomeCompleto ) && (sairConfirma(  )) ){
            return false;
        }else{
            mensagemDeErro = validaNomes( cliente->nomeCompleto );
            if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}}
    }while( mensagemDeErro != NULL);
    return true;
}
bool solicitaNomePreferencial( Dados *cliente ){
    char *validaNomes( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira seu nome preferencial (MÁX %d carac.)\n   <- ", (TAMANHO_NOME_PREF - 1) );
        fgets( cliente->nomePreferencial, TAMANHO_NOME_PREF, stdin );
        limpaDado( cliente->nomePreferencial );
        if( sair(cliente->nomePreferencial) && (sairConfirma(  )) ){
            return false;
        }else{
            mensagemDeErro = validaNomes( cliente->nomePreferencial );
            if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}}
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
    char **validaEmail( char* );
    char **mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira seu melhor e-mail [fulano@gmail.com - MÁX %d carac.]\n   <- ", (TAMANHO_EMAIL - 1) );
        fgets( cliente->email, TAMANHO_EMAIL, stdin );
        limpaDado( cliente->email );
        if( sair( cliente->email) && (sairConfirma(  )) ){
            return false;
        }else{ 
            mensagemDeErro = validaEmail( cliente->email );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
            puts(mensagemDeErro[corredor] );}}
    }while( mensagemDeErro[0] != NULL);
    return true;
}
char **validaEmail( char *email  ){
    ///incluir funcao de busca no banco de dados se o email já encontra-se cadastrado
    int tamanhoMin = 5;
    static char *mensagem[4] = {NULL};
    int erro = 0;
    const int quantidadeDominios = 5;
    char *dominios[] = { "@gmail.com", "@outlook.com", "@hotmail.com", "@live.com", "@yahoo.com" };
    
    strcpy( email, (padronizaDado(email)));
    for( int caracter = 0; email[caracter] != '\0'; caracter++ ){
        if( (isalnum( email[caracter] )) == 0 && email[caracter] != '.' && email[caracter] != '_' && email[caracter] != '@' ){
            mensagem[erro++] = "\t^ Email inválido! Utilize caracteres de A - Z, \nde 0 - 9, ( _ ), ( . ), sem espaço, sem acentuação \ne sem caracteres especiais além dos já citados!";
            break;}}

    for( int caracter = 0; email[caracter] != '\0'; caracter++ ){
        if( email[caracter] == '@' ){
            if( caracter < tamanhoMin ){
                mensagem[erro++] = "\t^ É necessário pelo menos 5 caracteres de endereço!";}
            for( int dominio = 0; dominio < quantidadeDominios; dominio++ ){
                if( (strcmp( &email[caracter], dominios[dominio] )) == 0 ){
                    mensagem[erro++] = NULL; break;
                }else if( (dominio+1) == quantidadeDominios ){
                    mensagem[erro++] = "\t^ Dominio inválido!";}}
            break;
        }else if( email[caracter+1] == '\0' ){
            mensagem[erro++] = "\t^ Email inválido!";}}
    mensagem[erro] = NULL;
    return mensagem;
}
bool solicitaSenha( Dados *cliente ){
    char **validaSenha( char* );
    char **mensagemDeErro = NULL;
    
    do{
        printf( "\n-> Crie uma senha segura de até %d caracteres [jw3h_7Da]\n"
                "   - Pelo menos uma letra maiúscula;\n"
                "   - Pelo menos uma letra minúscula;\n"
                "   - Pelo menos um caracter especia;\n"
                "   - Pelo menos um número;\n\n   -", (TAMANHO_SENHA -2) );
        fgets( cliente->senha, TAMANHO_SENHA, stdin );
        limpaDado( cliente->senha );
        if( sair(cliente->senha) && (sairConfirma(  )) ){
            return false;
        }else{
            mensagemDeErro = validaSenha( cliente->senha);
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor] );}}
    }while( mensagemDeErro[0] != NULL );
    return true;
}
char **validaSenha( char *senha ){
    static char *mensagem[4] = {NULL};
    int erro = 0; 

    for( int digito = 0; senha[digito] != '\0'; digito++ ){
        if( (islower(senha[digito]) > 0 ) ){
            for( int digito = 0; senha[digito] != '\0'; digito++ ){
                if( (isupper(senha[digito]) > 0) ){
                    for( int digito = 0; senha[digito] != '\0'; digito++ ){
                        if( (isdigit(senha[digito]) > 0) ){
                            for( int digito = 0; senha[digito] != '\0'; digito++ ){
                                if( (isalnum(senha[digito] )) == 0 ){
                                    mensagem[erro++] = NULL;
                                }else if( senha[digito+1] == '\0'){
                                    mensagem[erro++] = "\t^ Falta pelo menos um caracter especial!";}}
                            break;
                        }else if( senha[digito+1] == '\0'){
                            mensagem[erro++] = "\t^ Falta pelo menos um número!";}}
                    break;
                }else if( senha[digito+1] == '\0'){
                    mensagem[erro++] = "\t^ Falta pelo menos uma letra MAIÚSCULA!";}}
            break;
        }else if( senha[digito+1] == '\0'){
            mensagem[erro++] = "\t^ Falta pelo menos uma letra minúscula!";}
    }
    mensagem[erro] = NULL;
    return mensagem;
}
bool solicitaTelefone( Dados *cliente ){
    char **validaTelefone( char* );
    char **mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira seu telefone [xx xxxxx-xxxx]\n   <- ");
        fgets( cliente->telefone, TAMANHO_TELEFONE, stdin );
        limpaDado( cliente->telefone );
        if( sair(cliente->telefone) && (sairConfirma(  )) ){
            return false;
        }else{
            mensagemDeErro = validaTelefone( cliente->telefone );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
            puts(mensagemDeErro[corredor] );}}
    }while( mensagemDeErro[0] != NULL );
    return true;
}
char **validaTelefone( char *telefone  ){
    static char *mensagem[4] = {NULL};
    int erro = 0; 
    ///incluir funcao de busca no banco de dados se o telefone já encontra-se cadastrado

    if( !(validaTamanho(telefone, TAMANHO_TELEFONE)) ){
        mensagem[erro++] = "\t^ Dado incompleto!";}
    if( !(telefone[2] == ' ') || !(telefone[8] == '-') ){
        mensagem[erro++] = "\t^ Formato inválido!";}
    if( (telefone[2] == ' ') && !(telefone[3] == '9') ){
        mensagem[erro++] = "\t^ Inclua o 9!";}
    if( !(telefone[0] != '0') && !(telefone[1] == '0') ){
        mensagem[erro++] = "\t^ DDD inválido!";}
    for( int digito = 0; telefone[digito] != '\0'; digito++ ){
        if( (isdigit(telefone[digito])) == 0 && telefone[digito] != '\n' && telefone[digito] != ' ' && telefone[digito] != '-'  ){
            mensagem[erro++] = "\t^ Utilize apenas números!"; break;}}
    mensagem[erro] = NULL;
    return mensagem;
}
bool solicitaRenda( Dados *cliente ){
    char *validaRenda( char* );
    char *mensagemDeErro = NULL;
    
    do{
        printf("\n-> Insira sua renda mensal [R$ 1234 - MÁX %d carac.]\n   <- R$ ", (TAMANHO_RENDA -1) );
        fgets( cliente->renda, TAMANHO_RENDA, stdin );
        limpaDado( cliente->renda );
        if( sair(cliente->renda) && (sairConfirma(  )) ){
            return false;
        }else{
            mensagemDeErro = validaRenda( cliente->renda );
            if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}}
    }while( mensagemDeErro != NULL);
    return true;
}
char *validaRenda( char *renda ){
    static char *erro = NULL;

    for( int digito = 0; renda[digito] != '\0'; digito++ ){
        if( (isdigit(renda[digito])) == 0 ){
            erro = "\t^ Utilize apenas números!";
            break;
        }else if( renda[digito+1] == '\0' ){ 
            erro = NULL;}}
    return erro;
}

#endif // CADASTRO_H_INCLUDED


                    