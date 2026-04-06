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
// parte do trabalho joao pedro: remover aluno por rgm e menu
// Funcao auxiliar para limpar o teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


//INTERFACE DO MENU 
void Menu() {
    printf("\n========================================");
    printf("\n            GESTAO ACADEMICA            ");
    printf("\n========================================");
    printf("\n [1] Cadastrar Aluno (Ordenado)");
    printf("\n [2] Mostrar Todos os Alunos");
    printf("\n [3] Buscar Aluno por RGM");
    printf("\n [4] Remover Aluno por RGM"); 
    printf("\n [0] Sair do Programa");
    printf("\n========================================");
    printf("\n > Opcao: ");
}
    


void remover(ListaAlunos *l) {
    int rgm, i, pos = -1;
    printf("Digite o RGM para remover: ");
    scanf("%d", &rgm);

    // aqui ele Procura o aluno na lista sequencial
    for (i = 0; i < l->n; i++) {
        if (l->dados[i].rgm == rgm) {
            pos = i;
            break;
        }
    }
    // CASO O INDICE QUE FOI PASSADO SEJA = -1, VAI MOSTRAR QUE O ALUNO NAO FOI ENCONTRADO
    if (pos == -1) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    //  Limpa a memoria das disciplinas (lista encadeada) antes de excluir o aluno
    Disciplina *d = l->dados[pos].disciplinas;
    while (d != NULL) {
        Disciplina *aux = d;
        d = d->prox;
        free(aux);
    }

    //  desloca os alunos para esquerda para tampar o buraco do aluno removido
    for (i = pos; i < l->n - 1; i++) {
        l->dados[i] = l->dados[i + 1];
    }
    l->n--;

    printf("Aluno removido com sucesso.\n");
    printf("\n--- Lista Resultante ---\n");
    mostrarTodos(l); 
}

void buscar(ListaAlunos *l) {
    int rgm, i, encontrado = 0;
    Disciplina *d;

    printf("Digite o RGM para buscar: ");
    scanf("%d", &rgm);

    // percorre a lista de alunos para procurar o RGM informado
    for (i = 0; i < l->n; i++) {
        if (l->dados[i].rgm == rgm) {

            // se encontrar, exibe os dados do aluno
            printf("\nAluno encontrado!\n");
            printf("RGM: %d\n", l->dados[i].rgm);

            // percorre a lista encadeada de disciplinas do aluno
            d = l->dados[i].disciplinas;

            // verifica se o aluno possui disciplinas cadastradas
            if (d == NULL) {
                printf("  Nenhuma disciplina cadastrada.\n");
            } else {
                // exibe todas as disciplinas e notas
                while (d != NULL) {
                    printf("  %s - %.1f\n", d->nome, d->nota);
                    d = d->prox;
                }
            }

            // marca que o aluno foi encontrado
            encontrado = 1;
            break;
        }
    }

int main() {
    ListaAlunos lista;
    int opcao;
    iniciarlista(&lista);
// TRATAMENTO DE ERRO, caso a pessoa coloque uma letra ou simbolo, o programa nao trave
    do {
        Menu();
       
        if (scanf("%d", &opcao) != 1) { 
            limparBuffer(); 
            continue; 
        }
        limparBuffer();

        switch(opcao) {
            case 1: 
                cadastrar(&lista); 
                break;
            case 2: 
                mostrarTodos(&lista); 
                break;
            case 3:buscar(&lista);
                break;
            case 4: 
                remover(&lista); 
                break;
            case 0: 
                printf("Saindo...\n"); 
                break;
            default: 
                printf("Opcao invalida\n"); 
                break;
        }
    } while (opcao != 0);

    return 0;
}
