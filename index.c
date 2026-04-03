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

Disciplina *novaDisciplina(char *nome, float nota) {
    Disciplina *d = (Disciplina*) malloc(sizeof(Disciplina));
    strcpy(d->nome, nome);
    d->nota = nota;
    d->prox = NULL;
    return d;
}

void adicionarDisciplina(Aluno *a, char *nome, float nota) {
    Disciplina *d = novaDisciplina(nome, nota);
    Disciplina *p;
    if (a->disciplinas == NULL) {
        a->disciplinas = d;
        return;
    }
    p = a->disciplinas;
    while (p->prox != NULL) p = p->prox;
    p->prox = d;
}

void liberarDisciplinas(Disciplina *d) {
    Disciplina *tmp;
    while (d) {
        tmp = d->prox;
        free(d);
        d = tmp;
    }
}

int main() {
    Aluno a;
    Disciplina *d;

    a.rgm = 11111;
    a.disciplinas = NULL;

    adicionarDisciplina(&a, "Estrutura de Dados", 8.5);
    adicionarDisciplina(&a, "Calculo", 7.0);

    printf("RGM: %d\n", a.rgm);
    d = a.disciplinas;
    while (d) {
        printf("  %s - %.1f\n", d->nome, d->nota);
        d = d->prox;
    }

    liberarDisciplinas(a.disciplinas);
    return 0;
}
