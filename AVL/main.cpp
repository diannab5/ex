#include <iostream>

struct Articol{
    int id;
    char* titlu;
    char* categorie;
    int numarPagini;
    int numarAutori;
    
};

struct Nod{
    Articol a;
    Nod *next;
};

int hashFunction(int size, char* cheie){
    int s = 0;
    for(int i = 0; i < strlen(cheie); i++){
        s+=cheie[i];
    }
    
    return s%size;
}

Nod* creareNodLista(Articol a){
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->a.categorie = (char*)malloc(sizeof(char) * strlen(a.categorie));
    strcpy(nou->a.categorie, a.categorie);
    nou->a.titlu = (char*)malloc(sizeof(char) * strlen(a.titlu));
    strcpy(nou->a.titlu, a.titlu);
    nou->a.id = a.id;
    nou->a.numarAutori = a.numarAutori;
    nou->a.numarPagini = a.numarPagini;
    nou->next = NULL;
    return nou;
}

Articol creareArticol(Articol a){
    Articol nou;
    nou.categorie = (char*)malloc(sizeof(char) * strlen(a.categorie));
    strcpy(nou.categorie, a.categorie);
    nou.titlu = (char*)malloc(sizeof(char) * strlen(a.titlu));
    strcpy(nou.titlu, a.titlu);
    nou.id = a.id;
    nou.numarAutori = a.numarAutori;
    nou.numarPagini = a.numarPagini;

    return nou;
}

Nod* inserareLista(Nod* cap, Articol a){
    Nod* nou = creareNodLista(a);
    if(cap == NULL){
        cap = nou;
    }else{
        Nod* temp = cap;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nou;
    }
    return cap;
}

void inserareChaining(Nod** hTab, Articol a, int size){
    if(hTab != NULL){
        int poz = hashFunction(size, a.categorie);
        hTab[poz] = inserareLista(hTab[poz], a);
    }
}

void traversareHashTabel(Nod** hTab, int size){
    printf("\n\nTABELA DE DISPERSIE\n");
    for(int i = 0; i < size; i++){
        if(hTab[i]){
            printf("Lista %d \n", i);
            Nod* temp = hTab[i];
            while(temp != NULL){
                printf("%d, %s, %s, %d, %d\n", temp->a.id, temp->a.titlu, temp->a.categorie, temp->a.numarPagini, temp->a.numarAutori);
                temp = temp->next;
            }
            
        }
    }
}

int getNumarAutori(Nod** hTab, int size){
    int suma  = 0;
    for(int i = 0; i < size; i++){
        Nod* temp = hTab[i];
        while(temp != NULL){
            suma += temp->a.numarAutori;
            temp = temp->next;
        }
    }
    
    return suma;
}

Articol* getArticoleDinCategorie(Nod** hTab, int size, char* categorie, int &count){

    if(hTab){
        for(int i = 0; i < size; i++){
            if(hTab[i]){
                Nod* temp = hTab[i];
                while(temp != NULL){
                    if(strcmp(temp->a.categorie, categorie) == 0){
                        count++;
                    }
                    temp= temp->next;
                }
            }

        }
        
        Articol* vector = (Articol*)malloc(sizeof(Articol) * count);
        int j = 0;
        
        for(int i = 0; i < size; i++){
            if(hTab[i]){
                Nod* temp = hTab[i];
                while(temp != NULL){
                    if(strcmp(temp->a.categorie, categorie) == 0){
                        vector[j] = temp->a;
              
                        j++;
                    }
                    temp= temp->next;
                }
            }

        }
            return vector;
    }else{
        Articol* a = NULL;
        
        return a;
    }

}

void stergereNod(Nod* nod){
    free(nod->a.titlu);
    free(nod->a.categorie);
    free(nod);
}

void stergereElementLista(Nod** cap, int id){
    Nod* temp = *cap;
    if(temp->a.id == id){
        Nod* deSters = temp;
        temp = temp->next;
        stergereNod(deSters);
        *cap = temp;

   
    }
   
    while(temp->next != NULL){
        
        Nod* deSters = temp->next;
        if(deSters->a.id == id){
            temp->next = deSters->next;
            stergereNod(deSters);
        }
        temp = temp->next;
        
    }
    temp->next = NULL;
    

}



void stergereElementTabela(Nod** hTab, char* categorie, int id, int size){
    if(hTab){
        int poz = hashFunction(size, categorie);
        stergereElementLista(&hTab[poz], id);
    }
}

int* getPositions(Nod **hTab, int size, int &count){
    for(int i = 0; i < size; i++){
        if(hTab[i]){
            count++;
        }
    }
    
    int *positions = (int*)malloc(sizeof(int) * count);
    int j = 0;
    for(int i = 0; i < size; i++){
        if(hTab[i] != NULL){
            positions[j] = i;
            j++;
        }
    }
    
    return positions;
    
}

int getNumberOfPagesPerCategory(Nod* cap){
    Nod* temp = cap;
    int pages = 0;
    while(temp != NULL){
        pages += temp->a.numarPagini;
        temp = temp->next;
    }
    
    return pages;
}

int* getVectorPagini(Nod **hTab, int size, int &count){

    int *positions = getPositions(hTab, size, count);
    int* pages = (int*)malloc(sizeof(int) * count);
    int j = 0;
    for(int i = 0; i < count; i++){
        pages[j] = getNumberOfPagesPerCategory(hTab[positions[i]]);
        j++;
    }
    
    return pages;
}

Nod** marireNumarPagini(Nod** hTab, int size){
    for(int i = 0; i < size; i++){
        if(hTab[i]){
            Nod* temp = hTab[i];
            while(temp != NULL){
                temp->a.numarPagini += 1;
                temp= temp->next;
            }
        }

    }
    return hTab;
}


int main(int argc, const char * argv[]) {
    int size = 10;
    Nod** hTab = (Nod**)malloc(sizeof(Nod*) * size);
    for(int i = 0; i < size; i++){
        hTab[i] = NULL;
    }
    
    FILE *f;
    f = fopen("articole.txt", "r");
    char* token;
       
    char buf[120];
    Articol articol;
       
    while(fgets(buf, sizeof(buf), f)){
        token = strtok(buf, ",");
        articol.id = atoi(token);

        token =  strtok(NULL, ",");
        articol.titlu = (char*)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(articol.titlu, token);

        token =  strtok(NULL, ",");
        articol.categorie = (char*)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(articol.categorie, token);

        token =  strtok(NULL, ",");
        articol.numarPagini = atoi(token);

        token =  strtok(NULL, ",");
        articol.numarAutori = atoi(token);



        token = strtok(NULL, ",");
        if(token){
        printf("\nEroare preluare fisier");
        }

        inserareChaining(hTab, articol, size);

        articol.titlu = NULL;
        articol.categorie = NULL;

    }
    traversareHashTabel(hTab, size);
    
    int autori = getNumarAutori(hTab, size);
    printf("\nNumarul total de autori din tabela: %d\n", autori);
    Articol *vector;
    int count;
    
    vector = getArticoleDinCategorie(hTab, size, "Psiho", count);
    printf("\nVector de articole:");
    for(int i = 0; i < count; i++){
        printf("\n%d, %s, %s, %d, %d", vector[i].id, vector[i].titlu, vector[i].categorie,vector[i].numarPagini, vector[i].numarAutori);
    }
    
    stergereElementTabela(hTab, "SF", 11, size);
    hTab = marireNumarPagini(hTab, size);
    
    traversareHashTabel(hTab, size);
    int sizeVecPag = 0;
    int* pages = getVectorPagini(hTab, size, sizeVecPag);
    printf("\n\nVector pagini: ");
    for(int i = 0; i < sizeVecPag; i++){
        printf("%d ",pages[i]);
    }

}
