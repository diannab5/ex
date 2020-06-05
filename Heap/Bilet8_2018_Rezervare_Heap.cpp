#include<iostream>
#pragma warning(disable:4996)

struct Rezervare
{
	int	idRezervare;
	char* numeClient;
	char* nrTelefon;
	int	canal;
	int	durata;
};

struct Heap
{
	int dim;
	Rezervare* vector;
};

Rezervare creareRezervare(int id, int canal, int durata, char *numeClient, char *nrTelefon)
{
	Rezervare pNou;
	pNou.idRezervare = id;

	pNou.canal = canal;

	pNou.durata = durata;

	pNou.numeClient = (char*)malloc((strlen(numeClient) + 1) * sizeof(char));
	strcpy(pNou.numeClient, numeClient);

	pNou.nrTelefon = (char*)malloc((strlen(nrTelefon) + 1) * sizeof(char));
	strcpy(pNou.nrTelefon, nrTelefon);

	return pNou;
}

void afisareRezervare(Rezervare r)
{
	printf("\n%d %s %s %d %d\n", r.durata, r.numeClient, r.nrTelefon, r.canal, r.idRezervare);
}

void filtrareHeap(Heap heap, int pozRad)
{
	int fiuStanga = 2 * pozRad + 1;
	int fiuDreapta = 2 * pozRad + 2;

	int pozMax = pozRad;

	if (fiuStanga<heap.dim && heap.vector[fiuStanga].durata>heap.vector[pozMax].durata)
		pozMax = fiuStanga;
	if (fiuDreapta<heap.dim && heap.vector[fiuDreapta].durata>heap.vector[pozMax].durata)
		pozMax = fiuDreapta;

	if (pozMax != pozRad)
	{
		Rezervare temp = heap.vector[pozRad];
		heap.vector[pozRad] = heap.vector[pozMax];
		heap.vector[pozMax] = temp;

		if (pozMax < (heap.dim - 1) / 2)
		{
			filtrareHeap(heap, pozMax);
		}
	}
}

void filtrare(Heap h, int index)
{
	int indexMax = index;
	int indexS = 2 * index + 1;
	int indexD = 2 * index + 2;

	if (indexS<h.dim && h.vector[indexS].durata>h.vector[indexMax].durata)
		indexMax = indexS;
	if (indexD<h.dim && h.vector[indexD].durata>h.vector[indexMax].durata)
		indexMax = indexD;

	if (index != indexMax)
	{
		Rezervare temp = h.vector[index];
		h.vector[index] = h.vector[indexMax];
		h.vector[indexMax] = temp;

		filtrare(h, indexMax);
	}
}

Heap inserare(Heap h, Rezervare elem)
{
	Rezervare* vect1 = (Rezervare*)malloc((h.dim + 1) * sizeof(Rezervare));
	for (int i = 0; i<h.dim; i++)
		vect1[i] = h.vector[i];
	//
	vect1[h.dim] = elem;
	h.dim++;
	free(h.vector);
	h.vector = vect1;

	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	return h;
}

void afisareHeap(Heap heap)
{
	if (heap.vector)
	{
		for (int i = 0; i < heap.dim; i++)
		{
			afisareRezervare(heap.vector[i]);
		}
	}
}

Rezervare extragereRezervare(Heap* heap)
{
	if (heap->vector)
	{
		Rezervare rez = heap->vector[0];
		heap->vector[0] = heap->vector[heap->dim - 1];
		heap->vector[heap->dim - 1] = rez;
		heap->dim--;

		for (int i = (heap->dim - 1) / 2; i >= 0; i--)
		{
			filtrareHeap(*heap, i);
		}

		return rez;
	}
}

void main()
{
	Heap h;

	h.dim = 5;
	h.vector = (Rezervare*)malloc(h.dim * sizeof(Rezervare));

	h.vector[0] = creareRezervare(111, 1, 3, "Gigel", "0722333444");
	h.vector[1] = creareRezervare(222, 0, 2, "Dorel", "0744111222");
	h.vector[2] = creareRezervare(333, 1, 4, "Ionel", "0755000111");
	h.vector[3] = creareRezervare(444, 0, 5, "Maria", "0722888999");
	h.vector[4] = creareRezervare(555, 1, 1, "Vasile", "0722555777");

	for (int i = (h.dim - 1) / 2; i >= 0; i--)
	{
		filtrareHeap(h, i);
		
	}
		

	afisareHeap(h);

	printf("\n--------------------------\n");

	Rezervare r = creareRezervare(1234, 1, 2, "Marcel", "0213051234");
	h = inserare(h, r);

	afisareHeap(h);

	printf("\nRezervare extrasa: \n");
	Rezervare rex = extragereRezervare(&h);
	afisareRezervare(rex);
	printf("\n--------------------------\n");
	afisareHeap(h);
	

}