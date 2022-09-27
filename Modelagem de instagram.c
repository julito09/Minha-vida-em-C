#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include <locale.h>
#define MAXTAM 100
int usuarios=0;

void exibeMatrizNomes(char nomes[MAXTAM][MAXTAM]){
	int i;
	printf("******Usu�rios cadastrados******* \n");
	for(i=0;i<usuarios;i++){
    	printf("%s\n", nomes[i]);
	}
	printf("\n");
}

void exibeMatrizSeguidores(int seguidores[MAXTAM][MAXTAM]){
	int i,j;
	printf("\n");
	printf("*******Rela��o de seguidores******* \n");
	for(i=0;i<usuarios;i++){
		for(j=0;j<usuarios;j++){
			printf("|%d|",seguidores[i][j]);
		}		
		printf("\n");
	}
}


void inicializaGrafo(int m[MAXTAM][MAXTAM]){
    int i,j;
    // Utilizado a estrutura de 0...n-1 para que nao haja uma linha e coluna inteira vazia
    for(i=0;i<MAXTAM;i++){
        for(j=0;j<MAXTAM;j++){
            m[i][j]=0;
        }
    }
}

int verifUser(char nome[100], char nomes[MAXTAM][MAXTAM]){
    int i,j,cont=0,tam=0;
    for(i=0;i<usuarios;i++){
        if(strcmp(nome,nomes[i])==0)
        	return 1;
    }
    return 0;
}

void InserirUsuario(char nome[100], char nomes[MAXTAM][MAXTAM]){
    int i,j=0;
    if(verifUser(nome,nomes) == 1){
    	printf("O usu�rio j� existe, tente outro!\n");
	}else{
		strcpy(nomes[usuarios],nome);
		usuarios++;
		printf("\nQuantidade de usu�rios cadastrados: %d\n",usuarios);
	}
    exibeMatrizNomes(nomes);   	
}

int BuscaPosicao(char nomes[MAXTAM][MAXTAM], char nome[MAXTAM]){
	int i=0;
	
	if(verifUser(nome,nomes)==1){
		while(i<=usuarios){
		if(strcmp(nome,nomes[i])==0){
			return i;
		}
		i++;
		}	
	}
	return -1;
}

void InsereRelacao(int positX,int positY, int tempo,int m[MAXTAM][MAXTAM]){
	m[positY][positX] = tempo;
	
}

int verifRelacao(int positX,int positY,int m[MAXTAM][MAXTAM]){
	if(m[positY][positX] != 0){
		return 1;
	}else{
		return 0;
	}
}

// quem o x segue
void segueQuem(int x, int m[MAXTAM][MAXTAM],char nomes[MAXTAM][MAXTAM]){
	int j;
	for(j=0;j<usuarios;j++){
		if(m[x][j] != 0){
			printf("Segue %s h� %d meses\n",nomes[j],m[x][j]);
		}
	}
}

// quem segue o x
void quemMeSegue(int x, int m[MAXTAM][MAXTAM],char nomes[MAXTAM][MAXTAM]){
	int j;
	for(j=0;j<usuarios;j++){ 
		if(m[j][x] != 0){
			printf("� seguido por  %s h� %d meses\n",nomes[j],m[j][x]);
		}
	}
}

int calculaSeguidores(int m[MAXTAM][MAXTAM]){
	int i,j,cont=0;
	for(i=0;i<usuarios;i++){
		for(j=0;j<usuarios;j++){
			if(m[i][j]!=0)
				cont++;
		}			
	}
	return cont;
}

void excluiRelacao(int positX,int positY,int seguidores[MAXTAM][MAXTAM]){
	seguidores[positY][positX] = 0;
	exibeMatrizSeguidores(seguidores);
}

void AtualizaRelacao(int positX,int positY,int tempo,int seguidores[MAXTAM][MAXTAM]){
	seguidores[positY][positX] = tempo;
	exibeMatrizSeguidores(seguidores);
}
int xnot(char nomes[MAXTAM][MAXTAM], char nome[MAXTAM], char nome2[MAXTAM]){
	int result;
	result = strcmp(nome,nome2);
	if(result == 0){
		return 1;
	}else return 0;
}
int main(){
	setlocale(LC_ALL, "Portuguese");
    int seguidores[MAXTAM][MAXTAM];
    char nomes[MAXTAM][MAXTAM];
    char nome[MAXTAM],nome2[MAXTAM];
    int op=0,op2=0,op3=0,op4=0,positX=0,positY=0,tempo=0;
    
    inicializaGrafo(seguidores);

    while(true){
        printf("[0] - Encerrar\n");
        printf("[1] - Inserir\n");
        printf("[2] - Excluir\n");
        printf("[3] - Atualizar\n");
        printf("[4] - Exibir\n");
        scanf("%d",&op);

        switch(op){
            case 0:
                printf("Encerrando...");
                return 0;
        
            case 1:
                // Inserir
                printf("[1] - Usu�rio\n");
                printf("[2] - Rela��o\n");
                scanf("%d",&op3);
                switch(op3){
                    case 1:
                        // Inserir usuario
                        printf("Informe o nome do usu�rio: ");
                        scanf("%s", &nome);
                        InserirUsuario(nome,nomes);
                    break;

                    case 2:
	                    // Inserir relacao
	    
    					exibeMatrizNomes(nomes);
    					printf("Informe o nome do seguido: \n");
    					scanf("%s",&nome);
    					positX = BuscaPosicao(nomes,nome);
    					
    					printf("Informe o nome do seguidor: \n");
    					scanf("%s",&nome2);
    					positY = BuscaPosicao(nomes,nome2);
    					if(xnot(nomes,nome,nome2)==1){
    						printf("%s n�o pode seguir ele mesmo\n", nome);
    						break;
						}
    				
						printf("Qual o tempo de rela��o?\n");
    					scanf("%d",&tempo);
    					if(positX == -1 || positY == -1 || tempo <= 0){
    						printf("O seguido ou o seguidor n�o existe ou o tempo e inv�lido\n");
    					
    	
						}else if(verifRelacao(positX,positY,seguidores) == 1){
							printf("Essa rela��o j� existe, deseja atualizar? Y(1)/N(0)");
							scanf("%d",&op4);
							if(op4==1){
								printf("Informe o novo tempo de rela��o: \n");
								scanf("%d",&tempo);
								InsereRelacao(positX,positY,tempo,seguidores);	
							}
						}else{
							InsereRelacao(positX,positY,tempo,seguidores);
						}
						exibeMatrizSeguidores(seguidores);
	                break;
	                
	                default:
            		printf("Op��o inv�lida!\n");
                }
            break;

            case 2:
                // Excluir relacao
                printf("Informe o nome do seguido: \n");
                scanf("%s",&nome);
                if(verifUser(nome,nomes)==1){
                	positX = BuscaPosicao(nomes,nome);
                	printf("Posi��o do seguido: %d\n", positX);
                	printf("Informe o seguidor para ser excluido a rela��o: ");
                	scanf("%s",&nome);
                	if(verifUser(nome,nomes)==1){
                		positY = BuscaPosicao(nomes,nome);
						excluiRelacao(positX,positY,seguidores);
             		}else{
						printf("O usu�rio n�o existe!\n");
					}
				}else{
					printf("O usu�rio n�o existe!\n");
				}
				
            break;

            case 3:
                // Atualizar
                printf("\nAtualizando rela��o...\n");
                printf("Informe o nome do seguido: \n");
                scanf("%s",&nome);
                positX = BuscaPosicao(nomes,nome);
                if(verifUser(nome,nomes)==1){
                	printf("Informe o nome do seguidor: \n");
                	scanf("%s",&nome);
                	if(verifUser(nome,nomes)==1){
                		positY = BuscaPosicao(nomes,nome);	
                		if(verifRelacao(positX,positY,seguidores) == 1){
                			printf("Informe o novo tempo de rela��o: \n");
							scanf("%d",&tempo);
							AtualizaRelacao(positX,positY,tempo,seguidores);
						}else{
							printf("A rela��o nao existe! Deseja adicion�-la? Y(1)/N(0)\n");
							scanf("%d",&op4);
							if(op4==1){
								printf("Informe o tempo de rela��o: \n");
								scanf("%d",&tempo);
								InsereRelacao(positX,positY,tempo,seguidores);
								exibeMatrizSeguidores(seguidores);
							}
						}
					}else{
						printf("O usu�rio n�o existe! Deseja cadastra-lo? Y(1)/N(O)\n");
						scanf("%d",&op4);
						if(op4==1){
							InserirUsuario(nome,nomes);
						}	
					}
				}else{
					printf("O usu�rio n�o existe!\n");
				}
            break;

            case 4:   
                // Exibir
                printf("[1] - Exibir seguindos de um usu�rio \n");
                printf("[2] - Exibir seguidores de um usu�rio \n");
                printf("[3] - Exibir quantidade de seguidores cadastradas \n");
                scanf("%d",&op2);
                switch(op2){
                    case 1:
                        // Exibir seguidores de um usuario
                        printf("Insira o usu�rio que sera exibido os seguindos: \n");
                        scanf("%s",&nome);
                        if(verifUser(nome,nomes)==1){
                        	positX=BuscaPosicao(nomes,nome);
                        	segueQuem(positX,seguidores,nomes);
						}else{
							printf("O usu�rio n�o existe!\n");
						}
                    break;

                    case 2:
                        // Exibir seguindos de um usuario
						printf("Insira o usu�rio que sera exibido os seguidores: \n");
                        scanf("%s",&nome);
                        if(verifUser(nome,nomes)==1){
                        	positX=BuscaPosicao(nomes,nome);
                        	quemMeSegue(positX,seguidores,nomes);
						}else{
							printf("O usu�rio n�o existe!\n");
						}
                        
                    break;
                    
                    case 3:
                    	printf("Quantidade de seguidores cadastrados: %d\n",calculaSeguidores(seguidores));
                    break;    
					  	
             	    default:
            			printf("Op��o inv�lida!\n");
                }
            break;
            
            default:
            	printf("Op��o inv�lida!\n");
        }
   }
}
