#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


struct Masina {
	char* nrInamtriculare;
	char* marca;
	int nrOre;
	float sumaPlata;
};

struct nod {
	nod* next;
	Masina info;
};

nod* creareNod(Masina m) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info.nrInamtriculare = (char*)malloc((strlen(m.nrInamtriculare) + 1) * sizeof(char));
	strcpy(nou->info.nrInamtriculare, m.nrInamtriculare);
	nou->info.marca = (char*)malloc((strlen(m.marca) + 1) * sizeof(char));
	strcpy(nou->info.marca, m.marca);
	nou->info.nrOre = m.nrOre;
	nou->info.sumaPlata = m.sumaPlata;
	nou->next = NULL;
	return nou;
}

void push(nod** prim, nod** ultim, Masina m) {
	nod* nou = creareNod(m);
	if (*prim == NULL && *ultim == NULL) {
		*ultim = nou;
		*prim = nou;
	}
	else {
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

void afisareMasina(Masina m) {
	printf("\nNr.inmatriculare: %s, marca: %s, nr.ore: %d, suma plata: %5.2f ", m.nrInamtriculare, m.marca, m.nrOre, m.sumaPlata);
}
void traversare(nod* cap) {
	nod* temp = cap;
	while (temp) {
		afisareMasina(temp->info);
		temp = temp->next;
	}

}

int get(nod** prim, nod** ultim, Masina* m) {
	if (*prim == NULL) {
		*ultim = NULL;
		return -1;
	}
	else if (*prim != NULL && *ultim != NULL) {
		m->marca = (char*)malloc((strlen((*prim)->info.marca) + 1) * sizeof(char));
		strcpy((*m).marca, (*prim)->info.marca);

		m->nrInamtriculare = (char*)malloc((strlen((*prim)->info.nrInamtriculare) + 1) * sizeof(char));
		strcpy(m->nrInamtriculare, (*prim)->info.nrInamtriculare);
		
		m->nrOre = (*prim)->info.nrOre;
		m->sumaPlata = (*prim)->info.sumaPlata;
		nod* temp = (*prim);
		*prim = temp->next;
		free(temp->info.marca);
		free(temp->info.nrInamtriculare);
		free(temp);
		return 0;
	}
}
struct nodld {
	nodld* next;
	nodld* prev;
	Masina info;
};
nodld* creezNodLd(Masina m) {
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->info.nrInamtriculare = (char*)malloc((strlen(m.nrInamtriculare) + 1) * sizeof(char));
	strcpy(nou->info.nrInamtriculare, m.nrInamtriculare);
	nou->info.marca = (char*)malloc((strlen(m.marca) + 1) * sizeof(char));
	strcpy(nou->info.marca, m.marca);
	nou->info.nrOre = m.nrOre;
	nou->info.sumaPlata = m.sumaPlata;
	nou->next = NULL;
	return nou;
}
void inserareLd(nodld** cap, nodld** coada, Masina m) {
	nodld* nou = creezNodLd(m);
	if (*cap == NULL) {
		*cap = nou;
		nou->prev = *cap;
		nou->next = *cap;
		*coada = nou;
	}
	else {
		nodld* temp = *cap;
		while (temp->next != *cap) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
		(*coada)->next = *cap;
		(*cap)->prev = *coada;
	}
}

void traversareLista(nodld* cap) {
	nodld* temp = cap;
	while (temp->next != cap) {
		afisareMasina(temp->info);
		temp = temp->next;
	}
	afisareMasina(temp->info);
}


void main() {
	nod* prim = NULL;
	nod* ultim = NULL;
	Masina m;
	FILE* f;
	f = fopen("Fisier.txt", "r");
	char* token, file_buf[100], file_sep[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, file_sep);
		m.nrInamtriculare = (char*)malloc(sizeof(char)*(strlen(token) + 1));
		strcpy(m.nrInamtriculare, token);

		token = strtok(NULL, file_sep);
		m.marca = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(m.marca, token);

		token = strtok(NULL, file_sep);
		m.nrOre = atoi(token);

		token = strtok(NULL, file_sep);
		m.sumaPlata = atoi(token);
		//inserare in coada
		push(&prim, &ultim, m);
		
	}
	traversare(prim); //afisare

	Masina deSters;
	nodld* cap = NULL;
	nodld* coada = NULL;
	printf("\n\nConversie in lista: \n");
	while (get(&prim, &ultim, &deSters) == 0) {
		inserareLd(&cap, &coada, deSters);
	}
	traversareLista(cap);


}