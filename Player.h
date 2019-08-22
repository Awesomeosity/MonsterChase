#pragma once
#include <string>
class Player
{
private:
	char* _name;
	int _X;
	int _Y;

public:
	Player(int X, int Y, char name[]);
	~Player();
	char MoveLoop();
	void MovePlayer(char move);
	char* GetName();
	void SetName(char name[]);

	int GetX();
	void SetX(int X);
	int GetY();
	void SetY(int Y);
};

