#pragma once

typedef unsigned char BYTE;

typedef enum {
	ePlastic, eCarton, eWood, eRubber, eNofMaterialTypes
} eMaterialType;

static const char* MaterialTypeStr[eNofMaterialTypes]
= { "Plastic", "Carton", "Wood","Rubber"};


typedef struct
{
	int			price;    //price of 1 kg for the metrial.
	char			rank;
	eMaterialType	type;
} Material;


void getMaterial(Material* pMaterial);
int	checkMaterialRank(const char rank);
void getRank(Material* pMaterial);
void getPrice(Material* pMaterial);
eMaterialType getMaterialType(); 
eMaterialType getMaterialTypeByName(const char* type);
int	saveMaterialToBinaryFile(const Material* pMaterial, FILE* fp);
int	loadMaterialFromBinaryFile(Material* pMaterial, FILE* fp);
int	saveMaterialToFile(const Material* pMaterial, FILE* fp);
int	loadMaterialFromFile(Material* pMaterial, FILE* fp);
void printMaterial(const Material* pMaterial); 
int	saveMaterialToBinaryFileCompressed(const Material* pMaterial, FILE* fp);
int	readMaterialFromBinaryFileCompressed(Material* pMaterial, FILE* fp);