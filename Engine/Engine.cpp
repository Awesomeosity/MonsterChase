// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
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
