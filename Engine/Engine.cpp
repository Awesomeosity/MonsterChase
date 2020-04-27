// Engine.cpp : Defines the functions for the static library.
//

#include <cassert>
#include <iostream>
#include "framework.h"
#include "GLib/BasicTypes.h"
#include "GLib/GLib.h"
#include "Objects/Renderable.h"
#include "Objects/SmartPointer.h"
#include "Objects/WeakPointer.h"
#include "Objects/World.h"
#include "Physics/Physics.h"
#include "Physics/PhysicsData.h"
#include "Timing/Timing.h"
#include "Types/Point2D.h"

#include "External/nlohmann/json.hpp"
#include "Objects/GameObject.h"

namespace Engine
{
	Physics* physSystem;
	Renderable* renderSystem;
	World* world;
	SmartPointer<GameObject> player_object;

	void initEngine()
	{
		OutputDebugStringA("DEBUG: Starting systems.\n");
		world = new World();
		physSystem = new Physics();
		renderSystem = new Renderable();
	}

	void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
	{
		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];

		static bool WKey = false;
		static bool AKey = false;
		static bool SKey = false;
		static bool DKey = false;

		switch (i_VKeyID)
		{
			//W
		case 87:
			WKey = !WKey;
			break;
			//S
		case 83:
			SKey = !SKey;
			break;
			//A
		case 65:
			AKey = !AKey;
			break;
			//D
		case 68:
			DKey = !DKey;
			break;
		case 81:
			//No key being held down.
		case 0:
		default:
			break;
		}

		sprintf_s(Buffer, lenBuffer, "DEBUG: VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
		OutputDebugStringA(Buffer);

		void* voidForcePtr = player_object->GetComponent("Forces");
		Point2D* forcePtr = reinterpret_cast<Point2D*>(voidForcePtr);

		Point2D tempForces;
		if (WKey && !SKey)
		{
			tempForces.SetY(100.0f);
		}
		else if (SKey && !WKey)
		{
			tempForces.SetY(-100.0f);
		}

		if (AKey && !DKey)
		{
			tempForces.SetX(-100.0f);
		}
		else if (!AKey && DKey)
		{
			tempForces.SetX(100.0f);
		}

		(*forcePtr).SetX(tempForces.GetX());
		(*forcePtr).SetY(tempForces.GetY());
	}

	std::vector<uint8_t> LoadFileToBuffer(std::string i_pFilename)
	{
		//assert(i_pFilename != nullptr);

		std::vector<uint8_t> Buffer;

		if (!i_pFilename.empty())
		{
			FILE* pFile = nullptr;
			errno_t fopenError = fopen_s(&pFile, i_pFilename.c_str(), "rb");
			if (fopenError == 0)
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
		}

		return Buffer;
	}


	GLib::Sprite* CreateSprite(std::string i_pFilename)
	{

		size_t sizeTextureFile = 0;

		// Load the source file (texture data)
		std::vector<uint8_t> pTextureFile = LoadFileToBuffer(i_pFilename.c_str());

		// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
		//GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;
		GLib::Texture* pTexture = GLib::CreateTexture(&pTextureFile[0], pTextureFile.size());

		if (pTexture == nullptr)
		{
			OutputDebugStringA("DEBUG: Texture loading failed.\n");
			return NULL;
		}
		else
		{
			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int depth = 0;

			bool result = GLib::GetDimensions(*pTexture, width, height, depth);
			assert(result == true);
			assert((width > 0 && height > 0));

			// Define the sprite edges
			GLib::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
			GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
			GLib::RGBA							Color = { 255, 255, 255, 255 };

			// Create the sprite
			GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs);
			if (pSprite == nullptr)
			{
				GLib::Release(pTexture);
				return nullptr;
			}

			// Bind the texture to sprite
			GLib::SetTexture(*pSprite, pTexture);

			OutputDebugStringA("DEBUG: Texture loading success.\n");
			return pSprite;
		}
	}

	WeakPointer<GameObject> CreateActor(std::string i_pScriptFilename, int& o_controllerType)
	{
		using json = nlohmann::json;
		std::vector<uint8_t> data = LoadFileToBuffer(i_pScriptFilename);

		assert(!data.empty());
		json obJSON = json::parse(data);

		assert(obJSON.contains("position"));
		assert(obJSON["position"].is_array());
		assert(obJSON["position"].size() == 2);
		Point2D actorPos = Point2D(obJSON["position"][0], obJSON["position"][1]);

		assert(obJSON.contains("rotation"));
		assert(obJSON["rotation"].is_number_float());

		WeakPointer<GameObject> actorPtr = world->AddObject(actorPos);
		float* actorRot = new float(obJSON["rotation"]);
		actorPtr->AddComponent("Rotation", actorRot);
			
		if (obJSON.contains("collision_data"))
		{
			assert(obJSON["collision_data"]["mass"].is_number_float());
			assert(obJSON["collision_data"]["kd"].is_number_float());
			assert(obJSON["collision_data"]["BB_X"].is_number_float());
			assert(obJSON["collision_data"]["BB_Y"].is_number_float());

			float actorMass = obJSON["collision_data"]["mass"];
			float actorKD = obJSON["collision_data"]["kd"];
			float actorBB_X = obJSON["collision_data"]["BB_X"];
			float actorBB_Y = obJSON["collision_data"]["BB_Y"];

			physSystem->AddCollidableObject(actorPtr, actorBB_X, actorBB_Y, actorMass, actorKD);
			OutputDebugStringA("DEBUG: Added Collidable object.\n");
		}

		if (obJSON.contains("render_data"))
		{
			assert(obJSON["render_data"]["sprite"].is_string());

			std::string sprite = obJSON["render_data"]["sprite"];

			GLib::Sprite* pSprite = CreateSprite(sprite);
			renderSystem->AddRenderable(actorPtr, pSprite);
			OutputDebugStringA("DEBUG: Added Renderable object.\n");
		}

		assert(obJSON.contains("name"));
		assert(obJSON["name"].is_string());


		if (obJSON.contains("controller"))
		{
			assert(obJSON["controller"].is_string());
			std::string conType = obJSON["controller"];

			if (conType == "player")
			{
				o_controllerType = 0;

				//Kinda a hacky solution...
				player_object = actorPtr.Promote();
				Point2D* forcePointer = new Point2D();
				player_object->AddComponent("Forces", forcePointer);
				OutputDebugStringA("DEBUG: Added Player object.\n");
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
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		Timing::startTime();

		bool bQuit = false;

		do
		{
			const size_t	lenBuffer = 65;
			char			Buffer[lenBuffer];

			//Timing
			long dt = Timing::deltaTime();
			float dt_ms = (float)dt / 1000.0f;


			sprintf_s(Buffer, lenBuffer, "DEBUG: Frame time: %2.5f milliseconds.\n", dt_ms);
			OutputDebugStringA(Buffer);

			GLib::Service(bQuit);

			if (!bQuit)
			{
				//OutputDebugStringA("DEBUG: Starting system ticks.\n");
				physSystem->RunPhysics(dt_ms);
				renderSystem->RenderAll();
				//OutputDebugStringA("DEBUG: Ending system ticks.\n");
			}

		} while (bQuit == false);

		OutputDebugStringA("DEBUG: Beginning shutdown.\n");
		physSystem->Dispose();
		renderSystem->Dispose();
		delete world;
		delete physSystem;
		delete renderSystem;
		player_object.Reset();

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
		OutputDebugStringA("DEBUG: Ending shutdown.\n");
	}
}
