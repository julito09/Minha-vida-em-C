/* Esse emulador é capaz de realizar:
- Conversão de bases numericas ( binario - decimal / decimal - binario)
- Realiza normalizações baseado na mantissa,menor expoente e maior expoente
- Realiza a transformação pra negativo empregando as três representacoes especificas (c1,c2,sinal e amplitude)
- A explicitação se houve erros de under flow, over flow ou truncamento*/

//Obs: os valores podem ser inseridos com ponto ou virgula :)

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#include <ctype.h>
#include <locale.h>
#define maxtam 100
#define casas 50
void normalizarNega(double numero,char normalizado[maxtam], char bin[maxtam],int mantissa, int *contador, int *tamnumero){
	if(mantissa>*tamnumero)
		mantissa = *tamnumero;
	int l=3,cont=0;
	if(numero>=0)
		normalizado[0] = '0'; // bit de sinal negativo
		else normalizado[0] = '1';
	normalizado[1] = ' '; // espaco padronizado de acordo com o pdf
	normalizado[2] = '.'; // rt 
	
	int i =0,posic=0;
		while(bin[i]=='0' || bin[i]== '.' ){ // enquanto nao achar um digito diferente de 0 ele conta as posicoes
				if(bin[i] == '.'){ // se ele achar um . eu zero cont pq os numeros atras da . eram insignificantes
					cont=0; 
				}	
				cont++;	// conto quantas casas meu . pulou
				i++;		
		}
		posic = i; // salvo a posicao do vetor onde começa os digitos
		int max=posic+mantissa; // somo o valro da minha mantissa, onde vai ser o intervalo de numeros q eu vou jogar no vetor
		for(i=posic;i<max;i++){
			normalizado[l] = bin[i];
			l++;
		}
		cont --; // ele sempre contava 1 vez a +
	int tam = strlen(normalizado);
	normalizado[tam] = '\0';
	printf("%s",normalizado);
	cont = cont  * (-1) ; 
	*contador = cont;
	printf(" * 2^%i",*contador);
	printf("\n");
}
void normalizar(double numero,char normalizado[maxtam],char bin[maxtam],int mantissa, int *contador,int *tamnumero){
	if(mantissa>*tamnumero)
		mantissa = *tamnumero;
	int l=3, cont=0, posicaoponto=0;
	if(numero>=0)
		normalizado[0] = '0';
		else
			normalizado[0] = '1';
	 // bit de sinal negativo
	normalizado[1] = ' '; // espaco padronizado de acordo com o pdf
	normalizado[2] = '.'; // rt 
	int i =0,posic=0, posicaodoponto;
		while(bin[i]== '0'){ // enquanto nao achar um digito diferente de 0 ele conta as posicoes
				i++;
				cont++;	// conto quantas casas meu . pulou	
		}
	int max=cont+mantissa; // limite do meu vetor de acordo com a mantissa
		for(i=cont;i<=max;i++){
			if(bin[i]== '.'){
				posicaoponto = i; 
				i++;
			}
		normalizado[l] = bin[i];
		l++;
		}
	int tam = strlen(normalizado);
	normalizado[tam] = '\0';
	
	printf("%s", normalizado);
	*contador = posicaoponto - cont;
	printf(" * 2^%i\n",*contador);	
	
}
int comeco (char bin[maxtam]){ // onde comeca o numero
	for(int i=0;i<maxtam;i++){
		if(bin[i]!='0')
			return i;
	}
	return 0;
}
int fim (char bin[maxtam]){ // onde termina
	for(int i=maxtam;i>=casas;i--){
		if(bin[i]!='0')
			return i;
	}
	return 0;
}
void decimalparabinario(double numero, char bin[maxtam], int *tamnumero){
    double f;
    int i,cnum;
    f=numero-(int)numero;
    cnum=(int)numero;
    // Parte fracionada: inserida a partir da metade do vetor
    for(i=casas+1; i<=(casas*2); i++){
        f=f-(int)f;
        if((int)(f*2) == 0){
            bin[i] = '0';
        }else{
            bin[i] = '1';
        }
        f*=2;
    }
    // Parte inteira: inserida no inicio ate a metade do vetor
    for(i=casas-1; i>=0; i--){
        if(cnum%2==0){
            bin[i] = '0';
        }else{
            bin[i] = '1';
        }
        cnum/=2;
    }
    // Virgula
    bin[casas] = '.';
    
    printf("O numero %lf em binario é: ",numero);
    int inicio = comeco(bin);
	int final = fim(bin);
    for(i=inicio;i<=final;i++)
    	printf("%c", bin[i]);
    	
    *tamnumero = final - inicio;
    printf("\n\n");
}
void binarioparadecimal(char decimal[maxtam],double numero){
    int antesDec[50], depoisDec[50], tint=0, l=0, j=0, k=0;
    int antesDecnum=0, depoisDecnum=0;
    double fract=0, floatValue=0;
    char p = 'd';
    
    //Separa o inteiro do fracionada
    for(l=0; l<strlen(decimal); l++){
        if(decimal[l]=='.'){
            p='u';
        }
        else if(p=='d'){
            antesDec[l] = (int)decimal[l]-48;
            k++;
        }
        else{
            depoisDec[j] = (int)decimal[l]-48;
            j++;
        }
    }
    // Armazena o tamanho do inteiro e do fracionario
    antesDecnum = k;
    depoisDecnum= j;
    //Converter parte inteira para decimal
    j=0;
    for(l = antesDecnum-1; l>=0; l--){
        tint = tint + (antesDec[l] *(int) pow(2,j));
        j++;
    }
    //Converter parte fracionaria para decimal
    j = -1;
    for(l = 0; l<depoisDecnum; l++){
        fract = fract + (depoisDec[l]*pow(2,j));
        j--;
    }
    //Juntando as duas partes
    floatValue = tint + fract;
    if(numero<0)
    	floatValue = floatValue * (-1);
    printf("%.19lf\n\n",floatValue);

}
/* inverto todos os sinais do sinal e amplitude*/
void fazCompUm(char normalizado[maxtam],char comp1[maxtam], int *tamnumero, int *contador, double numero){
	int limit=3, i,j=0;
	char aux[maxtam];
	comp1[0] = '1'; // conversao pro bit de sinal negativo
	comp1[1] = ' ';
	comp1[2] = '.';
	limit += *tamnumero; // tam numero é o numero de casas que o numero precisa
	for(i=3;i<=limit;i++){
		if(normalizado[i]=='1'){
			comp1[i] = '0';
			
		}else if(normalizado[i]=='0'){
			comp1[i] = '1';
			
		}
	}
	int TAM2 = strlen(comp1);
	comp1[TAM2] = '\0';
	printf("%s",comp1); 
	printf(" * 2^%i",*contador);
	
}
/* acrescento o bit no bit de menos significancia*/
void fazCompDois(char comp1[maxtam], char comp2[maxtam], int *contador,double numero){
	int i = strlen(comp1);
	while(comp1[i]!='0'){
		comp2[i] = '0';
		i--;
	}
	comp2[i] = '1';
	i--;
	for(int j=i;j>=0;j--){
		comp2[j] = comp1[j];
	}
	int TAM = strlen(comp2);
	comp2[TAM-1] = '\0';
	
	printf("%s", comp2);
	printf(" x 2^%i",*contador);
}
/* so copio o numero apartir do */
void expozero(char bin[maxtam],char decimal[maxtam], int mantissa, int *tamnumero){
	if(mantissa>*tamnumero)
		mantissa = *tamnumero;
	int inicio = comeco(bin);
	int i,j=0,limite=mantissa+inicio;
	for(i=inicio;i<=limite;i++){
		decimal[j] = bin[i];
		j++;
	}
}
//verfica os erros de under flow, over, e truncamento
void verifica(int *contador,int menorE,int maiorE, int mantissa,int *tamnumero){
	int cont=0;
	if(*contador>maiorE){
		printf("ERRO DE OVERFLOW!!!!!\n\n");
		cont++;
	}
	else if(*contador<menorE){
		printf("ERRO DE UNDERFLOW!!!!!\n\n");
		cont++;
	}
	if(*tamnumero>mantissa){
		printf("ERRO DE TRUNCAMENTO!!!!!\n\n");
		cont++;
	}
	if(cont==0)
		printf("NÃO HOUVE ERRO!!!!!\n\n");
}
int main(){
	setlocale(LC_ALL, "Portuguese");
	double numero;
	char aux1[10],aux2[10],aux3[10];
    int mantissa, menorE, maiorE,tamnumero,expo=0,contador;
    char bin[maxtam], normalizado[maxtam], comp1[maxtam], comp2[maxtam],decimal[maxtam], NUMERO[maxtam], *stopstring;
    int ops=1, op,a=0,vv=0,aa=0,bb=0,test1=0,test2=0,test3=0;
    printf("******Bem vindo ao emulador de máquina finita******\n");
    do
    {
		if(ops==1){
			printf("Configurando a máquina...\n");
			printf("Digite a precisao da mantissa.\n");
			scanf("%s",&aux1);
			printf("Digite o menor valor de expoente.\n");
			scanf("%s",&aux2);
			printf("Digite o maior valor de expoente.\n");
			scanf("%s",&aux3);
		}
			test1=atoi(aux1); test2= atoi(aux2); test3=atoi(aux3);
			int tam1=strlen(aux1), tam2=strlen(aux2), tam3= strlen(aux3);
			aux1[tam1] = '\0'; aux2[tam2] = '\0'; aux3[tam3] = '\0';
			vv=0; aa = 0; bb = 0; 
			for(a=0;a<tam1;a++){
				vv += isalpha(aux1[a]);
			}
			for(int b=0;b<tam2;b++){
				aa += isalpha(aux2[b]);
			}
			for(int c=0;c<tam3;c++){
				bb += isalpha(aux3[c]);
			}
		if( test2 > test3 || test1<=0 || vv !=0 || aa !=0 || bb !=0 ){
			do{
			vv=0; aa = 0; bb = 0;
			printf("\nValores inválidos, digite novamente!!!!\n\n");
			printf("Digite a precisão da mantissa.\n");
			scanf("%s",&aux1);
			printf("Digite o menor valor de expoente.\n");
			scanf("%s",&aux2);
			printf("Digite o maior valor de expoente.\n");
			scanf("%s",&aux3);
			int tam1=strlen(aux1), tam2=strlen(aux2), tam3= strlen(aux3);
			aux1[tam1] = '\0'; aux2[tam2] = '\0'; aux3[tam3] = '\0'; 
			for(a=0;a<tam1;a++)
				vv += isalpha(aux1[a]);
			
			for(int b=0;b<tam2;b++)
				aa += isalpha(aux2[b]);
			
			for(int c=0;c<tam3;c++)
				bb += isalpha(aux3[c]);
	
			test1=atoi(aux1); test2= atoi(aux2); test3=atoi(aux3);
			}while(test2 > test3 || test1<=0 || vv != 0 || aa != 0 || bb != 0);
	
}
		mantissa = atoi(aux1); menorE = atoi(aux2); maiorE = atoi(aux3);
		printf("Digite um numero decimal a ser convertido.\n");
    	scanf("%s", &NUMERO);
    	int tamanho = strlen(NUMERO);
    	for(int e=0;e<tamanho;e++){
    		if(isalpha(NUMERO[e])!=0 ){
    			do{
    				printf("Valor inválido, digite novamente!!!\n");
					printf("Digite um numero decimal a ser convertido.\n");
					scanf("%s", &NUMERO);
				}while(isalpha(NUMERO[e])!=0 );
			}
		}
		numero = strtod(NUMERO, &stopstring);	
    	memset(bin,0,maxtam);
		memset(normalizado,0,maxtam);
		memset(comp1,0,maxtam);
		memset(comp2,0,maxtam);
		memset(decimal,0,maxtam); contador = 0;
        printf("\nConfiguração atual da máquina: (Num: %lf, M :%d, U: %d, O: %d)\n", numero,mantissa,menorE,maiorE);
        printf("\nO que o usuario deseja?.\n\n");
        printf("1. Binário para Decimal\n");
        printf("2. Decimal para Binário\n");
        printf("3. Realizar as conversões\n");
        printf("4. Sair\n");
        printf("\nDigite uma opção: \n");
        scanf("%d",&op); 
        while(op!=1 && op!=2 && op!=3 && op!=4){
		printf("Opção inválida\nDigite novamente uma opção: \n");
   		scanf("%d",&op); 
		}
        system("cls"); //Comando utilizado para limpar tela
        switch(op)
        {
        case 1:
        	char numero2[maxtam];
        	printf("Digite um numero em binário a ser convertido. \n");
        	scanf("%s",&numero2);
        	printf("O numero %s em decimal e: ",numero2);
            binarioparadecimal(numero2,numero);
            printf("\n");
            break;
        case 2:
        	printf("Configuração atual da máquina: (Num: %lf, M :%d, U: %d, O: %d)\n", numero,mantissa,menorE,maiorE);
            decimalparabinario(numero, bin,&tamnumero);
            break;
        case 3://Sair do programa
         	printf("Configuração atual da máquina: (Num: %lf, M :%d, U: %d, O: %d)\n", numero,mantissa,menorE,maiorE);
         	printf("\n*****CONVERSÕES*****\n\n");
          	decimalparabinario(numero, bin,&tamnumero);
            if(numero>=(-0.9999999999999999999999) && numero <= 0.99999999999999999999999 ){ 
            	printf("O numero normalizado em binário é: ");
            	normalizarNega(numero,normalizado,bin,mantissa,&contador,&tamnumero);
            		expozero(bin,decimal,mantissa,&tamnumero);
            		printf("\nO numero binário: %s transformado em decimal é:", decimal);
            		binarioparadecimal(decimal,numero);
			}
            else{
				printf("O numero normalizado em binário é: ");
            	normalizar(numero,normalizado,bin,mantissa,&contador,&tamnumero);
            	expozero(bin,decimal,mantissa,&tamnumero);
            	printf("\nO numero binário: %s transformado em decimal eh:", decimal);
            	binarioparadecimal(decimal,numero);
			}
			verifica(&contador,menorE,maiorE,mantissa,&tamnumero); // verifica under,over...

			if(numero<0){
				printf("*****Empregando as tres representações*****\n\n");
				if(numero>=(-0.999999999) && numero <= 0.999999999 ){
				printf("Numero em sinal e amplitude: ");
            	normalizarNega(numero,normalizado,bin,mantissa,&contador,&tamnumero);
            	printf("\n");
            }else{
    
            	printf("Numero em sinal e amplitude: ");
            	normalizar(numero,normalizado,bin,mantissa,&contador,&tamnumero); printf("\n");
			}
			printf("Numero em complemento de 1:");
			fazCompUm(normalizado,comp1,&tamnumero,&contador,numero);
			printf("\n");
			printf("\nNumero em complemento de 2:");
			fazCompDois(comp1,comp2,&contador,numero);
			printf("\n\n");
            break;
			}			
			break;
		case 4: 
			printf("Encerrando programa...");
			return 0;
        }
        printf("O que o usuario deseja?\n");
        printf("[1] - Alterar configurações.\n");
		printf("[2] - Manter configurações.\n");
		scanf("%i", &ops);
		system("cls"); //Comando utilizado para limpar tela
	}while(op != 4);
}


