/*1. Sistema de Atendimento Prioritário
Você está desenvolvendo um sistema de fila para atendimento em um hospital. 
Pacientes com maior gravidade devem ser atendidos primeiro, ou seja, a fila
deve ser ordenada de forma decrescente pela gravidade do caso 
 (nível de gravidade varia de 1 a 10).
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void cadastrar_paciente();
void adicionar_fila(char *nome, int gravidade, int idade, int cpf);
void imprimir();
void remover();

typedef struct no{
  char *nome;
  int idade;
  int cpf;
  int gravidade;
  struct no *prox;
}NO;

NO *inicio = NULL;
NO *fim = NULL;
int tam =0;


void menu(){
    int op;
    printf("\nHospital Dom Diego Ben 10\n");
    printf("\nSistema de Gestão Hospitalar (SGH).\n");
    printf("O que deseja:\n\n");
    printf("1 - Adicionar paciente na fila.\n");
    printf("2 - Ver a fila.\n");
    printf("3 - Chamar paciente.\n");
    scanf("%d", &op);
    getchar();
    if (op == 1){
        cadastrar_paciente();
    }else if(op == 2){
        imprimir();
    }else if(op == 3){
        remover();
    }else{
        printf("\nOpção inválida. Tente novamente.\n");
        menu();
    }
}

void adicionar_fila(char *nome, int gravidade, int idade, int cpf){
  NO * novo = malloc(sizeof(NO));
  novo->nome = strdup(nome);
  novo->cpf = cpf;
  novo->idade = idade;
  novo->gravidade = gravidade;
  novo->prox = NULL;

  if (inicio == NULL){
    inicio = novo;
    fim = novo;
    tam++;
  }else if (gravidade>inicio->gravidade){ //inicio
    novo->prox = inicio;
    inicio = novo;
  }else if (gravidade<inicio->gravidade && gravidade>fim->gravidade){ //meio
    NO *aux = inicio;
    while (aux != NULL && gravidade < aux->prox->gravidade){
      aux = aux->prox;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
  }else if (gravidade<fim->gravidade){
    fim->prox = novo;
    fim = novo;
  }
    tam++;
  
}

void cadastrar_paciente(){
    char nome[100];
    int idade; 
    int cpf;
    int gravidade;
    printf("Qual o nome do paciente?\n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Qual a idade do paciente?\n");
    scanf("%d", &idade);
    printf("Qual o CPF do %s.\n", nome);
    scanf("%d", &cpf);
    printf("De 1 a 10, qual o nível de urgência do paciente:\n");
    scanf("%d", &gravidade);
    if(gravidade <1 || gravidade>10){
        if (gravidade<1){
            gravidade = 1;
        }else{
            gravidade = 10;
        }
    }
    getchar();
    
    adicionar_fila(nome, gravidade, idade, cpf);
    menu();
}


  
void imprimir(){
    int op = -1;
    NO *aux = inicio;
    if(inicio == NULL){
        printf("\nFila vazia.\n");
        menu();
    }
    while(aux != NULL){
        printf("\nPaciente : %s, Gravidade: %d\n", aux->nome, aux->gravidade);
        aux = aux->prox;
    }
    printf("\n");
    printf("Para sair da fila, digite qualquer número.\n");
    scanf("%d", &op);
    if (op!= -1){
        menu();
    }
    
}
  

void remover() {
    if (inicio == NULL) {
        printf("\nFila vazia.\n");
        menu();
        return; 
    }
    NO *aux = inicio;
    inicio = inicio->prox;
    if (inicio == NULL) { 
        fim = NULL;
    }
    printf("\nChamando o paciente: %s.\n", aux->nome);
    free(aux->nome); 
    free(aux);
    tam--;
    menu();
}
  
int main(){
    menu();
    return 0;
}