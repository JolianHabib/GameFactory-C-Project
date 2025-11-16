#pragma once
#include "Game.h"

typedef struct 
{
	Game	Game; 
	int		quanityOfGame;
	int		serialNumber;
	double  OrderPrice;
} GameOrder;

int initGameOrderwithoutSerialNumber(GameOrder* pOrder,const Game* pGame);  
void getquanityOfGame(GameOrder* pOrder);
void freeOrder(GameOrder* pOrder);
void getOrderPrice(GameOrder* pOrder);
void printOrder(const GameOrder* pOrder);
int saveOrderToBinaryFile(const GameOrder* pOrder, FILE* fp);
void getOrderSerialNumber(GameOrder* pOrder);
void printOrderV(const void* val);
void freeOrderV(void* val);
int loadOrderFromBinaryFile(GameOrder* pOrder, FILE* fp);
int saveOrderToFile(const GameOrder* pOrder, FILE* fp);
int loadOrderFromFile(GameOrder* pOrder, FILE* fp);




