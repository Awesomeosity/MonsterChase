#include "Renderable.h"

void Renderable::AddRenderable(SmartPointer<GameObject> gameObj, GLib::Sprites::Sprite* sprPtr)
{
	renderables.push_back(renders(WeakPointer<GameObject>(gameObj), sprPtr));
}

void Renderable::RenderAll()
{
	GLib::BeginRendering();
	GLib::Sprites::BeginRendering();
	for (int i = 0; i < renderables.size(); i++)
	{
		float p_x = renderables[i].gameObj->GetPoint()->GetX();
		float p_y = renderables[i].gameObj->GetPoint()->GetY();
		float spritePos_X = p_x * 50;
		float spritePos_Y = p_y * 50;

		GLib::Point2D	Offset = { spritePos_X, spritePos_Y };

		GLib::Sprites::RenderSprite(*(renderables[i].sprPtr), Offset, 0);
	}

	GLib::Sprites::EndRendering();
	GLib::EndRendering();
}
