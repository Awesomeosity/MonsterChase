#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#else
#include <stdlib.h>
#endif // _DEBUG

char* MakeSentence(const char** strings)
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
	char* sentence = (char *)malloc(sizeof(char) * totalSize);
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

// This is only a simple unit test. 

int main(int i_argc, char** i_argl)
{
	const char* strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};

	char* pSentence = MakeSentence(strings);

	printf("The Sentence is: %s", pSentence);

	free(pSentence);

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;
}
