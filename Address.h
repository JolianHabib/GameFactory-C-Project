#pragma once


typedef struct
{
	char*    townName;
	int		numOfHouse;
	char*	streetName;
} Address;

int	initAddress(Address* pAd);
int	saveAddressToBinaryFile(const Address* pAddress, FILE* fp);
int	loadAddressFromBinaryFile(Address* pAddress, FILE* fp);
int	saveAddressToFile(const Address* pAddress, FILE* fp);
void freeAddress(Address* pAddress);
int	loadAddressFromFile(Address* pAddress,FILE* fp); 
void printAddress(const Address* pAd);
