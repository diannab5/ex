#include<malloc.h>
#include<string.h>
#include<stdio.h>


struct Fisier {
	char* denumire;
	char* cale_absoluta;
	char* extensie;
	unsigned int dimensiune;
};

struct nod {
	Fisier info;
	nod* next;
	nod* prev;
};

struct nodSimplu {
	Fisier info;
	nodSimplu* next;
};

struct ListaDubla {
	nod* prim;
	nod* ultim;
};

Fisier creareFisier(const char* denumire, const char* cale, const char* ext, unsigned int dim) {
	Fisier f;
	f.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(f.denumire, denumire);
	f.cale_absoluta = (char*)malloc(sizeof(char)*(strlen(cale) + 1));
	strcpy(f.cale_absoluta, cale);
	f.extensie = (char*)malloc(sizeof(char)*(strlen(ext) + 1));
	strcpy(f.extensie, ext);
	f.dimensiune = dim;

	return f;
}
void afisareFisier(Fisier f) {
	printf("\nFisierul %s are calea absoluta %s, extensia %s si o dimensiune de %d bytes.", f.denumire, f.cale_absoluta, f.extensie, f.dimensiune);
}

void afisareInceputSfarsit(ListaDubla lista) {
	nod* temp = lista.prim;//dam adresa capului listei
	while (temp) {
		afisareFisier(temp->info);
		temp = temp->next;
	}
}

void afisareSfarsitInceput(ListaDubla lista) {
	nod* temp = lista.ultim;//adresa ultimului nod
	while (temp) {
		afisareFisier(temp->info);
		temp = temp->prev;//parcurgem de la nodul precedent
	}
}


ListaDubla inserareInceput(ListaDubla lista, Fisier f) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = f;
	nou->next = lista.prim;//adresa primului nod
	nou->prev = NULL;//e primul deci prev e null
	if (lista.prim) {
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	else {
		lista.prim = nou;
		lista.ultim = nou;
	}
	return lista;
}

ListaDubla inserareSfarsit(ListaDubla lista, Fisier f) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = f;
	nou->next = NULL;
	nou->prev = lista.ultim;
	if (lista.ultim) {
		lista.ultim->next = nou;
		lista.ultim = nou;
	}
	else {
		lista.prim = nou;
		lista.ultim = nou;
	}
	return lista;
}

void stergereLista(ListaDubla &lista) {
	nod* temp = lista.prim;
	while (temp) {
		free(temp->info.denumire);
		free(temp->info.cale_absoluta);
		free(temp->info.extensie);
		nod* aux = temp;
		temp = temp->next;
		free(aux);
	}
	lista.prim = NULL;
	lista.ultim = NULL;
}

void stergereListaSimpla(nod*& cap) {
	nod* temp = cap;
	while (temp) {
		free(temp->info.denumire);
		free(temp->info.cale_absoluta);
		free(temp->info.extensie);
		nod* aux = temp;
		temp = temp->next;
		free(aux);
	}
}

nod* inserareInceput(nod* cap, Fisier f) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = f;
	nou->next = cap;
	return nou;
}

//Cautare in lista dubla si salvare rezultat in lista simpla
nod* cautareDupaExtensie(ListaDubla lista, const char* extensie) {
	nod* listaRezultat = NULL;
	if (lista.prim) {
		nod* temp = lista.prim;
		while (temp) {
			if (strcmp(temp->info.extensie, extensie) == 0) {
				listaRezultat = inserareInceput(listaRezultat, temp->info);
			}
			temp = temp->next;
		}
	}
	return listaRezultat;
}

void afisareListaSimpla(nod* cap) {
	nod* temp = cap;
	while (temp) {
		afisareFisier(temp->info);
		temp = temp->next;
	}
}

Fisier cautareFisier(ListaDubla lista, const char* cale) {
	if (lista.prim) {
		nod* temp = lista.prim;
		while (temp) {
			if (strcmp(temp->info.cale_absoluta, cale) == 0) {
				return temp->info;
			}
			temp = temp->next;
		}
	}
}
//Modifica in ld
ListaDubla modificaCaleFisier(ListaDubla lista, const char* cale_curenta, const char* cale_deModificat) {
	if (lista.prim) {
		Fisier f;
		f = cautareFisier(lista, cale_curenta);
		strcpy(f.cale_absoluta, cale_deModificat);
	}
	return lista;
}

//Functie de stergere dupa dimensiune
Fisier stergereDupaDimensiune(ListaDubla* lista, unsigned int dimensiune) {
	nod* temp = lista->prim;
	while (temp) {
		if (temp->info.dimensiune == dimensiune) {
			Fisier rezultat = creareFisier(temp->info.denumire, temp->info.cale_absoluta, temp->info.extensie, temp->info.dimensiune);
			if (temp->prev) {
				temp->prev->next = temp->next;
				if (temp->next) {
					//suntem intre 2 noduri
					temp->next->prev = temp->prev;
				}
				else {
					//suntem pe ultimul nod
					lista->ultim = temp->prev;
					if (lista->ultim == NULL) {
						lista->prim = NULL;
					}
				}
			}
			else {
				//suntem pe primul nod
				if (temp->next) {
					temp->next = lista->prim;
					temp->next->prev = NULL;
				}
				else {
					lista->prim = NULL;
					lista->ultim = NULL;
				}
			}
			free(temp->info.denumire);
			free(temp->info.cale_absoluta);
			free(temp->info.extensie);
			free(temp);
			return rezultat;
		}
		temp = temp->next;

	}
	if (temp->info.dimensiune != dimensiune) {
		return creareFisier("", "", "", 0);
	}
}


Fisier extragereDinListaDupaDenumire(ListaDubla &lista, const char* denumire) {
	nod* temp = lista.prim;
	while (temp && strcmp(temp->info.denumire, denumire) != 0) {
		temp = temp->next;
	}
	if (temp) {
		Fisier rezultat = temp->info;
		if (temp->prev) {
			temp->prev->next = temp->next;
			if (temp->next) {
				temp->next->prev = temp->prev;
			}
			else {
				lista.ultim = temp->prev;
			}
			free(temp);
		}
		else {
			lista.prim = temp->next;
			lista.prim->prev = NULL;
			free(temp);
		}
		return rezultat;
	}
	else {
		return creareFisier("", "", "", 0);
	}
}

//Inserare sortata dupa dimensiune
ListaDubla inserareSortata(ListaDubla lista, Fisier f) {
	if (lista.prim) {
		nod* temp = lista.prim;
		while (temp && strcmp(temp->info.denumire,f.denumire)<0) {//temp->info.dimensiune<f.dimensiune
			temp = temp->next;
		}
		if (temp) {
			nod* nou = (nod*)malloc(sizeof(nod));
			nou->info = f;
			nou->next = temp;
			nou->prev = temp->prev;
			if (temp->prev) {
				temp->prev->next = nou;
			}
			else {
				lista.prim = nou;
			}
			temp->prev = nou;
		}
		else {
			nod* nou = (nod*)malloc(sizeof(nod));
			nou->info = f;
			nou->next = NULL;
			nou->prev = lista.ultim;
			lista.ultim->next = nou;
			lista.ultim = nou;
		}
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = f;
		nou->next = NULL;
		nou->prev = NULL;
		lista.prim = nou;
		lista.ultim = nou;
	}
	return lista;
}

//Inserare pe pozitie
ListaDubla inserarePePozitie(Fisier f, ListaDubla lista, int pozitie) {
	if (pozitie <= 1 || lista.prim == NULL) {
		lista = inserareInceput(lista, f);
		return lista;
	}
	else {
		int contor = 1;
		nod* temp = lista.prim;
		while (temp && contor < pozitie) {
			temp = temp->next;
			contor++;
		}
		if (temp) {
			nod* nou = (nod*)malloc(sizeof(nod));
			nou->info = f;
			nou->next = temp;
			nou->prev = temp->prev;
			temp->prev->next = nou;
			temp->prev = nou;
			return lista;
		}
		else {
			lista = inserareSfarsit(lista, f);
			return lista;
		}
	}
}



void main() {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	lista = inserareInceput(lista, creareFisier("Student", "C:\\Users\\Stud", ".txt", 10));
	lista = inserareInceput(lista, creareFisier("Poza", "C:\\Users\\Pics", ".png", 2000));
	lista = inserareInceput(lista, creareFisier("Retete", "C:\\Users\\Gastro", ".txt", 500));
	lista = inserareInceput(lista, creareFisier("Index", "C:\\Users\\Site", ".html", 105));
	lista = inserareInceput(lista, creareFisier("Script", "C:\\Users\\Scripts", ".js", 86));

	/*printf("\nLista afisata de la inceput la sfarsit este: ");
	afisareInceputSfarsit(lista);
	printf("\n***************************");

	printf("\nLista afisata de la sfarsit la inceput este: ");
	afisareSfarsitInceput(lista);

	nod* rezultat = cautareDupaExtensie(lista, ".txt");
	printf("\nLista cu fisierele care au extensia cautata: ");
	afisareListaSimpla(rezultat);

	printf("\nAfisare lista modificata: ");
	lista = modificaCaleFisier(lista, "C:\\Users\\Stud", "C:\\Users\\StudentModificat");
	afisareInceputSfarsit(lista);

	Fisier cautat = stergereDupaDimensiune(&lista, 500);
	printf("\nFisierul cautat este:");
	afisareFisier(cautat);
	printf("\n\n****");
	printf("\nDupa extragere lista este ");
	afisareInceputSfarsit(lista);
	printf("\n\nAfisare element extras:");
	afisareFisier(extragereDinListaDupaDenumire(lista, "Index"));
	printf("\n\nLista dupa extragere:");
	afisareInceputSfarsit(lista
	*/
	

	lista = inserarePePozitie(creareFisier("User", "C:\\Users\\User", ".txt", 45), lista, 3);
	afisareInceputSfarsit(lista);

	
}