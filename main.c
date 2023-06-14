#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

void cleanTerminal();
void throwMessage();

typedef struct {
	char name[50];
	float points[3];
	int contPoints;
	float average;
}type_team;

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	type_team teams[5];
	char jurors[3][50];
	
	// menu
	int index = 0;
	bool showMenu = true;
	bool jurorsRegistered = false;
	bool allTeamsRegistered = false;
	
	// team name
	char teamName[50];
	bool readName = true;
	int contName = 0;

	// default assignments
	int teamIndex = 0;
	float points = 0.0;
	float empty[3] = {0.0};
	
	do{
		printf("1 - INSERIR NOME DA EQUIPE");
		printf("\n2 - INSERIR NOTA DA EQUIPE");
		if(!jurorsRegistered){
			printf(" (Cadastrar jurados)");
		}
		printf("\n3 - CALCULAR PONTUACAO DA EQUIPE");
		if(contName==0){
			printf(" (Cadastrar times)");
		}
		printf("\n4 - SALVAR ARQUIVO");
		printf("\n5 - CADASTRAR JURADOS\n");
		
		scanf("%d", &index);
		cleanTerminal();
	
		switch(index){
			case 1:
				printf("1 - INSERIR NOME DA EQUIPE\n");
				readName = true;
				
				while(readName && contName < 5){
					
					printf("\nInsira o nome da equipe %d ou 0 para finalizar:\n", contName + 1);
					scanf(" %[^\n]", &teamName);
					
					if(strcmp(teamName, "0") == 0){
						readName = false;
					}else {
						strcpy( teams[contName].name, teamName );
						teams[contName].contPoints = 0;
						contName ++;
					}
				}
				
				allTeamsRegistered = true;
				throwMessage("As 5 equipes já foram cadastradas");
				cleanTerminal();
				break;
			case 2:
				printf("2 - INSERIR NOTA DA EQUIPE\n");
				if(jurorsRegistered){
					printf("Selecione a equipe para cadastrar notas ou 0 para voltar:\n");
					printf("\n ____________________________\n");
					for(int i = 0; i<contName; i++){
						printf("\n   %d - %s\n", i+1, teams[i].name);
						printf("\n   |   Jurado   |   Nota   |\n");
						for(int j=0; j<3; j++){
							printf("   |      %s     |  %6.2f  |\n", jurors[j], teams[i].points[j]);
						}
						printf("\n ____________________________\n");
					}
					
					printf("\nEquipe: ");
					scanf("%d", &teamIndex);
					cleanTerminal();
					
					printf("2 - INSERIR NOTA DA EQUIPE\nEquipe %d\n", teamIndex);
					
					for(int i = 0; i<3; i++){
						printf("Nota do jurado %s:", jurors[i]);
						scanf("%f", &points);
						teams[teamIndex-1].points[i] = points;
					}
					
				}
				cleanTerminal();
				break;
			case 3:
				printf("Definir pontuacao da equipe");
				showMenu = false;
				break;
			case 4:
				printf("Salvar arquivo");
				showMenu = false;
				break;
			case 5:
				printf("5 - CADASTRAR JURADOS\n");
				for(int i = 0; i<3; i++){
					printf("Nome do jurado %d: ", i+1);
					scanf(" %[^\n]", &jurors[i]);
				}
				jurorsRegistered = true;
				cleanTerminal();
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
