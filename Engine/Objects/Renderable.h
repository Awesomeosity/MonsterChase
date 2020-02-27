#pragma once
#include "../GLib/BasicTypes.h"
#include "../GLib/GLib.h"
#include "WeakPointer.h"
#include "GameObject.h"
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
	~Renderable();
	void AddRenderable(WeakPointer<GameObject> gameObj, GLib::Sprites::Sprite* sprPtr);
	void ReleaseSprites();
	void RenderAll();
	void Dispose();
private:
	std::vector<SmartPointer<renders>> renderables;
};

