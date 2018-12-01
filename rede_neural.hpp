#ifndef REDE_NEURAL
#define REDE_NEURALs
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct neuronio {
    double entrada[536];
    double peso_b;
    double pesos_w[536];
    double saida;
    struct neuronio *prox;
}Neuronio;

typedef struct header {
    int qntd_elemetos;
    Neuronio * head;
    Neuronio *tail;
} Header;

Header *inicializaHeader();
double randPeso();
Neuronio *criaNeuronio(double entrada[536]);
void pesosW(Neuronio *novoNeuronio, double pesos[536]);
void entradaNeuronio(Neuronio* neuronio, double entrada[536]);
double funcaoAtivacao(Neuronio* neuronio);
void addNeuronioCamadaOculta(Header *header, double entrada[536]);
void camadaOculta(Header *header, int qntd_neuronio_oculta, double entrada[536]);
double *calculaSaida(Header *header);
void calculaPesosRand(Neuronio* neuronio);
#endif