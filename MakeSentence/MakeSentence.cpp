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
	return startNode;
}


char* MakeSentence(LinkedNode* startNode)
{
	LinkedNode* currNode = startNode;
	LinkedNode* secondPassNode = startNode;
	int totalSize = 0;
	//Per Word
	while (currNode != NULL)
	{
		char* currStr = currNode->string;
		int j = 0;
		//Per Char
		while (currStr[j] != '\0')
		{
			totalSize++;
			j++;
		}
		currNode = currNode->nextNode;
		totalSize++;
	}
	if (startNode == nullptr)
	{
		totalSize++;
	}
	totalSize++;

	char* sentence = (char *)malloc(sizeof(char) * totalSize);
	int iter = 0;
	while (secondPassNode != NULL)
	{
		int j = 0;
		char* currStr = secondPassNode->string;
		while (currStr[j] != '\0')
		{
			sentence[iter] = currStr[j];
			iter++;
			j++;
		}

		if (secondPassNode->nextNode != nullptr)
		{
			sentence[iter] = ' ';
			iter++;
		}
		secondPassNode = secondPassNode->nextNode;
	}
	sentence[iter] = '.';
	sentence[iter + 1] = '\0';
	return sentence;
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

	char* pSentence = MakeSentence(startNode);

	printf("The Sentence is: %s", pSentence);

	free(pSentence);

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;
}
