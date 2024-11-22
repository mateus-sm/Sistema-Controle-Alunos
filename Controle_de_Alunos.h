#define TF 50

struct TpDisci{
	char disci[TF];
	float nota1, nota2, freq;
	TpDisci *prox;
};

struct TpData{
	int d, m, a;
};

struct TpAluno{
	char nome[TF], curso[TF], rua[TF], bairro[TF], cidade[TF], estado[3];
	TpData data;
	TpAluno *prox, *ant;
	TpDisci *disciplina;
};

struct TpDescritorAluno {
	int qtde;
	TpAluno *inicio, *fim;
};

struct TpDescritorDisciplina {
	int qtde;
	TpDisci *inicio, *fim;
};

void InicializarDescritorAluno(TpDescritorAluno &D) {
	D.qtde = 0;
	D.inicio = D.fim = NULL;
}

TpAluno *NovoNoAluno(TpAluno AlunoAux) {
	TpAluno *aluno = new TpAluno;
	
	strcpy(aluno -> nome, AlunoAux.nome);
	strcpy(aluno -> curso, AlunoAux.curso);
	strcpy(aluno -> rua, AlunoAux.rua);
	strcpy(aluno -> bairro, AlunoAux.bairro);
	strcpy(aluno -> cidade, AlunoAux.cidade);
	strcpy(aluno -> estado, AlunoAux.estado);
	
	aluno -> data.d = AlunoAux.data.d;
	aluno -> data.m = AlunoAux.data.m;
	aluno -> data.a = AlunoAux.data.a;
	
	aluno -> prox = NULL;
	aluno -> ant = NULL;
	aluno -> disciplina = NULL;
	
	return aluno;
}

int BuscaAluno(char nome[TF], FILE *arq){
	
	TpAluno AlunoAux;
	
	fread(&AlunoAux, sizeof(TpAluno), 1, arq);
	while(!feof(arq) && stricmp(AlunoAux.nome, nome) != 0)
		fread(&AlunoAux, sizeof(TpAluno), 1, arq);
	
	if(!feof(arq))
		return ftell(arq) - sizeof(TpAluno);
	
	return -1;
}

int BuscaDisciplina(TpDisci Disciplina) {
	FILE *arq = fopen("Disciplinas.dat", "rb");
	TpDisci aux;
	int i;
	
	fread(&aux, sizeof(TpDisci), 1, arq);
	while(!feof(arq) && stricmp(aux.disci, Disciplina.disci) != 0) {
		fread(&aux, sizeof(TpDisci), 1, arq);
	}
	
	i = ftell(arq) - sizeof(TpAluno);
	fclose(arq);

	if(stricmp(aux.disci, Disciplina.disci) == 0) {
		return i;
	}
	
	return -1;
}

void ExcluirListaAlunos(TpDescritorAluno &D){
	
	if(D.qtde != 0){
		TpAluno *aux = D.inicio;
		D.inicio = D.inicio -> prox;
		delete aux;
		D.qtde--;
		ExcluirListaAlunos(D);
	}
}

void InserirAlunoOrdenado(TpDescritorAluno &D) {
	
	TpAluno *No, *ant, *atual, AlunoAux;
	
	FILE *arq = fopen("Aluno.dat", "rb");

	if (arq == NULL) {
		gotoxy(28, 10);
		printf("NAO EXISTEM ALUNOS CADASTRADOS!");
	}
	
	else {
		
		ExcluirListaAlunos(D);

		fread(&AlunoAux, sizeof(TpAluno), 1, arq);

		while(!feof(arq)){
			
			No = NovoNoAluno(AlunoAux);
			
			//1º caso - caso lista estiver vazia
			if (D.inicio == NULL) {
				D.inicio = D.fim = No;
			} else if (stricmp(D.inicio->nome, AlunoAux.nome) >= 0) {
				//2º caso - Elemento novo é menor que Inicio
				No->prox = D.inicio;
				D.inicio->ant = No;
				D.inicio = No;
			} else {
				//3º caso - Busca
				atual = D.inicio;
				while ((atual->prox != NULL) && (stricmp(atual->nome, AlunoAux.nome) < 0)) {
					atual = atual -> prox;
				}

				if (strcmp(atual->nome, AlunoAux.nome) >= 0) {
					No->prox = atual;
					atual->ant = D.fim->ant;
					atual->ant = No;
					atual->ant->prox = No;
				} else {
					No->ant = atual;
					atual->prox = No;
					D.fim = No;
				}
			}
			
			D.qtde++;

			fread(&AlunoAux, sizeof(TpAluno), 1, arq);
		}
		gotoxy(40, 10); printf("SUCESSO");
		gotoxy(38, 11); printf("ARQUIVO LIDO!");
		gotoxy(32, 12); printf("DADOS INSERIDOS NA LISTA!");
	}

	gotoxy(76,25);
	fclose(arq);
	getch();
}

void AlterarInfoAlunos(void){
	
	//system("cls");
	
	FILE *arq = fopen("Aluno.dat", "rb+");
	
	TpAluno AlunoAux;
	char op;
	
	if(arq == NULL)
		printf("Sem alunos no arquivo para realizar alteracoes!\n");
		
	else{
		printf("Aluno a alterar: ");
		fflush(stdin);
		gets(AlunoAux.nome);
		
		int Busca = BuscaAluno(AlunoAux.nome, arq);
			
		if(Busca != -1){
			
			printf("\nDeseja alterar qual informacao?");
			printf("\n[A] para Curso");
			printf("\n[B] para Data de Nascimento");
			printf("\n[C] para Rua");
			printf("\n[D] para Bairro");
			printf("\n[E] para Cidade");
			printf("\n[F] para Estado\n");
			printf("\nOpcao: ");
			op = toupper(getche());
			
			fseek(arq, Busca, 0);
			fread(&AlunoAux, sizeof(TpAluno), 1, arq);
			
			switch(op){
				
				case 'A':
					printf("\nDigite o novo Curso: ");
					fflush(stdin);
					gets(AlunoAux.curso);
					break;
				
				case 'B':
					printf("\nDigite a nova Data de Nascimento: ");
					scanf("%d %d %d", &AlunoAux.data.d, &AlunoAux.data.m, &AlunoAux.data.a);
					break;
				
				case 'C':
					printf("\nDigite o endereco da Rua: ");
					fflush(stdin);
					gets(AlunoAux.rua);
					break;
				
				case 'D':
					printf("\nDigite o endereco do Bairro: ");
					fflush(stdin);
					gets(AlunoAux.bairro);
					break;
				
				case 'E':
					printf("\nDigite a nova Cidade: ");
					fflush(stdin);
					gets(AlunoAux.cidade);
					break;
				
				case 'F':
					printf("\nDigite o novo Estado(XX): ");
					fflush(stdin);
					gets(AlunoAux.estado);		
			}
			
			fseek(arq, Busca, 0);
			fwrite(&AlunoAux, sizeof(TpAluno), 1, arq);
			printf("\nAlteracao realizada com sucesso!");
		}
		
		else
			printf("\nAluno nao encontrado!");
	}
	
	fclose(arq);
	getch();
}

void ExibirAluno(TpDescritorAluno D) {
	int i = 18;

	gotoxy(32, 10); printf("Informacoes %s: ", D.inicio -> nome);
	gotoxy(32, 11); printf("Ano de Nasc: %d/%d/%d", D.inicio -> data.d, D.inicio -> data.m, D.inicio -> data.a);
	gotoxy(32, 12); printf("Curso: %s", D.inicio -> curso);
	gotoxy(32, 13); printf("Rua: %s", D.inicio -> rua);
	gotoxy(32, 14); printf("Bairro: %s", D.inicio -> bairro);
	gotoxy(32, 15); printf("Cidade: %s", D.inicio -> cidade);
	gotoxy(32, 16); printf("Estado: %s", D.inicio -> estado);
}

void InicializarDescritorDisciplina(TpDescritorDisciplina &D) {
	D.inicio = D.fim = NULL;
	D.qtde = 0;
}

void ExibirAlunoComDisciplina(TpDescritorAluno D) {
	TpDescritorDisciplina auxD;
	InicializarDescritorDisciplina(auxD);
	auxD.inicio = D.inicio->disciplina;
	int x = 11, y = 18;

	gotoxy(32, 10); printf("Informacoes %s: ", D.inicio -> nome);
	gotoxy(32, 11); printf("Ano de Nasc: %d/%d/%d", D.inicio -> data.d, D.inicio -> data.m, D.inicio -> data.a);
	gotoxy(32, 12); printf("Curso: %s", D.inicio -> curso);
	gotoxy(32, 13); printf("Rua: %s", D.inicio -> rua);
	gotoxy(32, 14); printf("Bairro: %s", D.inicio -> bairro);
	gotoxy(32, 15); printf("Cidade: %s", D.inicio -> cidade);
	gotoxy(32, 16); printf("Estado: %s", D.inicio -> estado);

	if (auxD.inicio != NULL) {
		while(auxD.inicio != NULL) {
			gotoxy(x, y++); printf("Disciplina: %s", auxD.inicio->disci);
			gotoxy(x, y++); printf("Nota 1: %.2f", auxD.inicio->nota1);
			gotoxy(x, y++); printf("Nota 2: %.2f", auxD.inicio->nota2);
			gotoxy(x, y++); printf("Frequencia: %.2f", auxD.inicio->freq);
			auxD.inicio = auxD.inicio->prox;
			y = 18;
			x += 24;
			if (x == 83) {
				x = 11;
			}
		}
	}
}

void ExibirAlunos(TpDescritorAluno D, int flag) {
	
	if (D.qtde != 0) {
		for(int i = 9 ; i <= 22; i++){
			gotoxy(43, i); 
			printf("|");
		}
		int x, y = 10;

		if(flag % 2 == 0)
			x = 12;
		else
			x = 50;

		gotoxy(x, y++);
		printf("Informacoes: %s", D.inicio -> nome);
		gotoxy(x, y++);
		printf("Ano de Nasc: %d/%d/%.4d", D.inicio -> data.d, D.inicio -> data.m, D.inicio -> data.a);
		gotoxy(x, y++);
		printf("Curso: %s", D.inicio -> curso);
		gotoxy(x, y++);
		printf("Rua: %sn", D.inicio -> rua);
		gotoxy(x, y++);
		printf("Bairro: %s", D.inicio -> bairro);
		gotoxy(x, y++);
		printf("Cidade: %s", D.inicio -> cidade);
		gotoxy(x, y++);
		printf("Estado: %s", D.inicio -> estado);
		gotoxy(x, y++);

		
		D.inicio = D.inicio -> prox;
		D.qtde--;
		

		if(flag % 2 != 0){
			if(D.qtde != 0){ // NAO ACABOU
				gotoxy(48, 23);
				printf("[ENTER] PROXIMA PAGINA");
				getch();
				//limparQuadro();
				int x = 11, y = 9;
				while(y <= 24){
					gotoxy(x,y);
					printf("                                                               ");
					y++;
				}
				ExibirAlunos(D, flag + 1);
			} else {
				gotoxy(52, 23);
				printf("[ENTER] SAIR");
				getch();
			}
		}else{
			if(D.qtde != 0){
				ExibirAlunos(D, flag + 1);
			} else {
				gotoxy(52, 23);
				printf("[ENTER] SAIR");
				getch();
			}
		}
		
		
	}else if(D.qtde == 0 && flag == 0){
		gotoxy(28, 10);
		printf("NAO EXISTEM ALUNOS CADASTRADOS!");
	}

}

TpDisci *NovoNoDisciplina(TpDisci Disciplina) {
	TpDisci *Pont = new TpDisci;
	
	strcpy(Pont->disci, Disciplina.disci);
	Pont->nota1 = Disciplina.nota1;
	Pont->nota2 = Disciplina.nota2;
	Pont->freq = Disciplina.freq;
	Pont->prox = NULL;
	
	return Pont;
}

//Insere ordenado por nome da disciplina
void InserirOrdenadoDisciplina(TpDescritorDisciplina &D) {
	TpDisci *No, *ant, *atual, DisciAux;

	FILE *arq = fopen("Disciplinas.dat", "rb");

	if (arq == NULL) {
		gotoxy(28, 10);
		printf("NAO EXISTEM DISCIPLINAS CADASTRADAS!");
	} else {
		fread(&DisciAux, sizeof(TpDisci), 1, arq);

		while(!feof(arq)) {
			No = NovoNoDisciplina(DisciAux);

			D.qtde++;
			if (D.inicio == NULL) {
				D.inicio = D.fim = No;
			} else {
				if (stricmp(D.inicio->disci, DisciAux.disci) >= 0) {
					No->prox = D.inicio;
					D.inicio = No;
				} else {
					if (stricmp(D.inicio->disci, DisciAux.disci) <= 0) {
						D.fim = No;
						D.fim->prox = No;
					} else {
						ant = D.inicio;
						atual = D.inicio->prox;

						while (stricmp(atual->disci, DisciAux.disci) < 0) {
							ant = atual;
							atual = atual->prox;
						}

						No->prox = atual->prox;
						atual->prox = No;
					}
				}
			}

			fread(&DisciAux, sizeof(TpDisci), 1, arq);
		}

		gotoxy(40, 10); printf("SUCESSO");
		gotoxy(38, 11); printf("ARQUIVO LIDO!");
		gotoxy(32, 12); printf("DADOS INSERIDOS NA LISTA!");
	}

	gotoxy(76,25);
	fclose(arq);
	getch();
}

void ExibirDisciplina(TpDescritorDisciplina D) {
	gotoxy(32, 10); printf("Disciplina: %s", D.inicio->disci);
}
