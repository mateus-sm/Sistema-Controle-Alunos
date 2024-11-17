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

void InserirAlunoOrdenado(TpDescritorAluno &D) {
	
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
		printf("Arquivo lido e dados inseridos na lista com sucesso!");
	}

	fclose(arq);
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
}

void ExibirDisciplina(TpDescritorDisciplina D) {
    TpDisci *atual = D.inicio;
	int i = D.qtde;

    while (i != 0) {
        printf("\nDisciplina: %s\n", atual->disci);
        printf("Nota 1: %.2f\n", atual->nota1);
        printf("Nota 2: %.2f\n", atual->nota2);
        printf("Frequencia: %.2f\n", atual->freq);

        atual = atual->prox;
		i--;
    }
}