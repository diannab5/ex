//#include <stdlib.h>

//#include<malloc.h>
//#include <string.h> //strcpy, strlen
//#include <stdio.h> //printf, scanf

#include<iostream>
#pragma warning (disable:4996)

struct Proces
{
	int pid; //unic in multimea proceselor
	char* denumire;
	char* descriere;
	int mem_ocupata_KB;
	char* user;
};

// ARBORE BINAR de CAUTARE

// informatia utila
// adresa fiu stanga
// adresa fiu dreapta

struct nod
{
	Proces info;
	nod* stanga;
	nod* dreapta;
};

Proces creareProces(int id, const char *den, const char* desc, int mem, const char* user)
{
	Proces pNou;
	pNou.pid = id;

	pNou.denumire = (char*)malloc(sizeof(char)*(strlen(den) + 1));
	strcpy(pNou.denumire, den);

	pNou.descriere = (char*)malloc(sizeof(char)*(strlen(desc) + 1));
	strcpy(pNou.descriere, desc);

	pNou.mem_ocupata_KB = mem;

	pNou.user = (char*)malloc(sizeof(char)*(strlen(user) + 1));
	strcpy(pNou.user, user);

	return pNou;
}

void afisareProces(Proces p)
{
	printf("%d, %s, %s, %d, %s\n", p.pid, p.denumire, p.descriere, p.mem_ocupata_KB, p.user);
}

//returnam un nod* = radacina !!!
// verificam daca avem radacina
// daca este NULL: alocam un nod nou, ii setam atributele, radacina devine nou sau returnam nou 
// daca nu: verificam daca id-ul este mai mic => radacina->stanga = inserare(radacina->stanga,...)
// daca id-ul este mai mare => radacina->dreapta = inserare(radacina->dreapta,...)
// returnam radacina

nod* inserareInArbore(nod* root, Proces p)
{
	if (root == NULL)
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = p;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		root = nou;
	}
	else
	{
		if (p.pid < root->info.pid)
			root->stanga = inserareInArbore(root->stanga, p);
		else if (p.pid > root->info.pid)
			root->dreapta = inserareInArbore(root->dreapta, p);

		return root;
	}
}

nod *inserareNod(nod *r, Proces p, int &err)
{
	if (r == NULL) {
		nod* nou = new nod;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		nou->info = p;
		r = nou;
	}
	else if (r->info.pid == p.pid) err = 1;
	else if (r->info.pid > p.pid)
		r->stanga = inserareNod(r->stanga, p, err);
	else
		r->dreapta = inserareNod(r->dreapta, p, err);
	return r;
}

// AFISARE
// inordine   - SRD
// postordine - SDR
// preordine  - RSD

void afisareInOrdine(nod* root)
{
	if (root)
	{
		afisareInOrdine(root->stanga);
		afisareProces(root->info);
		afisareInOrdine(root->dreapta);
	}
}

void afisarePreordine(nod* root)
{
	if (root)
	{
		afisareProces(root->info);
		afisarePreordine(root->stanga);
		afisarePreordine(root->dreapta);
	}

}

void nrDescendenti(nod* r, int id, int &nrd) {
	if (r)
	{
		if (r->info.pid == id)
		{
			if (r->stanga && r->dreapta)
			{
				nrd = 2;
			}
			else
			{
				if (r->stanga)
				{
					nrd = 1;
				}
				else
				{
					if (r->dreapta)
					{
						nrd = 1;
					}
					else
					{
						nrd = 0;
					}
				}
			}
		}
		nrDescendenti(r->stanga, id, nrd);
		nrDescendenti(r->dreapta, id, nrd);
	}
}

void majorareMemorie(nod* root, double procent)
{
	if (root)
	{
		root->info.mem_ocupata_KB += procent * root->info.mem_ocupata_KB;
		majorareMemorie(root->stanga, procent);
		majorareMemorie(root->dreapta, procent);
	}

}

int memorieOcupata(nod* root)
{
	if (root)
	{
		return
			sizeof(root->info.pid) +
			sizeof(root->info.mem_ocupata_KB) +
			sizeof(char)*strlen(root->info.denumire) +
			sizeof(char)*strlen(root->info.descriere) +
			sizeof(char)*strlen(root->info.user) +
			3 * sizeof(char*) +
			memorieOcupata(root->stanga) +
			memorieOcupata(root->dreapta);
	}
	else
		return 0;
}

int determinareVolumTotalABC(nod* root)
{
	if (root)
	{
		return sizeof(root->info.pid) + sizeof(root->info.mem_ocupata_KB) + sizeof(char)*strlen(root->info.denumire) + sizeof(char)*strlen(root->info.descriere) + sizeof(char)*strlen(root->info.user) + determinareVolumTotalABC(root->stanga) + determinareVolumTotalABC(root->dreapta);
	}
	else
		return 0;
}

void afisareProcesDupaNivel(nod* root, int nivel)
{
	if (root)
	{
		if (nivel == 1)
		{
			afisareProces(root->info);

		}
		else
		{
			nivel--;
			afisareProcesDupaNivel(root->stanga, nivel);
			afisareProcesDupaNivel(root->dreapta, nivel);
		}
	}

}

void nrNoduriPeNivel(nod* root, int nivelCautat, int nivelCurent, int* nrNoduri)
{
	if (root)
	{
		if (nivelCautat == nivelCurent)
		{
			(*nrNoduri)++;
		}
		else
		{
			nivelCurent++;
			nrNoduriPeNivel(root->stanga, nivelCautat, nivelCurent, nrNoduri);
			nrNoduriPeNivel(root->dreapta, nivelCautat, nivelCurent, nrNoduri);
		}
	}

}

void inserareinVector(nod* root, int nivelCautat, int nivelCurent, int** rezultat, int* contor)
{
	if (root)
	{
		if (nivelCautat == nivelCurent)
		{
			(*rezultat)[(*contor)++] = root->info.pid;
		}
		else
		{
			nivelCurent++;
			inserareinVector(root->stanga, nivelCautat, nivelCurent, rezultat, contor);
			inserareinVector(root->dreapta, nivelCautat, nivelCurent, rezultat, contor);
		}
	}
}

int* vectorId(nod* root, int nivelCautat, int nivelCurent, int* nrNoduri, int* contor)
{
	nrNoduriPeNivel(root, nivelCautat, nivelCurent, nrNoduri);

	int* rezultat = NULL;

	if ((*nrNoduri) > 0)
	{
		rezultat = (int*)malloc(sizeof(int)*(*nrNoduri));
		inserareinVector(root, nivelCautat, nivelCurent, &rezultat, contor);
	}

	return rezultat;

}

nod* cautareMaxim(nod* root)
{
	if (root)
	{
		nod* temp = root;
		while (temp->dreapta)
			temp = temp->dreapta;
		return temp;

	}
	else return NULL;

}

// desi se modifica, radacina va fi returnata 

nod* stergereNod(nod* root, int idCautat)
{
	if (root)
	{
		if (root->info.pid == idCautat)
		{
			if (root->stanga == NULL)
			{
				nod* temp = root->dreapta;
				free(root->info.denumire);
				free(root->info.descriere);
				free(root->info.user);
				root = temp;
			}
			else
				if (root->dreapta == NULL)
				{
					nod* temp = root->stanga;
					free(root->info.denumire);
					free(root->info.descriere);
					free(root->info.user);
					root = temp;
				}
				else
				{
					nod* maxim = cautareMaxim(root->stanga);
					Proces aux = root->info;
					root->info = maxim->info;
					maxim->info = aux;
					root->stanga = stergereNod(root->stanga, idCautat);
				}
		}
		else
			if (idCautat < root->info.pid)
				root->stanga = stergereNod(root->stanga, idCautat);
			else if (idCautat > root->info.pid)
				root->dreapta = stergereNod(root->dreapta, idCautat);
	}
	return root;
}

// Radacina se MODIFICA => **
Proces extragereProces(nod** root, int idCautat)
{
	if (*root)
	{
		if ((*root)->info.pid == idCautat)
		{
			Proces p=creareProces((*root)->info.pid, (*root)->info.denumire, (*root)->info.descriere, (*root)->info.mem_ocupata_KB, (*root)->info.user);
			if ((*root)->stanga == NULL)
			{
				nod* temp = (*root)->dreapta;
				free((*root)->info.denumire);
				free((*root)->info.descriere);
				free((*root)->info.user);
				(*root) = temp;
			}
			else
				if ((*root)->dreapta == NULL)
				{
					nod* temp = (*root)->stanga;
					free((*root)->info.denumire);
					free((*root)->info.descriere);
					free((*root)->info.user);
					(*root) = temp;
				}
				else
				{
					nod* maxim = cautareMaxim((*root)->stanga);
					Proces aux = (*root)->info;
					(*root)->info = maxim->info;
					maxim->info = aux;
					return extragereProces(&(*root)->stanga, idCautat);
				}
			return p;

		}
		else
			if (idCautat < (*root)->info.pid)
				return extragereProces(&(*root)->stanga, idCautat);
			else if (idCautat > (*root)->info.pid)
				return extragereProces(&(*root)->dreapta, idCautat);
	}
	else
	{
		return creareProces(-1, "", "", 0, "");
	}
}

struct nodLista
{
	Proces info;
	nodLista* next;
};

nodLista* inserareInLista(nodLista* root, Proces p)
{
	if (root)
	{
		nodLista* temp = root;
		nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
		nou->info = p;
		nou->next = temp;
		return nou;
	}
	else
	{
		nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
		nou->info = p;
		nou->next = NULL;
		root = nou;
	}
	return root;
}

nodLista* copiereProcese(nod* root,nodLista* lista)
{
	if (root)
	{
		
		if (root->info.mem_ocupata_KB > 130000)
		{
			lista=inserareInLista(lista, root->info);
		}
		lista=copiereProcese(root->stanga,lista);
		lista=copiereProcese(root->dreapta,lista);
		
			
	}
	return lista;
}

void afisareLista(nodLista* root)
{
	if (root)
	{
		nodLista* temp = root;
		while (temp)
		{
			afisareProces(temp->info);
			temp = temp->next;
		}
	}
}

void numarFrunze(nod* root,int* nrFrunze)
{
	if (root)
	{
		if (root->stanga == NULL && root->dreapta == NULL)
		{
			(*nrFrunze)++;
		}
		else
		{
			numarFrunze(root->stanga, nrFrunze);
			numarFrunze(root->dreapta, nrFrunze);
		}
	}
}

void main() {

	nod *root = NULL;
	int insErr;

	// vector de task-uri
	int nrp = 8; // numar de procese
	Proces * vProcese = (Proces*)malloc(nrp * sizeof(Proces));

	vProcese[0] = creareProces(23, "chrome.exe", "Google Chrome", 132696, "gigel");
	vProcese[1] = creareProces(19, "explorer.exe", "Windows Explorer", 64765, "gigel");
	vProcese[2] = creareProces(52, "devenv.exe *32", "Microsoft Visual Studio 2012", 141028, "gigel");
	vProcese[3] = creareProces(21, "chrome.exe", "Google Chrome", 34760, "gigel");
	vProcese[4] = creareProces(73, "chrome.exe", "Google Chrome", 2836, "gigel");
	vProcese[5] = creareProces(15, "chrome.exe", "Google Chrome", 2836, "gigel");
	vProcese[6] = creareProces(14, "chrome.exe", "Google Chrome", 2836, "gigel");
	vProcese[7] = creareProces(16, "chrome.exe", "Google Chrome", 2836, "gigel");

	for (int i = 0; i < nrp; i++) {
		insErr = 0;
		root = inserareNod(root, vProcese[i], insErr);
		if (insErr) {
			printf("\n Procesul cu id %d exista in arbore.\n", vProcese[i].pid);
			free(vProcese[i].denumire);
			free(vProcese[i].descriere);
			free(vProcese[i].user);
		}
		else
			printf("\n Procesul %s a fost inserat\n", vProcese[i].denumire);
	}

	//afisareArbore
	afisareInOrdine(root);

	// determinare numar de descendenti pentru un proces specificat prin id
	int numar_descendenti = 0;
	nrDescendenti(root, 52, numar_descendenti);
	printf("\n Nr descendenti %d \n", numar_descendenti);

	printf("\n Memorie ocupata: %d \n", memorieOcupata(root));

	printf("\n Memorie ocupata Codrin : %d \n", determinareVolumTotalABC(root));

	majorareMemorie(root, 0.15);
	printf("\n\n");
	afisareInOrdine(root);
	printf("\n\n");
	afisareProcesDupaNivel(root, 2);

	int contor = 0;
	int nrNoduri = 0;
	int* rezultat = vectorId(root, 1, 0, &nrNoduri, &contor);
	for (int i = 0; i < nrNoduri; i++)
	{
		printf(" %d		", rezultat[i]);
	}

	//printf("\n Nr noduri pe nivel: %d\n", nrNoduriPeNivel(root, 1, 0));
	
	printf("\n\nArbore dupa stergere: \n");
	stergereNod(root, 19);
	afisarePreordine(root);
	
	printf("\n\nArbore dupa extragere: \n");
	Proces p = extragereProces(&root, 15);
	afisareProces(p);
	printf("\n\n");
	afisarePreordine(root);
	
	nodLista* lista = NULL;
	printf("\n Lista: \n");
	lista=copiereProcese(root,lista);
	afisareLista(lista);

	int nrFrunze = 0;
	numarFrunze(root, &nrFrunze);
	printf("\nNumar frunze: %d\n", nrFrunze);
}

