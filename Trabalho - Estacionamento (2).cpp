#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
// nome: Julio e thaina

// Estrutura de Dados Fila Dinâmica
typedef struct TipoCelula *TipoApontador; 

typedef struct TipoItem { 
	int placa;
	int prioridade;
	int deslocamento;
} TipoItem;

typedef struct TipoCelula {
	TipoItem Item;
	TipoApontador Prox;
} TipoCelula; 

typedef struct TipoFila {
	TipoApontador Frente, Tras;
}TipoFila;

// Funções de manipulação da Fila Dinâmica
void FFVazia(TipoFila *Fila ) { 
	Fila ->Frente = (TipoApontador) malloc(sizeof(TipoCelula )); 
	Fila ->Tras = Fila ->Frente; 
	Fila ->Frente ->Prox = NULL; 
}

int Vazia(TipoFila Fila ) { 
	return ( Fila.Frente == Fila.Tras) ;
}


void Enfileira (TipoItem x, TipoFila *Fila ) { 
	Fila ->Tras ->Prox = (TipoApontador) malloc(sizeof(TipoCelula )); 
	Fila ->Tras = Fila ->Tras ->Prox;
	Fila ->Tras ->Item = x; 
	Fila ->Tras ->Prox = NULL; 
}

void Desenfileira(TipoFila *Fila , TipoItem *Item) { 
	TipoApontador q; 
	if (Vazia( *Fila ) ) { 
		printf ( "\nErro fila esta vazia\n" ) ; return;
	} 
	q = Fila ->Frente; 
	Fila ->Frente = Fila ->Frente ->Prox; 
	*Item = Fila ->Frente ->Item; 
	free(q); 
}

void exibe (TipoFila fila){
	TipoApontador aux=fila.Frente->Prox;
	while(aux!=NULL){
		printf("\n!!Numero de identificacao:[%d]!!", aux->Item.placa);
		printf("\n!!Prioridade:[%d]!!\n", aux->Item.prioridade);
		aux=aux->Prox;
	}
}

void Prioridade(TipoFila *fila, TipoFila fila2){
	TipoApontador aux=fila->Frente->Prox;
	if (Vazia(*fila)){ 
		printf("\nErro fila esta vazia\n" );
	}else{
		while(aux!=NULL){
			if(aux->Item.prioridade == 1){
				Enfileira(aux->Item, &fila2);
				Desenfileira(fila,&aux->Item);
				
				break;
			}
			aux=aux->Prox;
		}
	}
}


main(){
	TipoFila fila;
	FFVazia(&fila);
	TipoFila fila2;
	FFVazia(&fila2);
	TipoFila aux;
	FFVazia(&aux);
	TipoItem item, item2;
	TipoApontador p;
	int op, cont=1;
	while(true){
	
	printf("\nBem vindo ao estacionamento do Julio e Thaina, o que voce deseja?\n");
	printf("[0] - Retirar um veiculo\n[1] - Estacionar um veiculo\n[2] - Exibir a fila principal\n[3] - Mover carros com prioridade da fila de espera pra fila principal\n[4] - Exibir fila de espera\n  "); scanf("%d", &op);
			
		if(op==1 && cont<=5){ // enquanto a fila tiver vagas disponiveis, o cont controla isso
			cont++;
			printf("Digite o numero de identificacao e a prioridade [0] ou [1] do seu carro\n");
			scanf("%d", &item.placa); scanf("%d", &item.prioridade);
			item.deslocamento=0;
			Enfileira(item, &fila);
		
		}
		if(op==1 && cont>5){ // se enxer a fila principal, entra na fila de espera
			printf("A ultima vaga foi ocupada, os proximos carros agora estarao na fila espera, assim que houver vagas te avisaremos!\n");
			printf("Essa e a fila de espera, por favor digite o numero de identificacao e a prioridade [0] ou [1] do seu carro:\n");
			scanf("%d", &item.placa); scanf("%d", &item.prioridade);
			item.deslocamento=0;
			Enfileira(item, &fila2);
		}
		
		
		if(op==0){
			item2.deslocamento=0;	
			printf("Digite o numero de identificacao do veiculo a ser retirado:\n");
			scanf("%i", &item2.placa);
			TipoApontador p=fila.Frente->Prox;
			
			while(p!=NULL){
				if(item2.placa==p->Item.placa){ // se o carro tiver na frente ele desempilha
					item2.deslocamento++; // deslocamento
					Desenfileira(&fila, &item);
					cont--; // controlar numero de vagas
					break;
					
				}
				item2.deslocamento++; // se nao ele vai desempilhando até q o carro esteja na frente
				Desenfileira(&fila, &item);
				Enfileira(item, &aux);
				p=p->Prox;		
			}
			while(!Vazia(aux)){
				Desenfileira(&aux, &item); // volta os carros de volta pra fila principal após retirar o carro escolhido
				Enfileira(item, &fila);
			}

			printf("O veiculo %i foi retirado e deslocado %i vezes\n",item2.placa, item2.deslocamento);
		
		}
		
		if(op==2){
			if(Vazia(fila))
				printf("A fila esta vazia");
				else 
					exibe(fila);
		}	
		
		if(op==3){
			if(cont<=5){
			printf("Ha vagas disponiveis na fila principal, o primeiro carro com prioridade 1 sera movido a fila principal");
			Prioridade(&fila2, fila);
		}else{
			printf("A fila principal esta cheia, espere ate que seja retirado um carro\n");
		}
		
	}
		if(op==4){
			if(Vazia(fila2))
				printf("A fila esta vazia");
					else 
						exibe(fila2);
		}
		
		
}

}
	
	

/*
(2) Travesas Bom Jesus dos Passos = estacionamento de 5 carros
(1) Travessa Monsenhor Joao Pedro = entra
(3) Rua Jaime Golçalves = sai
(4) auxiliar
se chegar cliente para retirar carro que nao esteja na primeira posicao
da 2, todos os carros entre o carro do cliente e a 3 serao deslocados
para fora do estacionamento(rua auxiliar 4)
o carro do cliente saira da 2 e os outros voltaram para o estacionamento
na mesma ordem que sairam

se o estacionamento estiver cheio os carros deverao formar uma fila 
de espera na 

quando um carro sair do estacionamento, se tiver carro com prioridade
na fila de espera(1), esse carro entrará no estacionamento 2
antes dos demais.

caso nao tenha carro com prioridade, o primeiro carro da 1 entrara no
estacionamento (2)
*/



		

