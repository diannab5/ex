#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct Factura
{
	int numarFactura;
	char* dataEmiterii;
	char* denumireClient;
	float valoareFactura;
	int nrProduse;
};

struct nod
{
	Factura info;
	nod* dreapta;
	nod* stanga;
};

Factura creareFactura(int numar, const char* data,const char* nume, float valoare, int nrprod)
{
	Factura f;
	f.numarFactura = numar;

	f.dataEmiterii = (char*)malloc(sizeof(char)*(strlen(data) + 1));
	strcpy(f.dataEmiterii, data);

	f.denumireClient = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(f.denumireClient, nume);

	f.valoareFactura = valoare;
	f.nrProduse = nrprod;

	return f;
}

void afisareFactura(Factura f)
{
	printf("\n%d, %s, %s, %5.2f, %d\n", f.numarFactura, f.dataEmiterii, f.denumireClient, f.valoareFactura, f.nrProduse);
}

nod* inserareInArbore(nod* root, Factura f)
{
	if (root)
	{
		if (f.numarFactura < root->info.numarFactura)
			root->stanga = inserareInArbore(root->stanga, f);
		else if (f.numarFactura > root->info.numarFactura)
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

void afisarePreordine(nod* root)
{
	if (root)
	{
		afisareFactura(root->info);
		afisarePreordine(root->stanga);
		afisarePreordine(root->dreapta);
	}
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

void afisarepeNivele(nod* root, int nivel)
{
	if (root)
	{
		if (nivel == 1)
		{
			afisareFactura(root->info);
		}
		else
		{
			nivel--;
			afisarepeNivele(root->stanga, nivel);
			afisarepeNivele(root->dreapta, nivel);
		}
	}
}

void afisareNivelcuNivel(nod*root)
{
	printf("\nNivel 1: \n");
	afisarepeNivele(root, 1);
	printf("\nNivel 2: \n");
	afisarepeNivele(root, 2);
	printf("\nNivel 3: \n");
	afisarepeNivele(root, 3);

}

void numarareFacturi(nod* root, const char* nume, int* nrFacturi)
{
	if (root)
	{
		if (strcmp(root->info.denumireClient, nume) == 0)
		{
			(*nrFacturi)++;
		}
		numarareFacturi(root->stanga, nume, nrFacturi);
		numarareFacturi(root->dreapta, nume, nrFacturi);
	}
}

void majorareValoare(nod* root, float suma)
{
	if (root)
	{
		root->info.valoareFactura += suma;
		majorareValoare(root->stanga, suma);
		majorareValoare(root->dreapta, suma);
	}
}

void main()
{
	nod* root = NULL;
	root = inserareInArbore(root, creareFactura(23, "2018.06.13", "La Nicusor", 333.62, 3));
	root = inserareInArbore(root, creareFactura(19, "2018.06.13", "La Dana", 333.62, 3));
	root = inserareInArbore(root, creareFactura(52, "2018.06.13", "La Dana", 333.62, 3));
	root = inserareInArbore(root, creareFactura(21, "2018.06.13", "La Nicusor", 333.62, 3));
	root = inserareInArbore(root, creareFactura(73, "2018.06.13", "La Nicusor", 333.62, 3));

	//afisarePreordine(root);
	//afisareInOrdine(root);
	//afisareNivelcuNivel(root);
	int nrFacturi = 0;
	numarareFacturi(root, "La Nicusor", &nrFacturi);
	printf("\nNumar facturi: %d\n", nrFacturi);
	afisareInOrdine(root);
	majorareValoare(root, 2.5);
	printf("\n\n");
	afisareInOrdine(root);
}