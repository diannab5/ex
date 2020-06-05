#include<stdio.h>
#include<malloc.h>
#include<string.h>



struct Restaurant {
	unsigned int id;
	char* adresaRestaurant;
	unsigned int nrTotalLocuri;
	unsigned int nrLocuriRezervate;
};

Restaurant creareRestaurant(unsigned int id, const char* adresa, unsigned int nrTotalLocuri, unsigned int nrLocuriRzervate) {
	Restaurant r;
	r.id = id;
	r.adresaRestaurant = (char*)malloc(sizeof(char)*(strlen(adresa) + 1));
	strcpy(r.adresaRestaurant, adresa);
	r.nrTotalLocuri = nrTotalLocuri;
	r.nrLocuriRezervate = nrLocuriRzervate;
	return r;

}

void afisareRestaurant(Restaurant r) {
	printf("\n Id: %d, adresa: %s, locuri totale %d, locuri rezervate: %d\n", r.id, r.adresaRestaurant, r.nrTotalLocuri, r.nrLocuriRezervate);

}

struct nod {
	Restaurant info;
	nod* next;
};

nod* inserareInceput(nod* cap, Restaurant r) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = r;
	if (cap) {
		nou->next = cap;
		nod* temp = cap;
		while (temp->next != cap) {
			temp = temp->next;
		}
		temp->next = nou; // se creaza noua legatura
	}
	else {
		//daca nu avem noduri in lista
		nou->next = nou;
	}
	return nou;
}

nod* inserareSfarsit(nod* cap, Restaurant r) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = r;
	nou->next = cap;
	if (cap) {
		nod* temp = cap;//ca sa parcurgem lista fara sa o alteram
		while (temp->next != cap) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		nou->next = nou;
		cap = nou;
	}
	return cap;
}

void afisareLista(nod* cap) {
	nod* temp = cap;
	while (temp && temp->next != cap) {
		afisareRestaurant(temp->info);
		temp = temp->next;
	}
	afisareRestaurant(temp->info);
}

void stergereLista(nod*& cap) {
	nod* temp = cap;
	while (temp && temp->next != cap) {
		free(temp->info.adresaRestaurant);
		nod* aux = temp;//se salveaza adresa nodului curent in temp
		temp = temp->next;
		free(aux);
	}
	free(temp);
}

nod* filtrare(nod* cap, float gradOcupareAcceptat) {
	nod* rezultat = NULL;
	nod* temp = cap;
	while (temp && temp->next != cap) {
		if ((temp->info.nrTotalLocuri / temp->info.nrLocuriRezervate) > gradOcupareAcceptat) {
			rezultat = inserareSfarsit(rezultat, temp->info);
		}
		temp = temp->next;
	}
	//verificam si ultimul restaurant
	if ((temp->info.nrTotalLocuri / temp->info.nrLocuriRezervate) > gradOcupareAcceptat) {
		rezultat = inserareSfarsit(rezultat, temp->info);
	}
	return rezultat;
}

int numarLocuriRezervate(nod* cap) {
	int nr = 0;
	nod* temp = cap;
	while (temp&&temp->next != cap) {
		nr = nr + temp->info.nrLocuriRezervate; //pentru fiecare nod adunam
		temp = temp->next;
	}
	nr = nr + temp->info.nrLocuriRezervate; //si din ultimul nod
	return nr; 
}

void stergereNod(nod* pred) {
	nod* temp = pred->next;
	pred->next = pred->next->next;
	free(temp->info.adresaRestaurant);
	free(temp);
}
void extragereSiStergereNod(nod* &cap, int id) {
	if (cap) {
		nod* temp = cap;
		if (cap->info.id == id) {
			if (cap->next != cap) {//cat timp nusunt la ultimul nod
				while (temp->next != cap) {
					temp = temp->next; //parcurg lista
				}//iese din while in ultimul nod
				afisareRestaurant(cap->info); //afisez nodul curent pe care il sterg
				nod* aux = cap;
				free(cap->info.adresaRestaurant);
				temp->next = cap->next;//a ajuns la final si modifica next-ul pentru ultimul element
				cap = cap->next;//noul cap de lista, adica nodul al doilea
				free(aux);

			}
		}else{
			while (temp->next != cap && temp->next != NULL && temp->next->info.id != id)
				temp = temp->next;
			if (temp->next != cap && temp->next != NULL)
				afisareRestaurant(temp->next->info);
			stergereNod(temp);
		}
	}
}

nod* extragereSiStergereNodDinLista(nod*& capLista, int idNod) {
	nod* nodExtras = (nod*)malloc(sizeof(nod));
	nod* copieCap = capLista;

	while (capLista->next != copieCap && capLista->next->info.id != idNod) {
		capLista = capLista->next;
	}

	if (capLista->next->info.id == idNod) {
		nodExtras->next = nodExtras;
		nodExtras->info = creareRestaurant(capLista->next->info.id, capLista->next->info.adresaRestaurant, capLista->next->info.nrTotalLocuri, capLista->next->info.nrLocuriRezervate);
		free(capLista->next->info.adresaRestaurant);
		nod* temp = capLista->next;
		if (capLista->next == copieCap) {
			capLista->next = copieCap->next;
			capLista = copieCap->next;
		}
		else {
			capLista->next = capLista->next->next;
			capLista = copieCap;
		}

		free(temp);
		return nodExtras;
	}
}

//Extragere(cu stergere) + conditie
//nrLocuriRezervate>decat o val primita ca param
void filtrareRestaurante(nod*& cap, unsigned int nrLocuri) {
	if (cap) {
		nod* temp = cap;
		while (temp->next != cap) {
			if (temp->next->info.nrLocuriRezervate > nrLocuri) {
				if (temp == cap) {
					while (temp->next != cap) {
						temp = temp->next;
					}
					nod* aux = cap;
					afisareRestaurant(cap->info);
					free(cap->info.adresaRestaurant);
					temp->next = cap->next;
					cap = cap->next;
					free(aux);
					temp = cap;
				}
				else {
					nod* deSters = temp->next;
					afisareRestaurant(deSters->info);
					stergereNod(temp);
				}
			}
			else {
				temp = temp->next;
			}
		}
		if (temp->next == cap && temp->info.nrLocuriRezervate > nrLocuri) {
			afisareRestaurant(temp->next->info);
			free(temp->next->info.adresaRestaurant);
			free(temp);
			cap = NULL;
		}
	}
}
void main() {
	nod* lista = NULL;
	lista = inserareInceput(lista, creareRestaurant(1, "Mircea Voda", 100, 20));
	lista = inserareInceput(lista, creareRestaurant(2, "Vintila Voda", 70, 10)); 
	//lista = inserareSfarsit(lista, creareRestaurant(3, "Lipscani", 120, 15)); // si de 2 ori inserareSfarsit fara inserare inceput (sa comentezi randurile de mai sus de exemplu)
	 //lista = inserareSfarsit(lista, creareRestaurant(4, "Calea Victoriei", 70, 10));
	 //lista = inserareSfarsit(lista, creareRestaurant(5, "Bd Unirii", 50, 12));

	nod* listaFiltrata = NULL; //initlizam o noua lista
	listaFiltrata = filtrare(lista, 5);
	printf("\nLista filtrata:");
	afisareLista(listaFiltrata);

	//printf("\n\nNr total de locuri rezervate %d ", numarLocuriRezervate(lista));
	//afisareLista(lista);
	

	//int id;
	//printf("Introduceti id-ul restaurantului ce doriti sa fie sters: ");
	//scanf("%d", &id);
	//functia de extragere(cu stergere&returnare) dupa cod si apoi afisare lista dupa stergere
	//extragereSiStergereNod(lista, id);
	//printf("\nDupa extragerea nodului mentionat, lista este: ");
	//afisareLista(lista);


	//nod* nodExtras = extragereSiStergereNodDinLista(lista, 1);
	//afisareLista(lista);

	unsigned int nrLocuri;
	printf("Introduceti valoarea: ");
	scanf("%f", &nrLocuri);
	filtrareRestaurante(lista, nrLocuri);
	printf("\nRestaurantele cu nrLocuriRezervate mai mare decat val introdusa ca parametru: ");
	afisareLista(lista);
	


	//stergereLista(lista);
	//lista = NULL;


}