#pragma once
#define MAX_STR_LEN 255

#define sub(x,y) (x-y)  //macro 1
#define mult(x,y) (x*y) //macro 2
#define Add5(x1,x2,x3,x4,x5) (x1+x2+x3+x4+x5) //macro 3

char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size, FILE* fp);
char* getDynStr(char* str);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);
void generalArrayFunction(void* arr, int size, size_t typeSize, void(*f)(void* element));


