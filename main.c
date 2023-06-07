#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
	int index = 0, contName = 0;
	bool showMenu = true;

	char name[50];
	bool readName = true;
	
	t = teams;
	
	do{
		printf("1 - INSERIR NOME DA EQUIPE\n");
		printf("2 - INSERIR NOTA DA EQUIPE\n");
		printf("3 - CALCULAR PONTUACAO DA EQUIPE\n");
		printf("4 - SALVAR ARQUIVO\n");
		
		scanf("%d", &index);
		cleanTerminal();
	
		switch(index){
			case 1:
				printf("1 - INSERIR NOME DA EQUIPE\n");
				readName = true;
				
				while(readName && contName < 5){
					
					printf("\nInsira o nome da equipe %d ou 0 para finalizar:\n", contName + 1);
					scanf(" %[^\n]", &name);
					
					if(strcmp(name, "0") == 0){
						readName = false;
					}else {
						teams[contName];
						contName ++;
					}
				}
				
				throwMessage("As 5 equipes já foram cadastradas");
				cleanTerminal();
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
