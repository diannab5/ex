#include<iostream>
#pragma warning(disable:4996)

struct Client
{
	int idClient;
	char* numeClient;
	float bugetClient;
	int durataProceduri;
	float costProceduri;
};

struct nod
{
	Client info;
	nod* dreapta;
	nod* stanga;
};

Client creareClient(int id, char* nume, float buget, int durata, float cost)
{
	Client c;
	c.idClient = id;

	c.numeClient = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(c.numeClient, nume);

	c.bugetClient = buget;
	c.costProceduri = cost;

	c.durataProceduri = durata;

	return c;
}

void afisareClient(Client c)
{
	printf("\n%d, %s, %5.2f, %5.2f, %d\n", c.idClient, c.numeClient, c.bugetClient, c.costProceduri, c.durataProceduri);
}

int inaltimeArbore(nod* root)
{
	if (root)
	{
		int stanga = inaltimeArbore(root->stanga);
		int dreapta = inaltimeArbore(root->dreapta);
		return stanga > dreapta ? stanga + 1 : dreapta + 1;
	}
	else
		return 0;
}

int gradDeEchilibru(nod* root)
{
	return inaltimeArbore(root->dreapta) - inaltimeArbore(root->stanga);
}

nod* rotireStanga(nod* root)
{
	nod* temp = root->dreapta;
	root->dreapta = temp->stanga;
	temp->stanga = root;
	return temp;
}

nod* rotireDreapta(nod* root)
{
	nod* temp = root->stanga;
	root->stanga = temp->dreapta;
	temp->dreapta = root;
	return temp;
}

nod* inserareInAVL(nod* root, Client c)
{
	if (root)
	{
		if (c.idClient < root->info.idClient)
			root->stanga = inserareInAVL(root->stanga, c);
		else if (c.idClient > root->info.idClient)
			root->dreapta = inserareInAVL(root->dreapta, c);

		int GE = gradDeEchilibru(root);
		if (GE == 2)
		{
			if (gradDeEchilibru(root->dreapta) == 1)
			{
				root = rotireStanga(root);
			}
			else
			{
				root->dreapta = rotireDreapta(root->dreapta);
				root = rotireStanga(root);
			}
		}

		if (GE == -2)
		{
			if (gradDeEchilibru(root->stanga) == -1)
			{
				root = rotireDreapta(root);
			}
			else
			{
				root->stanga = rotireStanga(root->stanga);
				root = rotireDreapta(root);
			}
		}

	}
	else
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = c;
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
		afisareClient(root->info);
		afisarePreordine(root->stanga);
		afisarePreordine(root->dreapta);
	}
	
}

void afisareSume(nod* root)
{
	if (root)
	{
		if (root->info.bugetClient > root->info.costProceduri)
			printf("Client %d - Suma ramasa: %5.2f\n", root->info.idClient, root->info.bugetClient - root->info.costProceduri);
		else
			printf("Client %d - Suma datorata: %5.2f\n", root->info.idClient, (root->info.costProceduri - root->info.bugetClient));
		afisareSume(root->stanga);
		afisareSume(root->dreapta);
	}
}

void numarareClienti(nod* root,int* nrClienti)
{
	if (root) 
	{
		(*nrClienti)++;
		numarareClienti(root->stanga,nrClienti);
		numarareClienti(root->dreapta,nrClienti);
	}
}

void inserareSume(nod* root, int* nrClienti, float** sume,int* i)
{
	if (root)
	{
		(*sume)[(*i)++] = root->info.bugetClient - root->info.costProceduri;
		
		inserareSume(root->stanga,nrClienti,sume,i);
		inserareSume(root->dreapta,nrClienti,sume,i);
	}
}

float* vectorSume(nod* root, int* nrClienti, int* i)
{
	numarareClienti(root, nrClienti);

	float* rez = NULL;

	if ((*nrClienti) > 0)
	{
		rez = (float*)malloc(sizeof(float)*(*nrClienti));
		inserareSume(root, nrClienti, &rez, i);	
	}
	return rez;
}

struct nodLista
{
	Client info;
	nodLista* next;
};

nodLista* inserareInLista(nodLista* root,Client c)
{
		nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
		nou->info = creareClient(c.idClient,c.numeClient,c.bugetClient,c.durataProceduri,c.costProceduri);
		nou->next = root;
		return nou;
	
}

nodLista* salvareFrunzeInLista(nod* root, nodLista* lista)
{
	if (root)
	{
		if (root->dreapta == NULL && root->stanga == NULL)
		{
			lista = inserareInLista(lista, root->info);
		}
		
		lista = salvareFrunzeInLista(root->stanga, lista);
		lista = salvareFrunzeInLista(root->dreapta, lista);
		
		
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
			afisareClient(temp->info);
			temp = temp->next;
		}
	}
}

void numarDatori(nod* root, int* nrDatori)
{
	if (root)
	{
		if (root->info.bugetClient < root->info.costProceduri)
		{
			(*nrDatori)++;
		}
		numarDatori(root->stanga,nrDatori);
		numarDatori(root->dreapta, nrDatori);

	}
}

void main()
{
	nod* root = NULL;
	FILE* f = fopen("Clienti.txt", "r");
	if (f)
	{
		int id; char nume[100]; float buget; float cost; int durata;
		fscanf(f, "%d", &id);
		while (!feof(f))
		{
			fscanf(f, "%s", nume);
			fscanf(f, "%f", &buget);
			fscanf(f, "%f", &cost);
			fscanf(f, "%d", &durata);
			Client c = creareClient(id, nume, buget, durata, cost);
			root = inserareInAVL(root, c);
			fscanf(f, "%d", &id);
		}
		fclose(f);
		afisarePreordine(root);
		printf("\n\n");
		//afisareSume(root);
		int nrClienti = 0;
		int i = 0;
		//float* sume=vectorSume(root,&nrClienti,&i);
		numarareClienti(root, &nrClienti);
		/*for (int i = 0; i < nrClienti; i++)
		{
			printf("%5.2f \n", sume[i]);

		}*/
		//printf("\nNumar de clienti: %d\n",nrClienti);
		//calculareSume(root, &nrClienti, &sume, &i);
		float* rez;
		rez = (float*)malloc(sizeof(float)*nrClienti);
		inserareSume(root, &nrClienti, &rez, &i);
		for (int i = 0; i < nrClienti; i++)
		{
		printf("%5.2f \n", rez[i]);

		}
		nodLista* lista = NULL;
		lista = salvareFrunzeInLista(root, lista);
		afisareLista(lista);
		int nrDatori = 0;
		numarDatori(root, &nrDatori);
		printf("\nNumar datori: %d\n",nrDatori);

	}


}