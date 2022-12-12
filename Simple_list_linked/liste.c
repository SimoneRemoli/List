#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0

struct nodo
{
 int valore;
 struct nodo *next;     /* puntatore al nodo successivo */
};

struct nodo * Insert(struct nodo *);
struct nodo * crea_nodo(int);
bool lista_vuota(struct nodo * );
struct nodo * views (struct nodo *);



int main(int argc, char *argv[])
{
	bool finito;         
	int scelta;
	struct nodo *testa = NULL;  /* testa è il puntatore alla prima struttura nodo inserita */

	finito = false;

	printf("\n Valore iniziale di testa (NULL) : %p",testa);
	int somma_posiz_pari;
	int somma_posiz_dispari;
do
  {
  		printf("\n ");
   		printf(" 0  Fine Lavoro \n ");
   		printf(" 1  Inserimento \n ");     
   		printf(" 2  Elimina valore \n "); 
   		printf(" 3  Views \n ");    
   

   		do 
   		{
   			printf(" Immetti la scelta : ");
   			scanf("%d",&scelta);
   		} while((scelta < 0)||(scelta > 3));
   	
   	switch(scelta)
   	{
   		case 0:
   		{
   			finito = true;
   		}break;
   		case 1:
   		{
   			testa = Insert(testa);
   		}break;
   		case 3:
   		{
   			testa = views(testa);
   		}break;
   	}
  }while(finito == false); 
   	return 0;
}

struct nodo * Insert(struct nodo * testa)
{
	int val = 0;
	printf("Digita il valore da inserire : ");
	scanf(" %d",&val);

	struct nodo *prec = NULL;
	struct nodo *app = NULL;
	struct nodo *nuovo_nodo = NULL;

	nuovo_nodo = crea_nodo(val);

	if(lista_vuota(testa))
	{
		testa = nuovo_nodo;
	}
	else
	{
		if(testa->valore>nuovo_nodo->valore)
		{
			nuovo_nodo -> next = testa;
			testa = nuovo_nodo;
		}
		else
		{
			app = testa;
			while((app!=NULL)&&((nuovo_nodo->valore)>=(app->valore)))
			{
				prec = app;
				app = app->next;
			}
			nuovo_nodo -> next = app;
			prec ->next = nuovo_nodo;
		}
	}
	
	return testa;
}

bool lista_vuota(struct nodo *testa)
{
	if(testa == NULL)
		return true;
	else
		return false;
}

struct nodo * crea_nodo(int val)
{
	struct nodo * nuovo_nodo = NULL;
	nuovo_nodo = malloc(sizeof(struct nodo));
	nuovo_nodo->valore = val;
	nuovo_nodo->next = NULL;
	return nuovo_nodo;
}

struct nodo * views (struct nodo * testa)
{
	struct nodo * temp = testa;
	while(temp!=NULL)
	{
		printf(" %d ",temp -> valore);
		temp = temp -> next;
	}
	return testa;
}

