#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Material.h"
#include "General.h"

void getMaterial(Material* pMaterial)
{
	pMaterial->type = getMaterialType();
	getRank(pMaterial);
	getPrice(pMaterial);
}

void getRank(Material* pMaterial)
{
	char rank, x;
	int ok = 0, rankFlag;
	do {
		printf("Enter rank of Material (betwen a to f or betwen A to F): ");
		scanf("%c", &rank);
		scanf("%c", &x); //clean buffer.
		rankFlag = checkMaterialRank(rank);
		if (rankFlag != 0)
		{
			if (rankFlag == 2)
				rank = toupper(rank);
			pMaterial->rank = rank;
			ok = 1;
		}
	} while (ok != 1);
}

void getPrice(Material* pMaterial)
{
	int ok = 0;
	int price;
	do {
		printf("Enter price of Material In Shekel: ");
		scanf("%d", &price);
		if (price > 0)
		{
			pMaterial->price = price;
			ok = 1;
		}
	} while (ok != 1);
}

int	checkMaterialRank(const char rank)
{
	if (rank >= 'A' && rank <= 'F')
		return 1;
	else if (rank >= 'a' && rank <= 'f')
	{
		return 2;
	}
	else
		return 0;
}

eMaterialType getMaterialType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofMaterialTypes; i++)
			printf("%d for %s\n", i, MaterialTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofMaterialTypes);
	getchar();
	return (eMaterialType)option;
}

eMaterialType getMaterialTypeByName(const char* type)
{
	int i, type1;
	for (i = 0; i < eNofMaterialTypes; i++)
		if (strcmp(type, MaterialTypeStr[i]) == 0)
			type1 = i;
	return (eMaterialType)type1;

}

int	saveMaterialToBinaryFile(const Material* pMaterial, FILE* fp)
{
	if (fwrite(pMaterial, sizeof(Material), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}

int	loadMaterialFromBinaryFile(Material* pMaterial, FILE* fp)
{
	if (fread(pMaterial, sizeof(Material), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}

int	saveMaterialToFile(const Material* pMaterial, FILE* fp)
{ 
	if (!pMaterial)
		return 0;
	fprintf(fp, "%s %c %d\n", MaterialTypeStr[pMaterial->type], pMaterial->rank, pMaterial->price);
	return 1;
}

int	loadMaterialFromFile(Material* pMaterial, FILE* fp)
{
	if (!pMaterial)
		return 0;
	char str[MAX_STR_LEN];
	fscanf(fp, "%s %c %d", str, &pMaterial->rank, &pMaterial->price);
	pMaterial->type = getMaterialTypeByName(str);
	return 1;
}

void printMaterial(const Material* pMaterial)
{
	printf("%s per A month, rank is: %c, price is: %d Shekel\n", MaterialTypeStr[pMaterial->type], pMaterial->rank, pMaterial->price);
}

int	saveMaterialToBinaryFileCompressed(const Material* pMaterial, FILE* fp)
{
	BYTE data[2] = { 0 };
	int len = 1;
	 data[0] = pMaterial->type << 7 | len << 6 |(( pMaterial->price >>7) ); 
	 data[1] = ((pMaterial->price) & 0xFF)<<0 ; // ((data[1] >> 7) & 0x1);

	if (fwrite(&data, sizeof(BYTE), 2, fp) != 2)
		return 0;

	if (fwrite(&pMaterial->rank, sizeof(char), len, fp) != len) 
		return 0;


	return 1;
}

int	readMaterialFromBinaryFileCompressed(Material* pMaterial, FILE* fp)
{
	BYTE data[2];
	if (fread(&data, sizeof(BYTE), 2, fp) != 2)
		return 0;
	pMaterial->type = (data[0] >> 7) & 0x1;
	int len = (data[0] >> 6) & 0x1;
	pMaterial->price = ((data[0] & 0x1F) << 7) | ((data[1] >> 0) & 0xFF);
	if (fread(&pMaterial->rank, sizeof(char), len, fp) != len)
		return 0;
	return 1;
}