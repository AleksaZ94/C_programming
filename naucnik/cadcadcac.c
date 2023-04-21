#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define MAXK 30
#define MAXN 20
#define MAXX 500

typedef struct{
   char ime[MAX];
   char prezime[MAX];
   int br_radova;
   char oblast[MAXK];
}naucnik;

void unos(char*, naucnik s[], int*);
void podaci(char*, naucnik s[], int, int);
void pr_duzina(naucnik s[], int);
void zad_oblast(naucnik s[], int);
int poredjenje(char*, char*);

int main(int brArg, char* arg[0])
{
    int n = 0;
    naucnik s[MAXN];
    if(brArg < 4)
    {
        printf("Nedovoljan broj argumenata!");
        exit(EXIT_FAILURE);
    }
    unos(arg[1],s,&n);
    int k;
    sscanf(arg[3],"%d", &k);
   // printf("%d", k);
    podaci(arg[2], s, n, k);
    pr_duzina(s,n);
    zad_oblast(s,n);
    return 0;
}

void unos(char* input, naucnik s[], int* z)
{
    FILE* f;
    *z = 0;
    char line[MAXX];
    f = fopen(input,"r");
    if(f == NULL)
    {
        printf("Greska prilikom otvaranja datoteke!");
        exit(EXIT_FAILURE);
    }
   int p;
    while(fgets(line,MAXX,f) != NULL)
    {
        //printf("%s", line);
        if((*z) % 2 == 0 || (*z) == 0)
        {
            p = (*z)/2;
            sscanf(line,"%s %s %d %s\r\n", s[p].ime, s[p].prezime, &s[p].br_radova, s[p].oblast);
        }
        (*z)++;
    }
    (*z) = p + 1;
    fclose(f);
}

void podaci(char* output, naucnik s[], int n, int zad)
{
    FILE* f;
    int i;
    f = fopen(output, "w");
    if(f == NULL)
    {
        printf("Greska prilikom citanja datoteke!");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < n; i++)
    {
        if(s[i].br_radova > zad)
        {
            fprintf(f,"%s %s %d %s\n", s[i].ime, s[i].prezime, s[i].br_radova, s[i].oblast);
        }
    }
    fclose(f);
}

void pr_duzina(naucnik s[], int n)
{
    float suma = 0;
    float rez;
    int i,j,x;
    char novi[MAX][MAX];
    int koric = 0;
    int z = 0;
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(j == n)
            {
                break;
            }
            if(poredjenje(s[i].prezime,s[j].prezime) == 0)
            {
               koric = 1;
            }
        }
        if(koric == 0)
        {
            strcpy(novi[z++],s[i].prezime);
            //printf("%s", s[i].prezime);
        }
        koric = 0;
    }
    for(i = 0; i < z; i++)
    {
       x = strlen(novi[i]);
       suma += x;
    }
    rez = suma/z;
    printf("Prosecna duzina prezimena je: %.2f", rez);
}

void zad_oblast(naucnik s[], int n)
{
    FILE* f;
    int i;
    int suma = 0;
    f = fopen("matematika.txt", "w");
    if(f == NULL)
    {
        printf("Greska prilikom otvaranj datoteke!");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < n; i++)
    {
        if(strcmp(s[i].oblast,"matematika") == 0)
        {
            suma += s[i].br_radova;
        }
    }
    fprintf(f,"Ukupan broj objavljenih radova za zadatu oblast matematika: %d", suma);
    fclose(f);
}

int poredjenje(char* k,char* m)
{
    int x,y,i;
    int p = 0;
    x = strlen(k);
    y = strlen(m);
    printf("%s %s\n", k,m);
    if(x == y)
    {
        for(i = 0; i < x; i++)
        {
            if(k[i] != m[i])
            {
                p = 1;
            }
            else
            {
                p = 0;
            }
            k++;
            m++;
        }
    }
    else
    {
        p = 1;
    }
    return p;
}
