#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generalFunctions.h"


char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (iscntrl(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (iscntrl(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

void* safeRealloc(void* base, size_t newByteCount)
{
	void* temp = realloc(base, newByteCount);
	if (!temp)
		free(base);
	return temp;
}

void removeExtraSpaces(char* str) {
	int i = 0, j = 0;
	int spaceFlag = 0;
	// Skip leading spaces
	while (str[i] && isspace(str[i])) i++;
	// Process the string
	while (str[i]) {
		if (isspace(str[i])) {
			if (!spaceFlag) {
				str[j++] = ' ';
				spaceFlag = 1;
			}
		}
		else {
			str[j++] = str[i];
			spaceFlag = 0;
		}
		i++;
	}
	// Remove trailing space
	if (j > 0 && str[j - 1] == ' ') {
		j--;
	}
	// Null terminate the string
	str[j] = '\0';
}

