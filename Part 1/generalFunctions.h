#define _CRT_SECURE_NO_WARNINGS
#ifndef __GENERALFUNCTIONS__
#define __GENERALFUNCTIONS__
#define MAX_LENGTH 255
#define BARCODE_SIZE 7

char* myGets(char* buffer, int size);
void* safeRealloc(void* base, size_t newByteCount);
void removeExtraSpaces(char* str);

#endif