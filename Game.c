#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "General.h"
#include "Machine.h"
#include "fileHelper.h"


int initGame(Game* pGame,Game* gameArr, const int numOfGames)
{
	pGame->gameName = getStrExactName("Enter Game Name");
	if (!pGame->gameName)
		return 0;
	getSerialNumber(pGame,gameArr, numOfGames);
	pGame->type = getGameType();
	getPriceGame(pGame);
	return 1;
}

void getPriceGame(Game* pGame)
{
	double price;
	int ok = 0;
	do {
		printf("Enter a price for a game In Skekel: ");
		scanf("%lf", &price);
		if (price > 0)
		{
			pGame->price = price;
			ok = 1;
		}
	} while (ok != 1);

}

eGameType getGameType() 
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofGameTypes; i++)
			printf("%d for %s\n", i, GameTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofGameTypes);
	getchar();
	return (eGameType)option;
}

Game* findGameBySerialNumber(Game* GameArr, const int numOfGames,const int SerialNumber)
{
	int i;
	for (i = 0;i < numOfGames;i++)
	{
		if (GameArr[i].SerialNumber == SerialNumber)
			return &GameArr[i];  
	}
	return NULL; 

}

int checkUniqeSerialNumber(Game* GameArr,const int numOfGames,const int SerialNumber)
{
	Game* pGame = findGameBySerialNumber(GameArr,numOfGames,SerialNumber);
	if (pGame != NULL)
		return 0;
	return 1;
}

void getSerialNumber(Game* pGame,Game* GameArr,const int numOfGames) 
{
	int ok = 0, serialNumber;
	do {
		printf("Enter Serial Number of Game: (between %d - %d) ",MIN_SN,MAX_SN); 
		scanf("%d", &serialNumber);
		if (serialNumber >= MIN_SN && serialNumber <= MAX_SN)
		{
			if (checkUniqeSerialNumber(GameArr, numOfGames, serialNumber) == 1)
			{
				ok = 1; 
			}
			else
				printf("The Seril Number in use.\n");
		}
		else
			printf("The Serial Number Not in the coorect range!.\n");
	} while (ok != 1);
	pGame->SerialNumber = serialNumber; 
}

int	saveGameToFile(const Game* pGame, FILE* fp)
{
	if (!pGame)
		return 0;
	fprintf(fp, "%s\n", pGame->gameName);
	fprintf(fp, "%d\n", pGame->SerialNumber);
	fprintf(fp, "%lf\n", pGame->price);
	fprintf(fp, "%s\n", GameTypeStr[pGame->type]);
	return 1;
}

int	saveGameToBinaryFile(const Game* pGame, FILE* fp)
{
	if (!writeStringToFile(pGame->gameName,fp,"Error write game name.\n"))
		return 0;
	if(!writeIntToFile(pGame->SerialNumber, fp,"Error write serial number.\n"))
		return 0;
	if (!writeDoubleToFile(pGame->price, fp, "Error write price of game./n"))
		return 0;
	if(!writeStringToFile(GameTypeStr[pGame->type],fp,"Error write type of game"))
		return 0;
	return 1;

}

int loadGameFromBinaryFile(Game* pGame, FILE* fp)
{
	char* type; 
	pGame->gameName = readStringFromFile(fp, "Error read game name\n");
	if (!readIntFromFile(&pGame->SerialNumber, fp, "Error read serial number.\n"))
		return 0;
	if (!readDoubleFromFile(&pGame->price, fp, "Error read price of game.\n")) 
		return 0;
	type = readStringFromFile(fp, "Error read type game\n");
	pGame->type = getGameTypeBystr(type); 
	return 1;
}

int loadGameFromFile(Game* pGame, FILE* fp)
{
	char type[MAX_STR_LEN];
	if (!pGame)
		return 0;
	pGame->gameName = readDynStringFromTextFile(fp);   
	if (!pGame->gameName)
		return 0;
	fscanf(fp,"%d",&pGame->SerialNumber);
	fscanf(fp, "%lf", &pGame->price);
	fscanf(fp, "%s", type);
	pGame->type = getGameTypeBystr(type);   
	return 1;
}

eGameType getGameTypeBystr(const char* type)
{
	int i, type1;
	for (i = 0; i < eNofGameTypes; i++)
		if (strcmp(type, GameTypeStr[i]) == 0)
			type1 = i;
	return (eGameType)type1; 
}

void printGame(const Game* pGame)
{
	printf("Game: %s, Serial Number is: %d, the type of Game is %s, price for customer: %.3lf Shekel\n",pGame->gameName, pGame->SerialNumber, GameTypeStr[pGame->type], pGame->price);
	
}

void printGameArr(const Game* GameArr, const int numOfGames)
{
	int i;
	for (i = 0;i < numOfGames;i++)
		printGame(&GameArr[i]);
}

void	freeGame(Game* pGame)
{
	free(pGame->gameName); 
}