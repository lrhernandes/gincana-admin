#include <stdio.h>
#include <stdbool.h>
#include<conio.h>

void cleanTerminal();
void throwMessage();

struct TEAM {
	char name[50];
	float points[3];
	float average;
};

int main(){
	
	struct TEAM teams[5];
	struct TEAM * t;
	int index = 0;
	bool showMenu = true;
	
	t = teams;
	
	do{
		printf("1 - Inserir Nome Equipe\n");
		printf("2 - Inserir Nota Equipe\n");
		printf("3 - Calcular Pontuacao Equipe\n");
		printf("4 - Salvar arquivo\n");
		
		scanf("%d", &index);
		cleanTerminal();
	
		switch(index){
			case 1:
				printf("Ler nome da equipe");
				showMenu = false;
				break;
			case 2:
				printf("Ler nota da equipe");
				showMenu = false;
				break;
			case 3:
				printf("Definir pontuacao da equipe");
				showMenu = false;
				break;
			case 4:
				printf("Salvar arquivo");
				showMenu = false;
				break;
			default:
				throwMessage("Opcao Invalida. Tente novamente");
				showMenu = true;
		}
	} while (showMenu);
}

void readTeamName(){
	
}

void cleanTerminal(){
	system("clear");
	system("cls");
}

void throwMessage(char message[]){
	printf(" ----------------------------------\n");
	printf("  %s \n", message);
	printf(" ----------------------------------\n");
}
