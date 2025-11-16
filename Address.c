#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "address.h"
#include "General.h"
#include "fileHelper.h"

int	initAddress(Address* pAd)
{
	pAd->townName = getStrExactName("Enter town Name");
	if (!pAd->townName)
		return 0;
	pAd->streetName = getStrExactName("Enter street Name");
	if (!pAd->streetName)
		return 0;
	printf("Enter number of House:\t");
	scanf("%d", &pAd->numOfHouse);
	return 1;
}

int	saveAddressToBinaryFile(const Address* pAddress, FILE* fp)
{
	if (!writeStringToFile(pAddress->townName, fp, "Error write Town Name.\n"))
		return 0;
	if (!writeStringToFile(pAddress->streetName, fp, "Error write street Name.\n"))
		return 0;
	if (!writeIntToFile(pAddress->numOfHouse, fp, "Error write number of house.\n")) 
		return 0;
	return 1;

}

int	loadAddressFromBinaryFile(Address* pAddress, FILE* fp)
{
	pAddress->townName = readStringFromFile(fp, "Error reading town name.\n");
	if (!pAddress->townName)
		return 0;
	pAddress->streetName = readStringFromFile(fp, "Error reading street name.\n");
	if (!pAddress->streetName)
		return 0;
	if(!readIntFromFile(&pAddress->numOfHouse,fp,"Error read number of house.\n"))
		return 0; 
	return 1;

}

int	saveAddressToFile(const Address* pAddress, FILE* fp)
{
	if (!pAddress)
		return 0;
	fprintf(fp, "%s\n%s\n%d\n", pAddress->townName, pAddress->streetName, pAddress->numOfHouse);
	return 1;
}

int	loadAddressFromFile(Address* pAddress,FILE* fp) 
{
	if (!pAddress)
		return 0;
	pAddress->townName = readDynStringFromTextFile(fp);
	pAddress->streetName = readDynStringFromTextFile(fp);
	fscanf(fp, "%d", &pAddress->numOfHouse); 
	return 1;
}

void freeAddress(Address* pAddress)
{
	free(pAddress->townName);
	free(pAddress->streetName);
}

void printAddress(const Address* pAd)
{
	printf("Adress: Town: %s, street Name is %s, house number: %d.\n", pAd->townName, pAd->streetName,pAd->numOfHouse);
}

