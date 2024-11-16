#define TF 50

struct TpDisci{
	char disci[TF];
	float nota1, nota2, freq;
	TpDisci *prox;
};

struct TpDiscr{
	int qtde;
	TpDisci *inicio, *fim;
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

TpAluno *NovoNoAluno(TpAluno AlunoAux, TpData DataAux) {
	TpAluno *aluno = new TpAluno;
	
	strcpy(aluno -> nome, AlunoAux.nome);
	strcpy(aluno -> curso, AlunoAux.curso);
	strcpy(aluno -> rua, AlunoAux.rua);
	strcpy(aluno -> bairro, AlunoAux.bairro);
	strcpy(aluno -> cidade, AlunoAux.cidade);
	strcpy(aluno -> estado, AlunoAux.estado);
	
	aluno -> data.d = DataAux.d;
	aluno -> data.m = DataAux.m;
	aluno -> data.a = DataAux.a;
	
	aluno -> prox = NULL;
	aluno -> ant = NULL;
	aluno -> disciplina = NULL;
	
	return aluno;
}

TpDisci *NovoNoDisciplina(char disci[TF], float nota1, float nota2, float freq){
	
	TpDisci *disc = new TpDisci;
	
	strcpy(disc -> disci, disci);

	disc -> nota1 = nota1;
	disc -> nota2 = nota2;
	disc -> freq = freq;

	disc -> prox = NULL;
	
	return disc;
}

TpAluno *InserirOrdenado(TpAluno *aluno) {
	TpAluno *aux, *No, AlunoAux;
	TpData data;
	
	printf("Digite seu nome | digite 'sair' para encerrar: ");
	fflush(stdin);
	gets(AlunoAux.nome);
	
	while (stricmp(AlunoAux.nome, "SAIR") != 0 || stricmp(AlunoAux.nome, "sair") != 0) {
		printf("Digite sua idade (dd/mm/aaaa): ");
		scanf("%d/%d/%d", &data.d, &data.m, &data.a);

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

		No = NovoNoAluno(AlunoAux, data);
		
		if (aluno == NULL || stricmp(AlunoAux.nome, aluno -> nome) < 0) {
			No -> prox = aluno;

			if (aluno != NULL) {
				aluno -> ant = No;
			}
			aluno = No;
		} else {
			aux = aluno;
			while (aux -> prox != NULL && stricmp(AlunoAux.nome, aux -> nome) > 0) {
				aux = aux -> prox;
			}

			if (stricmp(AlunoAux.nome, aux -> nome) <= 0) {
				No -> prox = aux;
				No -> ant = aux -> ant;
				aux -> ant = No;
				aux -> ant -> prox = No;
			} else {
				No -> ant = aux;
				aux -> prox = No;
			}
		}

		printf("\nDigite seu nome: ");
		fflush(stdin);
		gets(AlunoAux.nome);
	}

	return aluno;
}

void ExibirAlunos(TpAluno *alunos){

	if(alunos != NULL){

		printf("\nInformacoes do %s: \n\n", alunos -> nome);
		printf("Ano de Nasc: %d/%d/%d\n", alunos -> data.d, alunos -> data.m, alunos -> data.a);
		printf("Curso: %s\n", alunos -> curso);
		printf("Rua: %s\n", alunos -> rua);
		printf("Bairro: %s\n", alunos -> bairro);
		printf("Cidade: %s\n", alunos -> cidade);
		printf("Estado: %s\n", alunos -> estado);

		ExibirAlunos(alunos = alunos -> prox);
	}

	getch();
}