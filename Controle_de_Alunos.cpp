#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#include "Controle_de_Alunos.h"

void GravarAluno();

char menu() {
	clrscr();
	printf("* * * MENU * * *\n");
	printf("[A] Cadastrar aluno no arquivo\n");
	printf("[B] Ler alunos cadastrados\n");
	printf("[C] Exibir alunos cadastrados\n");
	printf("[ESC] SAIR\n");
	printf("Opcao: ");

	return toupper(getche());
}

int main(void) {
	TpAluno *A = NULL;
	char op;

	do {
		op = menu();

		clrscr();
		switch (op) {
			case 'A':
				GravarAluno(); getch();
			break;

			case 'B':
				A = InserirOrdenado(A); getch();
			break;

			case 'C':
				printf("Alunos:"); ExibirAlunos(A); getch();
			break;

			default:
				break;
		}

	} while (op != 27);

	return 0;
}

void GravarAluno() {
	TpAluno AlunoAux;
	TpData data;
	FILE *arq = fopen("aluno.dat", "ab");

	if (arq == NULL) {
		printf("Erro ao abrir arquivo!");
	} else {
		printf("* * *Gravar Aluno* * *\n");
		printf("Digite seu nome: ");
		fflush(stdin);
		gets(AlunoAux.nome);
	
		printf("Digite sua idade (dd/mm/aaaa): ");
		scanf("%d/%d/%d", &AlunoAux.data.d, &AlunoAux.data.m, &AlunoAux.data.a);

		printf("Digite seu curso: ");
		fflush(stdin);
		gets(AlunoAux.curso);

		printf("Digite sua rua: ");
		fflush(stdin);
		gets(AlunoAux.rua);

		printf("Digite seu bairro: ");
		fflush(stdin);
		gets(AlunoAux.bairro);

		printf("Digite sua cidade: ");
		fflush(stdin);
		gets(AlunoAux.cidade);

		printf("Digite seu estado (--): ");
		fflush(stdin);
		gets(AlunoAux.estado);

		fwrite(&AlunoAux, sizeof(TpAluno), 1, arq);

		printf("Dados gravados com sucesso!\n");
	}

	fclose(arq);
}