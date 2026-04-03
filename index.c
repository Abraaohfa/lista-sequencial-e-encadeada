#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 60

typedef struct Disciplina {
    char nome[50];
    float nota;
    struct Disciplina *prox;
} Disciplina;

typedef struct {
    int rgm;
    Disciplina *disciplinas;
} Aluno;

typedef struct {
    Aluno dados[MAX];
    int n;
} ListaAlunos;

void iniciarlista(ListaAlunos *l) {
    l->n = 0;
}

void adicionarDisciplina(Aluno *a, char *nome, float nota) {
    Disciplina *d = (Disciplina*) malloc(sizeof(Disciplina));
    Disciplina *p;
    strcpy(d->nome, nome);
    d->nota = nota;
    d->prox = NULL;
    if (a->disciplinas == NULL) { a->disciplinas = d; return; }
    p = a->disciplinas;
    while (p->prox != NULL) p = p->prox;
    p->prox = d;
}

void cadastrar(ListaAlunos *l) {
    int rgm, pos, i;
    char resp[5], nome[50];
    float nota;

    printf("RGM: ");
    scanf("%d", &rgm);

    pos = l->n;
    for (i = 0; i < l->n; i++) {
        if (rgm < l->dados[i].rgm) { pos = i; break; }
    }
    for (i = l->n; i > pos; i--)
        l->dados[i] = l->dados[i - 1];

    l->dados[pos].rgm = rgm;
    l->dados[pos].disciplinas = NULL;

    do {
        printf("Disciplina: "); scanf(" %[^\n]", nome);
        printf("Nota: ");       scanf("%f", &nota);
        adicionarDisciplina(&l->dados[pos], nome, nota);
        printf("Mais disciplina? (s/n): ");
        scanf("%s", resp);
    } while (resp[0] == 's' || resp[0] == 'S');

    l->n++;
}

void mostrarTodos(ListaAlunos *l) {
    Disciplina *d;
    int i;
    if (l->n == 0) { printf("Nenhum aluno cadastrado.\n"); return; }
    for (i = 0; i < l->n; i++) {
        printf("RGM: %d\n", l->dados[i].rgm);
        d = l->dados[i].disciplinas;
        while (d) { printf("  %s - %.1f\n", d->nome, d->nota); d = d->prox; }
    }
}

int main() {
    ListaAlunos lista;
    int op;
    iniciarlista(&lista);

    do {
        printf("\n1-Cadastrar  2-Mostrar  0-Sair\n> ");
        scanf("%d", &op);
        if (op == 1) cadastrar(&lista);
        else if (op == 2) mostrarTodos(&lista);
    } while (op != 0);

    return 0;
}
