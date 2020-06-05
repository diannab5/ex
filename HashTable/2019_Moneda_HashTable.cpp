#include<stdio.h>
#include<malloc.h>
#include<string.h>


struct Moneda {
	char cod[3];
	char* denumire;
	char* emitent;
	int sold_valutar;
};

struct HashTable {
	Moneda* *vector;
	int dim;
};

struct nod {
	Moneda info;
	nod* next;
};

HashTable initHashTable(int dim) {
	HashTable h;
	h.dim = dim;
	h.vector = (Moneda**)malloc(sizeof(Moneda*)*dim);
	for (int i = 0; i < dim; i++) {
		h.vector[i] = NULL;
	}
	return h;
}
//functia de inserare e codul
int hashFunction(HashTable h, Moneda m) {
	int suma = 0;
	for (int i = 0; i < 3; i++) {
		suma += m.cod[i];
	}
	return suma % h.dim;
}
Moneda creareMoneda(const char cod[3], const char* denumire, const char* emitent, int sold) {
	Moneda m;
	strcpy(m.cod, cod);
	m.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(m.denumire, denumire);
	m.emitent = (char*)malloc(sizeof(char)*strlen(emitent) + 1);
	strcpy(m.emitent, emitent);
	m.sold_valutar = sold;

	return m;
}

int inserareHash(HashTable h, Moneda m) {
	if (h.dim > 0) {
		int hashCode = hashFunction(h, m);
		if (h.vector[hashCode]) {//avem coliziune
			int index = (hashCode + 1) % h.dim;
			while (index != hashCode) {
				if (h.vector[index] == NULL) {
					h.vector[index] = (Moneda*)malloc(sizeof(Moneda));
					*(h.vector[index]) = creareMoneda(m.cod, m.denumire, m.emitent, m.sold_valutar);
				}
				else {
					index = (index + 1) % h.dim;
				}
			}
			if (index == hashCode) {
				return -1; // nu mai exista loc in tabela
			}
			return index;

		}
		else {
			h.vector[hashCode] = (Moneda*)malloc(sizeof(Moneda));
			*(h.vector[hashCode]) = creareMoneda(m.cod, m.denumire, m.emitent, m.sold_valutar);
			return hashCode;
		}
	}
	else {
		return -2;//nu exista tabela
	}
}


void afisareMoneda(Moneda m) {
	printf("\nMoneda %s (%s) e emisa de %s si are soldul de %d", m.denumire, m.cod, m.emitent, m.sold_valutar);
}

void afisareTabela(HashTable h) {
	for (int i = 0; i < h.dim; i++) {
		if (h.vector[i]) {
			afisareMoneda(*(h.vector[i]));
		}
	}
}
void afisareLista(nod* cap) {
	while (cap) {
		afisareMoneda(cap->info);
		cap = cap->next;
	}
}

nod* inserareInceput(nod* cap, Moneda m) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareMoneda(m.cod, m.denumire, m.emitent, m.sold_valutar);
	nou->next = cap;

	return nou;
}

nod* cautareMonede(HashTable h, int val) {
	nod* rezultat = NULL; //lista in care imi tin monezile mai mari
	for (int i = 0; i < h.dim; i++) {
		if (h.vector[i]->sold_valutar > val) {
			rezultat = inserareInceput(rezultat, *(h.vector[i]));
		}
	}
	return rezultat;
}

HashTable modificareSold(HashTable h, int sold_initial, int sold_final) {
	for (int i = 0; i < h.dim; i++) {
		if (h.vector[i]->sold_valutar == sold_initial)
			h.vector[i]->sold_valutar = sold_final;
	}
	return h;
}

void main() {
	HashTable ht = initHashTable(5);
	inserareHash(ht, creareMoneda("RON", "Leu romanesc", "BNR", 500000));
	inserareHash(ht, creareMoneda("ERO", "Euro", "BE", 15500000));
	inserareHash(ht, creareMoneda("USD", "Dolar american", "BA", 5500000));
	inserareHash(ht, creareMoneda("RON", "Dolar canadian", "BC", 2500000));
	inserareHash(ht, creareMoneda("GLS", "Lira sterlina", "BGB", 1400000));

	afisareTabela(ht);

	printf("\n***********************");
	printf("\nMonezile cu sold mai mare de 500000 unitati sunt:");
	nod* rezultat;
	rezultat = cautareMonede(ht, 500000);
	afisareLista(rezultat);

	printf("\n***********************");
	printf("\nDupa modificarea stocului pentru RON, tabela este:");
	ht = modificareSold(ht, 500000, 300000);
	afisareTabela(ht);
}