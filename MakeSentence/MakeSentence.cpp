#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <iostream>
#else
#include <stdlib.h>
#include "MakeSentence.h"
#endif // _DEBUG

struct LinkedNode
{
	char* string;
	LinkedNode* nextNode = NULL;
};

LinkedNode* queryLoop()
{
	LinkedNode* startNode = NULL;
	LinkedNode* prevNode = NULL;
	LinkedNode* currNode = NULL;

	char buf[256];
	do {
		std::cin.getline(buf, 256, '\n');
		if (buf[0] == '\0')
		{
			break;
		}

		currNode = (LinkedNode*)malloc(sizeof(LinkedNode));
		if (startNode == nullptr)
		{
			startNode = currNode;
		}
		else
		{
			prevNode->nextNode = currNode;
		}
		int i = 0;
		while (buf[i] != '\0')
		{
			i++;
		}
		currNode->string = (char*)malloc(sizeof(char) * ((unsigned long long)i + 1));
		int ii = 0;
		while (ii - 1 != i)
		{
			currNode->string[ii] = buf[ii];
			ii++;
		}

		prevNode = currNode;
	} while (true);
	if (prevNode != NULL)
	{
		prevNode->nextNode = NULL;
	}
#if defined(_DEBUG)
	_ASSERTE(_CrtCheckMemory());
#endif // _DEBUG

	return startNode;
}

char** convertInput(LinkedNode* links)
{
	LinkedNode* currRef = links;
	LinkedNode* initialRef = currRef;
	size_t count = 0;
	while (currRef != nullptr)
	{
		count++;
		currRef = currRef->nextNode;
	}

	if (count == 0)
	{
		return {NULL};
	}

	char** sentence = (char**)malloc(sizeof(char*) * (count + 1));

	for (int i = 0; i < count; i++)
	{
		sentence[i] = initialRef->string;
		initialRef = initialRef->nextNode;
	}

	sentence[count] = NULL;
	return sentence;
}

char* MakeSentence(char** strings)
{
	int totalSize = 0;
	int i = 0;
	//Per Word
	while (strings[i] != NULL)
	{
		const char* currStr = strings[i];
		int j = 0;
		//Per Char
		while (currStr[j] != '\0')
		{
			totalSize++;
			j++;
		}
		totalSize++;
		i++;
	}
	totalSize++;
	char* sentence = (char*)malloc(sizeof(char) * totalSize);
	int iter = 0;
	int ii = 0;
	while (strings[ii] != NULL)
	{
		int j = 0;
		const char* currStr = strings[ii];
		while (currStr[j] != '\0')
		{
			sentence[iter] = currStr[j];
			iter++;
			j++;
		}

		if (ii + 1 != i)
		{
			sentence[iter] = ' ';
		}
		else
		{
			sentence[iter] = '.';
			sentence[iter + 1] = '\0';
		}
		iter++;
		ii++;
	}
	return sentence;
}

void chainFree(LinkedNode* firstNode)
{
	if (firstNode == NULL)
	{
		return;
	}
	if (firstNode->nextNode != NULL)
	{
		chainFree(firstNode->nextNode);
	}
	free(firstNode->string);
	free(firstNode->nextNode);
}

// This is only a simple unit test. 

int main(int i_argc, char** i_argl)
{
	/*
	const char* strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};
	*/

	LinkedNode* startNode = queryLoop();
	char** converted = convertInput(startNode);
	char* pSentence = MakeSentence(converted);

	printf("The Sentence is: %s", pSentence);

	free(pSentence);

	chainFree(startNode);
	free(startNode);
	free(converted);

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;
}
