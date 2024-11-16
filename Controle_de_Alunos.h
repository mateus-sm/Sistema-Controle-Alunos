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
	
	FILE *arq = fopen("Aluno.dat", "rb");

	if (arq == NULL) {
		printf("Nao existem alunos no arquivo para serem inseridos na lista!");
	} else {
		while (!feof(arq)) {
			fread(&AlunoAux, sizeof(TpAluno), 1, arq);

			No = NovoNoAluno(AlunoAux);
			
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
		}
		printf("Dados lidos e Inseridos com sucesso!");
	}

	fclose(arq);
	return aluno;
}

void ExibirAlunos(TpAluno *alunos) {
	if (alunos != NULL) {
		printf("\nInformacoes do %s: \n\n", alunos -> nome);
		printf("Ano de Nasc: %d/%d/%d\n", alunos -> data.d, alunos -> data.m, alunos -> data.a);
		printf("Curso: %s\n", alunos -> curso);
		printf("Rua: %s\n", alunos -> rua);
		printf("Bairro: %s\n", alunos -> bairro);
		printf("Cidade: %s\n", alunos -> cidade);
		printf("Estado: %s\n", alunos -> estado);

		ExibirAlunos(alunos = alunos -> prox);
	}
}