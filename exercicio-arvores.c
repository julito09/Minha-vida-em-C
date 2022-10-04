#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"arvores.h"
// Trabalho Pratico de Arvores Binarias de Pesquisa
// Nome: Julio Cesar
int main () {
	int codigo,cpf,ra,op,op2;
	char data[10], nome[20],sexo[10];
	Arvore *a = cria_arv_vazia ();
	while(true){
	printf("[1] - Inserir aluno\n");
	printf("[2] - Retirar aluno\n");
	printf("[3] - Pesquisar aluno\n");
	printf("[4] - Vizualizar os dados\n");
	scanf("%d", &op);
	switch(op){
	case 1:
		printf("Digite o nome do aluno(a)\n");
		fflush(stdin);
		gets(nome);
		printf("Digite o sexo do aluno(a)\n");
		fflush(stdin);
		gets(sexo);
		printf("Digite a data de nascimento do aluno(a)\n");
		fflush(stdin);
		gets(data);
		printf("Digite o codigo do aluno(a):\n");
		scanf("%d",&codigo);
		printf("Digite o cpf do aluno(a):\n");
		scanf("%d",&cpf);
		printf("Digite o RA do aluno(a):\n");
		scanf("%d", &ra);
		a = inserir(a,codigo,cpf,data,ra,nome,sexo);
		printf("\nCadastrado realizado com sucesso!\n");
		system("pause");
		system("cls");
		break;
	case 2:
		printf("Digite o codigo do aluno a ser removido\n");
		scanf("%d",&codigo);
		Remover(a,codigo,cpf,ra,nome,data,sexo);
		system("pause");
		system("cls");
		break;
		
	case 3:
		printf("Digite o codigo do aluno a ser pesquisado\n");
		scanf("%d",&codigo);
		buscar(a,codigo);
		system("pause");
		system("cls");
		break;
	case 4:
		printf("[1] - Vizualizar em Pre-Ordem\n");
		printf("[2] - Vizualizar em Pos-Ordem\n");
		printf("[3] - Vizualizar em In-Ordem\n");
		scanf("%d", &op2);
		if(cont==0){
			printf("Nao ha alunos cadastrados!\n");
			system("pause");
			system("cls");
			break;
		}
		switch(op2){
			case 1:
				printf("\nAlunos cadastrados: #%d\n", cont);
				pre_ordem(a);
				system("pause");
				system("cls");
				break;
			case 2:
				printf("\nAlunos cadastrados: #%d\n", cont);
				pos_ordem(a);
				system("pause");
				system("cls");
				break;
			case 3:
				printf("\nAlunos cadastrados: #%d\n", cont);
				in_ordem(a);
				system("pause");
				system("cls");
				break;
			default:
				printf("\nOpcao invalida\n!");
				system("pause");
				system("cls");
				break;
		}
		break;
	default:
		printf("\nOpcao invalida\n!");
		system("pause");
		system("cls");
		break;
	}

}
return 0;


}
