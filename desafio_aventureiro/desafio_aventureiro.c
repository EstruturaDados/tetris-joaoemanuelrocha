#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5     // Tamanho fixo da fila
#define TAM_PILHA 3    // Capacidade máxima da pilha

// Estrutura que representa uma peça
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único
} Peca;

// ---------- FILA CIRCULAR ----------
typedef struct {
    Peca elementos[TAM_FILA];
    int frente, tras, tamanho;
} Fila;

// ---------- PILHA ----------
typedef struct {
    Peca elementos[TAM_PILHA];
    int topo;
} Pilha;

// ---------- Função para gerar uma nova peça ----------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// ---------- Funções da Fila ----------
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->elementos[f->tras] = p;
    f->tamanho++;
}

Peca desenfileirar(Fila *f) {
    Peca p = {' ', -1};
    if (filaVazia(f)) return p;
    p = f->elementos[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tamanho--;
    return p;
}

// ---------- Funções da Pilha ----------
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("⚠️  Pilha de reserva cheia!\n");
        return;
    }
    p->topo++;
    p->elementos[p->topo] = x;
}

Peca desempilhar(Pilha *p) {
    Peca x = {' ', -1};
    if (pilhaVazia(p)) {
        printf("⚠️  Pilha de reserva vazia!\n");
        return x;
    }
    x = p->elementos[p->topo];
    p->topo--;
    return x;
}

// ---------- Exibição ----------
void exibirEstado(Fila *f, Pilha *p) {
    printf("\n===== ESTADO ATUAL =====\n");
    printf("Fila de peças\t: ");
    if (filaVazia(f))
        printf("(vazia)");
    else {
        int i, idx;
        for (i = 0; i < f->tamanho; i++) {
            idx = (f->frente + i) % TAM_FILA;
            printf("[%c %d] ", f->elementos[idx].nome, f->elementos[idx].id);
        }
    }
    printf("\nPilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p))
        printf("(vazia)");
    else {
        for (int i = p->topo; i >= 0; i--)
            printf("[%c %d] ", p->elementos[i].nome, p->elementos[i].id);
    }
    printf("\n=========================\n");
}

// ---------- PROGRAMA PRINCIPAL ----------
int main() {
    Fila fila;
    Pilha pilha;
    int opcao, idCounter = 0;

    srand(time(NULL));
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++)
        enfileirar(&fila, gerarPeca(idCounter++));

    do {
        exibirEstado(&fila, &pilha);
        printf("\nOpções de Ação:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peça
                if (!filaVazia(&fila)) {
                    Peca jogada = desenfileirar(&fila);
                    printf("🕹️  Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                    enfileirar(&fila, gerarPeca(idCounter++));
                } else {
                    printf("Fila vazia!\n");
                }
                break;
            }

            case 2: { // Reservar peça
                if (!filaVazia(&fila)) {
                    if (!pilhaCheia(&pilha)) {
                        Peca reservada = desenfileirar(&fila);
                        empilhar(&pilha, reservada);
                        printf("💾 Peça reservada: [%c %d]\n", reservada.nome, reservada.id);
                        enfileirar(&fila, gerarPeca(idCounter++));
                    } else {
                        printf("⚠️  Pilha cheia! Não é possível reservar.\n");
                    }
                }
                break;
            }

            case 3: { // Usar peça da reserva
                if (!pilhaVazia(&pilha)) {
                    Peca usada = desempilhar(&pilha);
                    printf("✅ Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
                } else {
                    printf("⚠️  Nenhuma peça na reserva!\n");
                }
                break;
            }

            case 0:
                printf("\n👋 Saindo do jogo...\n");
                break;

            default:
                printf("❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}