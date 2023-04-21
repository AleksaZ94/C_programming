/*
 d) Za zadatu naučnu oblast izbrisati sve naučnike koji su
 se bavili tom oblašću (izbrisati iz liste) i preostale
 naučnike sačuvati u fajlu koji nosi naziv preostali.txt.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define MAXR 20
#define MAXO 30
#define MAX 150

typedef struct naucnik{
    char ime[MAXR];
    char prezime[MAXR];
    unsigned int br_rad;
    char oblast[MAXO];
    struct naucnik* sledeci;
}naucnik;

struct naucnik* glava;

void unos(char*, naucnik n, int*);
void ispisi();
void zadati(char*, int);
double prosek(double*);
int poredjenje(char*, char*);
void oblast(char*);
void preostali(char*);
void ispisi_pr();

int main(int brArg, char* arg[0])
{
    naucnik n;
    int pozicije[MAX];
    double pr_ocena = 0;
    int x = 0; //broj naucnika koji ce se kasnije korigovati u okviru funkcije
    int zad = 0;
    int z = 0;
    glava = NULL;
    if(brArg < 4)
    {
        printf("Nedovoljan broj argumenata!");
        exit(EXIT_FAILURE);
    }
    unos(arg[1],n, &x);
    //ispisi();
    sscanf(arg[3], "%d", &zad);
    zadati(arg[2],zad);
    //ispisi();
    prosek(&pr_ocena);
    printf("Prosecna duzina prezimena je: %.2lf\n", pr_ocena);
    char zad_o[MAX];
    printf("Unesi zadatu oblast: ");
    fgets(zad_o, sizeof(zad_o), stdin);
    *(zad_o + strlen(zad_o) - 1) = '\0';
    oblast(zad_o);
    preostali(zad_o);
    printf("\n");
    ispisi_pr();

    return 0;
}

void unos(char* input, naucnik n, int* x)
{
    FILE* f;
    f = fopen(input,"r");
    if(f == NULL)
    {
        printf("Greska prilikom otvaranja tekstualnog fajla %s", input);
        exit(EXIT_FAILURE);
    }
    while(fscanf(f, "%s %s %u %s", n.ime, n.prezime, &n.br_rad, n.oblast) != EOF)
    {
        (*x)++;
        if(glava==NULL)
        {
            naucnik* temp = (naucnik*)malloc(sizeof(naucnik));
            strcpy(temp->ime,n.ime);
            strcpy(temp->prezime,n.prezime);
            temp->br_rad = n.br_rad;
            strcpy(temp->oblast,n.oblast);
            temp->sledeci = NULL;
            glava = temp;
        }
        else
        {
            naucnik* temp2 = glava;
            while(temp2->sledeci != NULL)
            {
                temp2 = temp2->sledeci;
            }
            naucnik* temp = (naucnik*)malloc(sizeof(naucnik));
            strcpy(temp->ime,n.ime);
            strcpy(temp->prezime,n.prezime);
            temp->br_rad = n.br_rad;
            strcpy(temp->oblast,n.oblast);
            temp->sledeci = NULL;
            temp2->sledeci = temp;
        }
    }
    fclose(f);
}

void ispisi()
{
    naucnik* temp = glava;
    while(temp)
    {
        printf("%s %s %u %s \n", temp->ime, temp->prezime, temp->br_rad, temp->oblast);
        temp = temp->sledeci;
    }
}

void zadati(char* output, int zad)
{
    FILE* f;
    f = fopen(output,"w");
    if(f == NULL)
    {
        printf("Greska prilikom otvaranja fajla %s", output);
        exit(EXIT_FAILURE);
    }
    naucnik* temp = glava;
    while(temp)
    {
        if(temp->br_rad > zad)
        {
            fprintf(f,"%s %s %u %s\n", temp->ime, temp->prezime, temp->br_rad, temp->oblast);
        }
        temp = temp->sledeci;
    }
}

double prosek(double *pr_ocena)
{
    char* jedinstvena_prezimena[MAX];
    int flag = 0;
    int br_jed = 0;
    int suma = 0;
    int i = 0;
    naucnik* temp = glava; // krecemo od samog korena liste
    while(temp != NULL)
    {
        flag = 1;
        for(i = 0; i < br_jed; i++)
        {
            if(strcmp(jedinstvena_prezimena[i],temp->prezime) == 0)
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            jedinstvena_prezimena[br_jed] = temp->prezime;
            suma += strlen(jedinstvena_prezimena[br_jed]);
            br_jed++;
        }
        temp = temp->sledeci;
    }
    *pr_ocena = (double)suma/br_jed;
    return *pr_ocena;
}

int poredjenje(char *k , char *o)
{
    int x,y,p,i;
    p = 1;
    x = strlen(k);
    y = strlen(o);
    //printf("%s %s\n", k,o);
    if(x == y)
    {
        for(i = 0; i < x; i++)
        {
            if(k[i] != o[i])
            {
                p = 0;
                break;
            }
            else
            {
                p = 1;
            }
        }
    }
    else
    {
        p = 0;
    }
    return p;
}

void oblast(char* s)
{
   FILE* f;
   int suma = 0;
   char ime_datoteke[MAX];
   *(ime_datoteke) = '\0';
   strcpy(ime_datoteke,s);
   f = fopen(strcat(ime_datoteke,".txt"),"w");
   if(f == NULL)
   {
       printf("Greska prilikom otvaranja datoteke!\n");
       exit(EXIT_FAILURE);
   }
   naucnik* temp = glava;
   while(temp)
   {
       if(poredjenje(temp->oblast,s) == 1)
       {
           suma+= temp->br_rad;
       }
       temp = temp->sledeci;
   }
   fprintf(f,"Broj radova za zadatu naucnu oblast %s je: %d\n", s, suma);
   fclose(f);
}

void preostali(char* s)
{
   naucnik* temp = glava;
   naucnik* temp2;

   while(temp != NULL)
   {
       if(poredjenje(temp->oblast,s) == 1)
       {
           if(temp == glava)
           {
               glava = temp->sledeci;
               temp2 = temp;
               temp = temp->sledeci;
               free(temp2);
           }
           else
           {
             naucnik* temp3 = temp;
             temp2->sledeci = temp->sledeci;
             temp = temp->sledeci;
             if(temp == NULL)
             {
                 free(temp3);
                 break;
             }
             free(temp3);
           }

       }
       else
       {
           temp2 = temp;
           temp = temp->sledeci;
       }
   }
}

void ispisi_pr()
{
    FILE* f;
    f = fopen("preostali_nacnici.txt", "w");
    if(f == NULL)
    {
        printf("Greska prilikom otvaranj datoteke!");
        exit(EXIT_FAILURE);
    }
    naucnik* temp = glava;
    while(temp)
    {
        printf("%s %s %u %s \n", temp->ime, temp->prezime, temp->br_rad, temp->oblast);
        fprintf(f,"%s %s %u %s\n", temp->ime, temp->prezime, temp->br_rad, temp->oblast);
        temp = temp->sledeci;
    }
    fclose(f);
}
