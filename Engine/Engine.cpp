// Engine.cpp : Defines the functions for the static library.
//

#include "GLib/BasicTypes.h"
#include "GLib/GLib.h"
#include "framework.h"
#include <iostream>

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

void CreateActor(const char* i_pScriptFilename)
{

}

void Run()
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Mash", ID, static_cast<unsigned int>(playX) * 50 * 2, static_cast<unsigned int>(playY) * 50 * 2);

	while (1)
	{

	}
}