#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>



struct Factura
{
	int nrFactura;
	char* dataEmiterii;
	char* numeClient;
	float valFactura;
	int nrProduse;
};

Factura creareFactura(int nrFactura,const char* dataEmiterii,const char* numeClient, float valFactura, int nrProduse)
{
	Factura f;
	f.nrFactura = nrFactura;
	f.dataEmiterii = (char*)malloc(sizeof(char)*(strlen(dataEmiterii) + 1));
	strcpy(f.dataEmiterii, dataEmiterii);
	f.numeClient = (char*)malloc(sizeof(char)*(strlen(numeClient) + 1));
	strcpy(f.numeClient, numeClient);
	f.valFactura = valFactura;
	f.nrProduse = nrProduse;

	return f;
}
void afisareFactura(Factura f) {
	printf("\nFactura cu nr %d, emisa pe %s, client %s, in valoare de %5.2f lei are %d produse", f.nrFactura, f.dataEmiterii, f.numeClient, f.valFactura, f.nrProduse);
}

struct NOD {
	Factura info;
	NOD *st;
	NOD *dr;
};

NOD* rotireLaStanga(NOD* rad)
{
	if (rad)
	{
		NOD* aux = rad->dr;
		rad->dr = aux->st;
		aux->st = rad;
		return aux;
	}
	else
	{
		return rad;
	}
}
NOD* notireLaDreapta(NOD* rad)
{
	if (rad)
	{
		NOD* aux = rad->st;
		rad->st = aux->dr;
		aux->dr = rad;
		return aux;
	}
	else
	{
		return rad;
	}
}

int inaltimeArbore(NOD* rad)
{
	if (rad)
	{
		int inaltimeST = inaltimeArbore(rad->st);
		int inaltimeDR = inaltimeArbore(rad->dr);
		return(1 + (inaltimeST > inaltimeDR ? inaltimeST : inaltimeDR));
	}
	else
	{
		return 0;
	}
}
int calculareGradDeEchilibru(NOD* rad)
{
	if (rad)
	{
		int inaltimeST = inaltimeArbore(rad->st);
		int inaltimeDR = inaltimeArbore(rad->dr);
		return inaltimeST - inaltimeDR;
	}
	else
	{
		return 0;
	}
}

NOD* inserareInArboreAVL(NOD* rad, Factura f)
{
	if (rad)
	{
		if (rad->info.nrFactura > f.nrFactura)
		{
			rad->st = inserareInArboreAVL(rad->st, f);
		}
		else if (rad->info.nrFactura < f.nrFactura)
		{
			rad->dr = inserareInArboreAVL(rad->dr, f);
		}
		//inainte sa returnez verific echilibrul
		if (calculareGradDeEchilibru(rad) == 2)
		{
			if (calculareGradDeEchilibru(rad->st) != 1)
			{
				rad->st = rotireLaStanga(rad->st);
			}
			rad = notireLaDreapta(rad);
		}
		if (calculareGradDeEchilibru(rad) == -2)
		{
			if (calculareGradDeEchilibru(rad->dr) != -1)
			{
				rad->dr = notireLaDreapta(rad->dr);
			}
			rad = rotireLaStanga(rad);
		}
		return rad;
	}
	else
	{
		//cream nodul
		NOD* nou = (NOD*)malloc(sizeof(NOD));
		nou->dr = nou->st = NULL;
		nou->info = creareFactura(f.nrFactura, f.dataEmiterii, f.numeClient, f.valFactura, f.nrProduse);
		return nou;
	}
}

NOD* stergereDinAVL(NOD* rad, int nrFactura)
{
	if (rad)
	{
		if (rad->info.nrFactura > nrFactura)
		{
			rad->st = stergereDinAVL(rad->st, nrFactura);
		}
		else
		{
			if (rad->info.nrFactura < nrFactura)
			{
				rad->dr = stergereDinAVL(rad->dr, nrFactura);
			}
			else
			{
				//daca am gasit nod
				if (rad->st == NULL)
				{
					NOD* temp = rad->dr;
					free(rad->info.dataEmiterii);
					free(rad->info.numeClient);
					free(rad);
					rad = temp;
				}
				else if (rad->dr == NULL)
				{
					NOD* temp = rad->st;
					free(rad->info.dataEmiterii);
					free(rad->info.numeClient);
					free(rad);
					rad = temp;
				}
				else
				{
					//am 2 descendenti
					NOD* temp = rad->st;
					while (temp->dr)
						temp = temp->dr;
					//facem dezalocari
					free(rad->info.dataEmiterii);
					free(rad->info.numeClient);
					//mut ce am in temp in rad
					rad->info.nrFactura = temp->info.nrFactura;
					rad->info.dataEmiterii = (char*)malloc(sizeof(char)*(strlen(temp->info.dataEmiterii) + 1));
					strcpy(rad->info.dataEmiterii, temp->info.dataEmiterii);
					rad->info.numeClient = (char*)malloc(sizeof(char)*(strlen(temp->info.numeClient) + 1));
					strcpy(rad->info.numeClient, temp->info.numeClient);
					
					rad->info.nrProduse = temp->info.nrProduse;
					rad->info.valFactura = temp->info.valFactura;
					
					rad->st - stergereDinAVL(rad->st, temp->info.nrFactura);
				}

			}
		}
   }
	if (rad)
	{
		if (calculareGradDeEchilibru(rad) == 2)
		{
			if (calculareGradDeEchilibru(rad->st) != 1)
			{
				rad->st = rotireLaStanga(rad->st);
			}
			rad = notireLaDreapta(rad);
		}
		if (calculareGradDeEchilibru(rad) == -2)
		{
			if (calculareGradDeEchilibru(rad->dr) != -1)
			{
				rad->dr = notireLaDreapta(rad->dr);
			}
			rad = rotireLaStanga(rad);
		}
	}
	return rad;
}

void afisareArboreInordine(NOD* rad)
{
	if (rad)
	{
		afisareArboreInordine(rad->st);
		afisareFactura(rad->info);
		afisareArboreInordine(rad->dr);
	}
}


void afisareNivel(NOD* rad, int nivel)
{
	if (rad)
	{
		if (nivel == 0)
		{
			//afisez ce am in radacina
			afisareFactura(rad->info);
		}
		else
		{
			nivel--;
			afisareNivel(rad->st, nivel);
			afisareNivel(rad->dr, nivel);
		}
	}
}

void afisarePeNivele(NOD* rad)
{
	if (rad)
	{
		int nrNivele = inaltimeArbore(rad);
		for (int i = 0; i < nrNivele; i++)
		{
			printf("\nNivel %d", i + 1);
			afisareNivel(rad, i);
		}
	}
}


void aflaFacturiDupaNume(NOD* rad, const char* numeclient, int &nrFacturi)
{
	if (rad)
	{
		if (strcmp(rad->info.numeClient, numeclient) == 0)
		{
			nrFacturi++;
		}
		aflaFacturiDupaNume(rad->st, numeclient, nrFacturi);
		aflaFacturiDupaNume(rad->dr, numeclient, nrFacturi);

	}
}
void main()
{
	NOD* rad = NULL;
	rad = inserareInArboreAVL(rad, creareFactura(24, "12-10-2019", "Maria", 500.4, 3));
	rad = inserareInArboreAVL(rad, creareFactura(15, "12-10-2019", "Chiara", 340, 6));
	rad = inserareInArboreAVL(rad, creareFactura(36, "13-10-2018", "Teodora", 345.7, 2));
	rad = inserareInArboreAVL(rad, creareFactura(10, "12-10-2019", "Ilinca", 400.5, 3));
	rad = inserareInArboreAVL(rad, creareFactura(3, "16-10-2019", "Nadia", 236, 3));
	afisareArboreInordine(rad);
	printf("dupa stergere/n");
	rad=stergereDinAVL(rad, 36);
	afisareArboreInordine(rad);

	printf("\nAfisare pe nivele");
	afisarePeNivele(rad);
	int nrFacturi = 0;
	char numeclient[] = "Ilinca";
	aflaFacturiDupaNume(rad, numeclient, nrFacturi);
	printf("\n\n Clientul are %d facturi", nrFacturi);
}