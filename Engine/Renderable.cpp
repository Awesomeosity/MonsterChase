#include "Renderable.h"

Renderable::Renderable()
{
	renderables = std::vector<renders>();
}

Renderable::~Renderable()
{
	for (size_t i = 0; i < renderables.size(); i++)
	{
		renderables[i].gameObj.Reset();
	}

	renderables.clear();
}

void Renderable::AddRenderable(WeakPointer<GameObject> gameObj, GLib::Sprites::Sprite* sprPtr)
{
	renderables.push_back(SmartPointer<renders>(new renders(WeakPointer<GameObject>(gameObj), sprPtr)));
}

void Renderable::ReleaseSprites()
{
	for (size_t i = 0; i < renderables.size(); i++)
	{
		if (renderables[i].sprPtr)
		{
			GLib::Sprites::Release(renderables[i].sprPtr);
		}
	}
}

void Renderable::RenderAll()
{
	GLib::BeginRendering();
	GLib::Sprites::BeginRendering();
	for (size_t i = 0; i < renderables.size(); i++)
	{
		float p_x = renderables[i]->gameObj->GetPoint().GetX();
		float p_y = renderables[i]->gameObj->GetPoint().GetY();
		float spritePos_X = p_x * 50;
		float spritePos_Y = p_y * 50;

		GLib::Point2D	Offset = { spritePos_X, spritePos_Y };

		GLib::Sprites::RenderSprite(*(renderables[i]->sprPtr), Offset, 0);
	}

	GLib::Sprites::EndRendering();
	GLib::EndRendering();
}

void Renderable::Dispose()
{
	for (size_t i = 0; i < renderables.size(); i++)
	{
		GLib::Sprites::Release(renderables[i]->sprPtr);
		renderables[i]->gameObj.Reset();
		renderables[i].Reset();
	}

	renderables.clear();
}
