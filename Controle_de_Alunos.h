#define TF 50

void limparQuadro(void);

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
	fseek(arq, 0, 0);

	fread(&AlunoAux, sizeof(TpAluno), 1, arq);
	while(!feof(arq) && stricmp(AlunoAux.nome, nome) != 0)
		fread(&AlunoAux, sizeof(TpAluno), 1, arq);
	
	if(!feof(arq))
		return ftell(arq) - sizeof(TpAluno);
	
	return -1;
}

int BuscaDisciplina(TpDisci Disciplina, FILE *arq) {

	TpDisci aux;
	fseek(arq, 0, 0);
	
	fread(&aux, sizeof(TpDisci), 1, arq);
	while(!feof(arq) && stricmp(aux.disci, Disciplina.disci) != 0){
		fread(&aux, sizeof(TpDisci), 1, arq);
	}

	fseek(arq, -sizeof(TpDisci), 1);
	if(stricmp(aux.disci, Disciplina.disci) == 0){
		return ftell(arq) - sizeof(TpAluno);
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

void AlterarInfoAlunos(TpDescritorAluno &D){
	
	//system("cls");
	
	TpAluno *AlunoAux;
	char op, nome[TF];
	int x = 30, y = 10;

	gotoxy(30, 7);
	printf("* * * Alterar Alunos * * *");

	if(D.qtde == 0){
		gotoxy(30, 10);
		printf("Sem alunos na lista para realizar alteracoes!");
	}else {
		gotoxy(x, y++);
		printf("Insira o nome do aluno: ");
		fflush(stdin);
		gotoxy(x, y++);
		gets(nome);

		AlunoAux = D.inicio;
		while(AlunoAux != NULL && stricmp(AlunoAux -> nome, nome) != 0)
			AlunoAux = AlunoAux -> prox;

		if(AlunoAux != NULL){
			x = 30, y =10;
			limparQuadro();
			gotoxy(x, y++);
			printf("Aluno encontrado: %s", AlunoAux -> nome);
			gotoxy(x, y++);
			printf("Deseja alterar qual informacao?");
			gotoxy(x, y++);
			printf("[A] Curso");
			gotoxy(x, y++);
			printf("[B] Data de Nascimento");
			gotoxy(x, y++);
			printf("[C] Rua");
			gotoxy(x, y++);
			printf("[D] Bairro");
			gotoxy(x, y++);
			printf("[E] Cidade");
			gotoxy(x, y++);
			printf("[F] Estado\n");
			gotoxy(x, y++);
			printf("Opcao: ");
			op = toupper(getch());
			
			limparQuadro();
			x = 30, y = 10;
			switch(op){
				
				case 'A':
					gotoxy(x, y++);
					printf("Digite o novo Curso: ");
					fflush(stdin);
					gotoxy(x, y);
					gets(AlunoAux -> curso);
					break;
				
				case 'B':
					gotoxy(x, y++);
					printf("Digite a nova Data de Nascimento: ");
					gotoxy(x, y);
					scanf("%d %d %d", &AlunoAux -> data.d, &AlunoAux -> data.m, &AlunoAux -> data.a);
					break;
				
				case 'C':
					gotoxy(x, y++);
					printf("Digite o endereco da Rua: ");
					fflush(stdin);
					gotoxy(x, y);
					gets(AlunoAux -> rua);
					break;
				
				case 'D':
					gotoxy(x, y++);
					printf("Digite o endereco do Bairro: ");
					fflush(stdin);
					gotoxy(x, y);
					gets(AlunoAux -> bairro);
					break;
				
				case 'E':
					gotoxy(x, y++);
					printf("Digite a nova Cidade: ");
					fflush(stdin);
					gotoxy(x, y);
					gets(AlunoAux -> cidade);
					break;
				
				case 'F':
					gotoxy(x, y++);
					printf("Digite o novo Estado (--): ");
					fflush(stdin);
					gotoxy(x, y);
					gets(AlunoAux -> estado);		
			}
			
			limparQuadro();
			gotoxy(25, 10);
			printf("Alteracao realizada com sucesso!");
		}
	}
	
	getch();
}

void AlterarNotasAluno(TpDescritorAluno &D){
	
	char nome[TF], disci[TF];
	char op;
	TpAluno *aux;
	TpDisci *auxDisci;
	int x = 25, y = 10;
	
	gotoxy(23, 7);
	printf("* * Alterar informacoes da disciplina * *");
	
	if(D.qtde == 0){
		gotoxy(30, 10);
		printf("Sem alunos cadastrados!");
	}	
	
	else{
		gotoxy(x, y++);
		printf("Digite o aluno para alterar as notas: ");
		fflush(stdin);
		gotoxy(x, y++);
		gets(nome);
		
		aux = D.inicio;
		while(aux != NULL && stricmp(aux -> nome, nome) != 0)
			aux = aux -> prox;
			
		if(aux != NULL){
			x = 30, y = 10;
			limparQuadro();
			
			if(aux -> disciplina == NULL){
				gotoxy(x, y++);
				printf("Aluno sem disciplinas cadastradas!");
			}
			
			else{
				
				auxDisci = aux -> disciplina;
				while(auxDisci != NULL){
					gotoxy(x, y++);
					printf("Disciplina: %s", auxDisci -> disci);
					gotoxy(x, y++);
					printf("Nota 1: %.2f", auxDisci -> nota1);
					gotoxy(x, y++);
					printf("Nota 2: %.2f", auxDisci -> nota2);
					gotoxy(x, y++);
					printf("Frequencia: %.2f", auxDisci -> freq);
					auxDisci = auxDisci -> prox;
				}
				
				y++; gotoxy(x, y++);
				printf("Deseja alterar qual disciplina?: ");
				fflush(stdin);
				gotoxy(x, y++);
				gets(disci);
				
				auxDisci = aux -> disciplina;
				while(auxDisci != NULL && stricmp(auxDisci -> disci, disci) != 0)
					auxDisci = auxDisci -> prox;
				
				if(auxDisci != NULL){
					x = 30, y = 10;
					limparQuadro();
					
					gotoxy(x, y++);
					printf("Deseja alterar:");
					gotoxy(x, y++);
					printf("[1] Nota 1");
					gotoxy(x, y++);
					printf("[2] Nota 2");
					gotoxy(x, y++);
					printf("[3] Frequencia");
					gotoxy(x, y++);
					scanf("%c", &op);
					
					switch(op){
						
						case '1':
							gotoxy(x, y++);
							printf("Qual seria a nova nota 1?: ");
							gotoxy(x, y++);
							scanf("%f", &aux -> disciplina -> nota1);
							break;
							
						case '2':
							gotoxy(x, y++);
							printf("Qual seria a nova nota 2?: ");
							gotoxy(x, y++);
							scanf("%f", &aux -> disciplina -> nota2);
							break;
							
						case '3':
							gotoxy(x, y++);
							printf("Qual seria a nova frequencia?: ");
							gotoxy(x, y++);
							scanf("%f", &aux -> disciplina -> freq);
							break;
					}
					gotoxy(x, y++);
					printf("Alteracao realizada!");
				}
				
				else{
					gotoxy(x, y++);
					printf("Disciplina nao encontrada!");
				}
					
			}
		}
		else{
			gotoxy(x, y++);
			printf("Aluno nao encontrado!");
		}
	}
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
			y -= 4;
			x += 22;
			if (x == 77) {
				x = 11;
				y += 5;
			}
		}
	}
}

void ExibirAlunos(TpDescritorAluno D, int flag) {
	
	if (D.qtde != 0) {
		for(int i = 9 ; i <= 28; i++){
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
		printf("Rua: %s", D.inicio -> rua);
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
				gotoxy(48, 28);
				printf("[ENTER] PROXIMA PAGINA");
				getch();
				limparQuadro();
				ExibirAlunos(D, flag + 1);
			} else {
				gotoxy(52, 28);
				printf("[ENTER] SAIR");
				getch();
			}
		}else{
			if(D.qtde != 0){
				ExibirAlunos(D, flag + 1);
			} else {
				gotoxy(52, 28);
				printf("[ENTER] SAIR");
				getch();
			}
		}
		
		
	}else if(D.qtde == 0 && flag == 0){
		gotoxy(28, 10);
		printf("NAO EXISTEM ALUNOS CADASTRADOS!");
		getch();
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

void buscarAluno(void){
	FILE *ptr = fopen("Aluno.dat", "rb+");
	TpAluno AlunoAux;
	char op;
	int x = 30, y = 10;

	gotoxy(30, 7);
	printf("* * * Buscar Alunos * * *");

	do{
		gotoxy(x, y++);
		printf("Insira o nome do aluno: ");
		fflush(stdin);
		gotoxy(x, y++);
		gets(AlunoAux.nome);
		
		int pos = BuscaAluno(AlunoAux.nome, ptr);

		while(pos == -1 && strcmp(AlunoAux.nome, "\0") != 0){
			x = 30, y = 10;
			limparQuadro();
			gotoxy(x, y++);
			printf("Aluno nao encontrado!");
			gotoxy(x, y++);
			printf("Insira outro nome:");
			gotoxy(x, y);
			fflush(stdin);
			gets(AlunoAux.nome);
			pos = BuscaAluno(AlunoAux.nome, ptr);
		}

		if(pos != -1){
			fseek(ptr, pos, 0);
			fread(&AlunoAux, sizeof(TpAluno), 1, ptr);
			
			x = 30, y =10;
			limparQuadro();
			gotoxy(x, y++);
			printf("Aluno encontrado: %s", AlunoAux.nome);
			gotoxy(x, y++);
			printf("Curso: %s", AlunoAux.curso);
			gotoxy(x, y++);
			printf("Data de Nascimento: %d/%d/%d", AlunoAux.data.d, AlunoAux.data.m, AlunoAux.data.a);
			gotoxy(x, y++);
			printf("Rua: %s", AlunoAux.rua);
			gotoxy(x, y++);
			printf("Bairro: %s", AlunoAux.bairro);
			gotoxy(x, y++);
			printf("Cidade: %s", AlunoAux.cidade);
			gotoxy(x, y++);
			printf("Estado: %s", AlunoAux.estado);
			gotoxy(x, y++);
			
		}	
	

	}while (strcmp(AlunoAux.nome, "\0") != 0);
	
}

void buscarDisciplina(void){

	FILE *ptr = fopen("Disciplinas.dat", "rb+");

	TpDisci DisciAux;
	char op;
	int x = 30, y = 10;

	gotoxy(30, 7);
	printf("* * * Buscar Disciplina * * *");

	do{
		gotoxy(x, y++);
		printf("Insira o nome da disciplina: ");
		fflush(stdin);
		gotoxy(x, y++);
		gets(DisciAux.disci);
		
		int pos = BuscaDisciplina(DisciAux, ptr);

		while(pos == -1 && strcmp(DisciAux.disci, "\0") != 0){
			x = 30, y = 10;
			limparQuadro();
			gotoxy(x, y++);
			printf("Disciplina nao encontrada!");
			y++; gotoxy(x, y++);
			printf("Insira outra disciplina:");
			gotoxy(x, y);
			fflush(stdin);
			gets(DisciAux.disci);
			pos = BuscaAluno(DisciAux.disci, ptr);
		}

		if(pos != -1){
			fseek(ptr, pos, 0);
			fread(&DisciAux, sizeof(TpDisci), 1, ptr);
			
			x = 30, y =10;
			limparQuadro();
			gotoxy(x, y++);
			printf("Disciplina encontrada: %s", DisciAux.disci); y++;
		}

	}while (strcmp(DisciAux.disci, "\0") != 0);
}

void ExcluirAluno(TpDescritorAluno &D){

	TpAluno *atual;
	TpDisci *aux;
	char nome[TF];

	if(D.inicio == NULL){
		gotoxy(28, 10);
		printf("NAO EXISTEM ALUNOS CADASTRADOS!");
	}
	
	else{

		gotoxy(19, 11);
		printf("Digite o nome do aluno que deseja excluir: ");
		fflush(stdin);
		gets(nome);

		atual = D.inicio;
		while(atual != NULL && stricmp(atual -> nome, nome) != 0)
			atual = atual -> prox;

		if(atual == NULL){
			gotoxy(32, 13);
			printf("Aluno nao encontrado!");
		}
		
		else{

			//caso aluno esteja no inicio
			if(atual -> ant == NULL){
				D.inicio = atual -> prox;
				atual -> prox -> ant = NULL;
			}

			//caso esteja no meio
			else if(atual -> ant == NULL && atual -> prox == NULL){
				atual -> ant -> prox = atual -> prox;
				atual -> prox = atual -> ant;
			}
			
			//caso esteja no final
			else{
				D.fim = atual -> ant;
				atual -> ant -> prox = NULL;
			}

			//excluindo lista de disciplinas do aluno
			while(atual -> disciplina != NULL){
				aux = atual -> disciplina;
				atual -> disciplina = atual -> disciplina -> prox;
				delete aux;
			}

			D.qtde--;
			delete atual;
			gotoxy(37, 13);
			printf("Aluno excluido!");
		}
	}

	getch();
}

void ExcluirNotas(TpDescritorAluno &D){
	
	TpAluno *aux;
	TpDisci *auxAtual, *auxProx;
	int x = 25, y = 10; char nome[TF], disci[TF];
	
	gotoxy(30, 7);
	printf("* * * Exclusao de Disciplina * * *");
	
	if(D.qtde == 0){
		gotoxy(x, y++);
		printf("Sem alunos na lista!");
	}
	
	else{
		gotoxy(x, y++);
		printf("Deseja excluir a disciplina de qual aluno?: ");
		gotoxy(x, y++);
		fflush(stdin);
		gets(nome);
		
		aux = D.inicio;
		while(aux != NULL && stricmp(aux -> nome, nome) != 0)
			aux = aux -> prox;
			
		if(aux != NULL){
			gotoxy(x, y++);
			printf("Deseja excluir qual disciplina?: ");
			gotoxy(x, y++);
			gets(disci);
			
			//se for a primeira da lista
			if(stricmp(aux -> disciplina -> disci, disci) == 0){
				auxAtual = aux -> disciplina;
				aux -> disciplina = aux -> disciplina -> prox;
				delete auxAtual;
				gotoxy(x, y++);
				printf("Disciplina excluida!");
			}
			
			//se for no meio ou no fim
			else{
				auxAtual = aux -> disciplina;
				auxProx = auxAtual -> prox;
				while(auxProx != NULL && stricmp(auxProx -> disci, disci) != 0){
					auxAtual = auxProx;
					auxProx = auxProx -> prox;
				}
					
				if(auxProx != NULL){
					auxAtual -> prox = auxProx -> prox;
					delete auxProx;
					gotoxy(x, y++);
					printf("Disciplina excluida!");
				}
				
				else{
					gotoxy(x, y++);
					printf("Disciplina nao encontrada!");
				}
			}
		}
		
		else{
			gotoxy(x, y++);
			printf("Aluno nao encontrado!");
		}
	}
	
	getch();	
}

void RelatorioDisciplina(TpDescritorAluno D){
	
	int x = 25, y = 10, cont = 0;
	TpAluno *auxAluno;
	TpDisci auxDisci, *auxDisci2;
	
	FILE *arq = fopen("Disciplinas.dat", "rb+");
		
	gotoxy(27, 7);
	printf("* * * Relatorio de Disciplina * * *");
	
	if(D.qtde == 0){
		gotoxy(x, y++);
		printf("Sem alunos na lista!");
	}
	
	else{
		gotoxy(x, y++);
		printf("Gerar relatorio qual disciplina?: ");
		fflush(stdin);
		gets(auxDisci.disci);
		
		if(BuscaDisciplina(auxDisci, arq) == -1){
			gotoxy(x, y++);
			printf("Disciplina nao encontrada!");
		}
		
		else{
		
			auxAluno = D.inicio;
			
			while(auxAluno != NULL){
				
				auxDisci2 = auxAluno -> disciplina;
				while(auxDisci2 != NULL){
					
					if(stricmp(auxDisci2 -> disci, auxDisci.disci) == 0){
						y++;gotoxy(x, y++);
						printf("Aluno: %s", auxAluno -> nome);
						gotoxy(x, y++);
						printf("Disciplina: %s", auxDisci.disci);
						gotoxy(x, y++);
						printf("Nota 1: %.2f", auxDisci2 -> nota1);
						gotoxy(x, y++);
						printf("Nota 2: %.2f", auxDisci2 -> nota2);
						gotoxy(x, y++);
						printf("Frequencia: %.2f", auxDisci2 -> freq);
						cont++;
					}
					
					auxDisci2 = auxDisci2 -> prox;
				}
				
				if(cont == 3){
					x = 23, y = 12, cont = 0;
					gotoxy(58, 18);
					printf("[ENTER] para");
					gotoxy(58, 19);
					printf("continuar");
					getch();
					limparQuadro();
					gotoxy(27, 7);
					printf("* * * Relatorio de Disciplina * * *");
				}
				
				auxAluno = auxAluno -> prox;
			}
		}
	}
	
	fclose(arq);
	getch();
}

void RelatorioReprovas(TpDescritorAluno D){

	TpAluno *aux = D.inicio;

	if(aux == NULL){
		gotoxy(28, 10);
		printf("NAO EXISTEM ALUNOS CADASTRADOS!");
	}

	else{
		FILE *arq = fopen("RelatorioReprova.txt", "w");

		while(aux != NULL){

			fprintf(arq, "%s:\n", aux -> nome);

			if(aux -> disciplina == NULL)
				fprintf(arq, "Aluno nao possui disciplinas!\n");

			else{
				while(aux -> disciplina != NULL){
								
					if(aux -> disciplina -> nota1 + aux -> disciplina -> nota2 < 12)
						fprintf(arq, "Reprovado em: %s -> Media final: %.2f\n", aux -> disciplina -> disci, (aux -> disciplina -> nota1 + aux -> disciplina -> nota2) / 2);
					
					else
						fprintf(arq, "Nao ha reprovas!\n");
					
					aux -> disciplina = aux -> disciplina -> prox;
				}
			}

			fprintf(arq, "\n");
			aux = aux -> prox;
		}

		gotoxy(28, 10);
		printf("DADOS LIDOS E ARQUIVO TXT GERADO!");

		fclose(arq);
	}

	getch();
}