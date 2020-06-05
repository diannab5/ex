#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define DIM 100

struct Articol
{
	int id;
	char* titlu;
	char* categorie;
	int nrPagini;
	int nrAutori;

};

struct Nod
{
	Articol info; //efectiv informatia utila 
	Nod* next; //adresa urmatorului nod

};

Nod* inserareLista(Nod* cap, Articol a)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = cap;
	return nou;
}

Articol creeareArticol(int id, const char* titlu, const char* categorie, int nrPagini, int nrAutori)
{
	Articol a;
	a.id = id;
	a.titlu = (char*)malloc(sizeof(char)*(strlen(titlu) + 1));
	strcpy(a.titlu, titlu);
	a.categorie = (char*)malloc(sizeof(char)*(strlen(categorie) + 1));
	strcpy(a.categorie, categorie);
	a.nrPagini = nrPagini;
	a.nrAutori = nrAutori;
	return a;
}

void afisareArticol(Articol a)
{
	printf("Articolul %d are titlul %s, este din categoria %s,nr de pagini %d, nr de autori %d \n", a.id, a.titlu, a.categorie, a.nrPagini, a.nrAutori);
}

int functieHash(char* categorie, int size) {
	int s = 0;
	for (int i = 0; i < strlen(categorie); i++)
	{
		s += categorie[i];
	}
	return s / size;
}

void inserareHash(Nod** hashTable, Articol a, int size)
{
	int k = functieHash(a.categorie, size);
	hashTable[k] = inserareLista(hashTable[k], a);
}

void parseHash(Nod** hashTabel, int size)
{
	for (int i = 0; i<size; i++)
		if (hashTabel[i])
		{
			Nod* temp = hashTabel[i];
			while (temp)
			{
				printf("Articolul %d are titlul %s, este din categoria %s, nr de pagini %d, nr de autori %d \n", temp->info.id, temp->info.titlu, temp->info.categorie, temp->info.nrPagini, temp->info.nrAutori);
				temp = temp->next;
			}
		}
}

int numarAutori(Nod** hashTable, int size) {
	int nrAutori = 0;
	for(int i=0;i<size;i++)
		if (hashTable[i]) {//daca am elemente in vector
			Nod* temp = hashTable[i];
			while (temp) {
				nrAutori += temp->info.nrAutori;
				temp = temp->next;
			}
		}
	return nrAutori;
}

int numarArticole(Nod** hashTbale, char* categorie, int size) {
	int nrArticole = 0;
	int k = functieHash(categorie, size);
	if (hashTbale[k]) {
		Nod* temp = hashTbale[k];
		while (temp) {
			nrArticole++;
			temp = temp->next;
		}
	}
	return nrArticole;
}

Articol* vectorArticole(Nod** hashTable, char* categorie, int* n, int size) {
	int k = functieHash(categorie, size); //calculez pozitia
	if (hashTable[k]) {
		Articol* vArticole = (Articol*)malloc(sizeof(Articol)*numarArticole(hashTable,categorie,size));
		Nod* temp = hashTable[k];
		while (temp) {
			vArticole[(*n)++] = temp->info;//salvez in vector info utila
			temp = temp->next;//trec la urmatorul
		}
		return vArticole;
	}
}

void MajorarePagini(Nod** hashTable, int size) {
	for(int i=0;i<size;i++)
		if (hashTable[i]) {
			Nod* temp = hashTable[i];
			while (temp) {
				(temp->info.nrPagini)++;
				temp = temp->next;
			}
		}
}

void stergereNod(Nod* nod) {
	free(nod->info.titlu);
	free(nod->info.categorie);
	free(nod);
}

void stergereElementLista(Nod** cap, int id) {
	Nod* temp = *cap;
	if (temp->info.id == id) {
		Nod* deSters = temp;
		temp = temp->next;
		stergereNod(deSters);
		*cap = temp;


	}

	while (temp->next != NULL) {

		Nod* deSters = temp->next;
		if (deSters->info.id == id) {
			temp->next = deSters->next;
			stergereNod(deSters);
		}
		temp = temp->next;

	}
	temp->next = NULL;


}



void stergereElementTabela(Nod** hTab, char* categorie, int id, int size) {
	if (hTab) {
		int poz = functieHash(categorie, size);
		stergereElementLista(&hTab[poz], id);
	}
}


void main() {
	Nod** hashTable; //vector de adrese
	//Articol a;
	hashTable = (Nod**)malloc(sizeof(Nod)*DIM);
	for (int i = 0; i < DIM; i++)
		hashTable[i] = 0;
	//inserareHash(hashTable, creeareArticol(1, "IoT Security", "Security", 12, 2), DIM);
	//inserareHash(hashTable, creeareArticol(2, "Cybernetic Security", "Security", 10, 1), DIM);
	//inserareHash(hashTable, creeareArticol(6, "Cybernetic Security", "Security", 15, 1), DIM);
	//inserareHash(hashTable, creeareArticol(3, "Mondial Bank", "Finance", 8, 3), DIM);
	//inserareHash(hashTable, creeareArticol(4, "Cash Flow", "Finance", 4, 2), DIM);
	//inserareHash(hashTable, creeareArticol(5, "Unenmployment Rate", "Economy", 10, 2), DIM);
	FILE *f;
	f = fopen("articole.txt", "r");
	char* token;

	char buf[120];
	Articol articol;

	while (fgets(buf, sizeof(buf), f)) {
		token = strtok(buf, ",");
		articol.id = atoi(token);

		token = strtok(NULL, ",");
		articol.titlu = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(articol.titlu, token);

		token = strtok(NULL, ",");
		articol.categorie = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(articol.categorie, token);

		token = strtok(NULL, ",");
		articol.nrPagini = atoi(token);

		token = strtok(NULL, ",");
		articol.nrAutori= atoi(token);



		inserareHash(hashTable, articol, DIM);

		articol.titlu = NULL;
		articol.categorie = NULL;

	}
	parseHash(hashTable, DIM);
	
	printf(" Numarul total de autori: %d ", numarAutori(hashTable, DIM));

	/*int n = 0;
	char vect[] = "Security";
	Articol* vart = vectorArticole(hashTable, vect, &n, DIM);
	printf("\n\n Vector articole in categoria aleasa\n");
	for (int i = 0; i < n; i++)
	{
		afisareArticol(vart[i]);
	}
	MajorarePagini(hashTable, DIM);
	printf("\n\nDupa majorare pagini: ");
	parseHash(hashTable, DIM);
	
	printf("\n\n");
	stergereElementTabela(hashTable, vect, 2, DIM);
	parseHash(hashTable, DIM);
	*/
}