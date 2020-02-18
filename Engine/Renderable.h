#pragma once
#include "GLib/BasicTypes.h"
#include "GLib/GLib.h"
#include "Objects/WeakPointer.h"
#include "Objects/GameObject.h"
#include <vector>
struct renders
{
	WeakPointer<GameObject> gameObj;
	GLib::Sprites::Sprite* sprPtr;
	renders(WeakPointer<GameObject> _obj, GLib::Sprites::Sprite* _ptr)
		: gameObj(_obj), sprPtr(_ptr)
	{

	}
};
class Renderable
{
public:
	void AddRenderable(WeakPointer<GameObject> gameObj, GLib::Sprites::Sprite* sprPtr);
	void RenderAll();
private:
	std::vector<renders> renderables;
};

