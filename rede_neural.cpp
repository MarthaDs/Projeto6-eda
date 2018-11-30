#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct neuronio {
    double entrada[537];
    double peso_b;
    double pesos_w[537];
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
Neuronio *criaNeuronio(double entrada[537]);
void pesosW(double *pesos_w);
void entradaNeuronio(Neuronio* neuronio, double entrada[537]);
double funcaoAtivacao(int n);
void addNeuronioCamadaOculta(Header *header, double entrada[537]);
double camadaOculta(Header *header, int qntd_neuronio_oculta, double entrada[537]);

int main (int argc, char *argv[]) {
	char *qntd_terminal = argv[1];
	int qntd_neuronio_oculta = atoi(qntd_terminal);
    Header *header = inicializaHeader();
    double entrada[537] = {0.0};

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

Neuronio *criaNeuronio(double entrada[537]) {
    Neuronio *novoNeuronio = (Neuronio*) malloc(sizeof(Neuronio));

    entradaNeuronio(novoNeuronio, entrada);
    novoNeuronio->peso_b = randPeso();
    pesosW(novoNeuronio->pesos_w);
    novoNeuronio->saida = 0;

    if(novoNeuronio != NULL) {
        novoNeuronio->prox = NULL;
    }
    return novoNeuronio;
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

void pesosW(double *pesos_w) {
    for(int i = 0; i < 536; i++) {
        pesos_w[i] = randPeso();
    }
}

void entradaNeuronio(Neuronio* neuronio, double entrada[537]) {
    for(int i = 0; i < 536; i++) {
        neuronio->entrada[i] = entrada[i];
    }
}

void addNeuronioCamadaOculta(Header *header, double entrada[537]) {
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

double camadaOculta(Header *header, int qntd_neuronio_oculta, double entrada[537]) {
    for(int i = 0;i <= qntd_neuronio_oculta; i++) {
        addNeuronioCamadaOculta(header, entrada);
    }
}