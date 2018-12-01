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
    iniciaPesosW(novoNeuronio);
    entradaNeuronio(novoNeuronio, entrada);
    novoNeuronio->saida = 0;

    if(novoNeuronio != NULL) {
        novoNeuronio->prox = NULL;
    }
    return novoNeuronio;
}

void iniciaPesosW(Neuronio *neuronio) {
    for(int i = 0; i < 536; i++) {
        neuronio->pesos_w[i] = 1;
    }
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
        printf("jese\n");
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
    printf("camada oculta criada\n");
    printf("erro será calculado\n");
}

double *calculaSaida(Header *header) {
    double saida[536];
    int i = 0;

    if(header->head != NULL) {
        for(Neuronio *aux = header->head; aux != NULL; aux = aux->prox) {
            aux->saida = funcaoAtivacao(aux);
            saida[i] = aux->saida;
            i++;
        }

    }
    return saida;
}

void criaCamadaSaida(Header *header) {
    Neuronio *neuronioSaida = criaNeuronio(calculaSaida(header)); 
    if(neuronioSaida != NULL)
       neuronioSaida->saida = funcaoAtivacao(neuronioSaida);
    
    atualizaPeso = 1;
}

void backPropagation(Header *header, int erro_esperado, int qntd_neuronio_oculta) {
    double erro_neuro[qntd_neuronio_oculta];
    double delta[qntd_neuronio_oculta];
    int i = 0;

    for(Neuronio *aux = header->head; aux != NULL; aux = aux->prox) {
        double erro = calculaErroCamada(aux);
        erro_neuro[i] =  erro_esperado - tangenteHiperbolica(erro);
        delta[i] = (1 - pow(erro,2)) * erro_neuro[i];
    
        for(int j = 0; j < 536 ; j++) {
            aux->pesos_w[j] = atualizaSinapses(aux->pesos_w[j],erro_neuro[i]);
        }
        
        aux->peso_b = atualizaSinapses(delta[i],erro_neuro[i]);

        i++;
    }

}

double atualizaSinapses(double delta, double erro) {
    double alfa = 0.1;
    double atualiza = 0;

    atualiza = 2 * alfa * erro * delta;

    return atualiza;
}

double calculaErroCamada(Neuronio *neuronio) {
    double erro = 0;
        for(int i = 0; i < 536; i++) {
            erro += neuronio->entrada[i] * neuronio->pesos_w[i]; 
        }
        return erro;
}

double tangenteHiperbolica(double erro){
    double tan = (erro * (-1));

    double tanH = (pow(2.718, erro) - pow(2.718, tan)) / (pow(2.718, erro) + pow(2.718, tan));

    return tanH; 
}
