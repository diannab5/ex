#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define DIM 100

struct Gradinita {
	char* idGradinita;
	char* numeGradinita;
	char* stradaGradinita;
	int anInfiintare;
	int nrCopii;
};

struct Nod
{
	Gradinita info;
	Nod* next;

};


Gradinita creeareGradinita(const char* id, const char* nume, const char* strada, int anInfiintare, int nrCopii)
{
	Gradinita a;
	a.idGradinita = (char*)malloc(sizeof(char)*(strlen(id) + 1));
	strcpy(a.idGradinita, id);

	a.numeGradinita = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(a.numeGradinita, nume);

	a.stradaGradinita = (char*)malloc(sizeof(char)*(strlen(strada) + 1));
	strcpy(a.stradaGradinita, strada);
	a.anInfiintare = anInfiintare;
	a.nrCopii = nrCopii;

	return a;
}
Nod* inserareLista(Nod* cap, Gradinita g)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = g;
	nou->next = cap;
	return nou;
}

int functieHash(const char* idGradinita, int size) {
	int s = 0;
	for (int i = 0; i < strlen(idGradinita); i++)
	{
		s += idGradinita[i];
	}
	return s % size;
}

void inserareHash(Nod** hashTable, Gradinita g, int size)
{
	int k = functieHash(g.idGradinita, size);
	hashTable[k] = inserareLista(hashTable[k], g);
}

void afisareGradinita(Gradinita g) {
	printf("\nGradinita cu id-ul %s, are numele %s, se afla pe strada %s, a fost infiinta in %d si are %d copii\n", g.idGradinita, g.numeGradinita, g.stradaGradinita, g.anInfiintare, g.nrCopii);
}

void parseHash(Nod** hashTabel, int size)
{
	for (int i = 0; i<size; i++)
		if (hashTabel[i])
		{
			Nod* temp = hashTabel[i];
			while (temp)
			{
				afisareGradinita(temp->info);
				temp = temp->next;
			}
		}
}

Gradinita citireGradinitaFisier(FILE*& f) {
	Gradinita g;

	char buffer[50];
	fscanf(f, "%s", buffer);
	g.idGradinita = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(g.idGradinita, buffer);

	char buffer2[50];
	fscanf(f, "%s", buffer2);
	g.numeGradinita = (char*)malloc(sizeof(char)*(strlen(buffer2) + 1));
	strcpy(g.numeGradinita, buffer2);

	char buffer3[50];
	fscanf(f, "%s", buffer3);
	g.stradaGradinita = (char*)malloc(sizeof(char)*(strlen(buffer3) + 1));
	strcpy(g.stradaGradinita, buffer3);

	fscanf(f, "%d", &g.anInfiintare);
	fscanf(f, "%d", &g.nrCopii);

	return g;

}

struct nodDublu {
	Gradinita info;
	nodDublu* next;
	nodDublu* prev;
};

struct ListaDubla {
	nodDublu* prim;
	nodDublu* ultim;
};

ListaDubla inserareSfarsit(ListaDubla lista, Gradinita g) {
	nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
	nou->info = g;
	nou->next = NULL;
	nou->prev = lista.ultim;
	if (lista.ultim) {
		lista.ultim->next = nou;
		lista.ultim = nou;
	}
	else {
		lista.prim = nou;
		lista.ultim = nou;
	}
	return lista;
}

void conversie(Nod** &hashTable, ListaDubla lista,int size) {
	for (int i = 0; i < size; i++) {
		if (hashTable[i]) {
			Nod* temp = hashTable[i];
			while (temp) {
				if (strcmp(temp->info.idGradinita, "G5") == 0) {
					Gradinita g = creeareGradinita(temp->info.idGradinita, temp->info.numeGradinita, temp->info.stradaGradinita, temp->info.anInfiintare, temp->info.nrCopii);
					 lista=inserareSfarsit(lista,g);
				}
				temp = temp->next;
			}
		}
		
	}
}

void afisareListaDubla(ListaDubla lista) {
	nodDublu* temp = lista.prim;
	while (temp) {
		afisareGradinita(temp->info);
		temp = temp->next;
	}
}


void main() {
	Nod** hashTable;
	hashTable = (Nod**)malloc(sizeof(Nod)*DIM);
	for (int i = 0; i < DIM; i++)
		hashTable[i] = 0;

	Gradinita g;
	FILE* fisier = fopen("gradinite.txt", "r");
	if (fisier) {
		while (!feof(fisier)) {

			g = citireGradinitaFisier(fisier);
			inserareHash(hashTable, g, DIM);
		}
		fclose(fisier);
	}

	parseHash(hashTable, DIM);
	
	printf("\n\nConversie");
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	conversie(hashTable, lista, DIM); //nu afiseaza nimic
	afisareListaDubla(lista);



}