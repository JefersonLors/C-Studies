#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct aluno{
    char nome[20];
    struct aluno *proximo;
}aluno;

void inserirAluno( aluno** );
void limparLista( aluno** ); 
void listarAlunos( aluno* );
void excluirAluno( aluno* ); 
void pesquisarAluno( aluno* ); 

int main( ){
    char resposta[3];
    aluno *primeiro = NULL;

    do{
        printf( "MENU:\n"
                " i -> inserir\n" 
                " l -> listar\n"
                " p -> pesquisar\n"
                " e -> excluir\n"
                " a -> limpar\n"
                " \n <- ");
        fgets( resposta, 3, stdin );
        switch( resposta[0] ){
            case 'i':
                inserirAluno( &primeiro );
                puts("\n");
                break;
            case 'l':
                listarAlunos( primeiro );
                puts("\n");
                break;
            case 'p':
                pesquisarAluno( primeiro );
                puts("\n");
                break;
            case 'e':
                excluirAluno( primeiro );
                puts("\n");
                break;
            case 'a':
                limparLista( &primeiro );
                puts("\n");
                break;
        } 
    }while( resposta[0] != '0' );
}

void inserirAluno( aluno **primeiro ){
    aluno *atual,
          *novo;
     
    printf( "\nINSERINDO:\n " );
    if( (*primeiro) == NULL ){
        (*primeiro) = (aluno *)malloc( sizeof(aluno) );
        printf( "Nome: " );
        fgets( (*primeiro)->nome, 20, stdin );
        (*primeiro)->proximo = NULL;
    }else{
        novo = (aluno *)malloc( sizeof(aluno) );
        printf( "Nome: " );
        fgets( novo->nome, 20, stdin );
        
        atual = *primeiro;
        while( atual->proximo != NULL ){
            atual = atual->proximo;}
        
        atual->proximo = novo;
        novo->proximo = NULL;
    }
}
void listarAlunos( aluno *primeiro ){
    aluno *atual = primeiro;

    printf( "\nALUNOS:\n" );
    while( atual != NULL ){
        printf( "- %s\n", atual->nome );
        atual = atual->proximo;
    }
}
void pesquisarAluno( aluno *primeiro ){
    char alunoPesquisar[20];
    aluno *atual = primeiro;

    printf( "\nDigite o nome: " );
    fgets( alunoPesquisar, 20, stdin );
    
    while( atual != NULL ){
        if( strcmp( atual->nome, alunoPesquisar ) == 0 ){
            printf( "\nEncontrado\n" );
            break;}
        atual = atual->proximo;
    }
}
void excluirAluno( aluno *primeiro ){
    char alunoExcluir[20];
    aluno *atual = primeiro,
          *atualBackup = NULL;
    
    printf( "\nDigite o nome: " );
    fgets( alunoExcluir, 20, stdin );
    
    while( atual != NULL && strcmp( atual->nome, alunoExcluir ) != 0 ){
        atualBackup = atual;
        atual = atual->proximo;}

    if( atualBackup == NULL ){
        printf( "\nAluno excluido\n" );
        primeiro = atual->proximo;
    }else{
        printf( "\nAluno excluido\n" );
        atualBackup->proximo = atual->proximo;}
    free( atual );
}
void limparLista( aluno **primeiro ){
    aluno *atual = *primeiro;

    while( atual != NULL ){
        aluno *backup = atual->proximo;
        free( atual );
        atual = backup; }
    *primeiro = NULL;
}
