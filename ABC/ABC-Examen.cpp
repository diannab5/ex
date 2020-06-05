#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>


struct Examen
{
	char* materie;
	unsigned int codExamen;
	int nrCredite;
	int nrStud;
	float* noteObtinute;
};

Examen creareExamen(const char* materie, unsigned int codExamen, int nrCredite, int nrStud, float* noteObtinute)
{
	Examen e;
	e.materie = (char*)malloc(sizeof(char)*(strlen(materie) + 1));
	strcpy(e.materie, materie);
	e.codExamen = codExamen;
	e.nrCredite = nrCredite;
	e.nrStud = nrStud;
	e.noteObtinute = (float*)malloc(sizeof(float)*nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		e.noteObtinute[i] = noteObtinute[i];
	}
	return e;
}

void afisareExamen(Examen e)
{
	printf("\nMateria %s, are codul %d, nr credite %d, nr de studenti examinati %d\n", e.materie, e.codExamen, e.nrCredite, e.nrStud);
	printf(" notele obtinute la aceasta materie");
	for (int i = 0; i < e.nrStud; i++)

	{
		printf(" %5.2f", e.noteObtinute[i]);
	}
	

	
}

struct nod
{
	Examen info;
	nod* st;
	nod* dr;
};

nod* inserareInArbore(nod* rad, Examen e)
{
	if (rad)
	{
		if (rad->info.codExamen > e.codExamen)
		{
			rad->st = inserareInArbore(rad->st, e);
		}
		else
		{
			rad->dr = inserareInArbore(rad->dr, e);
		}
		return rad;
	}
	else
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->dr = NULL;
		nou->st = NULL;
		nou->info = creareExamen(e.materie, e.codExamen, e.nrCredite, e.nrStud, e.noteObtinute);
		return nou;
	}
}

nod* stergereExamenDupaId(nod* rad, int codExamen)
{
	if (rad)
	{
		if (rad->info.codExamen > codExamen)
		{
			rad->st=stergereExamenDupaId(rad->st, codExamen);
		}
		else if (rad->info.codExamen < codExamen)
		{
			rad->dr=stergereExamenDupaId(rad->dr, codExamen);
		}
		else
		{
			//daca am gasit nodul
			if (rad->st = NULL)
			{
				nod* temp = rad->dr;
				free(rad->info.materie);
				free(rad->info.noteObtinute);
				free(rad);
				rad = temp;
			}
			else if (rad->dr = NULL)
			{
				nod* temp = rad->st;
				free(rad->info.materie);
				free(rad->info.noteObtinute);
				free(rad);
				rad = temp;
			}
			else
			{
				//daca am doi descendenti
				nod* temp = rad->st;
				while (temp->dr)
					temp = temp->dr;
				free(rad->info.materie);
				free(rad->info.noteObtinute);
					//mutare date din temp in rad
				rad->info.materie = (char*)malloc(sizeof(char)*(strlen(temp->info.materie) + 1));
				strcpy(rad->info.materie, temp->info.materie);
				rad->info.codExamen = temp->info.codExamen;
				rad->info.nrCredite = temp->info.nrCredite;
				rad->info.nrStud = temp->info.nrStud;
				rad->info.noteObtinute = (float*)malloc(sizeof(float)*rad->info.nrStud);
				for (int i = 0; i < rad->info.nrStud; i++)
				{
					rad->info.noteObtinute[i] = temp->info.noteObtinute[i];
				}
				//sterg ce aveam in temp
				rad->st = stergereExamenDupaId(rad->st, temp->info.codExamen);
			}
		}
		
	}
	return rad;
}

void afisareArborePostordine(nod* rad)
{
	if (rad)
	{
		afisareArborePostordine(rad->st);
		afisareArborePostordine(rad->dr);
		afisareExamen(rad->info);
	}
}

void main()
{
	
	nod* rad = NULL;
	/*rad = inserareInArbore(rad, creareExamen("BCO", 20, 4, 3, new float[3]{ 8,5,8 }));
	rad = inserareInArbore(rad, creareExamen("ATP", 15, 4, 2, new float[2]{ 10,7 }));
	rad = inserareInArbore(rad, creareExamen("SDD", 25, 5, 4, new float[4]{ 10,10,6,8 }));
	rad = inserareInArbore(rad, creareExamen("Man", 3, 5, 5, new float[5]{ 6,8,9,5,3 }));
	rad = inserareInArbore(rad, creareExamen("POO", 16, 6, 3, new float[3]{ 6,8,9 }));*/

	Examen e;
	FILE* f;
	f = fopen("rezervare.txt", "r");
	char buffer[100];
	char* token;
	while (fgets(buffer, sizeof(buffer), f)) {
		token = strtok(buffer, ",");
		e.materie = (char*)malloc(sizeof(char)*(strlen(token) + 1));
		strcpy(e.materie, token);

		token = strtok(NULL, ",");
		e.codExamen = atoi(token);

		token = strtok(NULL, ",");
		e.nrCredite = atoi(token);

		token = strtok(NULL, ",");
		e.nrStud = atoi(token);

		token = strtok(NULL, ",");
		e.noteObtinute = (float*)malloc(sizeof(float)*nrStud);
		for (int i = 0; i < r.nrStud; i++) {
			e.noteObtinute = atof(token);
		}

		rad=inserareInArbore(rad, e);
		
	}

	afisareArborePostordine(rad);
	//rad = stergereExamenDupaId(rad, 3);
	//afisareArborePostordine(rad);
}