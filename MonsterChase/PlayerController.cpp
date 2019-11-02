#include "PlayerController.h"

PlayerController::PlayerController(GameObject* player, int sizeX, int sizeY)
	: player(player), sizeX(sizeX), sizeY(sizeY)
{
}

void PlayerController::Move(char direction)
{
	if (direction == 'W' || direction == 'w')
	{
		float Y = player->GetPoint()->GetY() + 1.0f;
		player->GetPoint()->SetY(Y);
	}
	if (direction == 'A' || direction == 'a')
	{
		float X = player->GetPoint()->GetX() - 1.0f;
		player->GetPoint()->SetX(X);
	}
	if (direction == 'S' || direction == 's')
	{
		float Y = player->GetPoint()->GetY() - 1.0f;
		player->GetPoint()->SetY(Y);
	}
	if (direction == 'D' || direction == 'd')
	{
		float X = player->GetPoint()->GetX() + 1.0f;
		player->GetPoint()->SetX(X);
	}
	boundCheck();
}

void PlayerController::boundCheck()
{
	if (player->GetPoint()->GetX() > sizeX)
	{
		player->GetPoint()->SetX(sizeX * -1);
	}

	if (player->GetPoint()->GetX() < sizeX * -1)
	{
		player->GetPoint()->SetX(sizeX);
	}

	if (player->GetPoint()->GetY() > sizeY)
	{
		player->GetPoint()->SetY(sizeY * -1);
	}

	if (player->GetPoint()->GetY() < sizeY * -1)
	{
		player->GetPoint()->SetY(sizeY);
	}

}
