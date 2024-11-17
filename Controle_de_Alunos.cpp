#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#include "Controle_de_Alunos.h"

void GravarAluno();
void GravarDisciplina();

char menu(){
	
	clrscr();
	printf("* * * MENU * * *\n");
	printf("[A] Cadastrar Aluno no arquivo\n");
	printf("[B] Ler Alunos cadastrados\n");
	printf("[C] Exibir Alunos cadastrados\n");
	printf("[D] Cadastrar Disciplina no arquivo\n");
	printf("[E] Ler Disciplinas cadastradas\n");
	printf("[F] Exibir Disciplinas cadastrados\n");
	printf("[ESC] SAIR\n");
	printf("Opcao: ");

	return toupper(getche());
}

int main(void) {
	TpAluno *A = NULL;
	TpDescritorAluno DescAluno;
	TpDescritorDisciplina DescDisci;
	char op;
	
	InicializarDescritorAluno(DescAluno);
	InicializarDescritorDisciplina(DescDisci);

	do {
		op = menu();
		clrscr();

		switch (op) {
			case 'A':
				GravarAluno();
			break;

			case 'B':
				InserirAlunoOrdenado(DescAluno);
			break;

			case 'C':
				printf("* * * ALUNOS * * *\n");
				ExibirAlunos(DescAluno);
			break;

			case 'D':
				GravarDisciplina();
			break;

			case 'E':
				InserirOrdenadoDisciplina(DescDisci);
			break;

			case 'F':
				printf("* * * DISCIPLINAS * * *\n");
				ExibirDisciplina(DescDisci);
			break;

			default:
				break;
		}
		getch();

	} while (op != 27);

	return 0;
}

void GravarDisciplina() {
	TpDisci Disciplina;

	FILE *arq = fopen("Disciplinas.dat", "ab");

	if (arq == NULL) {
		printf("Erro ao abrir arquivo!");
	} else {
		printf("* * * GRAVAR DISCIPLINA * * *\n");
		printf("Digite o nome da disciplina: ");
		fflush(stdin);
		gets(Disciplina.disci);
	
		printf("Digite a nota 1: ");
		scanf("%f", &Disciplina.nota1);

		printf("Digite a nota 2: ");
		scanf("%f", &Disciplina.nota2);

		printf("Digite a frequencia: ");
		fflush(stdin);
		scanf("%f", &Disciplina.freq);

		fwrite(&Disciplina, sizeof(TpDisci), 1, arq);

		printf("Dados gravados com sucesso!\n");
	}

	fclose(arq);
}

void GravarAluno() {
	TpAluno AlunoAux;
	TpData data;

	FILE *arq = fopen("Aluno.dat", "ab");

	if (arq == NULL) {
		printf("Erro ao abrir arquivo!");
	} else {
		printf("* * * GRAVAR ALUNO * * *\n");
		printf("Digite seu nome: ");
		fflush(stdin);
		gets(AlunoAux.nome);
	
		printf("Digite sua idade (dd/mm/aaaa): ");
		scanf("%d %d %d", &AlunoAux.data.d, &AlunoAux.data.m, &AlunoAux.data.a);

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