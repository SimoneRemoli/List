#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <tgmath.h>

/*Una matrice sparsa è una matrice in cui la maggior parte degli elementi sono zero, ovverosia una
matrice è sparsa se almeno (m * n) / 2 elementi sono zero.

Funzione C che accetta in input una matrice di dimensione arbitraria e restituisce
true se questa matrice è sparsa.*/

bool check_matrice_sparsa(int,int,int*);
void views(int,int,int*);
void load(int,int,int*);


int main(int argc, char *argv[])
{
	int righe,colonne;
	printf("Inserisci la dimensione delle righe : \n"); 
	scanf("%d",&righe);
	printf("Inserisci la dimensione delle colonne : \n");
	scanf("%d",&colonne);
	int *mat = malloc(righe*colonne*sizeof(int));
	load(righe,colonne,mat);
	views(righe,colonne,mat);
	if(check_matrice_sparsa(righe,colonne,mat))
		printf("La matrice è sparsa [*]\n");
	else
		printf("La matrice non è sparsa [*]\n");
	return 0;
}
void load(int righe,int colonne, int *mat)
{
	srand((unsigned int)time(NULL));
	for(int i=0;i<righe;i++)
	{
		for(int j=0;j<colonne;j++)
		{
			*(mat + i*colonne + j) = rand()%3;
		}
	}
}
void views(int righe,int colonne, int *mat)
{
	printf("\n");
	for(int i=0;i<righe;i++)
	{
		for(int j=0;j<colonne;j++)
		{
			printf("%d \t",*(mat + i*colonne + j));
		}
		printf("\n");
		printf("\n");
	}
}
bool check_matrice_sparsa(int righe,int colonne,int *mat)
{
	int count = 0;
	for(int i=0;i<righe;i++)
	{
		for(int j=0;j<colonne;j++)
		{
			if((*(mat + i*colonne + j)) == 0)
			{
				count++;
			}
		}
	}
	printf("Sono presenti %d zeri [*]\n",count);
	if(count >= ((righe*colonne)/2))
		return true;
	return false;
}