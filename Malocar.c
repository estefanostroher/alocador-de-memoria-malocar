#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/* Autor: Estefano Ströher Soares */

// Definição da estrutura de cabeçalho que armazena informações sobre cada bloco de memória.
struct header {
    size_t tam;             // Tamanho do bloco de memória
    bool livre;             // Indicador se o bloco está livre
    struct header *proximo; // Ponteiro para o próximo bloco na lista
};
typedef struct header Header;

Header *inicio = NULL, *fim = NULL; // Ponteiros para o início e fim da lista de blocos.
                                    // Setados como global porque como são utilizados dentro das funções
                                    // não é necessário passá-los como parâmetro, 
                                    // pois o intuito é recriar um malloc e free, respectivamente (no qual esses parâmetros não vão).

// Função para procurar um bloco livre que seja grande o suficiente para acomodar o tamanho solicitado.
Header *procurar_bloco_livre(size_t tam) {
    Header *atual = inicio;
    while(atual) {
        // Verifica se o bloco atual está livre e tem tamanho suficiente
        if(atual->livre = true && atual->tam >= tam)
            return atual;
        atual = atual->proximo;
    }
    return NULL; // Retorna NULL se não encontrar um bloco adequado
}

// Função para alocar a memória solicitada.
void *malocar(size_t tam) {
    size_t tam_total;
    void *bloco;
    Header *cabecalho;

    // Se o tamanho solicitado for 0, retorna NULL
    if(!tam)
        return NULL;

    // Procura um bloco livre existente
    cabecalho = procurar_bloco_livre(tam); // Se um bloco livre existente for encontrado, ele é retornado. 
                                           // Caso contrário, um novo bloco é alocado.

    // Se um bloco livre for encontrado, retorna o endereço do bloco.
    if(cabecalho) {
        cabecalho->livre = false; // Marca o bloco como ocupado
        return (void*)(cabecalho + 1); // Retorna o endereço logo após o cabeçalho
    }

    // Caso contrário, calcula o tamanho total a ser solicitado (cabeçalho + bloco de dados)
    tam_total = sizeof(Header) + tam;

    // Solicita um novo bloco de memória
    bloco = sbrk(tam_total);
    if(bloco == (void*) - 1) {
        printf("Erro ao alocar a memoria solicitada.\n");
        return NULL; // Retorna NULL se sbrk falhar
    }

    // Inicializa o cabeçalho do novo bloco
    cabecalho = bloco;
    cabecalho->tam = tam;
    cabecalho->livre = false;
    cabecalho->proximo = NULL;

    // Atualiza os ponteiros da lista encadeada
    if(!inicio)
        inicio = cabecalho;
    if(fim)
        fim->proximo = cabecalho;
    fim = cabecalho;
    return (void*)(cabecalho + 1); // Retorna o endereço logo após o cabeçalho
}

// Função para desalocar a memória alocada.
void desalocar(void *bloco) {
    Header *cabecalho, *tmp;
    void *program_break;

    // Se o ponteiro for NULL, não faz nada
    if(!bloco)
        return;
    
    // Calcula o endereço do cabeçalho
    cabecalho = (Header*)bloco - 1;

    // Obtém o endereço atual do break de programa
    program_break = sbrk(0);

    // Verifica se o bloco a ser desalocado é o último bloco alocado, se sim, o espaço é retornado ao sistema
    if((char*)bloco + cabecalho->tam == program_break) {
        // Atualiza os ponteiros inicio e fim se o bloco for o último
        if(inicio == fim) {
            inicio = fim = NULL;
        } else {
            tmp = inicio;
            while(tmp) {
                if(tmp->proximo == fim) {
                    tmp->proximo = NULL;
                    fim = tmp;
                }
                tmp = tmp->proximo;
            }
        }
        // Libera o bloco retornando o espaço para o sistema
        sbrk(0 - sizeof(Header) - cabecalho->tam);
        return;
    }
    // Marca o bloco como livre
    cabecalho->livre = true;
}

// Função de depuração para imprimir a lista de blocos da memória.
void listar_blocos_memoria() {
    Header *atual = inicio;
    printf("endereco_inicio = %p, endereco_fim = %p \n", (void*)inicio, (void*)fim);
    while(atual) {
        printf("endereco = %p, tam = %zu, livre(true or false) = %d, proximo = %p\n", (void*)atual, atual->tam, atual->livre, (void*)atual->proximo);
        atual = atual->proximo;
    }
}

int main() {
    listar_blocos_memoria();

    int i = 0;
    int *vet = (int*)malocar(sizeof(int) * 10);

    for(i = 0; i < 10; i++) {
        vet[i] = i;
        printf("vet[%d] = %d\n", i, vet[i]);
    }
    
    listar_blocos_memoria();
    desalocar(vet);
    vet = NULL;

    return 0;  
}
