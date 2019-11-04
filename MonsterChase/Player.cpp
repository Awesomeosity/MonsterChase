#include "Player.h"
#include "../Engine/Point2D.h"
#include "../Engine/GameObject.h"

Player::Player(Point2D point) : GameObject(point)
{
}

Player::~Player()
{
}

void Player::MovePlayer(char move, Player* player)
{
	if (move == 'W' || move == 'w')
	{
		float Y = player->GetPoint()->GetY() + 1.0f;
		player->GetPoint()->SetY(Y);
	}
	if (move == 'A' || move == 'a')
	{
		float X = player->GetPoint()->GetX() - 1.0f;
		player->GetPoint()->SetX(X);
	}
	if (move == 'S' || move == 's')
	{
		float Y = player->GetPoint()->GetY() - 1.0f;
		player->GetPoint()->SetY(Y);
	}
	if (move == 'D' || move == 'd')
	{
		float X = player->GetPoint()->GetX() + 1.0f;
		player->GetPoint()->SetX(X);
	}

}

void Player::MovePlayerMain(char movement, Player* player, const float playX, const float playY)
{
	player->MovePlayer(movement, player);
	//Make sure player wraps around
	if (player->GetPoint()->GetX() > playX)
	{
		player->GetPoint()->SetX(playX * -1);
	}

	if (player->GetPoint()->GetX() < playX * -1)
	{
		player->GetPoint()->SetX(playX);
	}

	if (player->GetPoint()->GetY() > playY)
	{
		player->GetPoint()->SetY(playY * -1);
	}

	if (player->GetPoint()->GetY() < playY * -1)
	{
		player->GetPoint()->SetY(playY);
	}

}
