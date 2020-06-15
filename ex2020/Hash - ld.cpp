#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>



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
struct HashTable {
	Nod** vector;
	int dim;
};

HashTable initHashTable(int dim) {
	HashTable h;
	h.dim = dim;
	h.vector = (Nod**)malloc(sizeof(Nod*)*dim);
	for (int i = 0; i < h.dim; i++) {
		h.vector[i] = NULL;
	}

	return h;
}
int functieHash(const char* idGradinita, int size) {
	int s = 0;
	for (int i = 0; i < strlen(idGradinita); i++)
	{
		s += idGradinita[i];
	}
	return s % size;
}

//cod este int
/*int functieHash(unsigned int nrReteta, int dim)
{
	return nrReteta % dim;
}
*/

int inserareHashTable(HashTable h, Gradinita g)
{
	if (h.dim > 0)
	{
		int k = functieHash(g.idGradinita,h.dim);
		h.vector[k] = inserareLista(h.vector[k], g);
		return k;
	}
	else
	{
		return -2;
	}
}
void afisareGradinita(Gradinita g) {
	printf("\nGradinita cu id-ul %s, are numele %s, se afla pe strada %s, a fost infiinta in %d si are %d copii\n", g.idGradinita, g.numeGradinita, g.stradaGradinita, g.anInfiintare, g.nrCopii);
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

void afisareHashTable(HashTable h)
{
	for (int i = 0; i<h.dim; i++)
		if (h.vector[i])
		{
			Nod* temp = h.vector[i];
			while (temp)
			{
				afisareGradinita(temp->info);
				temp = temp->next;

			}
		}
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

ListaDubla conversie(HashTable h, ListaDubla lista) {
	 
	if (h.dim>0) {
		for (int i = 0; i < h.dim; i++) 
			if(h.vector[i]){
			Nod* temp = h.vector[i];
			while (temp) {
				Gradinita g = creeareGradinita(temp->info.idGradinita, temp->info.numeGradinita, temp->info.stradaGradinita, temp->info.anInfiintare, temp->info.nrCopii);
				if (strcmp(temp->info.idGradinita, "G5") == 0) {

					lista = inserareSfarsit(lista, g);
				}
				temp = temp->next;
			}

		}
		return lista;
	}
	}



void afisareListaDubla(ListaDubla lista) {
	nodDublu* temp = lista.prim;
	while (temp) {
		afisareGradinita(temp->info);
		temp = temp->next;
	}
}

void strergereTabela(HashTable &h) {
	for (int i = 0; i < h.dim; i++) {
		while (h.vector[i]) {
			Nod*aux = h.vector[i];
			h.vector[i] = h.vector[i]->next;
			free(aux->info.idGradinita);
			free(aux->info.numeGradinita);
			free(aux->info.stradaGradinita);
			free(aux);
		}
	}
	free(h.vector);
	h.vector = NULL;
	h.dim = 0;
}

void dezalocareLista(ListaDubla &lista) {
	if (lista.prim) {
		nodDublu* temp = lista.prim;
		while (temp) {
			nodDublu* aux = temp->next;
			free(temp->info.idGradinita);
			free(temp->info.numeGradinita);
			free(temp->info.stradaGradinita);
			free(temp);
			temp = aux;
		}
		lista.prim = NULL;
		lista.ultim = NULL;
	}
}

void main() {
	
	HashTable h = initHashTable(40);
	Gradinita g;
	FILE* fisier = fopen("gradinite.txt", "r");
	if (fisier) {
		while (!feof(fisier)) {

			g = citireGradinitaFisier(fisier);
			inserareHashTable(h, g);
		}
		fclose(fisier);
	}

	afisareHashTable(h);

	printf("\n\nConversie");
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	lista=conversie(h, lista); 
	afisareListaDubla(lista);
	
	


}