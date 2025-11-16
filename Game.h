#pragma once
#include "GeneralList.h"

typedef enum {
	eThinkingGame, eChildrensGame, eBabyGame, eChanceGame,eBoardGame,eTargetGmae, eNofGameTypes
} eGameType;

static const char* GameTypeStr[eNofGameTypes]
= { "ThinkingGame", "ChildrensGame", "BabyGame","chanceGame","BoardGame","TargetGame"};


typedef struct
{
	char*		gameName;
	int 	    SerialNumber; 
	eGameType   type;
	double		price;
} Game;

int initGame(Game* pGame, Game* gameArr, const int numOfGames);
void getPriceGame(Game* pGame);
Game* findGameBySerialNumber(Game* GameArr,const int numofGames,const int SerialNumber);
int checkUniqeSerialNumber(Game* GameArr,const int numOfGames,const int SerialNumber); 
eGameType getGameType();
void getSerialNumber(Game* pGame,Game* GameArr,const int numOfGames); 
int	saveGameToFile(const Game* pGame, FILE* fp);
eGameType getGameTypeBystr(const char* type);
int	saveGameToBinaryFile(const Game* pGame, FILE* fp); 
int loadGameFromBinaryFile(Game* pGame, FILE* fp);
int loadGameFromFile(Game* pGame, FILE* fp);
void freeGame(Game* pGame); 
void printGame(const Game* pGame);
void printGameArr(const Game* GameArr, const int numOfGames);
