#include "Renderable.h"
Renderable::Renderable()
{
	InitializeCriticalSection(&queueModification);
}

Renderable::~Renderable()
{
	for (size_t i = 0; i < renderables.size(); i++)
	{
		renderables[i]->gameObj.Reset();
	}

	renderables.clear();
}

void Renderable::AddRenderable(WeakPointer<GameObject> gameObj, GLib::Sprite* sprPtr)
{
	EnterCriticalSection(&queueModification);
	renderables.push_back(SmartPointer<renders>(new renders(WeakPointer<GameObject>(gameObj), sprPtr)));
	LeaveCriticalSection(&queueModification);
}

void Renderable::ReleaseSprites()
{
	for (size_t i = 0; i < renderables.size(); i++)
	{
		if (renderables[i]->sprPtr)
		{
			GLib::Release(renderables[i]->sprPtr);
		}
	}
}

void Renderable::RenderAll()
{
	GLib::Sprites::BeginRendering();
	for (size_t i = 0; i < renderables.size(); i++)
	{
		float p_x = renderables[i]->gameObj->GetPoint().GetX();
		float p_y = renderables[i]->gameObj->GetPoint().GetY();
		float spritePos_X = p_x * 1;
		float spritePos_Y = p_y * 1;

		GLib::Point2D	Offset = { spritePos_X, spritePos_Y };

		GLib::Render(*(renderables[i]->sprPtr), Offset, 0);
	}

	GLib::Sprites::EndRendering();
	GLib::EndRendering();
}

void Renderable::Dispose()
{
	for (size_t i = 0; i < renderables.size(); i++)
	{
		GLib::Release(renderables[i]->sprPtr);
		renderables[i]->gameObj.Reset();
		renderables[i].Reset();
	}

	renderables.clear();
}
