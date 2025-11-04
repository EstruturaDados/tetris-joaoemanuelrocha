#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5 // tamanho máximo da fila

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // tipo da peça ('I', 'O', 'T', 'L')
    int id;    // identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca elementos[MAX_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

// Função que inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

// Verifica se a fila está vazia
int estaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Verifica se a fila está cheia
int estaCheia(Fila *f) {
    return f->tamanho == MAX_FILA;
}

// Gera uma nova peça com tipo aleatório e id incremental
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere uma nova peça na fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (estaCheia(f)) {
        printf("\n⚠️  A fila está cheia! Não é possível adicionar mais peças.\n");
        return;
    }
    f->elementos[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->tamanho++;
    printf("\n✅ Peça [%c %d] adicionada com sucesso!\n", p.nome, p.id);
}

// Remove a peça da frente da fila (dequeue)
void dequeue(Fila *f) {
    if (estaVazia(f)) {
        printf("\n⚠️  A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca removida = f->elementos[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->tamanho--;
    printf("\n🎮 Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("\n--- Fila de Peças ---\n");
    if (estaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int i = f->inicio;
    for (int c = 0; c < f->tamanho; c++) {
        Peca p = f->elementos[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n----------------------\n");
}

// Função principal
int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    int opcao, contadorID = 0;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorID++));
    }

    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(contadorID++));
                break;
            case 0:
                printf("\n👋 Saindo do jogo... Até mais!\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}