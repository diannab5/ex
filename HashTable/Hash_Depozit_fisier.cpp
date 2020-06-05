#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#include<conio.h>

#define DIM 100
#define LINESIZE 256

struct Depozit {
	char* idDepozit;
	int capacitate, nrTipuriCereale;
	char ** listaCereale;
	float procentIncarcare;
};

struct Nod {
	Depozit depo;
	Nod *next;
};

int calculPozitie(Depozit d, int size) {
	int s = 0;
	for (unsigned int i = 0; i<strlen(d.idDepozit); i++)
		s += d.idDepozit[i];

	return s % size;
}

Nod* inserareLista(Nod *p, Depozit d) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));

	nou->depo.idDepozit = d.idDepozit;
	nou->depo.capacitate = d.capacitate;
	nou->depo.nrTipuriCereale = d.nrTipuriCereale;
	nou->depo.listaCereale = d.listaCereale;
	nou->depo.procentIncarcare = d.procentIncarcare;

	nou->next = p;

	return nou;
}


void inserareHTable(Nod** hTab, Depozit d, int sizeHT) {
	int k;
	k = calculPozitie(d, sizeHT);

	hTab[k] = inserareLista(hTab[k], d);
}

int nrDepozite(Nod** hTab, int size, int c) {
	int s = 0;
	for (int i = 0; i<size; i++)
		if (hTab[i]) {
			Nod* tmp = hTab[i];
			while (tmp) 
			{
				if (tmp->depo.capacitate > c)
					s += 1;
				tmp = tmp->next;
			}
		}

	return s;
}

int capacitate(Nod** hTab, int dim)
{
	int suma = 0;
	for (int i = 0; i < dim; i++)
	{
		if (hTab[i])
		{
			Nod* temp = hTab[i];
			while (temp)
			{
				suma +=  temp->depo.capacitate;
				temp = temp->next;
			}
		}
	}
	return suma;
}

void crestere(Nod** hash, int dim, const char* id)
{
	for (int i = 0; i < dim; i++)
	{
		if (hash[i])
		{
			Nod* temp = hash[i];
			while (temp)
			{
				if (stricmp(temp->depo.idDepozit, id) == 0)
				{
					temp->depo.procentIncarcare += 10;
					if (temp->depo.procentIncarcare > 100)
						temp->depo.procentIncarcare = 100;
				}
				temp = temp->next;
			}
		}
	}
}

Nod* extrageGrau(Nod** hash)
{
	Nod* cap = NULL;
	for (int i = 0; i < DIM; i++)
	{
		if (hash[i])
		{
			Nod* temp = hash[i];
			while (temp)
			{
				for (int j=0; j<temp->depo.nrTipuriCereale; j++)
					if (stricmp(temp->depo.listaCereale[j], "grau") == 0)
					{
						cap = inserareLista(cap, temp->depo);
						j = temp->depo.nrTipuriCereale+1;
					}
				temp = temp->next;
			}
		}
	}
	return cap;
}

void afisareDepozit(Depozit d)
{
	printf("%s %d %d ", d.idDepozit, d.capacitate, d.nrTipuriCereale);
	for (int i = 0; i < d.nrTipuriCereale; i++)
		printf("%s ", d.listaCereale[i]);
	printf("%5.2f\n", d.procentIncarcare);
}

void afisareLista(Nod* inceput)
{
	Nod* temp = inceput;
	while (temp)
	{
		afisareDepozit(temp->depo);
		temp = temp->next;
	}
}

void afisareHash(Nod** hash, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		if (hash[i])
		{
			printf("%d\n", i);
			afisareLista(hash[i]);
			printf("\n");
		}
	}
}

void main() {

	Nod **HTable;
	Depozit tmpDepozit;

	HTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	for (int i = 0; i<DIM; i++)
		HTable[i] = 0;

	FILE * f;
	f = fopen("Depozite.txt", "r");

	char *token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		tmpDepozit.idDepozit = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(tmpDepozit.idDepozit, token);

		token = strtok(NULL, sep_list);
		tmpDepozit.capacitate = atoi(token);

		token = strtok(NULL, sep_list);
		tmpDepozit.nrTipuriCereale = atoi(token);

		tmpDepozit.listaCereale = (char**)malloc(tmpDepozit.nrTipuriCereale * sizeof(char*));

		for (int i = 0; i<tmpDepozit.nrTipuriCereale; i++) {
			token = strtok(NULL, sep_list);
			tmpDepozit.listaCereale[i] = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(tmpDepozit.listaCereale[i], token);
		}

		token = strtok(NULL, sep_list);
		tmpDepozit.procentIncarcare = atof(token);

		inserareHTable(HTable, tmpDepozit, DIM);
	}

	afisareHash(HTable, DIM);
	fclose(f);

	printf("Nr depozite: %d ", nrDepozite(HTable, DIM, 100));
	printf("\nCapacitate: %d", capacitate(HTable, DIM));
 
	crestere(HTable, DIM, "10AC");


	afisareHash(HTable, DIM);

	printf("\nAfisare liste cu grau:\n");
	Nod* lista = extrageGrau(HTable);
	afisareLista(lista);

	_getch();
}
