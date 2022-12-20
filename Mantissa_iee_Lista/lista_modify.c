#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <tgmath.h>
#define N 23  /*Mantissa bit*/
#define M 64 
/*
La funzione "insert_node" accetta un valore float espresso
in notazione IEEE 754 a 32 bit. La funzione estrae dal valore in virgola mobile una stringa
binaria costituita dalla mantissa ed interpreta tale stringa binaria come un intero. Effettua
quindi una scansione della lista puntata da head. Se viene trovato un nodo la cui chiave
corrisponde al valore della mantissa, incrementa il contatore del nodo corrispondente. Viceversa,
se non viene trovato alcun nodo contrassegnato da questa chiave, inserisce un nuovo nodo in
testa alla lista, impostando il contatore del nodo a 1.
*/

/*
Poteva essere svolto anche tramite l'ausilio della struttura Union bit*/

struct nodo 
{
	struct nodo *next;
	int key;
	int counter;
};

struct nodo* load(struct nodo *);
bool lista_vuota(struct nodo *);
struct nodo* crea_nodo(int, int);
struct nodo* views (struct nodo *);
int calcolo_bit_necessari(int );
void converto_intero_in_binario(int,int,int*);
void visualizza_intero(int *,int);
struct nodo* insert_node(struct nodo*, float);
int dove_e_il_primo_uno(int *, int);
long long int converti_mantissa_in_decimale(int *, int);
struct nodo* mantissa_key_confronto(int , struct nodo*, struct nodo*);


int main(int argc, char *argv[])
{
	float value = 0;
	bool fine = false;
	int scelta;
	struct nodo *testa = NULL;
	struct nodo *app = NULL;
	do{
		printf("\n");
		printf("\t \t Menù Organizzato \n");
		printf("\t--------------------------------------------------------\n");
		printf("\t1. Per aggiungere elementi nella lista [*]\n");
		printf("\t2. Per visualizzare tutti gli elementi nella lista [*]\n");
		printf("\t3. Per verificare se esiste un valore di key uguale alla mantissa del valore float [*]\n");
		printf("\t4. FINE [*]\n");
		printf("\t--------------------------------------------------------\n");
		printf("\t>> ");
		scanf("%d",&scelta);
		switch(scelta)
		{
			case 1:
			{
				testa = load(testa);
			}break;
			case 2:
			{
				testa = views(testa);
			}break;
			case 3:
			{
				printf("Inserisci il valore float : ");
				scanf("%f",&value);
				testa = insert_node(testa,value);
			}break;
			case 4:
			{
				fine = true;
			}
		}
	}while(fine ==false);
	return 0;
}
struct nodo* insert_node(struct nodo* testa, float value)
{
	float iee_754 = value;
	long long int dec_mantissa_val = 0;
	float *ptr = malloc(N*sizeof(float));
	int intero = (int)iee_754;
	int app = intero;
	int bit_necessari_per_la_lunghezza_del_vettore;
	bit_necessari_per_la_lunghezza_del_vettore = calcolo_bit_necessari(intero);
	int *in = malloc(bit_necessari_per_la_lunghezza_del_vettore*sizeof(float));
	converto_intero_in_binario(bit_necessari_per_la_lunghezza_del_vettore,app,in);
	iee_754 = iee_754 - intero; 
	intero = 0;
	for(int i=0;i<N;i++)
	{
		iee_754 = iee_754 * 2;
		*(ptr + i) = iee_754;
		intero = (int) iee_754;
		if(intero !=0)
			iee_754 = iee_754 - intero;
	}
	int *ptr_int = malloc(N*sizeof(int));
	for(int i=0;i<N;i++)
	{
		*(ptr_int + i) = (int) *(ptr + i);
	}
	int posizione_primo_uno = 0;
	posizione_primo_uno =  dove_e_il_primo_uno(in,bit_necessari_per_la_lunghezza_del_vettore); //1
	//printf("La dimensione di IN è proprio = %d\n", bit_necessari_per_la_lunghezza_del_vettore);//7
    int *mantissa = malloc(N*sizeof(int));
    int contatore = 0;
    for(int i=0;i<bit_necessari_per_la_lunghezza_del_vettore-posizione_primo_uno;i++)
    {
    	*(mantissa + i) = *(in + (i+posizione_primo_uno));
    	contatore++;
    }
    //printf("Contatore = %d\n",contatore );
    for(int i=contatore,j=0;i<N;i++,j++)
    {
    	*(mantissa + i) = *(ptr_int + j);
    }
    visualizza_intero(mantissa,N);
    dec_mantissa_val = converti_mantissa_in_decimale(mantissa,N);
    printf("Valore della mantissa in decimale = %lld\n", dec_mantissa_val);
    //ora confrontiamo il valore della mantissa con la key
    //-------------------------------------------------------
    bool mantissa_check = false;
    struct nodo* appoggio;
    appoggio = testa;
    printf("Ora verrà effettuato il controllo ! \n ");
    testa = mantissa_key_confronto(dec_mantissa_val,appoggio,testa); 
    free(mantissa);
	free(ptr);
	return testa;
}

struct nodo* mantissa_key_confronto(int valore, struct nodo* app,struct nodo *testa)
{
	bool trovato = false;
	printf("\n");
	while(app!=NULL)
	{
		if((app->key)==valore)
		{
			trovato = true;
			printf("\n Ho trovato il valore float corrispondente al decimale della mantissa [*]\n");
			printf("\n Procedo ad incrementare il valore di %d di 1 [*]\n",app->key);
			app->key = app->key + 1;
		}
		app = app -> next;
	}
	if(trovato == false)
	{
		//ossia, non ha trovato il valore
		struct nodo* nuovo_nodo = NULL;	
		struct nodo* app = NULL;
		int chiave = 0;
		printf("Non ho trovato alcun nodo la cui chiave è uguale al decimale della mantisssa [*]\n");
		printf("Inserisci il valore della chiave: ");
		scanf("%d",&chiave);
		nuovo_nodo = crea_nodo(chiave,1);
		//questo nodo va inserito in testa;
		app = testa;
		nuovo_nodo ->next = app;
		testa = nuovo_nodo;
		return testa;
	}
	return testa;
}

long long int converti_mantissa_in_decimale(int *mantissa, int n)
{
	long long int somma = 0;
	for(int i=n-1,j=0;i>=0;i--,j++)
	{
		//la mantissa viene vsualizzata al contrario (come giusto che sia).
		if(*(mantissa + i)==1)
		{
			somma += pow(2,j);
		}
	}
	return somma;
}
int dove_e_il_primo_uno(int *in, int bit_necessari_per_la_lunghezza_del_vettore)
{
	bool check = false;
	int salvo = 0;
	for(int i=0;i<bit_necessari_per_la_lunghezza_del_vettore;i++)
	{
		if(check == false)
		{
			if(*(in + i)==1)
			{
				salvo = i+1;
				check = true;
			}
		}
	}
	return salvo;
}
struct nodo* load(struct nodo *testa)
{
	struct nodo* nuovo_nodo = NULL;	
	static struct nodo* app;
	int chiave = 0;
	int contatore = 0;
	int scelta;
	chiave = 0, contatore = 0;
	printf(" Inserisci il valore della chiave : ");
	scanf("%d",&chiave);
	printf(" Inserisci il valore del contatore : ");
	scanf("%d",&contatore);
	nuovo_nodo = crea_nodo(chiave,contatore);
	if(lista_vuota(testa))
	{
		app = nuovo_nodo;
		testa = app;
	}
	else
	{
		app->next = nuovo_nodo;
		app = nuovo_nodo; /*La lista viene inserita a run-time*/
	}
	return testa;
}
bool lista_vuota(struct nodo *testa)
{
	if(testa==NULL)
		return true;
	else
		return false;
}
struct nodo* crea_nodo(int chiave, int contatore)
{
	struct nodo* nuovo_nodo = malloc(sizeof(struct nodo));
	nuovo_nodo->key = chiave;
	nuovo_nodo->counter = contatore;
	nuovo_nodo->next = NULL;
	return nuovo_nodo;
}
struct nodo * views (struct nodo * testa)
{
	struct nodo * temp = testa;
	while(temp!=NULL)
	{
		printf(" | %d ",temp ->key);
		printf(" %d | ----> ",temp ->counter);
		temp = temp -> next;
	}
	printf("\n");
	return testa;
}
int calcolo_bit_necessari(int intero)
{
	int long_vettore = 0;
	for(int i=0;i<64;i++)
	{
		if(intero<(pow(2,i)))
		{
			long_vettore = i;
			printf(" %d\n",long_vettore);
			return long_vettore;
		}
	}
}
void visualizza_intero(int *in,int bit_necessari_per_la_lunghezza_del_vettore)
{
	bool check = false;
	int value = 0;
	printf("bin : ");
	for(int i=0;i<bit_necessari_per_la_lunghezza_del_vettore;i++)
	{
		printf("%d",*(in + i));
	}
	printf("\n");
}
void converto_intero_in_binario(int bit_necessari_per_la_lunghezza_del_vettore,int app, int *in)
{
	for(int i=bit_necessari_per_la_lunghezza_del_vettore-1;i>=0;i--)
	{
		*(in + i) = app % 2;
		app = app / 2;
	}
	visualizza_intero(in,bit_necessari_per_la_lunghezza_del_vettore);
}
