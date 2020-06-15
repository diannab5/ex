#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Camera {
	char etaj[50];
	int nrCamera; //cheie
	char* tipCamera;
	float pretPeNoapte;
	char* statusCamera;
};

void afisareHotel(Camera c) {
	printf("\nEtaj %s , nr camera: %d, tipul camerei este %s, pretul pe noapte %5.2f, status camera: %s\n", c.etaj, c.nrCamera, c.tipCamera, c.pretPeNoapte,c.statusCamera);
}

struct nod {
	Camera info;
	nod* st;
	nod* dr;
};

nod* inserareInArbore(nod* rad, Camera c)
{
	if (rad)
	{
		if (c.nrCamera < rad->info.nrCamera)
			rad->st = inserareInArbore(rad->st, c);
		else if (c.nrCamera > rad->info.nrCamera)
			rad->dr = inserareInArbore(rad->dr, c);
	}
	else
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = c;
		nou->dr = NULL;
		nou->st = NULL;
		rad = nou;
	}

	return rad;
}

Camera citireHotelDinFisier(FILE*& f) {
	Camera c;
	char buffer[50];
	fscanf(f, "%s", buffer);
	strcpy(c.etaj, buffer);
	fscanf(f, "%d", &c.nrCamera);

	char buffer2[50];
	fscanf(f, "%s", buffer2);
	c.tipCamera = (char*)malloc(sizeof(char)*(strlen(buffer2) + 1));
	strcpy(c.tipCamera, buffer2);

	fscanf(f, "%f", &c.pretPeNoapte);

	char buffer3[50];
	fscanf(f, "%s", buffer3);
	c.statusCamera = (char*)malloc(sizeof(char)*(strlen(buffer3) + 1));
	strcpy(c.statusCamera, buffer3);

	return c;


}

void afisareArboreInordine(nod* rad) {
	if (rad) {
		afisareArboreInordine(rad->st);
		afisareHotel(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

struct nodLista {
	Camera info;
	nodLista* next;
	nodLista* prev;
};

struct ListaDubla {
	nodLista* prim;
	nodLista* ultim;
};

ListaDubla inserareListaDubla(ListaDubla lista, Camera c) {
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info = c;
	nou->next = NULL;
	nou->prev = lista.ultim;
	if (lista.ultim) {
		lista.ultim->next = nou;
		lista.ultim = nou;
	}
	else {
		lista.ultim = nou;
		lista.prim = nou;
	}
	return lista;
}

void afisareListaInceputSfarsit(ListaDubla lista) {
	if (lista.prim) {
		nodLista* temp = lista.prim;
		while (temp) {
			afisareHotel(temp->info);
			temp = temp->next;
		}
	}
}

Camera initializareCamera(const char etaj[50],int nrCamera,const char* tipCamera,float pretPeNoapte,const char* statusCamera) {
	Camera c;
	strcpy(c.etaj, etaj);
	c.nrCamera = nrCamera;
	c.tipCamera = (char*)malloc(sizeof(char)*(strlen(tipCamera) + 1));
	strcpy(c.tipCamera, tipCamera);
	c.pretPeNoapte = pretPeNoapte;
	c.statusCamera = (char*)malloc(sizeof(char)*(strlen(statusCamera) + 1));
	strcpy(c.statusCamera, statusCamera);
	return c;
}
void transformareArboreInListaDubla(ListaDubla &lista, nod* rad, float pretPeNoapte) {
	if (rad) {
		transformareArboreInListaDubla(lista, rad->st, pretPeNoapte);
		if (rad->info.pretPeNoapte > pretPeNoapte) {
			lista=inserareListaDubla(lista, initializareCamera(rad->info.etaj, rad->info.nrCamera, rad->info.tipCamera, rad->info.pretPeNoapte, rad->info.statusCamera));
		}
		transformareArboreInListaDubla(lista, rad->dr, pretPeNoapte);
	}
}
struct nodSimplu {
	Camera info;
	nodSimplu* next;
};

void push(nodSimplu* &stiva, Camera c) {
	nodSimplu* p = (nodSimplu*)malloc(sizeof(nodSimplu));
	p->info = c; 
	p->next = NULL; 
	if (stiva) {
		nodSimplu* nou = stiva;
		while (nou->next) 
		{
			nou = nou->next;
		}
		nou->next = p; 

	}
	else {
	
		stiva = p; 
	}
}
void transformareArboreInStiva(nodSimplu* &stiva, nod* rad, float pretPeNoapte) {
	if (rad) {
		transformareArboreInStiva(stiva, rad->st,pretPeNoapte);
		if (rad->info.pretPeNoapte > pretPeNoapte) {
			push(stiva, initializareCamera(rad->info.etaj, rad->info.nrCamera, rad->info.tipCamera, rad->info.pretPeNoapte, rad->info.statusCamera));
		}
		transformareArboreInStiva(stiva, rad->dr,pretPeNoapte);
	}
}

Camera pop(nodSimplu* &stiva) {
	if (stiva) {
		nodSimplu* copie = stiva;
		while (copie->next && copie->next->next) {
		
			copie = copie->next;
		}
		if (copie->next) {
			Camera c = copie->next->info;
			free(copie->next);
			copie->next = NULL;
			return c;
		}
		else {
			Camera c = copie->info;
			free(copie);
			stiva = NULL; 
			return c;
		}
	}
	else {
		throw "Nu avem stiva!";
	}
}

void afisareStiva(nodSimplu* &stiva) {
	while (stiva) {
		afisareHotel(pop(stiva));
	}

}
void dezalocareLista(ListaDubla &lista) {
	if (lista.prim) {
		nodLista* temp = lista.prim;
		while (temp) {
			nodLista* aux = temp->next;
			free(temp->info.tipCamera);
			free(temp->info.statusCamera);
			free(temp);
			temp = aux;
		}
		lista.prim = NULL;
		lista.ultim = NULL;
	}
}

void dezalocareArbore(nod* &rad) {
	if (rad) {
		dezalocareArbore(rad->st);
		dezalocareArbore(rad->dr);
		free(rad->info.tipCamera);
		free(rad->info.statusCamera);
		free(rad);
		rad = NULL;
	}
}

void numarareCamere(nod* root, int* nrCamere)
{
	if (root)
	{
		(*nrCamere)++;
		numarareCamere(root->st, nrCamere);
		numarareCamere(root->dr, nrCamere);
	}
}



void main() {
	Camera c;
	nod* rad = NULL;
	FILE* fisier = fopen("hotel.txt", "r");
	if (fisier) {
		while (!feof(fisier)) {
		
			c = citireHotelDinFisier(fisier);
			rad = inserareInArbore(rad, c);
		}
		fclose(fisier);
	}
	afisareArboreInordine(rad);
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	printf("\n\nAfisare transformare");
	transformareArboreInListaDubla(lista, rad, 200);
	afisareListaInceputSfarsit(lista);

	/*dezalocareArbore(rad);
	afisareArboreInordine(rad);
	dezalocareLista(lista);
	afisareListaInceputSfarsit(lista);
	*/
	int nrCamere = 0;
	numarareCamere(rad, &nrCamere);
	printf("\n\nNr camere: %d", nrCamere);

	printf("\n\nTransformare arbore in stiva:");
	nodSimplu* stiva = NULL;
	push(stiva, c);
	transformareArboreInStiva(stiva, rad,200);
	afisareStiva(stiva);

}