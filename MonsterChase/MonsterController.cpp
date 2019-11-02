#include "MonsterController.h"
#include <cstdlib>
MonsterController::MonsterController(GameObject* monster) :
	monster(monster)
{
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
	unsigned int randomVal = (rand() / (RAND_MAX / 2));
	if (randomVal == 0)
	{
		isActive = true;
	}
	else
	{
		isActive = false;
	}
}

void MonsterController::Move(Point2D point)
{
	if (isActive)
	{
		float x = monster->GetPoint()->GetX();
		float y = monster->GetPoint()->GetY();
		float diffX = point.GetX() - x;
		float diffY = point.GetY() - y;

		if (diffX > 0)
		{
			monster->GetPoint()->SetX(++x);
		}
		else if (diffX < 0)
		{
			monster->GetPoint()->SetX(--x);
		}
		else if (diffY > 0)
		{
			monster->GetPoint()->SetX(++y);
		}
		else
		{
			monster->GetPoint()->SetX(--y);
		}
	}
	checkAndSetTime();
}

void MonsterController::checkAndSetTime()
{
	deathTime--;
	if (deathTime == 0)
	{
		isActive = !isActive;
	}
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
}
