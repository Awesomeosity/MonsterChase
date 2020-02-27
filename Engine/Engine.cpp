// Engine.cpp : Defines the functions for the static library.
//

#include <cassert>
#include <iostream>
#include "framework.h"
#include "GLib/BasicTypes.h"
#include "GLib/GLib.h"
#include "Objects/SmartPointer.h"
#include "Objects/WeakPointer.h"
#include "Objects/World.h"
#include "Physics/Physics.h"
#include "Physics/PhysicsData.h"
#include "Timing/Timing.h"
#include "Types/Point2D.h"
#include "Renderable.h"

#include "External/nlohmann/json.hpp"
#include "Objects/GameObject.h"

Physics* physSystem;
Renderable* renderSystem;
World* world;

void initEngine()
{
	world = new World();
	physSystem = new Physics();
	renderSystem = new Renderable();
}

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);

	if (bWentDown)
	{
		//TODO: Implement multiple key detection
		physSystem->currKey = i_VKeyID;
	}
	else
	{
		physSystem->currKey = 0;
	}
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

WeakPointer<GameObject> CreateActor(const char* i_pScriptFilename, int& o_controllerType)
{
	using json = nlohmann::json;
	std::vector<uint8_t> data = LoadFileToBuffer(i_pScriptFilename);

	assert(!data.empty());
	json obJSON = json::parse(data);

	assert(obJSON.contains("position"));
	assert(obJSON["position"].is_array());
	assert(obJSON["position"].size() == 2);
	Point2D actorPos = Point2D(obJSON["position"][0], obJSON["position"][1]);

	WeakPointer<GameObject> actorPtr = world->AddObject(actorPos);

	if (obJSON.contains("collision_data"))
	{
		assert(obJSON["collision_data"]["mass"].is_number_float());
		assert(obJSON["collision_data"]["kd"].is_number_float());
		float actorMass = obJSON["collision_data"]["mass"];
		float actorKD = obJSON["collision_data"]["kd"];

		physSystem->AddCollidableObject(actorPtr, actorMass, actorKD);
	}

	if (obJSON.contains("render_data"))
	{
		assert(obJSON["render_data"]["sprite"].is_string());

		std::string sprite = obJSON["render_data"]["sprite"];

		GLib::Sprites::Sprite* pSprite = CreateSprite("data\\goodguy.dds");
		renderSystem->AddRenderable(actorPtr, pSprite);
	}

	assert(obJSON.contains("name"));
	assert(obJSON["name"].is_string());
	//TODO: Return name too? I guess?
	//std::string name = obJSON["name"];
	//char* name_c = const_cast<char*>(name.c_str());


	if (obJSON.contains("controller"))
	{
		assert(obJSON["controller"].is_string());
		std::string conType = obJSON["controller"];
		
		if (conType == "player")
		{
			o_controllerType = 0;
		}
		else if (conType == "normal")
		{
			o_controllerType = 1;
		}
		else if (conType == "random")
		{
			o_controllerType = 2;
		}
		else
		{
			o_controllerType = -1;
		}
	}

	return actorPtr;
}

void Run()
{
	//GLib::Sprites::Sprite* pGoodGuy = CreateSprite("data\\GoodGuy.dds");
	GLib::SetKeyStateChangeCallback(TestKeyCallback);

	Timing::startTime();

	bool bQuit = false;

	do
	{
		//Timing
		long dt = Timing::deltaTime();
		float dt_ms = (float)dt / 1000.0f;

		GLib::Service(bQuit);
		
		//TODO: Get Input


		if (!bQuit)
		{
			physSystem->RunPhysics(dt_ms);

			renderSystem->RenderAll();
		}

	} while (bQuit == false);

	physSystem->Dispose();
	renderSystem->Dispose();
	delete world;
	delete physSystem;
	delete renderSystem;

	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}