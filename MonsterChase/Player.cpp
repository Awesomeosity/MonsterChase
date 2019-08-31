#include "Player.h"
#include "../Engine/Point2D.h"
#include "../Engine/GameObject.h"

Player::Player(Point2D point, char name[]) : GameObject(point, name)
{
}

Player::~Player()
{
}