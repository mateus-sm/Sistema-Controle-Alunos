#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>
#include "Controle_de_Alunos.h"

int main(void){
	
	TpAluno *A = NULL;

	A = InserirOrdenado(A);
	ExibirAlunos(A);

	return 0;
}