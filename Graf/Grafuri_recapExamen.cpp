#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Facultate
{
	int id;
	char*nume;
};

Facultate creareFacultate(int id, char* nume)
{
	Facultate f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(f.nume, nume);
	return f;
}
void afisareFacultate(Facultate f)
{
	printf("\nId: %d", f.id);
	printf("\nNume: %s", f.nume);
}
struct nodListaPrincipala;
struct nodListaSecundara
{
	nodListaSecundara* next;
	nodListaPrincipala *info;
};
struct nodListaPrincipala
{
	nodListaSecundara *vecini;
	Facultate info;
	nodListaPrincipala* next;
};

nodListaPrincipala* inserareListaPrincipala(nodListaPrincipala* cap, Facultate f)
{
	nodListaPrincipala* nou = (nodListaPrincipala*)malloc(sizeof(nodListaPrincipala));
	nou->next = NULL;
	nou->vecini = NULL;
	nou->info = creareFacultate(f.id,f.nume);
	if (cap!=NULL)
	{
		nodListaPrincipala* temp = cap;
		while(cap->next)
		{
			cap = cap->next;

		}
		cap->next = nou;
		
	}
	else { return nou; }
	return cap;
}
nodListaSecundara* inserareListaSecundara(nodListaSecundara* cap, nodListaPrincipala *info)
{
	nodListaSecundara* nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
	nou->info = info;
	nou->next = NULL;
	if (cap)
	{
		nodListaSecundara* temp = cap;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
		
	}
	else { return nou; }
	return cap;
}

nodListaPrincipala* cautareDupaID(nodListaPrincipala* cap, int id)
{
	while (cap&&cap->info.id != id)
	{
		cap = cap->next;
	}
	return cap;
}

void inserareArcInGraf(nodListaPrincipala* graf, int idStart, int idStop)
{
	if (graf)
	{
		nodListaPrincipala *nodStart = cautareDupaID(graf, idStart);
		nodListaPrincipala* nodStop = cautareDupaID(graf, idStop);
		if (nodStart != NULL & nodStop != NULL)
		{
			nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
			nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);

		}
	}
}
void afisareListaSecundara(nodListaSecundara* cap)
{
	while (cap)
	{
		printf(" %d.%s\n", cap->info->info.id, cap->info->info.nume);
		cap = cap->next;
	}
}

void afisareListaPrincipala(nodListaPrincipala* cap)
{
	while (cap)
	{
		printf(" %d.%s are urmatorii vecini:\n", cap->info.id, cap->info.nume);
		afisareListaSecundara(cap->vecini);
		cap = cap->next;
	}
}

struct nodStiva
{
	Facultate info;
	nodStiva* next;
};

nodStiva* push(nodStiva* s, Facultate f)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info = creareFacultate(f.id,f.nume);
	nou->next = s;
	return nou;
}

nodStiva* pop(nodStiva*s, Facultate &varf)
{
	if (s)
	{
		nodStiva* temp = s;
		s = s->next;
		varf = creareFacultate(temp->info.id,temp->info.nume);
		free(temp->info.nume);
		free(temp);
	}
	return s;
}

int calculareNumarVarfuri(nodListaPrincipala* lp)
{
	int nr = 0;
	while (lp)
	{
		nr++;
		lp = lp->next;
	}
	return nr;
}

Facultate* parcurgereDF(nodListaPrincipala* lp, Facultate nodStart)
{
	int * flags;
	int k = 0;
	Facultate* output;
	nodStiva* stack = 0;
	flags = (int*)malloc(sizeof(int)*calculareNumarVarfuri(lp));
	for (int i = 0; i < calculareNumarVarfuri(lp); i++)
		flags[i] = 0;
	output = (Facultate*)malloc(sizeof(Facultate)*calculareNumarVarfuri(lp));
	stack = push(stack, nodStart);
	flags[nodStart.id - 1] = 1;
	while (stack)
	{
		Facultate varf;
		stack = pop(stack, varf);
		output[k] = varf;
		k = k + 1;
		nodListaPrincipala* tmp = cautareDupaID(lp, varf.id);
		nodListaSecundara* tms = tmp->vecini;
		while (tms)
		{
			if (flags[tms->info->info.id - 1] == 0)
			{
				stack = push(stack, tms->info->info);
				flags[tms->info->info.id - 1] = 1;
			}
			tms = tms->next;
		}
	}
	free(flags);
	return output;
}

void main()
{
	Facultate f1 = creareFacultate(1, "ASE");
	Facultate f2 = creareFacultate(2, "Poli");
	Facultate f3 = creareFacultate(3, "Uni");
	nodListaPrincipala* graf = NULL;
	graf = inserareListaPrincipala(graf, f1);
	graf = inserareListaPrincipala(graf, f2);
	graf = inserareListaPrincipala(graf, f3);
	inserareArcInGraf(graf, 1, 2);
	inserareArcInGraf(graf, 1, 3);
	inserareArcInGraf(graf, 3, 2);
	inserareArcInGraf(graf, 2, 1);
	afisareListaPrincipala(graf);
	Facultate* output = NULL;
	output=parcurgereDF(graf, f2);
	for (int i = 0; i < calculareNumarVarfuri(graf); i++)
	{
		afisareFacultate(output[i]);
	}

}