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

TpAluno *NovoNoAluno(char nome[TF], int dia, int mes, int ano, char curso[TF], char rua[TF], char bairro[TF], char cidade[TF], char estado[3]){
	
	TpAluno *aluno = new TpAluno;
	
	strcpy(aluno -> nome, nome);
	strcpy(aluno -> curso, curso);
	strcpy(aluno -> rua, rua);
	strcpy(aluno -> bairro, bairro);
	strcpy(aluno -> cidade, cidade);
	strcpy(aluno -> estado, estado);
	
	aluno -> data.d = dia;
	aluno -> data.m = mes;
	aluno -> data.a = ano;
	
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

TpAluno *InserirOrdenado(TpAluno *aluno){
	
	TpData data;
	char nome[TF], curso[TF], rua[TF], bairro[TF], cidade[TF], estado[3];
	TpAluno *aux, *No;
	
	printf("Digite seu nome | digite 'sair' to close: ");
	fflush(stdin);
	gets(nome);
	
	while(stricmp(nome, "SAIR") != 0 || stricmp(nome, "sair") != 0){
		
		printf("Digite sua idade dd/mm/aaaa: ");
		scanf("%d %d %d", &data.d, &data.m, &data.a);

		printf("Digite seu curso: ");
		fflush(stdin);
		gets(curso);

		printf("Digite sua rua: ");
		fflush(stdin);
		gets(rua);

		printf("Digite seu bairro: ");
		fflush(stdin);
		gets(bairro);

		printf("Digite sua cidade: ");
		fflush(stdin);
		gets(cidade);

		printf("Por ultimo seu estado (ee): ");
		fflush(stdin);
		gets(estado);

		No = NovoNoAluno(nome, data.d, data.m, data.a, curso, rua, bairro, cidade, estado);
		
		if(aluno == NULL || stricmp(nome, aluno -> nome) < 0){
			No -> prox = aluno;

			if(aluno != NULL)
				aluno -> ant = No;

			aluno = No;
		}

		else{

			aux = aluno;
			while(aux -> prox != NULL && stricmp(nome, aux -> nome) > 0)
				aux = aux -> prox;

			if(stricmp(nome, aux -> nome) <= 0){

				No -> prox = aux;
				No -> ant = aux -> ant;
				aux -> ant = No;
				aux -> ant -> prox = No;
			}

			else{

				No -> ant = aux;
				aux -> prox = No;
			}
		}

		printf("\nDigite seu nome: ");
		fflush(stdin);
		gets(nome);
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