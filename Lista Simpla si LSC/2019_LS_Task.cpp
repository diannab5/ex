#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Task {
	int idTask;
	char* dataCreare;
	char* dataAsignare;
	char* inginerAsignat;
	int prioritate;
	char* stareTask;
};

Task creareTask(int idTask,const char* dataCreare,const char* dataAsignare, const char* inginerAsignat, int priotirate,const char* stareTask) {
	Task t;
	t.idTask = idTask;
	t.dataCreare = (char*)malloc(sizeof(char)*(strlen(dataCreare) + 1));
	strcpy(t.dataCreare, dataCreare);
	t.dataAsignare = (char*)malloc(sizeof(char)*(strlen(dataAsignare) + 1));
	strcpy(t.dataAsignare, dataAsignare);
	t.inginerAsignat = (char*)malloc(sizeof(char)*(strlen(inginerAsignat) + 1));
	strcpy(t.inginerAsignat, inginerAsignat);
	t.prioritate = priotirate;
	t.stareTask = (char*)malloc(sizeof(char)*(strlen(stareTask) + 1));
	strcpy(t.stareTask, stareTask);
	return t;
}

Task copiereTask(Task t) {
	Task copie;
	copie.idTask = t.idTask;
	copie.dataCreare = (char*)malloc(sizeof(char)*(strlen(t.dataCreare) + 1));
	strcpy(copie.dataCreare, t.dataCreare);
	copie.dataAsignare = (char*)malloc(sizeof(char)*(strlen(t.dataAsignare) + 1));
	strcpy(copie.dataAsignare, t.dataAsignare);
	copie.inginerAsignat = (char*)malloc(sizeof(char)*(strlen(t.inginerAsignat) + 1));
	strcpy(copie.inginerAsignat, t.inginerAsignat);
	copie.prioritate = t.prioritate;
	copie.stareTask = (char*)malloc(sizeof(char)*(strlen(t.stareTask) + 1));
	strcpy(copie.stareTask, t.stareTask);
	return copie;
}

void afisareTask(Task t) {
	printf("Id: %d, data creare: %s, data asignare: %s, inginer: %s, prioritate: %d, stare: %s\n", t.idTask, t.dataCreare, t.dataAsignare, t.inginerAsignat, t.prioritate, t.stareTask);
}

struct nod {
	Task info;
	nod* next;
};

nod* inserareInceput(nod* cap, Task t) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = t;
	nou->next = cap;
	return nou;
}

void afisareLista(nod* cap) {
	while (cap) {
		afisareTask(cap->info);
		cap = cap->next;
	}
}

int nrTaskuri(nod* cap, const char* stareNou, const char* stareDeschis) {
	nod* temp = cap;
	int contor = 0;
	while (temp) {
		if (strcmp(temp->info.stareTask, stareNou) == 0) {
			contor++;
		}
		else if (strcmp(temp->info.stareTask, stareDeschis) == 0) {
			contor++;
		}
		temp = temp->next;
	}
	return contor;
}

int nrIngineri(nod* cap, const char* data) {
	int contor = 0;
	nod* temp = cap;
	while (temp) {
		if (strcmp(temp->info.dataAsignare, data) == 0) {
			contor++;
		}
		temp = temp->next;
	}
	return contor;
}

//Asignare task prin idTask unui inginer precizat cu numele. La momentul asignarii tas-kul trece din nou in deschis
void asignareTask(int id, const char* inginer, nod* cap, const char* stareTask) {
	nod* temp = cap;
	while (temp) {
		if (temp->info.idTask == id) {
			temp->info.inginerAsignat = (char*)malloc(sizeof(char)*(strlen(inginer) + 1));
			strcpy(temp->info.inginerAsignat, inginer);
			if (strcmp(temp->info.stareTask, "nou") == 0) {
				temp->info.stareTask = (char*)malloc(sizeof(char)*(strlen(stareTask) + 1));
				strcpy(temp->info.stareTask, stareTask);
			}
		}
		temp = temp->next;
	}
}

//Extragere task
Task extragereTask(nod*& cap) {
	if (cap) {
		Task t = copiereTask(cap->info);
		nod* temp = cap;
		cap = temp->next;
		free(temp);
		return t;
	}
	else {
		return creareTask(-1, "", "", "", -1, "");
	}
}
//dezalocare lista
void stergereLista(nod*& cap) {
	while (cap) {
		free(cap->info.dataCreare);
		free(cap->info.dataAsignare);
		free(cap->info.inginerAsignat);
		free(cap->info.stareTask);
		//retin adresa nodului curent in alt pointer
		nod* temp = cap;
		cap = cap->next;
		free(temp);
	}
}

//inserare crecatoare dupa id task
void inserareSortataDupaId(nod*& cap, Task t) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = t;
	if (cap) {
		//primul cal verificam daca info din nodul existent e mai mare decat info din noul nod
		//se insereaza la inceput
		if (cap->info.idTask > t.idTask) {
			nou->next = cap;
			cap = nou;
		}
		else {//undeva in interior
			nod* temp = cap;//pierd nodurile din spate daca nu iau temp
			while (temp->next&&temp->info.idTask < t.idTask) {
				temp = temp->next;
			}
			nou->next = temp->next;
			temp->next = nou;
		}
	}
	else
	{
		nou->next = NULL;//nu exista nod in lista, cream noi
		cap = nou;
	}
}

//inserare la sfarsit
nod* inserareSfarsit(nod* cap, Task t) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = t;
	nou->next = NULL;
	if (cap) {
		nod* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		return nou;
	}
	return cap;
}

//functie de filtrare
//returneaza un vector care contine task-urile cu un id mai mare decat un id dat
Task* filtrare(nod* cap, int* nr, int idDat) {
	if (cap) {
		nod* temp = cap;
		while (temp) {
			if (temp->info.idTask > idDat) {
				(*nr)++;
			}
			temp = temp->next;
		}
		if ((*nr) > 0) {
			Task* vector = (Task*)malloc(sizeof(Task)*(*nr));
			int contor = 0;
			temp = cap;
			while (temp) {
				if (temp->info.idTask > idDat) {
					vector[contor] = temp->info;
					contor++;
				}
				temp = temp->next;
			}
			return vector;
		}
		else {
			return NULL;
		}
	}
	else {
		return NULL;
	}
}

//lista cu task-urile unui inginer
nod* taskDupaInginer(nod* cap, const char* inginer) {
	nod* rezultat = NULL;
	nod* temp = cap;
	while (temp) {
		if (strcmp(temp->info.inginerAsignat, inginer) == 0) {
			rezultat = inserareInceput(rezultat, temp->info);
		}
		temp = temp->next;
	}
	return rezultat;
}

//Stergere task dupa prioritate
nod* stergereTask(nod* cap, int prioritate) {
	if (cap) {
		if (cap->info.prioritate == prioritate) {
			nod* temp = cap;
			cap = cap->next;
			free(temp->info.dataCreare);
			free(temp->info.dataAsignare);
			free(temp->info.inginerAsignat);
			free(temp->info.stareTask);
			free(temp);
		}
		else {
			nod* temp = cap;
			while (temp->next && temp->next->info.prioritate != prioritate)
				temp = temp->next;
			if (temp->next) {
				nod* aux = temp->next;
				temp->next = temp->next->next;
				free(aux->info.dataCreare);
				free(aux->info.dataAsignare);
				free(aux->info.inginerAsignat);
				free(aux->info.stareTask);
			}
		}
	}
	return cap;
}


void main() {
	nod* lista = NULL;
	 lista=inserareSfarsit(lista, creareTask(2, "10-06-2020", "13-06-2020", "Marius", 2, "nou"));
	 lista = inserareSfarsit(lista, creareTask(3, "08-06-2020", "07-06-2020", "Cristi", 4, "deschis"));
	 lista = inserareSfarsit(lista, creareTask(4, "04-06-2020", "07-06-2020", "Iulia", 5, "inchis"));
	 lista = inserareSfarsit(lista, creareTask(7, "02-06-2020", "06-06-2020", "Alex", 3, "nou"));
	 lista = inserareSfarsit(lista, creareTask(5, "10-06-2020", "11-06-2020", "Alex", 6, "nou"));
	afisareLista(lista);

	//Punctul 2
	printf("\nNr de task-uri la care nu s-a inceput lucrul este %d\n", nrTaskuri(lista, "nou", "deschis"));

	printf("\nNr de ingineri a caror task a fost asignat pe data de 07-06-2020 %d \n", nrIngineri(lista, "07-06-2020"));

	//punctul 4
	asignareTask(2, "Alex", lista, "deschis");
	printf("\nAfisare lista dupa asignarea task-ului cu id-ul 1 catre inginerul Alex: \n");
	afisareLista(lista);

	//pct 5
	printf("\nNodul extras:\n");
	afisareTask(extragereTask(lista));

	printf("\nNodul extras:\n"); //extragem  de 3 ori pt ca asa cere pct 6
	afisareTask(extragereTask(lista));

	printf("\nNodul extras:\n");
	afisareTask(extragereTask(lista));

	printf("\nAfisare lista dupa extragere:\n"); //aici a vrut sa vada ca s-au sters cele 3 noduri extrase din lista
	afisareLista(lista);

	printf("\n");
	Task* vector = NULL;
	int nrVector = 0;
	vector = filtrare(lista, &nrVector, 1);
	printf("Task-urile cu id-ul mai mare de 1 sunt: \n");
	for (int i = 0; i < nrVector; i++) {
		printf("Task-ul are id-ul %d \n", vector[i].idTask);
	}
	lista = taskDupaInginer(lista, "Alex");
	afisareLista(lista);
	printf("\nAfisare lista dupa ce am sters elementul cu prioritatea 3\n");
	lista = stergereTask(lista, 3);
	afisareLista(lista);

	
	//stergereLista(lista);

}