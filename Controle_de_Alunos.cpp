#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#include "Controle_de_Alunos.h"

void GravarAluno();
void GravarDisciplina(TpDescritorDisciplina &DescDisci);
void limparQuadro(void);
void limparTitulo(void);
void moldura(int colunai, int linhai, int colunaf, int linhaf, int frente, int fundo);
void moldeMenuInicial(void);
void moldeMenuAlunos(void);
char menuDisciplina(void);
char menuNum(void);
char menuAlunos(void);
void clear();
TpAluno PercorrerListaAluno(TpDescritorAluno D);
void PercorrerListaDisciplina(TpDescritorDisciplina D, TpDisci &disci);
void ConectarDisciplina(TpDescritorAluno &D, TpAluno Aluno, TpDisci Disciplina);
void ExibirDisciplinas();
void inicializarAluno(TpAluno &A);
void inicializarDisciplina(TpDisci &D);
void PercorrerListaAlunoComDisciplina(TpDescritorAluno D);

int main(void) {
	TpAluno *A = NULL;
	TpAluno Aluno;
	TpDisci Disciplina;
	TpDescritorAluno DescAluno;
	TpDescritorDisciplina DescDisci;
	char op;
	
	InicializarDescritorAluno(DescAluno);
	InicializarDescritorDisciplina(DescDisci);
	
	do {
		op = menuNum();
		limparQuadro();

		switch (op) {
			case '1':
				op = menuAlunos();
				limparQuadro();

				switch (op){
					case 'A':
						GravarAluno();
					break;
					case 'B':
						buscarAluno();
					break;
					case 'C':
						AlterarInfoAlunos();
					break;
					case 'D':
						
					break;
				}

			break;

			case '2':
				InserirAlunoOrdenado(DescAluno);
			break;

			case '3':
				limparTitulo();
				gotoxy(35, 7);
				printf("* * * Alunos * * *");
				ExibirAlunos(DescAluno, 0);
				limparQuadro();
			break;
				
			case '4':
				op = menuDisciplina();
				limparQuadro();

				switch(op){
					case 'A':
						GravarDisciplina(DescDisci);
					break;
					case 'B':
						buscarDisciplina();
					break;
					case 'C':

					break;
					case 'D':	
					
					break;

				}
				
			break;

			case '5':
				InserirOrdenadoDisciplina(DescDisci);
			break;

			case '6':
				limparTitulo();
				limparQuadro();
				ExibirDisciplinas();
				getch();
			break;
			
			case '7':
				
			break;

			case '8':
				inicializarAluno(Aluno);
				Aluno = PercorrerListaAluno(DescAluno);
				
				inicializarDisciplina(Disciplina);
				PercorrerListaDisciplina(DescDisci, Disciplina);

				if (Aluno.curso[0] != '\0' && Disciplina.nota1 != 0.0) {
					ConectarDisciplina(DescAluno, Aluno, Disciplina);
				}
			break;
			
			case '9':
				PercorrerListaAlunoComDisciplina(DescAluno);
			break;

			default:
				break;
		}

	} while (op != 27);
	
	return 0;
}

void PercorrerListaAlunoComDisciplina(TpDescritorAluno D) {
	char tecla;

	if (D.inicio == NULL) {
		gotoxy(18, 10); printf("Lista de alunos vazia!");
	} else {
		do {
			limparQuadro();
			gotoxy(11, 23); printf("Dicas de navegacao: ");
			gotoxy(11, 24); printf("[A] ou [D] Percorrer | [ESC] Sair | ");
			ExibirAlunoComDisciplina(D);
			tecla = toupper(getch());

			switch (toupper(tecla)) {
				case 'A':
					if (D.inicio->ant != NULL) {
						D.inicio = D.inicio->ant;
					}
				break;

				case 'D':
					if (D.inicio->prox != NULL) {
						D.inicio = D.inicio->prox;
					}
				break;

			}
		} while(tecla != 27);

	}

}

void inicializarAluno(TpAluno &aluno) {
	aluno.nome[0] = '\0';
    aluno.curso[0] = '\0';
    aluno.rua[0] = '\0';
    aluno.bairro[0] = '\0';
    aluno.cidade[0] = '\0';
    aluno.estado[0] = '\0';
    aluno.estado[1] = '\0';
    aluno.data.d = 0;
    aluno.data.m = 0;
    aluno.data.a = 0;
    aluno.ant = NULL;
    aluno.disciplina = NULL;
    aluno.prox = NULL;
}

void inicializarDisciplina(TpDisci &disciplina) {
	disciplina.disci[0] = '\0';  
    disciplina.nota1 = 0.0;
    disciplina.nota2 = 0.0;
    disciplina.freq = 0.0; 
    disciplina.prox = NULL;
}

void ExibirDisciplinas() {
	int c = 30, l = 11;
	TpDisci DisciAux;
	FILE *arq = fopen("Disciplinas.dat", "rb");

	if (arq == NULL) {
		gotoxy(18, 10); printf("Arquivo de disciplinas vazio!");
	} else {
		limparTitulo(); gotoxy(32, 7); printf("* * * Disciplinas * * *");
		gotoxy(30, l++); printf("Disciplinas disponiveis:");

		fread(&DisciAux, sizeof(TpDisci), 1, arq);
		while (!feof(arq)) {
			gotoxy(c, l++); printf("Disciplina: %s", DisciAux.disci);
			fread(&DisciAux, sizeof(TpDisci), 1, arq);
		}
	}

	fclose(arq);
}

void clear(void) {
	textbackground(0);
    //Limpa 50 linhas
    gotoxy(1, 1);
    for (int i = 1; i < 50; i++) {
        clreol();
        gotoxy(1, i);
    }
    gotoxy(1, 1);
}

void ConectarDisciplina(TpDescritorAluno &D, TpAluno Aluno, TpDisci Disciplina) {
	TpAluno *AlunoAtual = D.inicio;
	TpDisci *No = NovoNoDisciplina(Disciplina);

	//Loop para chegar no aluno que vai receber a disciplina
	while (strcmp(AlunoAtual->nome, Aluno.nome) != 0) {
		AlunoAtual = AlunoAtual->prox;
	}

	//Logica para adicionar a disciplina
	if (AlunoAtual->disciplina == NULL) {
		AlunoAtual->disciplina = No;
	} else {
        // Ponteiro auxiliar para percorrer as disciplinas
        TpDisci *DisciplinaAtual = AlunoAtual->disciplina;

        // Percorre até a última disciplina
        while (DisciplinaAtual->prox != NULL) {
            DisciplinaAtual = DisciplinaAtual->prox;
        }

        // Conecta a nova disciplina ao final da lista
        DisciplinaAtual->prox = No;
	}
}

TpAluno PercorrerListaAluno(TpDescritorAluno D) {
	char tecla;
	TpAluno AlunoAux;
	FILE *arq = fopen("Aluno.dat", "rb");

	if (D.inicio == NULL) {
		gotoxy(18, 10); printf("Lista de alunos vazia!");
	} else {
		do {
			limparQuadro();
			gotoxy(11, 23); printf("Dicas de navegacao: ");
			gotoxy(11, 24); printf("[A] ou [D] Percorrer | [SPACE] Selecionar");
			ExibirAluno(D);
			tecla = toupper(getch());

			switch (toupper(tecla)) {
				case 'A':
					if (D.inicio->ant != NULL) {
						D.inicio = D.inicio->ant;
					}
				break;

				case 'D':
					if (D.inicio->prox != NULL) {
						D.inicio = D.inicio->prox;
					}
				break;

				case 32: 
					fseek(arq, 0, 0);
					fread(&AlunoAux, sizeof(TpAluno), 1, arq);
					while(!feof(arq) && stricmp(AlunoAux.nome, D.inicio->nome) != 0)
						fread(&AlunoAux, sizeof(TpAluno), 1, arq);

					gotoxy(32, 18); printf("Aluno selecionado: %s", AlunoAux.nome); getch();
				break;
			}
		} while(tecla != 32);

	}

	fclose(arq);
	return AlunoAux;
}

void PercorrerListaDisciplina(TpDescritorDisciplina D, TpDisci &Disciplina) {
	char nomeDisci[30];
	FILE *arq = fopen("Disciplinas.dat", "rb");

	if (arq == NULL) {
		gotoxy(18, 10); printf("Arquivo de Disciplinas vazio!");
	} else {
		if (D.inicio == NULL) {
			gotoxy(18, 10); printf("Lista de Disciplinas vazia!");
		} else {
			limparQuadro();
			gotoxy(18, 9); printf("Digite o nome da disciplina que quer inserir:");
			ExibirDisciplinas();
			gotoxy(64, 9); fflush(stdin); gets(nomeDisci);

			while(D.inicio != NULL && stricmp(D.inicio->disci, nomeDisci) != 0) {
				D.inicio = D.inicio->prox;
			}

			if(!BuscaDisciplina(Disciplina, arq)) {
				gotoxy(30, 10); printf("Disciplina nao encontrada!"); getch();
			} else {
				gotoxy(30, 10); printf("Disciplina selecionada: %s", nomeDisci); getch();

				strcpy(Disciplina.disci, nomeDisci);
				limparQuadro();
				gotoxy(32, 10); printf("Digite a nota1: "); scanf("%f", &Disciplina.nota1);
				limparQuadro();
				gotoxy(32, 10); printf("Digite a nota2: "); scanf("%f", &Disciplina.nota2);
				limparQuadro();
				gotoxy(32, 10); printf("Digite a frequencia: "); scanf("%f", &Disciplina.freq);
			}
		}
	}

	fclose(arq);
}

void GravarDisciplina(TpDescritorDisciplina &D) {
	TpDisci Disciplina;
	int l = 30, c = 10;

	FILE *arq = fopen("Disciplinas.dat", "ab+");

	if (arq == NULL) {
		gotoxy(l, c);
		printf("Erro ao abrir arquivo!");
	} else {
		limparTitulo();
		gotoxy(27, 7); printf("* * * Cadastrar Disciplinas * * *");
		gotoxy(l, c);
		printf("Digite o nome da disciplina: ");
		fflush(stdin);
		c++; gotoxy(l, c);
		gets(Disciplina.disci);
	
		if(BuscaDisciplina(Disciplina, arq) == -1){

			fwrite(&Disciplina, sizeof(TpDisci), 1, arq);
			limparQuadro();

			gotoxy(30, 12);
			printf("Dados gravados com sucesso!");

		} else {
			gotoxy(30, 12);
			printf("Disciplina ja cadastrada");
		}
	}

	fclose(arq);
	getch();
}

void GravarAluno() {
	TpAluno AlunoAux;
	TpData data;
	int x = 30, y = 10;

	FILE *arq = fopen("Aluno.dat", "ab");

	if (arq == NULL) {
		gotoxy(30,10);
		printf("Erro ao abrir arquivo!");
	} else {
		limparTitulo();
		gotoxy(30, 7);
		printf("* * * Cadastrar Alunos * * *");
		gotoxy(x,y++);
		printf("Digite seu nome: ");
		fflush(stdin);
		gotoxy(x,y++);
		gets(AlunoAux.nome);
		
		while(strcmp(AlunoAux.nome, "") != 0){
			gotoxy(x,y++);
			printf("Digite seu Ano de Nasc. (dd/mm/aaaa): ");
			gotoxy(x,y++);
			scanf("%d %d %d", &AlunoAux.data.d, &AlunoAux.data.m, &AlunoAux.data.a);
			gotoxy(x,y++);
			printf("Digite seu curso: ");
			fflush(stdin);
			gotoxy(x,y++);
			gets(AlunoAux.curso);
			gotoxy(x,y++);
			printf("Digite sua rua: ");
			fflush(stdin);
			gotoxy(x,y++);
			gets(AlunoAux.rua);
			gotoxy(x,y++);
			printf("Digite seu bairro: ");
			fflush(stdin);
			gotoxy(x,y++);
			gets(AlunoAux.bairro);
			gotoxy(x,y++);
			printf("Digite sua cidade: ");
			fflush(stdin);
			gotoxy(x,y++);
			gets(AlunoAux.cidade);
			gotoxy(x,y++);
			printf("Digite seu estado (--): ");
			fflush(stdin);
			gotoxy(x,y++);
			gets(AlunoAux.estado);

			fwrite(&AlunoAux, sizeof(TpAluno), 1, arq);
			limparQuadro();


			x = 30, y = 10;	
			gotoxy(x,y++);
			printf("Digite seu nome: ");
			fflush(stdin);
			gotoxy(x,y++);
			gets(AlunoAux.nome);
		}
		
		gotoxy(30, 10);
		printf("Dados gravados com sucesso!");
		getch();
		limparQuadro();
	}	

	fclose(arq);
}

void limparQuadro(void) {
	int x = 11, y = 9;
	
	while(y <= 24){
		gotoxy(x,y);
		printf("                                                               ");
		y++;
	}
	gotoxy(76, 25);
}

void limparTitulo(void){
	gotoxy(12,7);
	printf("                                                              ");
	gotoxy(76,25);
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
	
	moldura(10, 5, 75, 25, 7, 2); //borda externa //64
	moldura(11, 6, 74, 8, 7, 0); //titulo

	moldura(12,10,28,14,7,0); //ITEM 1 
	moldura(34,10,51,14,7,0); //ITEM 2 
	moldura(57,10,73,14,7,0); //ITEM 3 

	moldura(12,17,28,21,7,0); //ITEM 4 
	moldura(34,17,51,21,7,0); //ITEM 5 
	moldura(57,17,73,21,7,0); //ITEM 6 

	gotoxy(30, 7); printf("* * * Controle de Alunos * * *");
			
}

char menuNum(void) {
	system("cls");
	moldeMenuInicial();
	
	gotoxy(13,11);
	printf("[1] Acessar");
	gotoxy(17,12);
	printf("Alunos");
	

	gotoxy(35,11);
	printf("[2] Ler");
	gotoxy(39,12);
	printf("Alunos");

	gotoxy(58,11);
	printf("[3] Exibir");
	gotoxy(62,12);
	printf("Alunos");

	gotoxy(13,18);
	printf("[4] Acessar");
	gotoxy(17,19);
	printf("Disciplinas");

	gotoxy(35,18);
	printf("[5] Ler");
	gotoxy(39,19);
	printf("Disciplinas");
	
	gotoxy(58,18);
	printf("[6] Exibir");
	gotoxy(62,19);
	printf("Disciplinas");

	gotoxy(76,25);

	return toupper(getch());
}

char menuAlunos(void){
	clrscr();
	moldeMenuAlunos();

	gotoxy(19,11);
	printf("[A] Cadastrar");
	gotoxy(23,12);
	printf("Alunos");

	gotoxy(50,11);
	printf("[B] Buscar");
	gotoxy(54,12);
	printf("Alunos");

	gotoxy(19,18);
	printf("[C] Alterar");
	gotoxy(23, 19);
	printf("Alunos");
	
	gotoxy(50,18);
	printf("[D] Excluir");
	gotoxy(54,19);
	printf("Alunos");

	gotoxy(35, 7); 
	printf("* * * Alunos * * *");

	gotoxy(76,25);

	return toupper(getch());
}

char menuDisciplina(void){
	clrscr();
	moldeMenuAlunos();

	gotoxy(19,11);
	printf("[A] Cadastrar");
	gotoxy(23,12);
	printf("Discplinas");

	gotoxy(50,11);
	printf("[B] Buscar");
	gotoxy(54,12);
	printf("Discplinas");

	gotoxy(19,18);
	printf("[C] Alterar");
	gotoxy(23, 19);
	printf("Discplinas");
	
	gotoxy(50,18);
	printf("[D] Excluir");
	gotoxy(54,19);
	printf("Discplinas");

	gotoxy(33, 7); 
	printf("* * * Disciplinas * * *");

	gotoxy(76,25);

	return toupper(getch());
}

void moldeMenuAlunos(void){
	moldura(10, 5, 75, 25, 7, 2); //borda externa //64
	moldura(11, 6, 74, 8, 7, 0); //titulo

	moldura(18,10,36,14,7,0); //ITEM 1 
	moldura(49,10,67,14,7,0); //ITEM 2

	moldura(18,17,36,21,7,0); //ITEM 3 
	moldura(49,17,67,21,7,0); //ITEM 4  

}