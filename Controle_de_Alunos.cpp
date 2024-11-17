#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#include "Controle_de_Alunos.h"

void GravarAluno();
void GravarDisciplina();
void limparQuadro(void);
void limparTitulo(void);
void moldura(int colunai, int linhai, int colunaf, int linhaf, int frente, int fundo);
void moldeMenuInicial(void);
char menuNum(void);

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
		op = menuNum();
		limparQuadro();

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
	int l = 30, c = 10;

	FILE *arq = fopen("Disciplinas.dat", "ab");

	if (arq == NULL) {
		gotoxy(l, c);
		printf("Erro ao abrir arquivo!");
	} else {
		limparTitulo();
		gotoxy(27, 7);
		printf("* * * Cadastrar Disciplinas * * *\n");
		gotoxy(l, c);
		printf("Digite o nome da disciplina: ");
		fflush(stdin);
		c++; gotoxy(l, c);
		gets(Disciplina.disci);
		while(strcmp(Disciplina.disci, "") != 0 ){
			c++;gotoxy(l, c);
			printf("Digite a nota 1: ");
			c++; gotoxy(l, c);
			scanf("%f", &Disciplina.nota1);
			c++; gotoxy(l, c);
			printf("Digite a nota 2: ");
			c++; gotoxy(l, c);
			scanf("%f", &Disciplina.nota2);
			c++; gotoxy(l, c);
			printf("Digite a frequencia: ");
			fflush(stdin);
			c++; gotoxy(l, c);
			scanf("%f", &Disciplina.freq);
			
			fwrite(&Disciplina, sizeof(TpDisci), 1, arq);
			limparQuadro();
			gotoxy(30, 10);
			printf("Dados gravados com sucesso!");
			getch();
			limparQuadro();

			l = 30, c = 10;
			gotoxy(l, c);
			printf("Digite o nome da disciplina: ");
			fflush(stdin);
			c++; gotoxy(l, c);
			gets(Disciplina.disci);
		}
		
	}

	fclose(arq);
}

void GravarAluno() {
	TpAluno AlunoAux;
	TpData data;
	int l = 30, c = 10;

	FILE *arq = fopen("Aluno.dat", "ab");

	if (arq == NULL) {
		gotoxy(30,10);
		printf("Erro ao abrir arquivo!");
	} else {
		limparTitulo();
		gotoxy(30, 7);
		printf("* * * Cadastrar Alunos * * *\n");
		gotoxy(l,c);
		printf("Digite seu nome: ");
		fflush(stdin);
		c++; gotoxy(l, c);
		gets(AlunoAux.nome);
		
		while(strcmp(AlunoAux.nome, "") != 0){
			c++; gotoxy(l, c);
			printf("Digite sua idade (dd/mm/aaaa): ");
			c++; gotoxy(l, c);
			scanf("%d %d %d", &AlunoAux.data.d, &AlunoAux.data.m, &AlunoAux.data.a);
			c++; gotoxy(l, c);
			printf("Digite seu curso: ");
			fflush(stdin);
			c++; gotoxy(l, c);
			gets(AlunoAux.curso);
			c++; gotoxy(l, c);
			printf("Digite sua rua: ");
			fflush(stdin);
			c++; gotoxy(l, c);
			gets(AlunoAux.rua);
			c++; gotoxy(l, c);
			printf("Digite seu bairro: ");
			fflush(stdin);
			c++; gotoxy(l, c);
			gets(AlunoAux.bairro);
			c++; gotoxy(l, c);
			printf("Digite sua cidade: ");
			fflush(stdin);
			c++; gotoxy(l, c);
			gets(AlunoAux.cidade);
			c++; gotoxy(l, c);
			printf("Digite seu estado (--): ");
			fflush(stdin);
			c++; gotoxy(l, c);
			gets(AlunoAux.estado);

			fwrite(&AlunoAux, sizeof(TpAluno), 1, arq);
			limparQuadro();
			gotoxy(30, 10);
			printf("Dados gravados com sucesso!");
			getch();
			limparQuadro();

			l = 30, c = 10;	
			gotoxy(l,c);
			printf("Digite seu nome: ");
			fflush(stdin);
			c++; gotoxy(l, c);
			gets(AlunoAux.nome);
		}
		
	}

	fclose(arq);
}

void limparQuadro(void){
	int l = 12, c = 9;
	
	while(c <= 22){
		gotoxy(l,c);
		printf("                                                               ");
		c++;
	}
}

void limparTitulo(void){
	gotoxy(12,7);
	printf("                                                              ");
	gotoxy(76,23);
}

void moldura(int colunai, int linhai, int colunaf, int linhaf, int frente, int fundo){
	textcolor(frente);
	textbackground(fundo);
	
	gotoxy(colunai, linhai); 
	printf("%c", 201); //canto superior esquerdo
	gotoxy(colunaf, linhai); 
	printf("%c", 187);//canto superior direito
	gotoxy(colunai, linhaf); 
	printf("%c", 200); //canto inferior esquerdo
	gotoxy(colunaf, linhaf); 
	printf("%c", 188);//canto inferior direito
	
	
	for(int a = colunai + 1; a < colunaf; a++){ 
		gotoxy(a, linhai); printf("%c", 205); 			
		gotoxy(a, linhaf); printf("%c", 205);
	}

	for(int b = linhai + 1; b < linhaf; b++){
		gotoxy(colunai, b); printf("%c", 186);
		gotoxy(colunaf, b); printf("%c", 186);
	}
	
	
	//voltar cores de texto e fundo padrão
	textcolor(7);
	textbackground(0);
	
}

void moldeMenuInicial(void){
	//clrscr();
	
	moldura(10, 5, 75, 23, 7, 2); //borda externa //64
	moldura(11, 6, 74, 8, 7, 0); //titulo

	moldura(12,10,28,14,7,0); //ITEM 1 
	moldura(34,10,51,14,7,0); //ITEM 2 
	moldura(57,10,73,14,7,0); //ITEM 3 

	moldura(12,17,28,21,7,0); //ITEM 4 
	moldura(34,17,51,21,7,0); //ITEM 5 
	moldura(57,17,73,21,7,0); //ITEM 6 

	gotoxy(30, 7); 
	printf("* * * Controle de Alunos * * *");
			
}

char menuNum(void) {
	clrscr();
	moldeMenuInicial();
	
	gotoxy(13,11);
	printf("[A] Cadastrar");
	gotoxy(17,12);
	printf("Alunos");

	gotoxy(35,11);
	printf("[B] Ler");
	gotoxy(39,12);
	printf("Alunos");

	gotoxy(58,11);
	printf("[C] Exibir");
	gotoxy(62,12);
	printf("Alunos");

	gotoxy(13,18);
	printf("[D] Cadastrar");
	gotoxy(17,19);
	printf("Disciplinas");

	gotoxy(35,18);
	printf("[E] Ler");
	gotoxy(39,19);
	printf("Disciplinas");
	
	gotoxy(58,18);
	printf("[F] Exibir");
	gotoxy(62,19);
	printf("Disciplinas");

	gotoxy(76,23);

	return toupper(getch());
}