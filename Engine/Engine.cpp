// Engine.cpp : Defines the functions for the static library.
//

#include <cassert>
#include <iostream>
#include "framework.h"
#include "GLib/BasicTypes.h"
#include "GLib/GLib.h"
#include "Objects/SmartPointer.h"
#include "Objects/WeakPointer.h"
#include "Physics/Physics.h"
#include "Physics/PhysicsData.h"
#include "Timing/Timing.h"
#include "Types/Point2D.h"

#include "External/nlohmann/json.hpp"
#include "Objects/GameObject.h"
#include "../MonsterChase/Controllers/PlayerController.h"


unsigned int currKey = 0;

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);

	if (bWentDown)
	{
		//TODO: Implement multiple key detection
		currKey = i_VKeyID;
	}
	else
	{
		currKey = 0;
	}
#endif // __DEBUG
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

std::vector<uint8_t> LoadFileToBuffer(const char* i_pFilename)
{
	assert(i_pFilename != nullptr);

	std::vector<uint8_t> Buffer;

	FILE* pFile = nullptr;

	if (fopen_s(&pFile, i_pFilename, "rb") == 0)
	{
		assert(pFile != nullptr);

		int FileIOError = fseek(pFile, 0, SEEK_END);
		assert(FileIOError == 0);

		long FileSize = ftell(pFile);
		assert(FileSize >= 0);

		FileIOError = fseek(pFile, 0, SEEK_SET);
		assert(FileIOError == 0);

		Buffer.reserve(FileSize);
		Buffer.resize(FileSize);

		size_t FileRead = fread(&Buffer[0], 1, FileSize, pFile);
		assert(FileRead == FileSize);

		fclose(pFile);
	}

	return Buffer;
}


void fnEngine()
{
	std::cout << "Engine Test\n";

}

void GetName(char* name)
{
	while (true)
	{
		std::cin.getline(name, 256);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Invalid input. Please try entering a string.\n";
		}
		else
		{
			return;
		}
	}
}

SmartPointer<GameObject> CreateActor(const char* i_pScriptFilename)
{
	using json = nlohmann::json;
	std::vector<uint8_t> data = LoadFileToBuffer(i_pScriptFilename);

	if (!data.empty())
	{
		json createdJSON = json::parse(data);
		//TODO create structure for json decision tree
		//TODO verification
		//TODO return SmartPointer
	}
}

void Run(HINSTANCE i_hInstance, int i_nCmdShow)
{
	float playX = 10.0f;
	float playY = 10.0f;

	unsigned short ID = 65535;

	Point2D* zero = new Point2D(0, 0);
	GameObject* playerObj = new GameObject(*zero);

	PlayerController* player = new PlayerController();

	PhysicsData* playerPhysics = new PhysicsData(playerObj, 1, 0);

	player->SetGameObject(playerObj);
	player->Setup(const_cast<char*>("lmao"), playX, playY);


	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Mash", ID, static_cast<unsigned int>(playX) * 50 * 2, static_cast<unsigned int>(playY) * 50 * 2);

	while (1)
	{
		if (bSuccess)
		{
			GLib::SetKeyStateChangeCallback(TestKeyCallback);

			GLib::Sprites::Sprite* pGoodGuy = CreateSprite("data\\GoodGuy.dds");

			Timing::startTime();

			bool bQuit = false;

			do
			{
				//Timing
				long dt = Timing::deltaTime();
				float dt_ms = (float)dt / 1000.0f;

				GLib::Service(bQuit);

				if (!bQuit)
				{
					Point2D force;
					switch (currKey)
					{
						//W
					case 87:
						force = Point2D(0, 1);
						break;
						//S
					case 83:
						force = Point2D(0, -1);
						break;
						//A
					case 65:
						force = Point2D(-1, 0);
						break;
						//D
					case 68:
						force = Point2D(1, 0);
						break;
					case 81:
						break;
						//No key being held down.
					case 0:
					default:
						force = Point2D(0, 0);
						break;
					}
					//Reset key press each frame;
					currKey = 0;

					//Physics
					Physics::calcNewPos(dt_ms, playerPhysics, force);

					//Render
					GLib::BeginRendering();
					GLib::Sprites::BeginRendering();
					if (pGoodGuy)
					{
						float p_x = player->getPlayerPosition()->GetX();
						float p_y = player->getPlayerPosition()->GetY();
						float playerSpritePos_X = p_x * 50;
						float playerSpritePos_Y = p_y * 50;

						GLib::Point2D	Offset = { playerSpritePos_X, playerSpritePos_Y };

						GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0);
					}

					GLib::Sprites::EndRendering();
					GLib::EndRendering();
				}

			} while (bQuit == false);

			// IMPORTANT:  Tell GLib to shutdown, releasing resources.
			GLib::Shutdown();
		}

	}
}