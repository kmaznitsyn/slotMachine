#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

void startGame() {
	printf("Enter any key to start: ");
	char anyChar;
	scanf("%c", &anyChar);
}

int main() {
	srand(time(0));  // Initialize random number generator
	const int MAX_SYMBOLS_IN_COMBINATION = 3;
	
	const int AMOUNT_OF_CREDITS = 5000;
	//для быстроты работы можно сразу тут перечислить ВСЕ комбинации включая 5ХХ и 7ХХ
	const char *WINNING_COMBINATIONS[7];
	WINNING_COMBINATIONS[0] = "444";
	WINNING_COMBINATIONS[1] = "111";
	WINNING_COMBINATIONS[2] = "222";
	WINNING_COMBINATIONS[3] = "333";
	WINNING_COMBINATIONS[4] = "444";
	WINNING_COMBINATIONS[5] = "555";
	WINNING_COMBINATIONS[6] = "777";
	
	const int FINE_AMOUNT = 250;
	const int DEVIL_NUMBER_FINE_AMOUNT = 666;
	
	
	bool lost = false;
	bool win = false;
	bool hasWinningCombination = false;;
	
	//Барабанчики для хранения итоговой комбинации
	char firstDrum;
	char secondDrum;
	char thirdDrum;
	
	char combination[MAX_SYMBOLS_IN_COMBINATION];
	
	startGame();
	//в начале у всех играющих 5000 кредитов
	int playerScore = AMOUNT_OF_CREDITS;
	while(!lost) {
		printf("Your money: %d\n", playerScore);
		firstDrum = rand() % 7 + '0';
		secondDrum = rand() % 7 + '0';
		thirdDrum = rand() % 7 + '0';
		
		combination[0] = firstDrum;
		combination[1] = secondDrum;
		combination[2] = thirdDrum;
		
		//Интеджер, который будет принимать в себя значение выиграшной комбинации
		//Кредиты для игрока
		int winningSumFromCombination;
		//iterating though winning combinations
		int i;
		printf("Your combination on drum: %s\n", combination);
		for (i = 0; i < 7; i++) {
			if (strcmp(combination, WINNING_COMBINATIONS[i]) == 0) {
				hasWinningCombination = true;
				//если три семерки игрок победил
				if (strcmp(combination, "777") == 0) {
					win = true;
					break;
				} else {
					//atoi - конвертирует стрингу в интеджер
					winningSumFromCombination = atoi(combination);
					printf("You are lucky today. Get your credits %d\n", winningSumFromCombination);
					playerScore += winningSumFromCombination;
					break;
				}
			}
		}
		
		if (strcmp(combination, "666") == 0) {
			printf("No winning combination today. DEVIL_NUMBER  %d\n", DEVIL_NUMBER_FINE_AMOUNT);
			playerScore -= 	DEVIL_NUMBER_FINE_AMOUNT;
		}
		if (!hasWinningCombination) {
			printf("No winning combination today. Fine amount %d\n", FINE_AMOUNT);
			playerScore -= 	FINE_AMOUNT;
		}
		
		if (win) {
			printf("\nYou win. Take jackpot!");
			return 0;
		}
		
		if (playerScore < FINE_AMOUNT) {
			lost = true;
			printf("\nYou lost. Go home!");
			break;
		}
		sleep(2);
		printf("Next execution \n");
	}
	
	return 0;
}
