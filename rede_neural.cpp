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
void pesosW(Neuronio *novoNeuronio);
void entradaNeuronio(Neuronio* neuronio, double entrada[536]);
double funcaoAtivacao(Neuronio* neuronio);
void addNeuronioCamadaOculta(Header *header, double entrada[536]);
void camadaOculta(Header *header, int qntd_neuronio_oculta, double entrada[536]);
double *calculaSaida(Header *header);

int main (int argc, char *argv[]) {
	char *qntd_terminal = argv[1];
	int qntd_neuronio_oculta = atoi(qntd_terminal);
    Header *header = inicializaHeader();
    double entrada[536] = {0.0};

    printf("Qnd de neuronio na camada oculta: %d\n",qntd_neuronio_oculta);
    camadaOculta(header,qntd_neuronio_oculta, entrada);


    return 0;
}

Header *inicializaHeader() {
	Header *header = (Header*) malloc(sizeof(Header));
    header->qntd_elemetos = 0;
    header->head = NULL;
    header->tail = NULL;
	return header;
}

Neuronio *criaNeuronio(double entrada[536]) {
    Neuronio *novoNeuronio = (Neuronio*) malloc(sizeof(Neuronio));

    novoNeuronio->peso_b = randPeso();
    pesosW(novoNeuronio);
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
    double p = 0;

    p = rand()%9999+1;

    p /= 10000;
    return p;
}

void pesosW(Neuronio *novoNeuronio) {
    for(int i = 0; i < 536; i++) {
        novoNeuronio->pesos_w[i] = randPeso();
    }
}

void entradaNeuronio(Neuronio* neuronio, double entrada[536]) {
    for(int i = 0; i < 536; i++) {
        neuronio->entrada[i] = (entrada[i] * neuronio->pesos_w[i])
            + neuronio->peso_b;
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
}

void camadaOculta(Header *header, int qntd_neuronio_oculta, double entrada[536]) {
    for(int i = 0;i <= qntd_neuronio_oculta; i++) {
        addNeuronioCamadaOculta(header, entrada);
    }
}

int camadaSaida(Header *header, double entrada[536]) {
     
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