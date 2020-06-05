#include<stdio.h>
#include<malloc.h>
#include<string.h>



struct Imobil
{
	unsigned int idImobil; //cheie
	char* numeStrada;
	unsigned int nrStrada;
	int nrApartamente;
	int* nrLocatari;
	float valTotalaPlata;
};

Imobil initImobil(unsigned int id,const char* numeStrada, unsigned int nrStrada, int nrApartamente, int* nrLocatari, float valPlata)
{
	Imobil imobil;
	imobil.idImobil = id;
	imobil.numeStrada = (char*)malloc(sizeof(char)*(strlen(numeStrada) + 1));
	strcpy(imobil.numeStrada, numeStrada);
	imobil.nrApartamente = nrApartamente;
	imobil.nrStrada = nrStrada;
	imobil.nrLocatari = (int*)malloc(sizeof(int)*nrApartamente);
	for (int i = 0; i < nrApartamente; i++)
	{
		imobil.nrLocatari[i] = nrLocatari[i];
	}
	imobil.valTotalaPlata = valPlata;
	return imobil;
}

void afisareImobil(Imobil imobil)
{
	printf("\nId: %d,nume strada: %s,nr strada: %d,nr apartamente din bloc: %d, val totala plata: %5.2f\n", imobil.idImobil, imobil.numeStrada, imobil.nrStrada, imobil.nrApartamente, imobil.valTotalaPlata);
	printf("numar locatari din fiecare apartament:");
	for (int i = 0; i < imobil.nrApartamente; i++)
	{
		printf(" %d", imobil.nrLocatari[i]);
	}
}


struct nod
{
	Imobil info;
	nod *st;
	nod *dr;
};

int calculInaltimeArbore(nod* rad)
{
	if (rad)
	{
		int inaltimST = calculInaltimeArbore(rad->st);
		int inaltimeDR = calculInaltimeArbore(rad->dr);
		return 1 + (inaltimST > inaltimeDR ? inaltimST : inaltimeDR);
	}
	else
	{
		return 0;
	}

}

int calculGE(nod* rad)
{
	if (rad)
	{
		int inaltimeST = calculInaltimeArbore(rad->st);
		int inaltimeDR = calculInaltimeArbore(rad->dr);
		return inaltimeST - inaltimeDR;
	}
	else
	{
		return 0;
	}
}

nod* rotireLaStanga(nod* rad)
{
	if (rad)
	{
		nod* temp = rad->dr;
		rad->dr = temp->st;
		temp->st = rad;
		return temp;
	}
	else
	{
		return rad;
	}
}

nod* rotireLaDreapta(nod* rad)
{
	if (rad)
	{
		nod* temp = rad->st;
		rad->st = temp->dr;
		temp->dr = rad;
		return temp;
	}
	else
	{
		return rad;
	}
}


nod* inserareInAVL(nod* rad, Imobil i)
{
	if (rad)
	{
		if (rad->info.idImobil >i.idImobil)
		{
			rad->st = inserareInAVL(rad->st, i);
		}
		else if (rad->info.idImobil < i.idImobil)
		{
			rad->dr = inserareInAVL(rad->dr, i);
		}
		
		//inainte sa returnez radacina fac verificari
		if (calculGE(rad) == 2)
		{
			if (calculGE(rad->st) != 1)
			{
				rad->st = rotireLaStanga(rad->st);
			}
			rad = rotireLaDreapta(rad);
		}
		if (calculGE(rad) == -2)
		{
			if (calculGE(rad->dr) != -1)
			{
				rad->dr = rotireLaDreapta(rad->dr);
			}
			rad = rotireLaStanga(rad);
		}
		return rad;
	}
	else
	{
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->dr = nou->st = NULL;
		nou->info = initImobil(i.idImobil, i.numeStrada, i.nrStrada,i.nrApartamente, i.nrLocatari, i.valTotalaPlata);
		return nou;
	}
}


void afisareInordine(nod *rad)
{
	if (rad)
	{
		afisareInordine(rad->st);
		afisareImobil(rad->info);
		afisareInordine(rad->dr);
	}
}


void numarImobileDePeOstrada(nod* rad, const char* denumireStrada, int &nrImobile)
{
	if (rad)
	{
		numarImobileDePeOstrada(rad->st, denumireStrada, nrImobile);
		if (strcmp(denumireStrada, rad->info.numeStrada) == 0)
		{
			nrImobile++;
		}
		numarImobileDePeOstrada(rad->dr, denumireStrada, nrImobile);

	}
}

float valoarePlata(nod* rad, unsigned int idImobil)
{
	if (rad)
	{
		valoarePlata(rad->st, idImobil);
			valoarePlata(rad->dr, idImobil);
		if (rad->info.idImobil == idImobil)
		{
			int nrTotalDeLocatari = 0;
			for (int i = 0; i < rad->info.nrApartamente; i++)
			{
				nrTotalDeLocatari += rad->info.nrLocatari[i];
			}
			return rad->info.valTotalaPlata / nrTotalDeLocatari;
		}
	}
}
void main()
{

	nod* rad = NULL;

	int* pers1 = (int*)malloc(sizeof(int) * 5);
	pers1[0] = 2;
	pers1[1] = 3;
	pers1[2] = 4;
	pers1[3] = 5;
	pers1[4] = 2;

	int* pers2 = (int*)malloc(sizeof(int) * 3);
	pers2[0] = 2;
	pers2[1] = 3;
	pers2[2] = 4;

	int* pers3 = (int*)malloc(sizeof(int) * 5);
	pers3[0] = 2;
	pers3[1] = 3;
	pers3[2] = 1;
	pers3[3] = 5;
	pers3[4] = 2;

	int* pers4 = (int*)malloc(sizeof(int) * 2);
	pers4[0] = 2;
	pers4[1] = 3;

	int* pers5 = (int*)malloc(sizeof(int) * 6);
	pers5[0] = 2;
	pers5[1] = 3;
	pers5[2] = 4;
	pers5[3] = 5;
	pers5[4] = 2;
	pers5[5] = 3;

	rad = inserareInAVL(rad, initImobil(23, "Strada Fizicienilor", 18, 5, pers1, 2500));
	rad = inserareInAVL(rad, initImobil(15, "Strada Panselutelor", 47, 3, pers2, 1700));
	rad = inserareInAVL(rad, initImobil(68, "Strada Panselutelor", 20, 5, pers3, 9500));
	rad = inserareInAVL(rad, initImobil(42, "Strada Plutonier", 8, 2, pers4, 5500));
	rad = inserareInAVL(rad, initImobil(53, "Strada Fizicienilor", 11, 6, pers5, 4000));

	afisareInordine(rad);

	int nrImobilee = 0;
	numarImobileDePeOstrada(rad, "Strada Fizicienilor", nrImobilee);
	printf("\n\nNr de imobile de pe strada fizicienilor %d", nrImobilee);

	float plata = valoarePlata(rad, 23);
	printf("\n\nPlata pentru o persoana din imobilul cerut este: %5.2f lei.", plata);

}