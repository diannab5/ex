#include<stdio.h>
#include<malloc.h>
#include<string.h>



struct Masina {
	char* inmatriculare;
	int an;
	int nrLocuri;
	float pret;
};

struct nod {
	Masina info;
	nod* next;
};

Masina creareMasina(const char* inmatriculare, int an, int nrLocuri, float pret) {
	Masina m;
	m.inmatriculare = (char*)malloc(sizeof(char)*(strlen(inmatriculare) + 1));
	strcpy(m.inmatriculare, inmatriculare);
	m.an = an;
	m.nrLocuri = nrLocuri;
	m.pret = pret;
	return m;
}


//pct 1-LSI gestionata pe principiul FIFO
nod* inserareSfarsit(nod* cap, Masina m) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = m;
	nou->next = NULL;
	if (cap) {
		nod* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		cap = nou;
	}
	return cap;
}

//inserare in coada
nod* pushQueue(nod* coada, Masina m) {
	coada = inserareSfarsit(coada, m);
	return coada;
}

//extragere din coada
Masina popQueue(nod* &coada) {
	if (coada) {
		Masina m = coada->info;
		nod* temp = coada;
		coada = temp->next;
		free(temp);
		return m;
	}
	else {
		return creareMasina("", -1, -1, -1);
	}
}

void afisareMasina(Masina m) {
printf("Masina cu nr de inmatriculare %s, fabricata in anul %d, are %d locuri, iar pretul este de %5.2f EUR.\n", m.inmatriculare, m.an, m.nrLocuri, m.pret);
}
void afisareLista(nod* cap) {
	nod* p = cap;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

//pct 2- afisare lista folosind doar operatiile specifice cozii
void afisareCoada(nod* &coada) {
	while (coada) {
		Masina m = popQueue(coada);
		afisareMasina(m);
	}
}

//extragere masini care au atributul nrLocuri intr-un interval
nod* extragereMasini(nod* cap, int pragMin, int pragMax) {
	nod* coada = NULL;
	nod* temp = cap;
	while (temp) {
		if (temp->info.nrLocuri > pragMin&&temp->info.nrLocuri < pragMax) {
			coada = pushQueue(coada, temp->info);
		}
		temp = temp->next;
	}
	return coada;
}

//Conversie coada in masiv uni prin extragere
int nrMasini(nod* cap) {
	nod* temp = cap;
	int contor = 0;
	while (temp) {
		contor++;
		temp = temp->next;
	}
	return contor;
}

Masina* conversie(nod* cap) {
	Masina* vector = (Masina*)malloc(sizeof(Masina)*nrMasini(cap));
	nod* temp = cap;
	int nr = nrMasini(cap);
	for (int i = 0; i < nr; i++) {
		vector[i] = popQueue(cap);
	}
	return vector;
}

int isEmptyQueue(nod* cap) {
	return cap == NULL;
}


void main() {
	nod* coada = NULL;
	coada = pushQueue(coada, creareMasina("B394820", 2010, 4, 5000.55));
	coada = pushQueue(coada, creareMasina("B993799", 2016, 5, 8000));
	coada = pushQueue(coada, creareMasina("B45DIY", 2016, 2, 9000));
	coada = pushQueue(coada, creareMasina("B55PKI", 2010, 20, 4400));

	afisareLista(coada);

	printf("\nLista masini care au nr de locuri in intervalul 1-10:\n");
	afisareLista(extragereMasini(coada, 1, 10));
}