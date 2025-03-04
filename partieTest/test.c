/* test.c - 13/03/2013 - Romain Dubessy Exemple de programme. */
#include <stdio.h>          /*bibliotheque stqndart des entrees et sorties*/

#define SIZE 10         /*fixer la taille du tableau*/

void initialiser(int* tab);
void trier(int* tab);
void afficher(int tab[]);
int main(int argc, char* argv[])
{
    if (argc != 1)
    {
        fprintf(stderr, "Utilisation: %s\n", argv[0]);
        return 1;
    }
    else
    {
        int tab[SIZE];
        initialiser(tab);
        afficher(tab);
        trier(tab);
        afficher(tab);
        printf("Taper entrée pour quitter!\n");
        getchar();
    }
    return 0;
}
void initialiser(int* tab)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < SIZE; i++)
        tab[i] = rand() % 1000;
}
void trier(int* tab)
{
    int i;

    int j; /*declaration de j*/

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE - 1 - i; j++)
        {
            if (tab[j] > tab[j + 1])
            {
                int tmp = tab[j];       /*imission du popint virgule*/
                    tab[j] = tab[j + 1];
                tab[j + 1] = tmp;
            }
        }
    }
}
void afficher(int tab[])
{
    int i;
    printf("Tableau:");
    for (i = 0; i <= SIZE; i ++)        /*mission du + on fait i++ au lieu de i+*/
        printf(" %d", tab[i]);
    printf("\n");
}
/* test.c */