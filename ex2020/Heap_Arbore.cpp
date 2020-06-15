#include<malloc.h>
#include"stdlib.h"
#include"string.h"
#include"stdio.h"

struct Factura {
	int nrZilePanaLaScadenta; //prioritate
	int idFactura;
	char* numeFactura;
	char* furnizorFactura;
	float sumaPlata;
};

void afisareFactura(Factura f) {
	printf("\nNr zile pana la scadenta %d, id: %d, nume: %s, furnizor: %s, suma de plata: %5.2f\n", f.nrZilePanaLaScadenta, f.idFactura, f.numeFactura, f.furnizorFactura, f.sumaPlata);
}

Factura citireDinFisierFactura(FILE* &f) {
	Factura factura;
	fscanf(f, "%d", &factura.nrZilePanaLaScadenta);
	fscanf(f, "%d", &factura.idFactura);
	char buffer[50];
	fscanf(f, "%s", buffer);
	factura.numeFactura = (char*)malloc(sizeof(factura.numeFactura)*(strlen(buffer) + 1));
	strcpy(factura.numeFactura, buffer);

	char buffer2[50];
	fscanf(f, "%s", buffer2);
	factura.furnizorFactura = (char*)malloc(sizeof(factura.furnizorFactura)*(strlen(buffer2) + 1));
	strcpy(factura.furnizorFactura, buffer2);
	fscanf(f, "%f", &factura.sumaPlata);

	return factura;

}

struct Heap
{
	int dimensiune;
	Factura* vector;
};

Heap initHeap(int dimensiune) {
	if (dimensiune>0)
	{
		Heap h;
		h.dimensiune = dimensiune;
		h.vector = (Factura*)malloc(sizeof(Factura)*dimensiune);
		return h;
	}
}

void filtrareHeap(Heap h, int pozitie) {
	if (h.dimensiune)
	{
		int max = pozitie;
		int pozST = 2 * pozitie + 1;
		int pozDR = 2 * pozitie + 2;
		if (pozST<h.dimensiune && h.vector[max].nrZilePanaLaScadenta<h.vector[pozST].nrZilePanaLaScadenta)
		{
			max = pozST;
		}
		if (pozDR<h.dimensiune && h.vector[max].nrZilePanaLaScadenta<h.vector[pozDR].nrZilePanaLaScadenta)
		{
			max = pozDR;
		}
		if (max != pozitie)
		{
			Factura temp = h.vector[pozitie];
			h.vector[pozitie] = h.vector[max];
			h.vector[max] = temp;
			if ((2 * max + 1) <h.dimensiune)
			{
				filtrareHeap(h, max);
			}
		}
	}
}

void afisareHeap(Heap h) {
	if (h.dimensiune>0)
	{
		for (int i = 0; i < h.dimensiune; i++)
		{
			afisareFactura(h.vector[i]);
		}
	}
}



void stergereHeap(Heap &h) {
	if (h.dimensiune)
	{
		for (int i = 0; i < h.dimensiune; i++)
		{
			free(h.vector[i].numeFactura);
			free(h.vector[i].furnizorFactura);
		}
		free(h.vector);
		h.dimensiune = 0;
	}
}

/*Factura extragereFacturi(Heap h) {
	if (h.dimensiune > 0) {
		for (int i = 0; i < h.dimensiune; i++) {
			if (h.vector[i].nrZilePanaLaScadenta < 3) {
				Factura f = h.vector[i];

			}
		}
	}
}*/


struct nod
{
	Factura info;
	nod* dreapta;
	nod* stanga;
};

nod* inserareInArbore(nod* root, Factura f)
{
	if (root)
	{
		if (f.nrZilePanaLaScadenta < root->info.nrZilePanaLaScadenta)
			root->stanga = inserareInArbore(root->stanga, f);
		else if (f.nrZilePanaLaScadenta > root->info.nrZilePanaLaScadenta)
			root->dreapta = inserareInArbore(root->dreapta, f);
	}
	else
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = f;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		root = nou;
	}

	return root;
}

void afisareInOrdine(nod* root)
{
	if (root)
	{
		afisareInOrdine(root->stanga);
		afisareFactura(root->info);
		afisareInOrdine(root->dreapta);
	}
}

Factura creareFactura(int nrZilePanaLaScadenta, int idFactura, const char* numeFactura, const char* furnizorFactura, float sumaPlata) {
	Factura f;
	f.nrZilePanaLaScadenta = nrZilePanaLaScadenta;
	f.idFactura = idFactura;
	f.numeFactura = (char*)malloc(sizeof(char)*(strlen(numeFactura) + 1));
	strcpy(f.numeFactura, numeFactura);
	f.furnizorFactura = (char*)malloc(sizeof(char)*(strlen(furnizorFactura) + 1));
	strcpy(f.furnizorFactura, furnizorFactura);
	f.sumaPlata = sumaPlata;
	return f;

}

Factura extragereHeap(Heap &h) {
		if (h.dimensiune > 0)
		{
			Factura rezultat = h.vector[0];
			Factura* vectorTemp = (Factura*)malloc(sizeof(Factura)*(h.dimensiune - 1));
			for (int i = 0; i < h.dimensiune - 1; i++)
			{
				vectorTemp[i] = h.vector[i + 1];
			}
			free(h.vector);
			h.dimensiune--;
			h.vector = vectorTemp;
			for (int i = (h.dimensiune - 2) / 2; i >= 0; i--)
			{
				filtrareHeap(h, i);
			}
			return rezultat;
		}
	}

nod* copiazaDinHeapInArbore(Heap &h) {
	if (h.dimensiune > 0)
	{
		nod* rad = NULL;
		while (h.dimensiune > 0)	
		{
			rad = inserareInArbore(rad, extragereHeap(h));
		}
				
		return rad;
			
	}
	
}

void main() {
	Factura factura;
	int dimensiuneInitiala = 10;
	Heap h = initHeap(dimensiuneInitiala);
	FILE* fisier = fopen("facturi.txt", "r");
	if (fisier)
	{
		for (int i = 0; i < dimensiuneInitiala; i++)
		{
			h.vector[i] = citireDinFisierFactura(fisier);
		}
	}
	fclose(fisier);
	afisareHeap(h);
	printf("\n\nSortare heap:");
	for (int i = (h.dimensiune - 2) / 2; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}
	afisareHeap(h);
	printf("\nConversie heap in arbore:");
	nod* rad = NULL;
	rad=copiazaDinHeapInArbore(h);
	afisareInOrdine(rad);
}