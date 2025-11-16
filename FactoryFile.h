#pragma once

int	initFactoryFromBinaryFile(Factory* pFactory, const char* fileName); 
int createWorkerArr(Factory* pFactory); 
int loadWorkerArrFromFile(Factory* pFactory, FILE* fp);
int createDepartmentArr(Factory* pFactory);
int loadDepartmentArrFromFile(Factory* pFactory, FILE* fp);
int loadCustomerArrFromFile(Factory* pFactory, FILE* fp);
int loadGameArrFromFile(Factory* pFactory, FILE* fp);
int	saveFactoryToBinaryFile(const Factory* pFactory, const char* fileName);
int loadDepartmentArrFromTextFile(Factory* pFactory, FILE* fp);
int loadWorkerArrFromTextFile(Factory* pFactory, FILE* fp);
int loadGameArrFromTextFile(Factory* pFactory, FILE* fp);
int loadCustomerArrFromTextFile(Factory* pFactory, FILE* fp);
int initFactoryFromFile(Factory* pFactory, const char* fileName);
int saveFactoryToTextFile(const Factory* pFactory, const char* fileName);