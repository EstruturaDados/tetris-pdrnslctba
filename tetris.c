#include <stdio.h>
#include <stdlib.h>   // rand, srand
#include <time.h>     // time (semente do sorteio)

#define MAX 5   // capacidade fixa da fila de pecas

// Cada peca tem um tipo (nome) e um id unico de criacao.
typedef struct {
    char nome;   // 'I', 'O', 'T' ou 'L'
    int id;      // numero unico, na ordem em que a peca foi criada
} Peca;

// A fila circular: o vetor de pecas mais os controles de posicao.
typedef struct {
    Peca itens[MAX];   // vetor que guarda as pecas
    int inicio;        // indice da frente (proxima peca a ser jogada)
    int fim;           // indice de onde a proxima peca entra
    int total;         // quantas pecas tem na fila agora
} Fila;

// Gera uma peca automaticamente. Sorteia um tipo entre os 4 possiveis
// e usa um contador que so cresce para dar um id unico a cada peca.
Peca gerarPeca() {
    static int proximoId = 0;      // "static" faz o valor sobreviver entre
                                   // chamadas: ele lembra onde parou
    char tipos[4] = {'I', 'O', 'T', 'L'};

    Peca nova;
    nova.nome = tipos[rand() % 4]; // sorteia um dos 4 tipos
    nova.id = proximoId;           // id atual
    proximoId++;                   // proximo a nascer tera id maior
    return nova;
}

// Diz se a fila esta vazia (nenhuma peca dentro).
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Diz se a fila esta cheia (ja tem o maximo de pecas).
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Insere uma peca no fim da fila (enqueue), se houver espaco.
void inserir(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel inserir.\n");
        return;   // aborta: fila e void, esse return so sai da funcao
    }
    f->itens[f->fim] = p;          // coloca a peca na posicao do fim
    f->fim = (f->fim + 1) % MAX;   // avanca o fim, dando a volta com % MAX
    f->total++;                    // registra mais uma peca
}

// Remove a peca da frente da fila (dequeue), se houver alguma.
void remover(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nao ha peca para jogar.\n");
        return;
    }
    Peca jogada = f->itens[f->inicio];   // le quem esta na frente
    printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
    f->inicio = (f->inicio + 1) % MAX;   // avanca a frente, dando a volta
    f->total--;                          // uma peca a menos
}

// Mostra todas as pecas da fila, da frente para o fim.
void exibirFila(Fila *f) {
    printf("\nFila de pecas\n");

    if (filaVazia(f)) {
        printf("(vazia)\n\n");
        return;
    }

    // Comeca no inicio e anda "total" vezes, sempre com % MAX para
    // dar a volta quando passa do fim do vetor.
    int i = f->inicio;
    int contador;
    for (contador = 0; contador < f->total; contador++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % MAX;
    }
    printf("\n\n");
}

int main() {
    srand(time(NULL));   // semente do sorteio: pecas diferentes a cada execucao

    Fila fila;
    fila.inicio = 0;
    fila.fim = 0;
    fila.total = 0;

    int contador;
    // Inicializa a fila ja com MAX pecas geradas automaticamente.
    for (contador = 0; contador < MAX; contador++) {
        inserir(&fila, gerarPeca());
    }

    int opcao;
    do {
        exibirFila(&fila);
        printf("Opcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            remover(&fila);
        } else if (opcao == 2) {
            inserir(&fila, gerarPeca());
        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
