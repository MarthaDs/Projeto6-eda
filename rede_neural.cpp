#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rede_neural.hpp"
#include <time.h>

int atualizaPeso = 0;

Header *inicializaHeader() {
	Header *header = (Header*) malloc(sizeof(Header));
    header->qntd_elemetos = 0;
    header->head = NULL;
    header->tail = NULL;
	return header;
}

Neuronio *criaNeuronio(double entrada[536]) {
    Neuronio *novoNeuronio = (Neuronio*) malloc(sizeof(Neuronio));

    novoNeuronio->peso_b = 0;
    novoNeuronio->pesos_w[536] = {1};
    entradaNeuronio(novoNeuronio, entrada);
    novoNeuronio->saida = 0;

    if(novoNeuronio != NULL) {
        novoNeuronio->prox = NULL;
    }
    return novoNeuronio;
}

double funcaoAtivacao(Neuronio *neuronio) {
    double fun_n, n = 0;
    double e = 2.718281828459045235360287;

    for(int i = 0; i < 536; i++) {
        n += neuronio->entrada[i]; 
    }

    e = pow(e,-n);
    fun_n = 1/(1 + e);

    return fun_n;
}

double randPeso() {
    srand(time(0));
    double p = 0;

    p = (rand() % 32000 - 16000);
    return p;
}

void pesosW(Neuronio *novoNeuronio, double pesos[536]) {
    for(int i = 0; i < 536; i++) {
        novoNeuronio->pesos_w[i] = pesos[i];
    }
}

void calculaPesosRand(Neuronio* neuronio) {
    double pesosW_rand[536];

    for(int i = 0; i < 536; i++) {
        neuronio->pesos_w[i] = randPeso();    
    }
}

void entradaNeuronio(Neuronio* neuronio, double entrada[536]) {
    if(atualizaPeso == 0) {
        calculaPesosRand(neuronio);
        neuronio->peso_b = randPeso();
        printf("Primeiros pesos gerados randomicamente\n");
    }
    else{
        printf("Pesos atualizados atraves do calculo de erro\n");
        for(int i = 0; i < 536; i++) {
        neuronio->entrada[i] = (entrada[i] * neuronio->pesos_w[i])
            + neuronio->peso_b;
        }
    }
}

void addNeuronioCamadaOculta(Header *header, double entrada[536]) {
        if(header->head == NULL) {
            header->head = criaNeuronio(entrada);
            header->tail = header->head;
            header->qntd_elemetos++;
        }
        else {
            header->tail->prox = criaNeuronio(entrada);
            header->tail = header->tail->prox;
            header->qntd_elemetos++;
        }
        printf("add neuronio \n");

}

void camadaOculta(Header *header, int qntd_neuronio_oculta, double entrada[536]) {
    for(int i = 0;i < qntd_neuronio_oculta; i++) {
        addNeuronioCamadaOculta(header, entrada);
    }
    atualizaPeso = 1;
    printf("camada oculta criada\n");
    printf("erro será calculado\n");
}

double *calculaSaida(Header *header) {
    double saida[536];
    int i = 0;

    if(header->head != NULL) {
        for(Neuronio *aux; aux != NULL; aux = aux->prox) {
            aux->saida = funcaoAtivacao(aux);
            saida[i++] = aux->saida;
        }
    }
    return saida;
}

void criaCamadaSaida(Header *header) {
    Neuronio *neuronioSaida = criaNeuronio(calculaSaida(header)); 
    neuronioSaida->saida = funcaoAtivacao(neuronioSaida);
}