// MonsterMash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <assert.h>
#include "Controllers/MonsterController.h"
#include "Controllers/PlayerController.h"
#include "Controllers/RandomController.h"
#include "conio.h"
#include <stdint.h>
#include <Windows.h>

#include "../Engine/Engine.cpp"
#include "../Engine/GLib/BasicTypes.h"
#include "../Engine/GLib/GLib.h"
#include "../Engine/Objects/GameObject.h"
#include "../Engine/Types/Point2D.h"
#include <vector>

void inline GetMonsterCount(unsigned int* const maxMonsters)
{
	//TEMP: Fixed Monster Count because no input lol
	*maxMonsters = 1;
	
	/*
	unsigned int monsterCount = 0;
	while (true)
	{
		std::cout << "Please enter the initial amount of monsters: ";
		std::cin >> monsterCount;

		if (std::cin.fail() || monsterCount > UINT_MAX - 10)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid input. Please try entering an positive integer.\n";
		}
		else
		{
			std::cin.ignore(INT_MAX, '\n');
			*maxMonsters = monsterCount;
			break;
		}
	}
	*/
}

bool inline CheckPlayer(PlayerController* const player, std::vector<MonsterController*>* monsters, std::vector<RandomController*>* randoms)
{
	float playerX = player->getPlayerPosition()->GetX();
	float playerY = player->getPlayerPosition()->GetY();

	for (size_t i = 0; i < (*monsters).size(); i++)
	{
		if ((*monsters)[i]->getActive() && (*monsters)[i]->getPosition()->GetX() == playerX && (*monsters)[i]->getPosition()->GetY() == playerY)
		{
			return false;
		}
	}
	for (size_t i = 0; i < (*randoms).size(); i++)
	{
		if ((*randoms)[i]->getActive() && (*randoms)[i]->getPosition()->GetX() == playerX && (*randoms)[i]->getPosition()->GetY() == playerY)
		{
			return false;
		}
	}

	return true;
}

void inline GameLoop(PlayerController* const player, const std::vector<IGameObjectController*>* controllers, std::vector<MonsterController*>* monsters, std::vector<RandomController*>* randoms)
{
	float beforePosX, beforePosY, afterPosX, afterPosY;
	bool isAlive = true;
	while (isAlive)
	{
		beforePosX = player->getPlayerPosition()->GetX();
		beforePosY = player->getPlayerPosition()->GetY();
		for (size_t i = 0; i < controllers->size(); i++)
		{
			(*controllers)[i]->UpdateGameObject();
			if (i == 0)
			{
				afterPosX = player->getPlayerPosition()->GetX();
				afterPosY = player->getPlayerPosition()->GetY();
				if (beforePosX == afterPosX && beforePosY == afterPosY)
				{
					//std::cout << "Quitting...\n";
					isAlive = false;
					break;
				} 
				if (!CheckPlayer(player, monsters, randoms))
				{
					//std::cout << "You got hit!\n";
					isAlive = false;
					break;
				}
			}
		}

	}
}

inline GameObject* MonsterCreateLoop(const float playX, const float playY, unsigned int* const maxMonsters, GameObject* player, std::vector<IGameObjectController*>* controllers, std::vector<MonsterController*>* monsters, std::vector<RandomController*>* randoms)
{
	unsigned int i = 0;
	bool isActive = false;
	GetMonsterCount(maxMonsters);
	//std::cout << *maxMonsters << " is the initial amount of monsters.\n";
	GameObject* monsterObjs = new GameObject[*maxMonsters + 10];
	for (; i < *maxMonsters + 10; i++)
	{
		char* name = new char[256]();

		if (isActive)
		{
			//TEMP: Change this back when we get inputs
			//std::cout << "Please enter Monster #" << i - 9 << "'s name: ";
			//GetName(name);
		}
		else
		{
			char beginning[256] = "Monster #";
			char buffer[256];
			buffer[0] = '\0';
			_itoa_s(i, buffer, 10);
			strcat_s(beginning, buffer);
			strcpy_s(name, 256, beginning);
		}

		if (rand() / (RAND_MAX / 2) == 0)
		{
			//TEMP: Change this back when we get inputs
			strcpy_s(name, 256, "bruh");
			MonsterController* newController = new MonsterController(isActive, playX, playY, &(monsterObjs[i]), player, name);
			
			controllers->push_back(newController);
			monsters->push_back(newController);
		}
		else
		{
			RandomController* newController = new RandomController(isActive, playX, playY, &(monsterObjs[i]), name);
			controllers->push_back(newController);
			randoms->push_back(newController);
		}

		if (i == 9)
		{
			isActive = true;
		}
	}

	return monsterObjs;
}

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE* pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t* pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

GLib::Sprites::Sprite* CreateSprite(const char* i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite* pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}

void inline CreatePlayer(const float playX, const float playY, PlayerController* player, GameObject* playerObj)
{
	//TEMP: Change this back when we get inputs
	char* playerName = new char[256]();
	strcpy_s(playerName, 256, "bruh");
	//GetName(playerName);
	player->SetGameObject(playerObj);
	player->Setup(playerName, playX, playY);
}

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc();
	unsigned short ID = 65535;
	float playX = 10.0f;
	float playY = 10.0f;

	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Mash", ID, static_cast<unsigned int>(playX) * 50 * 2, static_cast<unsigned int>(playY) * 50 * 2);
	
	unsigned int monsterCount = 0;
	unsigned int* maxMonsters = &monsterCount;
	Point2D* zero = new Point2D(0, 0);
	GameObject* playerObj = new GameObject(*zero);
	std::vector<IGameObjectController*>* controllers = new std::vector<IGameObjectController*>();
	std::vector<MonsterController*>* monsters = new std::vector<MonsterController*>();
	std::vector<RandomController*>* randoms = new std::vector<RandomController*>();

	PlayerController* player = new PlayerController();
	controllers->push_back(player);


	GameObject* generated = MonsterCreateLoop(playX, playY, maxMonsters, playerObj, controllers, monsters, randoms);
	CreatePlayer(playX, playY, player, playerObj);

	if (bSuccess)
	{
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		//TODO: Generate multiple sprites?
		GLib::Sprites::Sprite* pGoodGuy = CreateSprite("data\\GoodGuy.dds");
		GLib::Sprites::Sprite* pBadGuy = CreateSprite("data\\BadGuy.dds");

		//float beforePosX, beforePosY, afterPosX, afterPosY;
		bool bQuit = false;

		do
		{
			
			GLib::Service(bQuit);
			if (!bQuit)
			{

				GLib::BeginRendering();
				GLib::Sprites::BeginRendering();
				if (pGoodGuy)
				{
					float playerSpritePos_X = player->getPlayerPosition()->GetX() * 50;
					float playerSpritePos_Y = player->getPlayerPosition()->GetY() * 50;

					static GLib::Point2D	Offset = { playerSpritePos_X, playerSpritePos_Y };

					GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0);
				}

				if (pBadGuy)
				{
					for (size_t i = 0; i < (*monsters).size(); i++)
					{
						if ((*monsters)[i]->getActive())
						{
							float monsterSpritePos_X = (*monsters)[i]->getPosition()->GetX() * 50;
							float monsterSpritePos_Y = (*monsters)[i]->getPosition()->GetY() * 50;

							static GLib::Point2D	Offset = { monsterSpritePos_X, monsterSpritePos_Y };

							GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0);

						}
					}
					for (size_t i = 0; i < (*randoms).size(); i++)
					{
						if ((*randoms)[i]->getActive())
						{
							float monsterSpritePos_X = (*randoms)[i]->getPosition()->GetX() * 50;
							float monsterSpritePos_Y = (*randoms)[i]->getPosition()->GetY() * 50;

							static GLib::Point2D	Offset = { monsterSpritePos_X, monsterSpritePos_Y };

							GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0);

						}
					}
				}
				GLib::Sprites::EndRendering();
				GLib::EndRendering();
			}

		} while (bQuit == false);

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

	for (size_t i = 0; i < controllers->size(); i++)
	{
		delete (*controllers)[i];
	}
	delete controllers;
	delete monsters;
	delete randoms;
	delete playerObj;
	delete zero;
	delete[] generated;
	_CrtDumpMemoryLeaks();

}

int main()
{
	float playX = 10.0f;
	float playY = 10.0f;
	unsigned int monsterCount = 0;
	unsigned int* maxMonsters = &monsterCount;
	Point2D* zero = new Point2D(0, 0);
	GameObject* playerObj = new GameObject(*zero);
	std::vector<IGameObjectController*>* controllers = new std::vector<IGameObjectController*>();
	std::vector<MonsterController*>* monsters = new std::vector<MonsterController*>();
	std::vector<RandomController*>* randoms = new std::vector<RandomController*>();

	PlayerController* player = new PlayerController();
	controllers->push_back(player);


	GameObject* generated = MonsterCreateLoop(playX, playY, maxMonsters, playerObj, controllers, monsters, randoms);
	CreatePlayer(playX, playY, player, playerObj);
	
	GameLoop(player, controllers, monsters, randoms);

	for (size_t i = 0; i < controllers->size(); i++)
	{
		delete (*controllers)[i];
	}
	delete controllers;
	delete monsters;
	delete randoms;
	delete playerObj;
	delete zero;
	delete[] generated;
	_CrtDumpMemoryLeaks();

#pragma warning (disable: 6031)
	_getch();
#pragma warning (disable: 6031)

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
