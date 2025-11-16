#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "GameOrder.h" 
#include "fileHelper.h"
#include "General.h"

int initGameOrderwithoutSerialNumber(GameOrder* pOrder,const Game* pGame)
{
	pOrder->Game = *pGame;
	getquanityOfGame(pOrder); 
	getOrderPrice(pOrder);
	return 1;
}

void getquanityOfGame(GameOrder* pOrder)
{
	int ok = 0, quanity;
	do {
		printf("Enter Quanity of the game you want to order: ");
		scanf("%d",&quanity);
		if (quanity > 0)
		{
			pOrder->quanityOfGame = quanity;
			ok = 1;
		}
	} while (ok != 1);
}

void getOrderSerialNumber(GameOrder* pOrder)
{
	int ok = 0, serialnumber;
	do {
		printf("Enter a serial Number of Order: ");
		scanf("%d", &serialnumber);
		if (serialnumber > 0)
			ok = 1;
	} while (ok != 1);
	pOrder->serialNumber = serialnumber;
}

void getOrderPrice(GameOrder* pOrder)
{
	pOrder->OrderPrice = mult(pOrder->quanityOfGame , pOrder->Game.price); 

}

int saveOrderToBinaryFile(const GameOrder* pOrder, FILE* fp)
{
	if (!writeIntToFile(pOrder->quanityOfGame, fp, "Error write Qunity game.\n"))  
		return 0;
	if (!writeIntToFile(pOrder->serialNumber, fp, "Error write Quaniry game.\n"))
		return 0;
	if (!saveGameToBinaryFile(&pOrder->Game,fp)) 
		return 0;
	return 1;
}

int loadOrderFromBinaryFile(GameOrder* pOrder, FILE* fp)
{
	if (!readIntFromFile(&pOrder->quanityOfGame, fp, "Error read Quanity game:\n"))
		return 0;
	if (!readIntFromFile(&pOrder->serialNumber, fp, "Error read serial number:\n"))
		return 0;
	if (!loadGameFromBinaryFile(&pOrder->Game, fp)) 
		return 0;
	getOrderPrice(pOrder); 
	return 1;

}

int saveOrderToFile(const GameOrder* pOrder, FILE* fp)
{
	if (!pOrder)
		return 0;
	fprintf(fp,"%d\n", pOrder->quanityOfGame);
	fprintf(fp, "%d\n", pOrder->serialNumber);
	if (!saveGameToFile(&pOrder->Game, fp)) 
		return 0;
	return 1;
}

int loadOrderFromFile(GameOrder* pOrder, FILE* fp)
{
	if (!pOrder)
		return 0;
	fscanf(fp,"%d", &pOrder->quanityOfGame);
	fscanf(fp, "%d", &pOrder->serialNumber);
	if (!loadGameFromFile(&pOrder->Game,fp))
		return 0;
	getOrderPrice(pOrder);
	return 1;

}

void printOrderV(const void* val)
{
	const GameOrder* pOrder = (const GameOrder*)val;
	printOrder(pOrder);
	printf("\n");

}

void printOrder(const GameOrder* pOrder)
{
	printf("Order, serial Number: %d, you have %d Quanity game total price %.3lf Shekel.\n",pOrder->serialNumber, pOrder->quanityOfGame,pOrder->OrderPrice);
	printGame(&pOrder->Game);   
}

void freeOrder(GameOrder* pOrder)
{
	free(pOrder);
}

void freeOrderV(void* val)
{
	GameOrder* pGameOrder = *(GameOrder**)val;
	freeOrder(pGameOrder); 
}
