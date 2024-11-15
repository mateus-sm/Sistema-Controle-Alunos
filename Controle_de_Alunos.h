#define TF 50

struct TpDisci{
	char disci[TF];
	int nota1, nota2, freq;
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

TpAluno *NovoNoAluno(TpData data, char nome[TF], char curso[TF], char rua[TF], char bairro[TF], char cidade[TF], char estado[3]){
	
	TpAluno aluno = new TpAluno;
	
	aluno.nome = nome;
	aluno.curso = curso;
	aluno.rua = rua;
	aluno.bairro = bairro;
	aluno.cidade = cidade;
	aluno.estado = estado;
	aluno.data.d = data.d;
	aluno.data.m = data.m;
	aluno.data.a = data.a;
	
	aluno -> prox = NULL;
	aluno -> ant = NULL;
	aluno -> disciplina = NULL;
	
	return aluno;
}

TpDisci *NovoNoDisciplina(char disci[TF], int nota1, int nota2, int freq){
	
	TpDisci *disci = new TpDisci;
	
	disci.disci = disci;
	disci.nota1 = nota1;
	disci.nota2 = nota2;
	disci.freq = freq;
	disci -> prox = NULL;
	
	return disci;
}

TpAluno *InserirOrdenado(TpAluno aluno){
	
	char nome[TF], curso[TF], rua[TF], bairro[TF], cidade[TF], estado[3];
	TpAluno *aux, *No;
	
	printf("Digite seu nome: ");
	nome = gets();
	
	while(nome != 27){
		
		
		
		printf("\nDigite seu nome: ");
		nome = gets();
	}
	
	return aluno;
}