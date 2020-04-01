#include <stdio.h>
#include <stdlib.h>
#define N 127

typedef struct no
{
    int chave;
    int info;
} No;

typedef No *Hash[N];

int hash(int chave, int tam);
void insere(Hash tabela, int chave, int info);
No *busca(Hash tabela, int chave);
int remover(Hash tabela, int chave);

int main()
{
    int info = 0;
    int chave = 0;
    int escolha_menu = 0;

    Hash tabela;
    No *aux = NULL;

    for (int i = 0; i < N; i++) //Inicializando meu vetor de ponteiros para No com endereços vazios.
        tabela[i] = NULL;

    while (escolha_menu != -1)
    {
        system("clear");

        printf(" ___________________________________________ \n");
        printf("|############### HASH-INTERNA ##############|\n");
        printf("|                                           |\n");
        printf("|                [1] INSERIR                |\n");
        printf("|                [2] BUSCAR                 |\n");
        printf("|                [3] REMOVER                |\n");
        printf("|                [4] SAIR                   |\n");
        printf("|___________________________________________|\n");

        printf("\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &escolha_menu);

        switch (escolha_menu)
        {
        case 1:
            printf("\nDigite o numero deseja guardar: ");
            scanf("%d", &info);
            setbuf(stdin, NULL);
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            setbuf(stdin, NULL);
            insere(tabela, chave, info);
            break;

        case 2:
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            aux = busca(tabela, chave);
            if (aux != NULL)
            {
                printf("\nNumero guardado: %d", aux->info);
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            else
            {
                printf("Nao encontrado!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 3:
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            if (remover(tabela, chave))
            {
                printf("Removido com sucesso!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            else
            {
                printf("Nao encontrado!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 4:
            escolha_menu = -1;
            printf("Bye!\n\n");
            break;

        default:
            printf("\nOpção incorreta, pressione [ENTER] e tente novamente!");
            escolha_menu = 0;
            setbuf(stdin, NULL);
            getchar();
            break;
        }
    }
    return 0;
}

int hash(int chave, int tam) //Método da multiplicacao.
{
    int posicao;
    int aux[7];
    chave = chave * chave;
    
    for (int i = 0; i < 7; i++)
    {
        aux[6 - i] = chave % 10;
        chave = chave / 10;
    }

    posicao = (aux[2] * 100) + (aux[3] * 10) + aux[4];

    if (posicao > tam)
    {
        posicao = posicao - (aux[2] * 100); 
    }
    
    return posicao; 
}

void insere(Hash tabela, int chave, int info)
{
    int h = hash(chave, N);

    while (tabela[h] != NULL) // encontrou o elemento.
    {
        if (tabela[h]->chave == chave)
            break;
        h = (h + 1) % N;
    }

    if (tabela[h] == NULL) // não encontrou o elemento.
    {
        tabela[h] = (No *)malloc(sizeof(No));
        tabela[h]->chave = chave;
        tabela[h]->info = info;
    }
}

No *busca(Hash tabela, int chave)
{
    int h = hash(chave, N);

    while (tabela[h] != NULL)
    {
        if (tabela[h]->chave == chave)
            return tabela[h];
        h = (h + 1) % N;
    }
    return NULL;
}

int remover(Hash tabela, int chave)
{
    No *aux = busca(tabela, chave);
    if (aux != NULL)
    {
        free(aux);
        aux = NULL;
        return 1;
    }
    return 0;
}