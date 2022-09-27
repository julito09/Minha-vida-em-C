#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define MAXTAM 1000000
#define k 5
#define control 10
int vet[MAXTAM];
int aux[MAXTAM];
void insertionSort(int vet[MAXTAM]){
    int i,j,aux=0;
    for(i=1;i<=MAXTAM;i++){
        aux = vet[i];
        for(j=i;(j>0)&&(aux<vet[j-1]);j--){
            vet[j] = vet[j-1];
        }
        vet[j] = aux;
	}
}
void insertionSortQuick(int vet[MAXTAM], int esq, int dir){
    int i,j,aux=0;
    for(i=esq+1;i<dir;i++){
        aux = vet[i];
        for(j=i;(j>0)&&(aux<vet[j-1]);j--){
            vet[j] = vet[j-1];
        }
        vet[j] = aux;
	}
}
int mediana(int vet[MAXTAM]){
 	int i,pivo,calculo;
 	for(i=0;i<k;i++){
		vet[i] = rand() % MAXTAM;
	}
	insertionSort(vet);
	calculo = ((k-1) / 2) + 1;
	pivo = vet[calculo];
	return pivo;
}


int separa (int v[MAXTAM], int esq, int dir){
   int pivo = v[esq], i = esq+1, j = dir, t;
   while ( i <= j) {
      if (v[i] <= pivo) i++;
      else if (pivo < v[j]) j--; 
      else {
        t = v[i];
		v[i] = v[j];
		v[j] = t;
        i++; j--;
      }
   }                
    v[esq] = v[j];
	v[j] = pivo;
   return j; 
}
void quickSort(int v[MAXTAM], int esq, int dir)//iterativo
{

   int j, *pilhap, *pilhar, t;
   pilhap = malloc ((dir-esq+1) * sizeof (int));
   pilhar = malloc ((dir-esq+1) * sizeof (int));
   pilhap[0] = esq; pilhar[0] = dir; t = 0; 
   
   while (t >= 0) {
      
      esq = pilhap[t]; dir = pilhar[t]; t--;
      if (esq < dir) {
         j = separa (v, esq, dir);    
         t++; pilhap[t] = esq; pilhar[t] = j-1; 
         t++; pilhap[t] = j+1; pilhar[t] = dir; 
      }
   }
}

void quicksortRecur(int v[MAXTAM], int esq, int dir) {

	int j;
	if (esq < dir) {
    	j = separa (v, esq, dir);
    	if((dir-esq) < control){
    		insertionSortQuick(v,esq,dir);
		}else{
		quicksortRecur(v, esq, j-1);
      	quicksortRecur(v, j+1, dir);
		}
   	}
}
int separaMediana(int v[MAXTAM], int esq, int dir){
	int p = mediana(vet),aux;
	aux = v[esq];
    v[esq] = v[p];
    v[p] = aux;
    p = dir;
   int pivo = v[esq], i = esq+1, j = dir, t;
   while ( i <= j) {
      if (v[i] <= pivo) i++;
      else if (pivo < v[j]) j--; 
      else {
        t = v[i];
		v[i] = v[j];
		v[j] = t;
        i++; j--;
      }
   }                
   v[esq] = v[j];
	v[j] = pivo;
   return j; 
}
void quicksortmediana(int v[MAXTAM], int esq, int dir){

	int j;
	if (esq < dir) {
    	j = separa (v, esq, dir);
		quicksortRecur(v, esq, j-1);
      	quicksortRecur(v, j+1, dir);
   	}
	
}
void meuSort(int vet[MAXTAM], int esq, int dir){
	esq = 0; dir = MAXTAM -1;
	int media=0;
	int i, j=0,soma=0;
	for(i=0;i<MAXTAM;i++){
		soma+=vet[i];
	}
	media = soma / MAXTAM;
	for(i=0;i<MAXTAM;i++){
		if(vet[i]<=media){
			aux[i] = vet[i];
			j++;
		}
	}
	for(i=0;i<MAXTAM;i++){
		if(vet[i]>media){
			aux[j] = vet[i];
			j++;
		}
	}
	quicksortRecur(aux,esq,dir);
//	for(i=0;i<MAXTAM;i++){
	//	printf("|%d|", aux[i]);
	//}


	
}


 int main(){
 	clock_t begin ;
 	double time_spent = 0.0;
 	long long int op=0,n=MAXTAM,op2;
 	int i,esq=0,dir=n-1;
 	clock_t inicio, fim;
 	clock_t end ;

	while(op!=5){
		for(i=0;i<MAXTAM;i++){
		vet[i] = rand() % MAXTAM;
		}
		printf("1. Quick Sort Iterativo\n");
        printf("2. QuickSort Mediana\n");
        printf("3. QuickSort + Insertion Sort\n");
        printf("4. Meu sort\n");
        printf("5. Sair\n");
        scanf("%d", &op);
        if(op!=1 && op!=2 && op!=3 && op!=4 && op!= 5){
			printf("\nOpcao invalida\n\n");
			system("pause");
		}	
		switch(op){


		case 1:
			begin = clock();
			quickSort(vet,esq,dir);
			end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			time_spent*=1000;
			printf("\nAlgoritmo utilizado: Quick Sort Interativo\nTempo gasto para ordenar %.19lf milissegundos\nTamanho do vetor: %d\n\n",time_spent,n);
			time_spent = 0;
			system("pause");
			break;
		case 2:
			begin = clock();
			quicksortmediana(vet,esq,dir);
			end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			time_spent*=1000;
			printf("\nAlgoritmo utilizado: Quick Sort Mediana\nTempo gasto para ordenar %.19lf milissegundos\nTamanho do vetor: %d\n\n",time_spent,n);
			time_spent = 0;

			system("pause");
			break;
		case 3:
			begin = clock();
			quicksortRecur(vet,esq,dir);
			end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			time_spent*=1000;
			printf("\nAlgoritmo utilizado: Quick Sort + Insertion\nTempo gasto para ordenar %.19lf milissegundos\nTamanho do vetor: %d\n\n",time_spent,n);
			time_spent = 0;
			system("pause");
			
			break;
		case 4:
			begin = clock();
			meuSort(vet,esq,dir);
			end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			time_spent*=1000;
			printf("\nAlgoritmo utilizado: Meu Sort\nTempo gasto para ordenar %.19f milissegundos\nTamanho do vetor: %d\n\n",time_spent,n);
			time_spent = 0;
			system("pause");
			break;
		case 5:
			printf("Encerrando...");
			return 0;
		}
		
	}
	
}
