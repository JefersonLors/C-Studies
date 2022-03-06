#ifndef CADASTRO_H_INCLUDED
#define CADASTRO_H_INCLUDED

#include "utilitarias.h"

///CONSTANTES DE ARQUIVOS
#define ARQUIVO_CADASTRO_CLIENTE "arquivoClienteCadastro.dat"
#define DADOS_ARQUIVO_CADASTRO "dadosArquivoCadastro.txt" 
///--------------------------------------///

///CONSTANTES DE REGISTROS
#define TAMANHO_NOME_COMP 61
#define TAMANHO_NOME_PREF 31
#define TAMANHO_EMAIL 81
#define TAMANHO_TELEFONE 15  
#define TAMANHO_CPF 16           
#define TAMANHO_SENHA 10
#define TAMANHO_RENDA 10
#define TAMANHO_DATA_NASCIMENTO 12
///--------------------------------------///

///CONSULTAS;
bool consultaCpf( const char* );
bool consultaEmail( const char* );
bool consultaTelefone( const char* );

struct dados{
    char nomeCompleto[ TAMANHO_NOME_COMP ],
         nomePreferencial[ TAMANHO_NOME_PREF ],
         email[ TAMANHO_EMAIL ],
         telefone[ TAMANHO_TELEFONE ],
         cpf[ TAMANHO_CPF ],
         senha[ TAMANHO_SENHA ],
         renda[ TAMANHO_RENDA ],
         nascimento[ TAMANHO_DATA_NASCIMENTO ];
    int ID;
}cliente;
typedef struct dados Dados;

enum SITUACAO_DO_DADO { CADASTRADO = 1, NOVO = 0};
typedef enum SITUACAO_DO_DADO SITUACAO_DO_DADO; 

int quantidadeDeContas = -1;

///FUNÇÕES DE VALIDAÇÃO
char **validaCpf( const char* );
char *validaNomes( const char* );
char **validaData_De_Nascimento( const char* );
char **validaEmail( char* );
char **validaSenha( const char* );
char **validaTelefone( const char* );
char *validaRenda( const char* );
///--------------------------------------///

///FUNÇÕES DE SOLICITAÇÃO
bool solicitaEmail( Dados* );
bool solicitaNomePreferencial( Dados* );
bool solicitaNomeCompleto( Dados* );
bool solicitaTelefone( Dados* );
bool solicitaRenda( Dados* );
bool solicitaSenha( Dados* );
bool solicitaCpf( Dados* );
bool solicitaData_De_Nascimento( Dados* );
///--------------------------------------///

bool cadastrarCliente( Dados cliente ){ 
    FILE *arquivoClienteCadastro = fopen( ARQUIVO_CADASTRO_CLIENTE, "a" );
    FILE *dadosArquivosCadastros = fopen( DADOS_ARQUIVO_CADASTRO, "a" );

    if( arquivoClienteCadastro == NULL && dadosArquivosCadastros == NULL ){
        puts( "\n Arquivo não criado para registros!\n" );
        return false;
    }else{
        fscanf( dadosArquivosCadastros, "%4d", &quantidadeDeContas );
        fclose( dadosArquivosCadastros );
        cliente.ID = ++quantidadeDeContas;
        dadosArquivosCadastros = fopen( DADOS_ARQUIVO_CADASTRO, "w" );
        fprintf( dadosArquivosCadastros, "%3d", quantidadeDeContas );
        fclose( dadosArquivosCadastros );
        
        if( solicitaCpf( &cliente ) )
            if( solicitaData_De_Nascimento( &cliente ) )
                if( solicitaNomeCompleto( &cliente ) )
                    if( solicitaEmail( &cliente ) )
                        if( solicitaTelefone( &cliente ) )
                            if( solicitaRenda( &cliente ) )
                                if( solicitaNomePreferencial( &cliente ) )
                                    if( solicitaSenha( &cliente ) ){
                                        fseek( arquivoClienteCadastro, (cliente.ID)*sizeof(Dados), SEEK_SET ); 
                                        fwrite( &cliente, sizeof(Dados), 1, arquivoClienteCadastro );
                                        fclose( arquivoClienteCadastro );   
                                        return true;}}
        
///adicionar fução que conta os cpfs e checar se bate com a quantidade de contas criadas porque está
///dando erro
    --quantidadeDeContas; 
    dadosArquivosCadastros = fopen( DADOS_ARQUIVO_CADASTRO, "w" );
    fprintf( dadosArquivosCadastros, "%3d", quantidadeDeContas );
    fclose( dadosArquivosCadastros );
    return false;
}
bool solicitaCpf( Dados *cliente ){
    char **mensagemDeErro = NULL;

    do{
        abasCadastro(1);
        fgets( cliente->cpf, TAMANHO_CPF, stdin );
        limpaDado( cliente->cpf );
        if( sair(cliente->cpf) ){
            if( sairConfirma(  ) ){
                return false;
            }else{
                char *vazio[1] = {" "};
                mensagemDeErro = vazio;}
        }else{
            mensagemDeErro = validaCpf( cliente->cpf );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor]);}}
    }while( mensagemDeErro[0] != NULL );
    return true;
}
char **validaCpf( const char *cpf ){
    static char *mensagem[3] = {NULL};
    SITUACAO_DO_DADO CPF = NOVO;
    int erro = 0; 
 
    if( !(validaTamanho(cpf, TAMANHO_CPF)) ){
        mensagem[erro++] = "\t^ Dado incompleto"; }
    if( !(cpf[3] == '.') || !(cpf[7] == '.') || !(cpf[11] == '-') ){
        mensagem[erro++] = "\t^ Formato invalido";}
    for( int digito = 0; cpf[digito] != '\0'; digito++ ){
        if( (isdigit( cpf[digito] )) == 0 && cpf[digito] != '.' && cpf[digito] != '-' ){
            mensagem[erro++] = "\t^ Utilize apenas numeros";
            break;}}

    mensagem[erro] = NULL;

    if( mensagem[0] == NULL ){
        CPF = consultaCpf( cpf );
        if( CPF == CADASTRADO ){
            mensagem[erro++] = "\t^ Cpf já cadastrado";
            mensagem[erro] = NULL;}}
    
    return mensagem;
}
bool solicitaData_De_Nascimento( Dados *cliente ){
    char **mensagemDeErro = NULL;

    do{
        abasCadastro(7);
        fgets( cliente->nascimento, TAMANHO_DATA_NASCIMENTO, stdin );
        limpaDado( cliente->nascimento );
        if( sair(cliente->nascimento) ){ 
            if( sairConfirma(  ) ){
                return false;
            }else{
                char *vazio[1] = {" "};
                mensagemDeErro = vazio;}
        }else{ 
            mensagemDeErro = validaData_De_Nascimento( cliente->nascimento );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor] );}}
    }while( mensagemDeErro[0] != NULL );

    return true;
}
char **validaData_De_Nascimento( const char *data ){
    static char *mensagem[7] = {NULL};
    int erro = 0;

    if( !(validaTamanho(data, TAMANHO_DATA_NASCIMENTO)) ){
        mensagem[erro++] = "\t^ Dado incompleto";}
    if( !(data[2] == '/') || !(data[5] == '/') ){
        mensagem[erro++] = "\t^ Formato invalido";}
    for( int digito = 0; data[digito] != '\0'; digito++ ){
        if( (isdigit( data[digito] )) == 0 && data[digito] != '/' ){
            mensagem[erro++] = "\t^ Utilize apenas numeros!";
            break;}}
    if( mensagem[0] == NULL ){
        if( (data[0] > '3') || (data[0] == '3' && data[1] > '1') || ((data[0] == '0') && (data[1] == '0')) ) {
            mensagem[erro++] = "\t^ Dia inválido";}
        if( (data[3] > '1') || (data[3] == '1' && data[4] > '2') || ((data[3] == '0') && (data[4] == '0')) ){
            mensagem[erro++] = "\t^ Mês inválido";}
        if( (data[6] > '2') || (data[8] == '2' && data[9] > '2') || ((data[6] == '2') && (data[7] > '0')) || ((data[7] == '0') && (data[8] > '2')) ){
            mensagem[erro++] = "\t^ Ano inválido";}
        if( (data[6] < '1') || (data[6] == '1' && data[7] < '9') ){
            mensagem[erro++] = "\t^ Ano inválido";}}
    if( mensagem[0] == NULL && (data[6] == '2') && (data[0] == '0') && (data[9] > '4') ){
        mensagem[erro++] = "\t^ Ops!! Você não tem idade para fazer o cadastro.";}
    mensagem[erro] = NULL;
    return mensagem;
}
bool solicitaNomeCompleto( Dados *cliente ){
    char *mensagemDeErro = NULL;
    
    do{
        abasCadastro(3);
        fgets( cliente->nomeCompleto, TAMANHO_NOME_COMP, stdin );
        limpaDado( cliente->nomeCompleto );
        if( sair( cliente->nomeCompleto ) ){
            if( sairConfirma(  ) ){
                return false; 
            }else{ mensagemDeErro = " ";}
        }else{
            mensagemDeErro = validaNomes( cliente->nomeCompleto );
            if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}}
    }while( mensagemDeErro != NULL);
    return true;
}
bool solicitaNomePreferencial( Dados *cliente ){
    char *mensagemDeErro = NULL;
    
    do{
        abasCadastro(4);
        fgets( cliente->nomePreferencial, TAMANHO_NOME_PREF, stdin );
        limpaDado( cliente->nomePreferencial );
        if( sair(cliente->nomePreferencial) ){
            if( sairConfirma(  ) ){
                return false;
            }else{ mensagemDeErro = " ";}
        }else{
            mensagemDeErro = validaNomes( cliente->nomePreferencial );
            if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}}
    }while( mensagemDeErro != NULL);
    return true;
}
char *validaNomes( const char *nome ){
    static char *erro = NULL;

    for( int letra = 0; nome[letra] != '\0'; letra++ ){
        if( ( isalpha( nome[letra] ) == 0) && (nome[letra] != '\n') && (nome[letra] != ' ') ){
            erro = "\t^ Utilize apenas letras";
            break;}
        erro = NULL;}
}
bool solicitaEmail( Dados *cliente ){
    char **mensagemDeErro = NULL;
    
    do{
        abasCadastro(5);
        fgets( cliente->email, TAMANHO_EMAIL, stdin );
        limpaDado( cliente->email );
        if( sair( cliente->email) ){
            if( sairConfirma(  ) ){
                return false;
            }else{
                char *vazio[1] = {" "};
                mensagemDeErro = vazio;}
        }else{ 
            mensagemDeErro = validaEmail( cliente->email );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor]);}}
    }while( mensagemDeErro[0] != NULL);
    return true;
}
char **validaEmail( char *email  ){
    int tamanhoMin = 5;
    static char *mensagem[4] = {NULL};
    int erro = 0;
    const int quantidadeDominios = 5;
    char *dominios[] = { "@gmail.com", "@outlook.com", "@hotmail.com", "@live.com", "@yahoo.com" };
    SITUACAO_DO_DADO EMAIL = NOVO;
    
    strcpy( email, (padronizaDado(email)));
    for( int caracter = 0; email[caracter] != '\0'; caracter++ ){
        if( (isalnum( email[caracter] )) == 0 && email[caracter] != '.' && email[caracter] != '_' && email[caracter] != '@' ){
            mensagem[erro++] = "\t^ Email inválido! Utilize caracteres de A - Z, \nde 0 - 9, ( _ ), ( . ), sem espaço, sem acentuação \ne sem caracteres especiais além dos já citados";
            break;}}

    for( int caracter = 0; email[caracter] != '\0'; caracter++ ){
        if( email[caracter] == '@' ){
            if( caracter < tamanhoMin ){
                mensagem[erro++] = "\t^ É necessário pelo menos 5 caracteres de endereço";}
            for( int dominio = 0; dominio < quantidadeDominios; dominio++ ){
                if( (strcmp( &email[caracter], dominios[dominio] )) == 0 ){
                    mensagem[erro] = NULL; break;
                }else if( (dominio+1) == quantidadeDominios ){
                    mensagem[erro++] = "\t^ Dominio inválido";}}
            break;
        }else if( email[caracter+1] == '\0' ){
            mensagem[erro++] = "\t^ Email inválido";}}
    
    mensagem[erro] = NULL;

    if( mensagem[0] == NULL ){
        EMAIL = consultaEmail( email );
        if( EMAIL == CADASTRADO ){
            mensagem[erro++] = "\t^ Email já cadastrado";
            mensagem[erro] = NULL;}}
   
    return mensagem;
}
bool solicitaSenha( Dados *cliente ){
    char **mensagemDeErro = NULL;
    
    do{
        abasCadastro(2);
        fgets( cliente->senha, TAMANHO_SENHA, stdin );
        limpaDado( cliente->senha );
        if( sair(cliente->senha) ){
            if( sairConfirma(  ) ){
                return false;
            }else{
                char *vazio[1] = {" "};
                mensagemDeErro = vazio;}
        }else{
            mensagemDeErro = validaSenha( cliente->senha);
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
                puts(mensagemDeErro[corredor] );}}
    }while( mensagemDeErro[0] != NULL );
    return true;
}
char **validaSenha( const char *senha ){
    static char *mensagem[4] = {NULL};
    int erro = 0; 

    for( int digito = 0; senha[digito] != '\0'; digito++ ){
        if( (islower(senha[digito]) > 0 ) ){
            break;
        }else if( senha[digito+1] == '\0'){
            mensagem[erro++] = "\t^ Falta pelo menos uma letra minúscula";} }
    
    for( int digito = 0; senha[digito] != '\0'; digito++ ){
        if( (isupper(senha[digito]) > 0) ){
            break;
        }else if( senha[digito+1] == '\0'){
            mensagem[erro++] = "\t^ Falta pelo menos uma letra MAIÚSCULA";} }
    
    for( int digito = 0; senha[digito] != '\0'; digito++ ){
        if( (isdigit(senha[digito]) > 0) ){
            break;
        }else if( senha[digito+1] == '\0'){
            mensagem[erro++] = "\t^ Falta pelo menos um número";} }
    
    for( int digito = 0; senha[digito] != '\0'; digito++ ){
        if( (isalnum(senha[digito] )) == 0 ){
            break;
        }else if( senha[digito+1] == '\0'){
            mensagem[erro++] = "\t^ Falta pelo menos um caracter especial";} }
    
    mensagem[erro] = NULL;
    return mensagem;
}
bool solicitaTelefone( Dados *cliente ){
    char **mensagemDeErro = NULL;
    
    do{
        abasCadastro(8);
        fgets( cliente->telefone, TAMANHO_TELEFONE, stdin );
        limpaDado( cliente->telefone );
        if( sair(cliente->telefone) ){
            if( sairConfirma(  ) ){
                return false;
            }else{
                char *vazio[1] = {" "};
                mensagemDeErro = vazio;}
        }else{
            mensagemDeErro = validaTelefone( cliente->telefone );
            for( int corredor = 0; mensagemDeErro[corredor] != NULL; corredor++ ){
            puts(mensagemDeErro[corredor] );}}
    }while( mensagemDeErro[0] != NULL );
    
    return true;
}
char **validaTelefone( const char *telefone  ){
    static char *mensagem[4] = {NULL};
    int erro = 0; 
    SITUACAO_DO_DADO TELEFONE = NOVO;
    ///incluir funcao de busca no banco de dados se o telefone já encontra-se cadastrado

    if( !(validaTamanho(telefone, TAMANHO_TELEFONE)) ){
        mensagem[erro++] = "\t^ Dado incompleto";}
    if( !(telefone[2] == ' ') || !(telefone[8] == '-') ){
        mensagem[erro++] = "\t^ Formato inválido";}
    if( (telefone[2] == ' ') && !(telefone[3] == '9') ){
        mensagem[erro++] = "\t^ Inclua o 9";}
    if( !(telefone[0] != '0') && !(telefone[1] == '0') ){
        mensagem[erro++] = "\t^ DDD inválido";}
    for( int digito = 0; telefone[digito] != '\0'; digito++ ){
        if( (isdigit(telefone[digito])) == 0 && telefone[digito] != '\n' && telefone[digito] != ' ' && telefone[digito] != '-'  ){
            mensagem[erro++] = "\t^ Utilize apenas números"; break;}}
    mensagem[erro] = NULL;

    if( mensagem[0] == NULL ){
        TELEFONE = consultaTelefone( telefone );
        if( TELEFONE == CADASTRADO ){
            mensagem[erro++] = "\t^ Telefone já cadastrado";
            mensagem[erro] = NULL;}}
    
    return mensagem;
}
bool solicitaRenda( Dados *cliente ){
    char *mensagemDeErro = NULL;
    
    do{
        abasCadastro(6);
        fgets( cliente->renda, TAMANHO_RENDA, stdin );
        limpaDado( cliente->renda );
        if( sair(cliente->renda) ){
            if( sairConfirma(  ) ){
                return false;
            }else{ mensagemDeErro = " ";}
        }else{
            mensagemDeErro = validaRenda( cliente->renda );
            if( mensagemDeErro != NULL ){
            puts( mensagemDeErro );}}
    }while( mensagemDeErro != NULL);
    return true;
}
char *validaRenda( const char *renda ){
    static char *erro = NULL;

    for( int digito = 0; renda[digito] != '\0'; digito++ ){
        if( (isdigit(renda[digito])) == 0 ){
            erro = "\t^ Utilize apenas números";
            break;
        }else if( renda[digito+1] == '\0' ){ 
            erro = NULL;}}
    return erro;
}
bool consultaCpf( const char *cpf ){
    FILE *clientesCadastrados = fopen( ARQUIVO_CADASTRO_CLIENTE, "r" ),
         *dadosGerais = fopen( DADOS_ARQUIVO_CADASTRO, "r" );
    
    fscanf( dadosGerais, "%d", &quantidadeDeContas );
        
    for( int id = 0; id <= quantidadeDeContas; id++ ){
        fseek( clientesCadastrados, id*sizeof(Dados), SEEK_SET);
        fread( &cliente, sizeof(Dados), 1, clientesCadastrados);   
        if( (strcmp( cpf, cliente.cpf)) == 0 ){
        fclose(dadosGerais);
        fclose(clientesCadastrados);
        return true;}}

    fclose(dadosGerais);
    fclose(clientesCadastrados);
    return false;
}
bool consultaEmail( const char *email ){
    FILE *clientesCadastrados = fopen( ARQUIVO_CADASTRO_CLIENTE, "r" ),
         *dadosGerais = fopen( DADOS_ARQUIVO_CADASTRO, "r" );
    
    fscanf( dadosGerais, "%d", &quantidadeDeContas );
        
    for( int id = 0; id <= quantidadeDeContas; id++ ){
        fseek( clientesCadastrados, id*sizeof(Dados), SEEK_SET);
        fread( &cliente, sizeof(Dados), 1, clientesCadastrados); 
        
        if( (strcmp( email, cliente.email)) == 0 ){
            fclose(dadosGerais);
            fclose(clientesCadastrados);
            return true;}}

    fclose(dadosGerais);
    fclose(clientesCadastrados);
    return false;
}
bool consultaTelefone( const char *telefone){
    FILE *clientesCadastrados = fopen( ARQUIVO_CADASTRO_CLIENTE, "r" ),
         *dadosGerais = fopen( DADOS_ARQUIVO_CADASTRO, "r" );
    
    fscanf( dadosGerais, "%d", &quantidadeDeContas );
        
    for( int id = 0; id <= quantidadeDeContas; id++ ){
        fseek( clientesCadastrados, id*sizeof(Dados), SEEK_SET);
        fread( &cliente, sizeof(Dados), 1, clientesCadastrados);   
        if( (strcmp( telefone, cliente.telefone)) == 0 ){
            fclose(dadosGerais);
            fclose(clientesCadastrados);
            return true;}}

    fclose(dadosGerais);
    fclose(clientesCadastrados);
    return false;
}
#endif // CADASTRO_H_INCLUDED


                    