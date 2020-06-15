#include<stdio.h>
#include<malloc.h>
#include<string.h>


struct Angajat {
	int id;
	char* nume;
	float salariu;
	char* regiune;
	float oreLucrate;
};

struct nod {
	Angajat info;
	nod* next;
	nod* prev;
};

struct ListaDubla {
	nod* prim;
	nod* ultim;
};

void afisareAngajat(Angajat a)
{
	printf(" %d. %s are salariul %5.2f, lucreaza in regiunea %s si are %5.2f ore lucrate\n", a.id, a.nume, a.salariu, a.regiune, a.oreLucrate);
}

Angajat citireAngajatDinFisier(FILE*& f) {
	Angajat a;

	fscanf(f, "%d", &a.id);

	char buffer[50];
	fscanf(f, "%s", buffer);
	a.nume = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(a.nume, buffer);

	fscanf(f, "%f", &a.salariu);

	char buffer2[50];
	fscanf(f, "%s", buffer2);
	a.regiune = (char*)malloc(sizeof(char)*(strlen(buffer2) + 1));
	strcpy(a.regiune, buffer2);

	fscanf(f, "%f", &a.oreLucrate);

	return a;
}
Angajat creareAngajat(int id, const char* nume, float salariu, const char* regiune, float oreLucrate) {
	Angajat a;
	a.id = id;
	a.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(a.nume, nume);
	a.salariu = salariu;
	a.regiune = (char*)malloc(sizeof(char)*(strlen(regiune) + 1));
	strcpy(a.regiune, regiune);
	a.oreLucrate = oreLucrate;
	return a;
}

void inserareListaDubla(ListaDubla &lista, Angajat a) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = a;
	nou->next = NULL;
	nou->prev = lista.ultim;
	if (lista.ultim) {
		lista.ultim->next = nou;
		lista.ultim = nou;
	}
	else {
		lista.ultim = nou;
		lista.prim = nou;
	}
}

void afisareListaInceputSfarsit(ListaDubla lista) {
	if (lista.prim) {
		nod* temp = lista.prim;
		while (temp) {
			afisareAngajat(temp->info);
			temp = temp->next;
		}
	}
}

void afisareListaSfarsitInceput(ListaDubla lista) {
	if (lista.prim) {
		nod* temp = lista.ultim;
		while (temp) {
			afisareAngajat(temp->info);
			temp = temp->prev;
		}
	}
}


void stergereNodDupaNume(ListaDubla &lista, const char*nume) {
	if (lista.prim) {
		nod*p = lista.prim;
		while (p&& strcmp(p->info.nume, nume) != 0) {
			p = p->next;
		}
		if (p) {
			if (p->prev) {
				p->prev->next = p->next;
				if (p->next) {
					p->next->prev = p->prev;
				}
				else {
					lista.ultim = p->prev;
				}
			}
			else {
				p->next->prev = NULL;
				lista.prim = p->next;
			}
			free(p->info.nume);
			free(p->info.regiune);
			free(p);
		
		}
		
	}
}

void dezalocareLista(ListaDubla &lista) {
	if (lista.prim) {
		nod* temp = lista.prim;
		while (temp) {
			nod* aux = temp->next;
			free(temp->info.nume);
			free(temp->info.regiune);
			free(temp);
			temp = aux;
		}
		lista.prim = NULL;
		lista.ultim = NULL;
	}
}

struct nodArbore {
	Angajat info;
	nodArbore* dr;
	nodArbore* st;
};

nodArbore* inserareArbore( nodArbore* rad,Angajat a) {
	if (rad)
	{
		if (rad->info.id > a.id)
		{
			rad->st = inserareArbore(rad->st, a);
		}
		else
		{
			rad->dr = inserareArbore(rad->dr, a);
		}
		return rad;
	}
	else
	{
		nodArbore* nou = (nodArbore*)malloc(sizeof(nodArbore));
		nou->dr = NULL;
		nou->st = NULL;
		nou->info = a;
		return nou;
	}
}

void copiazaAngajatDinListaInArbore(nodArbore* &rad, ListaDubla lista) {
	if (lista.prim) {
		nod* p = lista.prim;
		while (p) {
			if (p->info.id > 10) {
				Angajat a = creareAngajat(p->info.id, p->info.nume, p->info.salariu, p->info.regiune, p->info.oreLucrate);
				rad = inserareArbore(rad, a);
			}
			p = p->next;
		}
	}
}

void traversareArboreInordine(nodArbore* rad) {
	if (rad) {
		traversareArboreInordine(rad->st);
		afisareAngajat(rad->info);
		traversareArboreInordine(rad->dr);
	}
}

void dezalocareArbore(nodArbore* &rad) {
	if (rad) {
		dezalocareArbore(rad->st);
		dezalocareArbore(rad->dr);
		free(rad->info.nume);
		free(rad->info.regiune);
		free(rad);
		rad = NULL;
	}
}

int calculeazaNrNoduriCareTrbCopiate(nodArbore*radacina, int cheie) {
	int numar = 0;
	if (radacina) {
		if (radacina->info.id == cheie || radacina->info.id<cheie) {
			numar++;
			numar += calculeazaNrNoduriCareTrbCopiate(radacina->dr, cheie);
		}
		else if (radacina->info.id == cheie || radacina->info.id > cheie) {
			numar += calculeazaNrNoduriCareTrbCopiate(radacina->st, cheie);
		}

	}
	return numar;
}



void afisareAngajatDupaNivel(nodArbore* root, int nivel)
{
	if (root)
	{
		if (nivel == 1)
		{
			afisareAngajat(root->info);

		}
		else
		{
			nivel--;
			afisareAngajatDupaNivel(root->st, nivel);
			afisareAngajatDupaNivel(root->dr, nivel);
		}
	}

}

void main() {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	FILE* fisier;
	fisier = fopen("angajati.txt", "r");
	if (fisier) {
		while (!feof(fisier)) {
			Angajat a;
			a = citireAngajatDinFisier(fisier);
		     inserareListaDubla(lista, a);
		}
		fclose(fisier);
	}
	
	printf("\nLista inainte de stergere:\n");
	afisareListaInceputSfarsit(lista);

	printf("\nDupa stergere:\n");
	stergereNodDupaNume(lista, "Inna");
	afisareListaInceputSfarsit(lista);


    printf("\nCopiaza in arbore toti angajatii cu id-ul mai mare decat 10\n");
	nodArbore* rad = NULL;
	copiazaAngajatDinListaInArbore(rad, lista);
	printf("\nAngajatii copiati in arbore\n");
	traversareArboreInordine(rad);
	printf("\n\n");
	printf("\n\nAfisare angajati dupa nivel\n");
	afisareAngajatDupaNivel(rad, 2);
	printf("\n\n");
	
	int cheie = 30;
	int index = 0;
	printf("\nCopiaza noduri din arbore de la radacina pana la nodul %d\n",cheie);
	int nrNoduriDeCopiat = calculeazaNrNoduriCareTrbCopiate(rad, cheie);
	printf("%d", nrNoduriDeCopiat);
	

	//dezalocareArbore(rad);
	

}
