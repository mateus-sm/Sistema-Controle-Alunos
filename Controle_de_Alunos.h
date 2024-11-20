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

int BuscaDisciplina(TpDisci Disciplina){
	
	FILE *arq = fopen("Disciplinas.dat", "rb");
	
	TpDisci aux;
	
	fread(&aux, sizeof(TpDisci), 1, arq);
	while(!feof(arq) && stricmp(aux.disci, Disciplina.disci) != 0)
		fread(&aux, sizeof(TpDisci), 1, arq);
	
	if(!feof(arq))
		return ftell(arq) - sizeof(TpAluno);
	
	return -1;
}

void InserirAlunoOrdenado(TpDescritorAluno &D) {
	
	TpAluno *No, *ant, *atual, AlunoAux;
	
	FILE *arq = fopen("Aluno.dat", "rb");

	if (arq == NULL) {
		gotoxy(30, 10);
		printf("Nao existem alunos no arquivo para serem inseridos na lista!");
	}
	
	else {

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
		gotoxy(18, 10);
		printf("Arquivo lido e dados inseridos na lista com sucesso!");
	}

	fclose(arq);
	getch();
}

void AlterarInfoAlunos(void){
	
	system("cls");
	
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

void ExibirAlunos(TpDescritorAluno D) {

	if (D.qtde != 0) {
		printf("\nInformacoes do %s: \n\n", D.inicio -> nome);
		printf("Ano de Nasc: %d/%d/%d\n", D.inicio -> data.d, D.inicio -> data.m, D.inicio -> data.a);
		printf("Curso: %s\n", D.inicio -> curso);
		printf("Rua: %s\n", D.inicio -> rua);
		printf("Bairro: %s\n", D.inicio -> bairro);
		printf("Cidade: %s\n", D.inicio -> cidade);
		printf("Estado: %s\n", D.inicio -> estado);
		D.inicio = D.inicio -> prox;
		D.qtde--;

		ExibirAlunos(D);
	}
}

void InicializarDescritorDisciplina(TpDescritorDisciplina &D) {
	D.inicio = D.fim = NULL;
	D.qtde = 0;
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
		printf("Arquivo de Disciplinas vazio!");
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

		printf("Arquivo lido e dados inseridos na lista com sucesso!");
	}

	fclose(arq);
	getch();
}

void ExibirDisciplina() {

	int c = 30, l = 10;
	TpDisci DisciAux;
	FILE *arq = fopen("Disciplinas.dat", "rb");

	gotoxy(32, 7);
	printf("* * * DISCIPLINAS * * *");
	
	fread(&DisciAux, sizeof(TpDisci), 1, arq);
    while (!feof(arq)){
		gotoxy(c, l++);
		printf("Disciplina: %s", DisciAux.disci);
		fread(&DisciAux, sizeof(TpDisci), 1, arq);
    }

	getch();
}
