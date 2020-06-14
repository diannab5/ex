#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Persoana {
	int id;
	char* nume;
	
};

Persoana crearePersoana(int id, const char* nume) {
	Persoana p;
	p.id = id;
	p.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(p.nume, nume);
	return p;
}

void afisarePersoana(Persoana p) {
	printf("\n Id: %d, nume %s\n", p.id, p.nume);

	/*for (int i = 0; i < s.nrNote; i++)
	{
		printf("%d, ", s.vectorNote[i]);
	}*/
}
//lista circulara contine 2 pointeri ce ponteaza catre urmatorul si anteriorul nod
//primul nod pointeaza catre el insusi, la afisare, stergere sau introducere date trebuie introdus un nod TEMP ce are rol de counter
//fara TEMP se produce infinite looop....

struct nod {
	Persoana info;
	nod* next;
	nod* prev;
};

nod* initializareNod(Persoana p, nod* next, nod* prev) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = p;//shallow
	nou->next = next;
	nou->prev = prev;
	return nou;
}

struct ListaDubla {
	nod* prim;
	nod* ultim;
};

ListaDubla inserareLaInceput(ListaDubla lista, Persoana p) {
	nod* nou = initializareNod(p, NULL, NULL);
	if (lista.prim) {
		nou->next = lista.prim;
		nou->prev = lista.ultim;
		lista.prim->prev = nou;
		lista.ultim->next = nou;
		lista.prim = nou;
	}
	else {
		lista.prim = nou;
		lista.ultim = nou;
		nou->next = nou;
		nou->prev = nou;
	}
	return lista;
}

ListaDubla inserareLaSfarsit(ListaDubla lista, Persoana p) {
	nod* nou = initializareNod(p, NULL, NULL);
	if (lista.ultim) {
		nou->prev = lista.ultim;
		lista.ultim->next = nou;
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.ultim = nou;
	}
	else {
		lista.prim = nou;
		lista.ultim = nou;
	}
	return lista;
}

void afisareListaDubla(ListaDubla lista) {
	nod* temp = lista.prim;
	if (lista.prim)
	{
		while (temp->next != lista.prim) {
			afisarePersoana(temp->info);
			temp = temp->next;
		}
		afisarePersoana(temp->info);
	}
	
}

void stergereListaDublaCIrculara(ListaDubla &l) {
	if (l.prim)
	{
		nod* temp = l.prim;
		while (l.prim->next != temp) {
			nod* temp2 = l.prim;
			l.prim = l.prim->next;
			free(temp2->info.nume);
			free(temp2);
		}
		free(l.prim->info.nume);
		free(l.prim);
		l.prim = l.ultim = NULL;
	}
	
}

Persoana extragerePersoanaDinLista(ListaDubla &l, const char* numeCautat) {
	if (l.prim)
	{
		if (strcmp(l.prim->info.nume, numeCautat) == 0) 
		{
			Persoana rezultat = crearePersoana(l.prim->info.id, l.prim->info.nume);//deep copy
			nod* temp = l.prim;
			l.prim = l.prim->next;
			l.ultim->next = l.prim;
			free(temp->info.nume);
			free(temp);
			return rezultat;
		}
		else {
			nod* temp = l.prim->next;
			while (temp->next != l.prim)
			{
				if (strcmp(temp->info.nume, numeCautat) == 0) {
					Persoana rezultat = crearePersoana(temp->info.id, temp->info.nume);//deep copy
					nod* temp2 = temp;
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					temp = temp->next;
					free(temp2->info.nume);
					free(temp2);
					return rezultat;
				}
				temp = temp->next;
			}
			if (strcmp(temp->info.nume, numeCautat) == 0) {
				Persoana rezultat = crearePersoana(temp->info.id, temp->info.nume);//deep copy
				nod* temp2 = temp;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp = l.prim;
				free(temp2->info.nume);
				free(temp2);
				return rezultat;
			}
			else
			{
				throw "Nu exista persoana cautata in lista!";
			}
		}
	}
	else
	{
		throw "lista este goala";
	}
}


Persoana citirePersoanaFisier(FILE*& f) {
	Persoana p;
	fscanf(f, "%d", &p.id);
	char buffer[50];
	fscanf(f, "%s", buffer);
	p.nume = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(p.nume, buffer);

	/*
	s.vectorNote = (int*)malloc(sizeof(int)*s.nrNote);
	for (int i = 0; i < s.nrNote; i++)
	{
		fscanf(f, "%d", &s.vectorNote[i]);
	}
	*/
	return p;
}
void main() {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	FILE* fisier;
	fisier = fopen("persoane.txt", "r");
	if (fisier) {
		while (!feof(fisier)) {
			Persoana p;
		     p = citirePersoanaFisier(fisier);
			 lista=inserareLaSfarsit(lista, p);
		}
		fclose(fisier);
	}
	afisareListaDubla(lista);
	Persoana cautata = extragerePersoanaDinLista(lista, "Irina");
	afisarePersoana(cautata);
	printf("\nAfisare dupa stergere");
	afisareListaDubla(lista);
	

	

}