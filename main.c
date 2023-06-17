#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

void cleanTerminal();
void throwMessage();
void calculatePodium();

typedef struct {
	char name[50];
	float points[3];
	int contPoints;
	float average;
}type_team;

typedef struct {
	char teamName[50];
	float average;
}type_podium;

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	type_team teams[5];
	type_podium podium[3];
	char jurors[3][50];
	FILE *arq;
	
	// menu
	int index = 0;
	bool showMenu = true;
	bool jurorsRegistered = false;
	bool allTeamsRegistered = false;
	bool averagePointsCalculated = false;
	
	// team points
	bool readPoints = true;
	int contPoints = 0;
	
	// team name
	char teamName[50];
	bool readName = true;
	int contName = 0;

	// default assignments
	int teamIndex = 0;
	float points = 0.0;
	float empty[3] = {0.0};
	
	do{
		printf("1 - INSERIR NOMES DAS EQUIPES       ");
		printf("\n2 - INSERIR NOTAS DAS EQUIPES       ");
		if(!jurorsRegistered){
			printf(" * Cadastrar jurados");
		}
		if(contName==0){
			printf(" * Cadastrar times");
		}
		printf("\n3 - CALCULAR PONTUACAO DAS EQUIPES       ");
		if(contName<5){
			printf(" *Cadastrar todos os times");
		}
		if(contPoints<15){
			printf(" *Cadastrar todas as notas");
		}
		printf("\n4 - SALVAR ARQUIVO       ");
		if(!averagePointsCalculated){
			printf(" *Calcular pontuação das equipes");
		}
		printf("\n5 - CADASTRAR JURADOS");
		printf("\n6 - SAIR\n");
		
		
		if(averagePointsCalculated){
			printf("\n\nPódio:\n");
		    for (int i = 0; i < 3; i++) {
		        printf("%dº lugar: Equipe %s - Pontuação: %.2f\n", i + 1, podium[i].teamName, podium[i].average);
		    }
		}
		
		scanf("%d", &index);
		cleanTerminal();
	
		switch(index){
			case 1:
				printf("1 - INSERIR NOMES DAS EQUIPES\n");
				readName = true;
				
				while(readName && contName < 5){
					
					printf("\nInsira o nome da equipe %d ou 0 para voltar:\n", contName + 1);
					scanf(" %[^\n]", &teamName);
					
					if(strcmp(teamName, "0") == 0){
						readName = false;
					}else {
						strcpy( teams[contName].name, teamName );
						teams[contName].contPoints = 0;
						contName ++;
					}
				}
				
				throwMessage("As 5 equipes já foram cadastradas");
				cleanTerminal();
				break;
			case 2:
				readPoints = true;
				if(jurorsRegistered){
					while(readPoints){
						bool invalidTeam = false;
						do{
							invalidTeam = false;
							printf("2 - INSERIR NOTAS DAS EQUIPES\n");
							printf("Selecione a equipe para cadastrar notas ou 0 para voltar:\n");
							for(int i = 0; i<contName; i++){
								printf("\n   %d - %s\n", i+1, teams[i].name);
								for(int j=0; j<teams[i].contPoints; j++){
									printf("   - Jurado %s: %.2f\n",jurors[j], teams[i].points[j]);
								}
							}
							printf("\nNúmero da equipe ou 0 para voltar: ");
							scanf("%d", &teamIndex);
							
							if(teamIndex == 0){
								readPoints = false;
							}
							
							cleanTerminal();
							
							if(teams[teamIndex-1].contPoints == 3){
								throwMessage("A equipe já tem todas as notas cadastradas. Selecione outra equipe\n");
								invalidTeam = true;
							} else if(teamIndex>contName){
								throwMessage("Número da equipe inválido. Selecione outra equipe");
								invalidTeam = true;
							}
							
						}while(invalidTeam);
						
						if(readPoints){
							printf("2 - INSERIR NOTAS DA EQUIPES\nEquipe %s\n", teams[teamIndex-1].name);
							for(int i = 0; i<3; i++){
								printf("Nota do jurado %s: ", jurors[i]);
								scanf("%f", &points);
								teams[teamIndex-1].points[i] = points;
								teams[teamIndex-1].contPoints = teams[teamIndex-1].contPoints + 1;
								contPoints = contPoints + 1;
							}
							cleanTerminal();
						}
					}
					
				}
				cleanTerminal();
				break;
			case 3:
				showMenu = false;
				char close[50];
				if(contName == 5 && contPoints == 15){
					printf("3 - CALCULAR PONTUAÇÃO DAS EQUIPES");
					for(int i; i<5; i++){
						float pointsAcm = 0.0;
						for(int j=0; j<3; j++){
							pointsAcm = pointsAcm + teams[i].points[j];
						}
						teams[i].average = pointsAcm/3;
					}
					
					calculatePodium(teams, podium);
					printf("\nPontuação calculada!");
				    printf("\n\nPódio:\n");
				    for (int i = 0; i < 3; i++) {
				        printf("%dº lugar: Equipe %s - Pontuação: %.2f\n", i + 1, podium[i].teamName, podium[i].average);
				    }
				    
					printf("\nDigite 0 para voltar ");
					scanf("%s", &close);
					cleanTerminal();
					showMenu = true;
					averagePointsCalculated = true;
				}
				showMenu = true;
				break;
			case 4:
				if(averagePointsCalculated){
					showMenu = false;
					printf("4 - SALVAR ARQUIVO");
					arq = fopen("podium.txt","a");
					for (int i = 0; i < 3; i++) {
				        fprintf(arq, "%dº lugar: Equipe %s - Pontuação: %.2f\n", i + 1, podium[i].teamName, podium[i].average);
				    }
				    fclose(arq);
				    printf("\nArquivo salvo!");
				    printf("\nDigite 0 para voltar ");
					scanf("%s", &close);
					cleanTerminal();
					showMenu = true;
				}
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
			case 6:
				showMenu = false;
				printf("Programa encerrado");
				break;
			default:
				throwMessage("Opcao Invalida. Tente novamente");
				showMenu = true;
		}
	} while (showMenu);
}

void calculatePodium(type_team teams[], type_podium podium[]) {
    float totalPoints[5] = {0};
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            totalPoints[i] += teams[i].points[j];
        }
        teams[i].average = totalPoints[i] / 3;
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (teams[i].average < teams[j].average) {
                type_team temp = teams[i];
                teams[i] = teams[j];
                teams[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < 3; i++) {
        strcpy(podium[i].teamName, teams[i].name);
        podium[i].average = teams[i].average;
    }
}

void readTeamName(){
	
}

void cleanTerminal(){
	system("clear");
	system("cls");
}

void throwMessage(char message[]){
	printf(" --------------------------------------------------------------------\n");
	printf("  %s \n", message);
	printf(" --------------------------------------------------------------------\n");
}
