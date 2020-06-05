#include<stdio.h>
#include<malloc.h>
#include<string.>



struct Factura {
	char* serieFactura;
	char dataEmiterii[11];
	char denumireClient[20];
	float valoareFactura;


};

struct nod {
	Factura info;
	nod* next;
};

Factura initializareFactura(const char* serie, const char dataEmitere[], const char denumireClient[], float valoareFactura) {
	Factura f;
	f.serieFactura = (char*)malloc(sizeof(char)*(strlen(serie) + 1));
	strcpy(f.serieFactura, serie);
	strcpy(f.dataEmiterii, dataEmitere);
	strcpy(f.denumireClient, denumireClient);
	f.valoareFactura = valoareFactura;
	return f;
}

void afisareFactura(Factura f) {
	printf("\n Factura cu seria %s , emisa la data de %s, clientului %s are valoarea de %5.2f% \n", f.serieFactura, f.dataEmiterii, f.denumireClient, f.valoareFactura);
}

nod* inserareInceput(Factura f, nod* cap) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = f;
	nou->next = cap;
	return nou;
}

void afisareListaFacturi(nod* cap) {
	while (cap) {
		afisareFactura(cap->info);
		cap = cap->next;

	}
}


int nrFacturiDupaDataCalendaristica(nod* cap, const char data[]) {
	int nr = 0; //numarul de facturi
	nod* temp = cap; //avem nevoie de un temp ca sa nu pierdem
	while (temp) { //cat timp avem lista
		if (strcmp(temp->info.dataEmiterii, data) == 0) {//comparam ce am primit ca parametru cu ce avem in lista
			afisareFactura(temp->info); //afisam factura
			nr++; //daca am gasit, creste ++
		}
		temp = temp->next; //trecem la urmatorul nod in lista
	}
	return nr;
}

nod* facturileEmiseAleUnuiClient(const char denumireClient[], nod* cap) {
	nod* rezultat = NULL; // initializez o lista goala
	nod* temp = cap; //ca sa nu pierd date
	while (temp) {//cat timp am elemente in lista
		if (strcmp(temp->info.denumireClient, denumireClient) == 0) {
			rezultat = inserareInceput(temp->info,rezultat); //inserez in lista daca conditia e indeplinita
		}
		temp = temp->next; //trec la urmatorul nod
	}
	return rezultat; //returnez lista cu clienti a caror nume l-am dat ca parametru
}


//dezalocare lista
void stergereLista(nod*& cap) {
	while (cap) {
		nod* temp = cap;
		cap = cap->next;
		free(cap->info.serieFactura);
		free(temp);
	}
	
}


void main() {
	nod* lista = NULL;
	//lista = inserareInceput(initializareFactura("XD200", "10-11-2020", "Marcus", 456.7),lista);
	//lista = inserareInceput(initializareFactura("Sd455", "12-12-2020", "Maia", 234), lista);
	//lista = inserareInceput(initializareFactura("Kl400", "10-11-2020", "Tara", 56), lista);
	//lista = inserareInceput(initializareFactura("Mk450", "12-11-2020", "Marcus", 100), lista);
	//lista = inserareInceput(initializareFactura("XD25", "10-05-2020", " Alex", 85), lista);

	//afisareListaFacturi(lista);
	//printf("\nFacturile din data de 10-11-2020 sunt: ");
	//int nrFacturi = nrFacturiDupaDataCalendaristica(lista, "10-11-2020");
	//printf("\n*******");
	//nod* rezultat = facturileEmiseAleUnuiClient("Marcus", lista);
	//afisareListaFacturi(rezultat);

	
		


}