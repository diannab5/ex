#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define DIM 40

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


struct nodDublu {
	Gradinita info;
	nodDublu* next;
	nodDublu* prev;
};
struct ListaDubla {
	nodDublu* prim;
	nodDublu* ultim;
};
ListaDubla inserareInceput(ListaDubla lista, Gradinita g) {
	nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
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

ListaDubla inserareDinHash( Nod **hashTabel, int size){
  ListaDubla l;
for(int i=0;i<size;i++){
  if (hashTabel[i])
		{
			 Nod* temp = hashTabel[i];
			while (temp)
			{
				inserareInceput(l, temp->info);
				temp = temp->next;
			}
		}
}
return l;
}

 Gradinita creeareGradinita(const char* id, const char* nume, int nrCopii, int anInfiintare,char* strada)
{
	 Gradinita a;
  a.idGradinita=(char*)malloc(sizeof(char)*(strlen(id)+1));
	strcpy(a.idGradinita,id);
	a.numeGradinita = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(a.numeGradinita, nume);
	a.stradaGradinita = (char*)malloc(sizeof(char)*(strlen(strada) + 1));
	strcpy(a.stradaGradinita, strada);
	a.nrCopii = nrCopii;
  a.anInfiintare=anInfiintare;
	return a;
}
 Nod* inserareLista( Nod* cap,  Gradinita g)
{
	struct Nod* nou = ( Nod*)malloc(sizeof( Nod));
	nou->info = g;
	nou->next = cap;
	return nou;
}

int functieHash(char* idGradinita, int size) {
	int s = 0;
	for (int i = 0; i < strlen(idGradinita); i++)
	{
		s += idGradinita[i];
	}
	return s / size;
}

void inserareHash( Nod** hashTable, Gradinita g, int size)
{
	int k = functieHash(g.idGradinita, size);
	hashTable[k] = inserareLista(hashTable[k], g);
}

void afisareGradinita( Gradinita g) {
	printf("\nGradinita cu id-ul %s, are numele %s, se afla pe strada %s, a fost infiinta in %d si are %d copii\n", g.idGradinita, g.numeGradinita, g.stradaGradinita, g.anInfiintare, g.nrCopii);
}

void parseHash( Nod** hashTabel, int size)
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

void afisareListaIncSf(ListaDubla lista) {
	nodDublu* aux = lista.prim;
	while (aux) {
		afisareGradinita(aux->info);
		aux = aux->next;
	}
}
void stergereNod( Nod* nod) {
	free(nod->info.idGradinita);
	free(nod->info.stradaGradinita);
  free(nod->info.numeGradinita);
	free(nod);
}

void stergereElementLista( Nod** cap, char* id) {
	struct Nod* temp = *cap;
	if (strcmp(temp->info.idGradinita,id)==0) {
	  struct	Nod* deSters = temp;
		temp = temp->next;
		stergereNod(deSters);
		*cap = temp;
	}

	while (temp->next != NULL) {

	struct	Nod* deSters = temp->next;
    if(strcmp(deSters->info.idGradinita,id)==0) {
			temp->next = deSters->next;
			stergereNod(deSters);
		}
		temp = temp->next;

	}
	temp->next = NULL;


}


void stergereElementTabela( Nod** hTab, char* id, int size) {
	if (hTab) {
		int poz = functieHash(id, size);
		stergereElementLista(&hTab[poz], id);
	}
}

void modificareElement( Nod** hTab, char* idVechi, char* idNou, int size){
  if (hTab) {
		int poz = functieHash(idVechi, size);
     Gradinita g=creeareGradinita(hTab[poz]->info.idGradinita, hTab[poz]->info.numeGradinita, hTab[poz]->info.nrCopii, hTab[poz]->info.anInfiintare, hTab[poz]->info.stradaGradinita);
    stergereElementLista(&hTab[poz], idVechi);
    strcpy(g.idGradinita,idNou);
    inserareHash(hTab, g, DIM);
	}
}

void stergereTabela(Nod** hashTabel,int size) {
  Nod* first=hashTabel[0];
  free(first->info.idGradinita);
	free(first->info.stradaGradinita);
	free(first->info.numeGradinita);
	for (int i = 0; i<size; i++) {
		Nod* temp = hashTabel[i]->next;
		while (temp) {
			free(temp->info.idGradinita);
			free(temp->info.stradaGradinita);
			free(temp->info.numeGradinita);
			Nod* aux = temp;
			free(aux);
		}
		free(hashTabel[i]);
		hashTabel[i] = 0;
	}
  }
int main() {
 	Nod** hashTable; 
	hashTable = ( Nod**)malloc(sizeof( Nod)*DIM);
	for (int i = 0; i < DIM; i++)
		hashTable[i] = 0;

	Gradinita g;
	FILE* f;
	f = fopen("gradinite.txt", "r");
	char* token;
	char buffer[100];
	while (fgets(buffer, sizeof(buffer), f)) {
		token = strtok(buffer, ",");
		g.idGradinita = (char*)malloc(sizeof(char)*(strlen(token)));
		strcpy(g.idGradinita, token);

		token = strtok(NULL, ",");
		g.numeGradinita = (char*)malloc(sizeof(char)*(strlen(token)));
		strcpy(g.numeGradinita, token);

		token = strtok(NULL, ",");
		g.stradaGradinita = (char*)malloc(sizeof(char)*(strlen(token)));
		strcpy(g.stradaGradinita, token);

		token = strtok(NULL, ",");
		g.anInfiintare = atoi(token);

		token = strtok(NULL, ",");
		g.nrCopii = atoi(token);

		inserareHash(hashTable, g, DIM);

	}
  // stergereElementTabela(hashTable, "2S",DIM);
  modificareElement(hashTable,"J56","BH1",DIM);
  // stergereTabela(hashTable, DIM);
  parseHash(hashTable, DIM);
  ListaDubla l;
  l.prim=NULL;
  l.ultim=NULL;
  // l=inserareDinHash(hashTable, DIM);
  // afisareListaIncSf(l);
  return 0;
}