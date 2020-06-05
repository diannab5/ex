#include<stdio.h>
#include<malloc.h>
#include<string.h>


struct Pacient
{
	int codPacient;
	char* numePacient;
	char* descriereProblema;
	float varsta;
	int prioritate;
};

struct HEAP
{
	Pacient* vector;
	int dim;
};

Pacient crearePacient(int codPacient, const char* numePacient,const char* descriereProblema, float varsta, int prioritate)
{
	Pacient p;
	p.codPacient = codPacient;
	p.numePacient = (char*)malloc(sizeof(char)*(strlen(numePacient) + 1));
	strcpy(p.numePacient, numePacient);
	p.descriereProblema = (char*)malloc(sizeof(char)*(strlen(descriereProblema) + 1));
	strcpy(p.descriereProblema, descriereProblema);
	p.varsta = varsta;
	p.prioritate = prioritate;
	return p;
}

void afisarePacient(Pacient p)
{
	printf("Cod pacient: %d, nume pacient: %s, problema: %s, varsta: %5.2f, prioritare %d\n", p.codPacient, p.numePacient, p.descriereProblema, p.varsta, p.prioritate);
}

void afisareHeap(HEAP heap)
{
	for (int i = 0; i < heap.dim; i++)
	{
		afisarePacient(heap.vector[i]);
	}
}

void filtrareHeap(HEAP heap, int pozitie)
{
	int fiuS = 2 * pozitie + 1;
	int fiuD = 2 * pozitie + 2;
	int max = pozitie;
	if (fiuS < heap.dim && heap.vector[max].prioritate < heap.vector[fiuS].prioritate)
	{
		max = fiuS;
	}
	if (fiuD < heap.dim && heap.vector[max].prioritate < heap.vector[fiuD].prioritate)
	{
		max = fiuD;
	}
	if (max != pozitie)
	{
		Pacient aux = heap.vector[max];
		heap.vector[max] = heap.vector[pozitie];
		heap.vector[pozitie] = aux;
		if (2 * max + 1 < heap.dim)
		{
			filtrareHeap(heap, max);
		}
	}
}


void modificaPrioritate(HEAP heap)
{
	if (heap.dim > 0)
	{
		for (int i = 0; i < heap.dim; i++)
		{
			if (heap.vector[i].prioritate != 5 && heap.vector[i].prioritate >= 2)
			{
				heap.vector[i].prioritate++;
			}
		}
	}
}

int determinareGravide(HEAP heap)
{
	int gravide = 0;
	if (heap.dim > 0)
	{
		for (int i = 0; i < heap.dim; i++)
		{
			if (heap.vector[i].prioritate == 5)
				gravide++;
		}
	}
	return gravide;
}


Pacient extragerePacient(HEAP &heap) {
	if (heap.dim > 0) {
		Pacient rezultat = heap.vector[0];
		Pacient* temp = (Pacient*)malloc(sizeof(Pacient)*(heap.dim - 1));

		for (int i = 0; i < heap.dim - 1; i++) {
			temp[i] = heap.vector[i + 1];
		}
		free(heap.vector);
		heap.vector = temp;
		heap.dim--;
		for (int i = (heap.dim - 2) / 2; i >= 0; i--) {
			filtrareHeap(heap, i);
		}
		return rezultat;
	}
	else {
		return crearePacient(0, "", "", 0, 0);
	}

}
void main()
{
	HEAP heap;
	heap.dim = 5;
	heap.vector = (Pacient*)malloc(sizeof(Pacient)*heap.dim);
	heap.vector[0] = crearePacient(4, "Diana", "Ecografie", 21, 5);
	heap.vector[1] = crearePacient(8, "Stefan", "Durere de cap", 22,3);
	heap.vector[2] = crearePacient(3, "Cristiana", "Raceala", 12, 4);
	heap.vector[3] = crearePacient(6, "Anabela", "Avort", 25, 5);
	heap.vector[4] = crearePacient(9, "Clarisa", "Deget umflat", 10, 1);
	afisareHeap(heap);
	for (int i = (heap.dim - 2) * 2; i >= 0; i--)
	{
		filtrareHeap(heap, i);
	}
	printf("\n\nDupa filtrare:\n");
	afisareHeap(heap);
	printf("\n\n\n");
	modificaPrioritate(heap);
	afisareHeap(heap);

	int nrgravide = determinareGravide(heap);
	printf("\n\nNr de gravide este: %d", nrgravide);
	extragerePacient(heap);
	printf("\n\nDupa stergere heap-ul este:");
	afisareHeap(heap);
}