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

struct TpDescr{
	int qtde;
	TpAluno *inicio, *fim;
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

void InicializarDescritor(TpDescr &D){
	
	D.qtde = 0;
	D.inicio = D.fim = NULL;
}

void InserirOrdenadoDescritor(TpDescr &D){
	
	TpAluno *No, *ant, *atual, AlunoAux;
	
	FILE *arq = fopen("Aluno.dat", "rb");

	if (arq == NULL) 
		printf("Nao existem alunos no arquivo para serem inseridos na lista!");
	
	else {

		fread(&AlunoAux, sizeof(TpAluno), 1, arq);

		while(!feof(arq)){
			
			No = NovoNoAluno(AlunoAux);
			
			//1º caso - caso lista estiver vazia
			if(D.inicio == NULL)
				D.inicio = D.fim = No;
			
			//2º caso
			else if(stricmp(D.inicio -> nome, AlunoAux.nome) >= 0){
				
				No -> prox = D.inicio;
				D.inicio = No;
			}
			
			//3º caso
			else if(stricmp(D.fim -> nome, AlunoAux.nome) <= 0){
				
				D.fim -> prox = No;
				D.fim = No;
			}
			
			//4º caso
			else{
				
				ant = D.inicio;
				atual = D.inicio -> prox;
				
				while(stricmp(atual -> nome, AlunoAux.nome) < 0){
					
					ant = atual;
					atual = atual -> prox;
				}
				
				No -> prox = ant -> prox;
				ant -> prox = No;
			}
			
			D.qtde++;

			fread(&AlunoAux, sizeof(TpAluno), 1, arq);
		}
		printf("\nArquivo lido e dados inseridos na lista com sucesso!");
	}

	fclose(arq);
}

void ExibirAlunos(TpDescr D) {

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