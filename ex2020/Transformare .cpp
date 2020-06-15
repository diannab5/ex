#include<iostream>
#include<string.h>
#include<malloc.h>
#include<stdio.h>
#include<conio.h>

struct Gradinita {
	int idGradinita;
	char* numeGradinita;
	int nrClase;
	char* numeClasa;
	float medieGradinita;
};

Gradinita initGradinita(int idGradinita, char* numeGradinita, int nrClase, char* numeClasa, float medieGradinita) {
	Gradinita g;
	g.idGradinita = idGradinita;
	g.numeGradinita = (char*)malloc(sizeof(char)*(strlen(numeGradinita) + 1));
	strcpy(g.numeGradinita, numeGradinita);
	g.nrClase = nrClase;
	g.numeClasa = (char*)malloc(sizeof(char)*(strlen(numeClasa) + 1));
	strcpy(g.numeClasa, numeClasa);
	g.medieGradinita = medieGradinita;
	return g;
}

Gradinita citesteGradinitaDinFisier(FILE* f) {
	Gradinita g;
	fscanf(f, "%d", g.idGradinita);
	char buffer[20];
	fscanf(f, "%s", buffer);
	g.numeGradinita = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(g.numeGradinita, buffer);
	fscanf(f, "%d", g.nrClase);
	char buffer1[20];
	fscanf(f, "%s", buffer1);
	g.numeGradinita = (char*)malloc(sizeof(char)*(strlen(buffer1) + 1));
	strcpy(g.numeGradinita, buffer1);
	fscanf(f, "%5.2f", g.medieGradinita);

	return g;

}

void afisareGradinita(Gradinita g) {
	printf("%d .Gradinita %s, are %d clase, cu numele %s, avand o medie de %5.2f \n",
		g.idGradinita, g.numeGradinita, g.nrClase, g.numeClasa, g.medieGradinita);
}

struct Nod {
	Gradinita info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dim;
};

int HashCode(Gradinita g, int dim) {
	int temp = 0;
	int poz = 0;
	for (int i = 0; i < strlen(g.numeGradinita); i++) {
		temp += g.numeGradinita[i];
	}
	poz = temp%dim;
	return poz;
}

Nod* inserareLista(Nod* rad, Gradinita g) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = g;
	nou->next = rad;
	rad = nou;
	return rad;
}

HashTable inserareHashTable(HashTable ht, Gradinita g) {
	int poz = HashCode(g, ht.dim);
	ht.vector[poz] = inserareLista(ht.vector[poz], g);
	return ht;
}

HashTable initializareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (Nod**)malloc(sizeof(Nod*)*dim);
	for (int i = 0; i < ht.dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		printf("Poz: %d \n", i);
		Nod* temp = ht.vector[i];
		while (temp) {
			afisareGradinita(temp->info);
			temp = temp->next;
		}
	}
}

void mofificaNumeGradinita(HashTable ht,  Gradinita g, const char* numeGradinita) {
	int poz = HashCode(g, ht.dim);
	Nod* temp = ht.vector[poz];
	while (temp) {
		if (strcmp(temp->info.numeGradinita, g.numeGradinita)==0) {
			free(temp->info.numeGradinita);
			temp->info.numeGradinita= (char*)malloc(sizeof(char)*(strlen(numeGradinita) + 1));
			strcpy(temp->info.numeGradinita, numeGradinita);
		}
		temp = temp->next;
	}
}


struct NodDublu {
	Gradinita info;
	NodDublu* next;
	NodDublu* prev;
};

struct ListaDubla {
	NodDublu* prim;
	NodDublu*ultim;
};

ListaDubla inserareListaDubla(ListaDubla lista, Gradinita g) {
	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
	nou->info = g;
	nou->next = lista.prim;
	nou->prev = NULL;
	if (lista.prim) {
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	else {
		lista.prim = nou;
		lista.ultim = nou;
	}
	return lista;
}

void afisareListaDubla(ListaDubla lista) {
	NodDublu* temp = lista.prim;
	while (temp) {
		afisareGradinita(temp->info);
		temp = temp->next;
	}
}


ListaDubla copiereHash(HashTable ht, ListaDubla lista, const char* nume) {
	for (int i = 0; i < ht.dim; i++) {
		Nod* temp = ht.vector[i];
		while (temp) {
			if (strcmp(temp->info.numeGradinita, nume) == 0) {
				lista = inserareListaDubla(lista, temp->info);
			}
			temp = temp->next;
		}
	}
	return lista;
}

void stergereLista(ListaDubla *lista) {
	NodDublu* p = lista->prim;
	while (p) {
		free(p->info.numeGradinita);
		free(p->info.numeClasa);
		NodDublu* t = p;
		p = p->next;
		free(t);
	}
	lista->prim = NULL;
	lista->ultim = NULL;
}



void main() {
	//HashTable ht1 = initializareHashTable(10);
	//FILE* fisier = fopen("gradinite.txt", "r");
	//if (fisier) {
	//	int nrAvioane = 0;
	//	fscanf(fisier, "%d", &nrAvioane);
	//	for (int i = 0; i < nrAvioane; i++) {
	//		ht1 = inserareHashTable(ht1, citesteGradinitaDinFisier(fisier)); 
	//	}
	//}
	//fclose(fisier);
	//afisareHashTable(ht1);

	Gradinita g1 = initGradinita(1, "Stelutele", 2, "mica mare ", 7.5);
	Gradinita g2 = initGradinita(2, "Albinutele", 2, "mica pregatitoare", 10);
	Gradinita g3 = initGradinita(3, "Floricelele", 3, "mica mare, pregatitoare", 9.5);
	Gradinita g4 = initGradinita(4, "Steaua de mare", 3, "mica, mare, pregatitoare", 8);
	Gradinita g5 = initGradinita(5, "Elefantul", 3, "mica, mare, pregatitoare", 10);
	Gradinita g6 = initGradinita(6, "Furnica", 3, "mica, mare, pregatitoare", 6.5);
	Gradinita g7 = initGradinita(7, "Greiere", 3, "mica, mare, pregatitoare", 9);
	Gradinita g8 = initGradinita(8, "Greierasul", 3, "mica, mare, pregatitoare", 8.5);
	Gradinita g9 = initGradinita(9, "Ursul", 3, "mica, mare, pregatitoare", 7.5);
	Gradinita g10 = initGradinita(10, "Abracadabra", 3, "mica, mare, pregatitoare", 6);

	HashTable ht = initializareHashTable(10);
	ht = inserareHashTable(ht, g1);
	ht = inserareHashTable(ht, g2);
	ht = inserareHashTable(ht, g3);
	ht = inserareHashTable(ht, g4);
	ht = inserareHashTable(ht, g5);
	ht = inserareHashTable(ht, g6);
	ht = inserareHashTable(ht, g7);
	ht = inserareHashTable(ht, g8);
	ht = inserareHashTable(ht, g9);
	ht = inserareHashTable(ht, g10);
	printf("\n------------------------CERINTA 1--------------------------------\n");
	afisareHashTable(ht);

	printf("\n-------------------------CERINTA 2-------------------------------\n");
	mofificaNumeGradinita(ht, g10, "Albinutele");
	afisareHashTable(ht);

	printf("\n-------------------------CERINTA 3-------------------------------\n");

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	lista = copiereHash(ht, lista, "Albinutele");
	afisareListaDubla(lista);

	printf("\n-------------------------CERINTA 5-------------------------------\n");
	stergereLista(&lista);
	afisareListaDubla(lista);
}