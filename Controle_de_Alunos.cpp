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
char menuNum(void);
void clear();
TpAluno PercorrerListaAluno(TpDescritorAluno D);
void PercorrerListaDisciplina(TpDescritorDisciplina D, TpDisci &disci);
void ConectarDisciplina(TpDescritorAluno &D, TpAluno Aluno, TpDisci Disciplina);
void ExibirDisciplinas();
void inicializarAluno(TpAluno &A);
void inicializarDisciplina(TpDisci &D);

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
			case 'A':
				GravarAluno();
			break;

			case 'B':
				InserirAlunoOrdenado(DescAluno);
			break;

			case 'C':
				limparTitulo();
				gotoxy(32, 7);
				printf("* * * ALUNOS * * *");
				ExibirAlunos(DescAluno);
				getch();
			break;

			case 'D':
				GravarDisciplina(DescDisci);
			break;

			case 'E':
				InserirOrdenadoDisciplina(DescDisci);
			break;

			case 'F':
				limparTitulo();
				limparQuadro();
				ExibirDisciplinas();
				getch();
			break;
			
			case 'G':
				AlterarInfoAlunos();
			break;

			case 'H':
				inicializarAluno(Aluno);
				Aluno = PercorrerListaAluno(DescAluno);

				inicializarDisciplina(Disciplina);
				PercorrerListaDisciplina(DescDisci, Disciplina);
				if (Aluno.curso[0] != '\0' && Disciplina.nota1 != 0.0) {
					ConectarDisciplina(DescAluno, Aluno, Disciplina);
				}
			break;

			default:
				break;
		}
		
	} while (op != 27);
	
	return 0;
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
		limparTitulo(); gotoxy(32, 7); printf("* * * DISCIPLINAS * * *");
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
	TpDisci *No = NovoNoDisciplina(Disciplina);
	TpDescritorAluno aux = D;

	//Loop para chegar no aluno que vai receber a disciplina
	while (strcmp(D.inicio->nome, Aluno.nome) != 0) {
		D.inicio = D.inicio->prox;
	}

	//Logica para adicionar a disciplina
	if (D.inicio->disciplina == NULL) {
		D.inicio->disciplina = No;
	} 
	// else {
	// 	while (aux.inicio->disciplina->prox != NULL) {
	// 		aux.inicio->disciplina = aux.inicio->disciplina->prox;
	// 	}

	// 	aux.inicio->disciplina->prox = No;
	// }
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
			gotoxy(32, 22); printf("Pressione [A] ou [D] para percorrer.");
			gotoxy(32, 23); printf("Pressione [SPACE] para selecionar.");
			gotoxy(32, 24); printf("Pressione [ESC] para sair.");
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
		} while(tecla != 27);

	}

	fclose(arq);
	return AlunoAux;
}

void PercorrerListaDisciplina(TpDescritorDisciplina D, TpDisci &Disciplina) {
	char nomeDisci[30];
	TpDisci aux;
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
			gotoxy(64, 9); gets(nomeDisci);

			while(D.inicio != NULL && strcmp(D.inicio->disci, nomeDisci) != 0) {
				D.inicio = D.inicio->prox;
			}

			fseek(arq, 0, 0);
			fread(&aux, sizeof(TpDisci), 1, arq);
			while(!feof(arq) && stricmp(aux.disci, D.inicio->disci) != 0)
				fread(&aux, sizeof(TpDisci), 1, arq);

			if (stricmp(aux.disci, D.inicio->disci) != 0) {
				gotoxy(30, 10); printf("Disciplina nao encontrada!"); getch();
			} else {
				gotoxy(30, 10); printf("Disciplina selecionada: %s", aux.disci); getch();

				strcpy(Disciplina.disci, aux.disci);
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

	FILE *arq = fopen("Disciplinas.dat", "ab");

	if (arq == NULL) {
		gotoxy(l, c);
		printf("Erro ao abrir arquivo!");
	} else {
		limparTitulo();
		getch();
		gotoxy(27, 7); printf("* * * CADASTRAR DISCIPLINAS * * *\n");
		gotoxy(l, c);
		printf("Digite o nome da disciplina: ");
		fflush(stdin);
		c++; gotoxy(l, c);
		gets(Disciplina.disci);
		
		fclose(arq);
	
		if(BuscaDisciplina(Disciplina) == -1){
			
			arq = fopen("Disciplinas.dat", "ab");
			
			fwrite(&Disciplina, sizeof(TpDisci), 1, arq);
			limparQuadro();
			
			gotoxy(30, 12);
			printf("Dados gravados com sucesso!");
			
			fclose(arq);
			
		} else {
			gotoxy(30, 12);
			printf("Disciplina ja cadastrada");
		}
		
		arq = fopen("Disciplinas.dat", "ab");
	}

	fclose(arq);
	getch();
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
			

			l = 30, c = 10;	
			gotoxy(l,c);
			printf("Digite seu nome: ");
			fflush(stdin);
			c++; gotoxy(l, c);
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
	int l = 12, c = 9;
	
	while(c <= 24){
		gotoxy(l,c);
		printf("                                                               ");
		c++;
	}
	gotoxy(1, 1);
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
	
	moldura(10, 5, 75, 25, 7, 2); //borda externa //64
	moldura(11, 6, 74, 8, 7, 0); //titulo

	moldura(12,10,28,14,7,0); //ITEM 1 
	moldura(34,10,51,14,7,0); //ITEM 2 
	moldura(57,10,73,14,7,0); //ITEM 3 

	moldura(12,17,28,21,7,0); //ITEM 4 
	moldura(34,17,51,21,7,0); //ITEM 5 
	moldura(57,17,73,21,7,0); //ITEM 6 

	gotoxy(28, 7); printf("* * * Controle de Alunos * * *");
			
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
