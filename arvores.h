#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef arvores
#define arvores .h
int cont=0;
char carac[35]={'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'};
// arvore
typedef struct _arvore {
   char nome[10];
   int codigo;
   int RA;
   int cpf;
   char data[15];
   char sexo[10];
   struct _arvore *esq;
   struct _arvore *dir;
}Arvore;

//Cria uma arvore vazia!
Arvore* cria_arv_vazia () {
   return NULL;
}

//Cria um no na arvore
Arvore* inserir(Arvore *a, int v,int cp, char dat[10], int ra, char nom[15], char sex[10]){
    if(a == NULL){
        a=(Arvore*)malloc(sizeof(Arvore));
        a->codigo = v;
        a->cpf = cp;
        strcpy(a->data,dat);
        a->RA = ra;
        strcpy(a->sexo,sex);
        strcpy(a->nome,nom);
        a->esq = NULL;
        a->dir = NULL;
        cont++;
    }
    else if(v < a->codigo){
        a->esq = inserir(a->esq,v,cp,dat,ra,nom,sex);
    }
    else{
        a->dir = inserir(a->dir,v,cp,dat,ra,nom,sex);
    }
    return a;
    
}
// remove um no na arvore
Arvore* Remover(Arvore *a, int v, int cpf, int ra, char nome[15], char data[15], char sexo[15]){
    if(a == NULL){
    	printf("Usuario nao existe!\n");
        return NULL;
    }
    else{
        if(a->codigo >v){
            a->esq = Remover (a->esq,v,cpf,ra,nome,data,sexo);
        }
        else if (a->codigo <v){
            a->dir = Remover (a->dir,v,cpf,ra,nome,data,sexo);
        }
        else{
            if((a->esq == NULL) && (a->dir == NULL)){
                free(a);
                a=NULL;
            }
            else if(a->dir == NULL){
                Arvore *tmp = a;
                a = a -> esq;
                free (tmp);
            }
            else if(a->esq == NULL){
                Arvore *tmp = a;
                a = a -> dir;
                free (tmp);
            }
            else{
                Arvore *tmp = a->esq;
                while(tmp->dir != NULL){
                    tmp=tmp->dir;
                }
                a->codigo = tmp->codigo;
                tmp->codigo = v;
                a->esq = Remover(a->esq,v,cpf,ra,nome,data,sexo);
                a->cpf = tmp->cpf;
                tmp->cpf = cpf;
                a->esq = Remover(a->esq,v,cpf,ra,nome,data,sexo);
                a->RA = tmp->RA;
                tmp->RA = ra;
                a->esq = Remover(a->esq,v,cpf,ra,nome,data,sexo);
                strcpy(a->data,tmp->data);
                strcpy(tmp->data,data);
                a->esq = Remover(a->esq,v,cpf,ra,nome,data,sexo);
                strcpy(a->sexo,tmp->sexo);
                strcpy(tmp->sexo,sexo);
                a->esq = Remover(a->esq,v,cpf,ra,nome,data,sexo);
                strcpy(a->nome,tmp->nome);
                strcpy(tmp->nome,nome);
                a->esq = Remover(a->esq,v,cpf,ra,nome,data,sexo);
                printf("\nAluno removido com sucesso\n!");
            }
        }
    }
    return a;
}

void pre_ordem (Arvore *arv) {
    if (arv != NULL){
    	printf ("\nNome do aluno(a): %s\n", arv->nome);
        printf ("Sexo do aluno(a): %s\n", arv->sexo);
        printf ("Data de nascimento do aluno(a): %s\n", arv->data);
        printf ("Codigo do aluno: %d\n", arv->codigo);
        printf ("CPF do aluno: %d\n", arv->cpf);
        printf ("RA do aluno: %d\n", arv->RA);
        printf ("%s",carac);
      	pre_ordem (arv->esq);
      	pre_ordem (arv->dir);
    }
}

void in_ordem (Arvore *arv) {
   if (arv != NULL) {
      	in_ordem (arv->esq);
    	printf ("\nNome do aluno(a): %s\n", arv->nome);
        printf ("Sexo do aluno(a): %s\n", arv->sexo);
        printf ("Data de nascimento do aluno(a): %s\n", arv->data);
        printf ("Codigo do aluno: %d\n", arv->codigo);
        printf ("CPF do aluno: %d\n", arv->cpf);
        printf ("RA do aluno: %d\n", arv->RA);
        printf ("%s",carac);
      	in_ordem (arv->dir);
   }
}

void pos_ordem (Arvore *arv){
    if (arv != NULL){
        pos_ordem (arv->esq);
        pos_ordem (arv->dir);
    	printf ("\nNome do aluno(a): %s\n", arv->nome);
        printf ("Sexo do aluno(a): %s\n", arv->sexo);
        printf ("Data de nascimento do aluno(a): %s\n", arv->data);
        printf ("Codigo do aluno: %d\n", arv->codigo);
        printf ("CPF do aluno: %d\n", arv->cpf);
        printf ("RA do aluno: %d\n", arv->RA);
        printf ("%s",carac);
    }
}

int buscar(Arvore *a, int v){
	int op;
    if(a==NULL){
       	printf("Usuario nao existe!\n\n");
    }
    else if(v < a->codigo){
        return buscar(a->esq,v);
    }
    else if(v > a->codigo){
        return buscar(a->dir,v);
    }else if(v == a->codigo){
    	printf("Usuario encontrado!\nDeseja Mostrar os dados do aluno?\n");
    	printf("[1] - Sim\n[2] - Nao\n");
    	scanf("%d",&op);
    	if(op==1){
    	printf ("\nNome do aluno(a): %s\n", a->nome);
        printf ("Sexo do aluno(a): %s\n", a->sexo);
        printf ("Data de nascimento do aluno(a): %s\n", a->data);
        printf ("Codigo do aluno: %d\n", a->codigo);
        printf ("CPF do aluno: %d\n", a->cpf);
        printf ("RA do aluno: %d\n\n", a->RA);
		}else return 0;
	}
    else{
        return 1;
    }
}
/* *int buscarpai(Arvore *a, int v){
	int op;
    if(a==NULL){
       	printf("Usuario nao existe!");
    }
    else if(v < a->codigo){
        return buscar(a->esq,v);
    }
    else if(v > a->codigo){
        return buscar(a->dir,v);
    }else if(a->esq->codigo == a->dir->codigo){
    	retorna a; // pai
	
	}
   
} */
/* *int buscarfilho(Arvore *a, int v){
	int op;
    if(a==NULL){
       	printf("Usuario nao existe!");
    }
    else if(v < a->codigo){
        return buscar(a->esq,v);
    }
    else if(v > a->codigo){
        return buscar(a->dir,v);
    }else if(a->esq->codigo == a->dir->dir){
    	 a->esq e a->dir sao irmaos
	
	}
   
} */
#endif
