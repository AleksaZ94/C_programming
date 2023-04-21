#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXR 20
#define MAXO 30

typedef struct naucnik{
    char ime[MAXR];
    char prezime[MAXR];
    unsigned int br_rad;
    char oblast[MAXO];
    struct naucnik* sledeci;
}naucnik;

struct naucnik* glava;

void unos(char*, int*);

int main(int brArg, char* arg[0])
{
    int n = 0; //broj naucnika koji ce se kasnije korigovati u okviru funkcije
    glava = NULL;
    if(brArg < 4)
    {
        printf("Nedovoljan broj argumenata!");
        exit(EXIT_FAILURE);
    }
    unos(arg[1], &n);

    return 0;
}

void unos(char* input, int* n)
{
    FILE* f;
    f = fopen(input,"r");
    if(f == NULL)
    {
        printf("Greska prilikom otvaranja tekstualnog fajla %s", input);
        exit(EXIT_FAILURE);
    }
    while(fscanf(f, "%s %s %u %s", naucnik->ime, naucnik->prezime, naucnik->br_rad, naucnik->oblast) != EOF)
    {
        if(glava==NULL)
        {
            naucnik* temp = (naucnik*)malloc(sizeof(naucnik));
            naucnik->ime = naucnik->ime;
            naucnik->prezime = naucnik->prezime;
            naucnik->br_rad = naucnik->br_rad;
            naucnik->oblast = naucnik->oblast;
            naucnik->sledeci = NULL;
            glava = temp;
        }
        else
        {
            naucnik* temp2 = glava;
            while(temp2)
            {
                temp2 = temp2->sledeci;
            }
            naucnik* temp = (naucnik*)malloc(sizeof(naucnik));
            temp->sledeci = NULL;
            temp2->sledeci = temp;
        }
    }

}
