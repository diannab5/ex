#include<iostream>
#pragma warning(disable:4996)

struct Task
{
	int idTask;
	char *dataAsignare;
	char *numeInginerAsignat;
	int nivelComplexitate;
	char *stareTask; // "nou", "deschis", "in lucru", "rezolvat", "inchis"
};

struct nod
{
	Task info;
	nod* dreapta;
	nod* stanga;
};

Task creareTask(int id, char* data, char* nume, int nivel, char* stare)
{
	Task t;
	t.idTask = id;

t.dataAsignare = (char*)malloc(sizeof(char)*(strlen(data) + 1));
strcpy(t.dataAsignare, data);

t.numeInginerAsignat = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
strcpy(t.numeInginerAsignat, nume);

t.stareTask = (char*)malloc(sizeof(char)*(strlen(stare) + 1));
strcpy(t.stareTask, stare);

t.nivelComplexitate = nivel;

return t;
}

void afisareTask(Task t)
{
	printf("\n %d, %s, %s, %d, %s \n", t.idTask, t.dataAsignare, t.numeInginerAsignat, t.nivelComplexitate, t.stareTask);
}

nod* inserareInArbore(nod* root, Task t)
{
	if (root)
	{
		if (t.idTask < root->info.idTask)
			root->stanga = inserareInArbore(root->stanga, t);
		else
			if (t.idTask > root->info.idTask)
				root->dreapta = inserareInArbore(root->dreapta, t);
	}
	else
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = t;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		root = nou;
	}
	return root;
}

void afisareArborePreordine(nod* root)
{
	if (root)
	{
		afisareTask(root->info);
		afisareArborePreordine(root->stanga);
		afisareArborePreordine(root->dreapta);
	}
}

void numarTaskuridupaNume(nod* root, char* numeCautat, int* nrTaskuri)
{
	if (root)
	{
		if (strcmp(root->info.numeInginerAsignat, numeCautat) == 0)
		{
			(*nrTaskuri)++;
		}

		numarTaskuridupaNume(root->stanga, numeCautat, nrTaskuri);
		numarTaskuridupaNume(root->dreapta, numeCautat, nrTaskuri);
	}

}

void modificareStare(nod* root, char* stareCautata, char* stareNoua)
{
	if (root)
	{
		if (strcmp(root->info.stareTask, stareCautata) == 0)
		{
			root->info.stareTask = (char*)malloc(sizeof(char)*(strlen(stareNoua) + 1));
			strcpy(root->info.stareTask, stareNoua);
		}

		modificareStare(root->stanga, stareCautata, stareNoua);
		modificareStare(root->dreapta, stareCautata, stareNoua);

	}
}

void numarareTaskuridupaComplexitate(nod* root, int limitaNivel, int* nrTaskuri)
{
	if (root)
	{
		if (root->info.nivelComplexitate > limitaNivel)
		{
			(*nrTaskuri)++;
		}
		numarareTaskuridupaComplexitate(root->stanga, limitaNivel, nrTaskuri);
		numarareTaskuridupaComplexitate(root->dreapta, limitaNivel, nrTaskuri);
	}
}

void stergereFrunze1(nod** root)
{
	if (*root)
	{
		if ((*root)->dreapta == NULL && (*root)->stanga == NULL)
		{
			free((*root)->info.dataAsignare);
			free((*root)->info.numeInginerAsignat);
			free((*root)->info.stareTask);
			free(*root);
			(*root) = NULL;
		}
		else
		{
			stergereFrunze1(&(*root)->stanga);
			stergereFrunze1(&(*root)->dreapta);
		}
		
	}
}

void stergereFrunze(nod* *root)
{
	if (*root)
	{
		if ((*root)->dreapta == NULL && (*root)->stanga == NULL)
		{
			free((*root)->info.dataAsignare);
			free((*root)->info.numeInginerAsignat);
			free((*root)->info.stareTask);
			free(*root);
			*root = NULL;
		}
		else
		{
			stergereFrunze(&(*root)->stanga);
			stergereFrunze(&(*root)->dreapta);
		}

	}
}

void main()
{
	nod* root = NULL;
	root=inserareInArbore(root, creareTask(4, "25.11.1997", "Gigi Neagu", 35, "nou"));
	root=inserareInArbore(root, creareTask(5, "25.11.1990", "Radu Neagu", 36, "deschis"));
	root=inserareInArbore(root, creareTask(3, "25.11.1990", "Iris Neagu", 25, "nou"));
	root=inserareInArbore(root, creareTask(6, "25.11.1997", "Gigi Neagu", 42, "rezolvat"));
	root=inserareInArbore(root, creareTask(2, "25.11.1997", "Gigi Neagu", 25, "nou"));

	afisareArborePreordine(root);

	int nrTaskuri1 = 0;
	numarTaskuridupaNume(root, "Gigi Neagu", &nrTaskuri1);
	printf("\nNumar taskuri pentru Gigi Neagu: %d\n", nrTaskuri1);

	printf("\n\n");
	modificareStare(root, "nou", "deschis");
	afisareArborePreordine(root);

	int nrTaskuri2 = 0;
	numarareTaskuridupaComplexitate(root, 24, &nrTaskuri2);
	printf("\nNumar taskuri: %d\n", nrTaskuri2);

	stergereFrunze1(&root);
	printf("\n\n");
	afisareArborePreordine(root);
}

		
		
		
		