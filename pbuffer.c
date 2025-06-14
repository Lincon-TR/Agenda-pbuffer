#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME (10 * sizeof(char))
#define IDADE (sizeof(int))
#define EMAIL (10 * sizeof(char))
#define PESSOA (NOME+IDADE+EMAIL)

int main() {
    void *pbuffer = malloc( sizeof(int) + sizeof(int) );
    *( int * )pbuffer = 0;
    *(( int * )pbuffer + 1) = 0;
    void *op = ( int * )pbuffer;
    void *qtd = ( int * )pbuffer + 1;

    while ( 1 ) {
    printf("\n--------Menu--------");
    printf("\nAdicionar pessoa - 1");
    printf("\nRemover Pessoa - 2");
    printf("\nBuscar Pessoa - 3");
    printf("\nListar todos - 4");
    printf("\nSaida - 5");
    printf("\n\nInforme a opcao: ");
    scanf("%d", &*( int * ) op );
    printf("\nOperacao: %d", *( int * ) op);
    printf("\nPessoas: %d\n", *( int * ) qtd);

    switch (*(int *)op) {
    case 1:
        ( * ( int * ) qtd )++;
        pbuffer = realloc( pbuffer, ( sizeof(int)*2 + PESSOA * ( * ( int *) qtd ) ) );
        op = ( int * )pbuffer;
        qtd = ( int * )pbuffer + 1;
        
        void *pessoa = ( char * )pbuffer + sizeof(int)*2 + PESSOA * ( * ( int * )qtd - 1 );

        printf("\nNome: ");
        scanf("%s", ( char * ) pessoa);
        
        printf("Idade: ");
        scanf("%d", ( int * )( pessoa + NOME ));
        
        printf("Email: ");
        scanf("%s", ( char * )( pessoa + NOME + IDADE ) );
        break;

    case 2:
		printf("\nInforme a posicao da pessoa a ser removida: ");
		scanf("%d", ( int * ) op);

        void *remove = NULL;
        void *substitui = NULL;

		while ( * ( int * )op < ( * ( int * ) qtd ) ) {
            remove = ( ( char * )pbuffer + sizeof(int) * 2 + PESSOA * ( * ( int * )op ) );
            substitui = ( ( char * )pbuffer + sizeof(int) * 2 + PESSOA * ( * ( int * )op + 1 ) );

            memmove( remove, substitui, PESSOA );
            ( * ( int * )op )++;
		}

        ( *( int * )qtd )--;
        pbuffer = realloc( pbuffer, ( sizeof(int)*2 + PESSOA * ( *( int * )qtd ) ) );
        op = ( int * )pbuffer;
        qtd = ( int * )pbuffer + 1;
		break;

    case 3:
        pbuffer = realloc( pbuffer, (sizeof(int)*2 + PESSOA * ( *( int * )qtd ) + NOME ) );
        op = (int *)pbuffer;
        qtd = (int *)pbuffer + 1;

        void *atual = NULL;
        void *nome = ( ( char * )pbuffer + (sizeof(int)*2 + PESSOA * ( *( int * )qtd ) ) );

        printf("\nInforme o nome a ser buscado: ");
        scanf("%s", ( char * )nome );

        ( *( int * )op ) = 0;

        while ( ( *( int * )op ) < ( *( int * )qtd ) ) {
            atual = ( ( char * )pbuffer + (sizeof(int)*2 + PESSOA * ( *( int * )op ) ) );
            if ( strcmp( ( char * )atual, ( char * )nome ) == 0 ) {
                printf("\nA posicao da pessoa e %d\n", *( int * )op );
                break;
            }
            ( *( int * )op )++;
        }

        if ( ( *( int * )op ) == ( *( int * )qtd ) ) {
            printf("Nome nao encontrado\n");
        }
        pbuffer = realloc( pbuffer, (sizeof(int)*2 + PESSOA * ( * ( int * )qtd ) ) );
        op = ( int * )pbuffer;
        qtd = ( int * )pbuffer + 1;
        break;

    case 4:
        ( *( int * )op) = 0;
        while ( ( *( int * )op ) < ( *( int * )qtd ) ) {
			printf("\n--------Pessoa--------\n");
            printf("Nome: %s\n", ( char * )pbuffer + sizeof(int)*2 + PESSOA * ( *( int * )op ) );
            printf("Idade: %d\n", *( int * )( ( char * )pbuffer + sizeof(int)*2 + PESSOA * ( *( int * )op ) + NOME ) );
            printf("Email: %s\n", ( char * )pbuffer + sizeof(int)*2 + PESSOA * ( *( int * )op ) + NOME + IDADE );
            (*(int *)op)++;
        }
		break;
    case 5:
        exit(1);
    default:
        break;
    }
    }
    
}
