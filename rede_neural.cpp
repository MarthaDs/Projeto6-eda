#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct neuronio {
    double entrada[537];
    double peso;
    double saida;
    int camada;
    int posicao;
    struct camdaSeguinte *prox_neuronios;
}Neuronio;

typedef struct camdaSeguinte {
    void *neuronio;
    struct camdaSeguinte *prox;
}camdaSeguinte;

double randPeso();

int main (int argc, char *argv[]) {
	char *qntd_terminal = argv[1];
	int qntd_neuronio_oculta = atoi(qntd_terminal);
	printf("Qnd de neuronio na camada oculta: %d\n",qntd_neuronio_oculta);



    return 0;
}

Neuronio CriaNeuronio(double entrada[537], int camada) {
    Neuronio *novoNeuronio = (Neuronio*) malloc(sizeof(Neuronio));

    (novoNeuronio)->entrada = entrada;
    novoNeuronio->camada = camada;
    novoNeuronio->prox_neuronios = NULL;

    int b = 1;
    double n = 0;
    
    for(int i = 0;i < 537; i++) {
        n += entrada[i] * randPeso();    
    }
    n += b;
    novoNeuronio->saida = funcaoAtivacao(n);

}

double funcaoAtivacao(int n) {
    double fun_n;
    double e = 2.718281828459045235360287;

    e = pow(e,-n);
    fun_n = 1/(1 + e);

    return fun_n;
}

double randPeso() {
    double p = 0;

    p = rand()%9999+1;

    p /= 10000;
    return p;
}

