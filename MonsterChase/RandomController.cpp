#include "RandomController.h"

RandomController::RandomController(GameObject* monster) :
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

void RandomController::Move()
{
	if (isActive)
	{
		float x = monster->GetPoint()->GetX();
		float y = monster->GetPoint()->GetY();

		unsigned int result = (rand() / (RAND_MAX / 5));
		switch (result)
		{
		case 0:
			monster->GetPoint()->SetX(++x);
			break;
		case 1:
			monster->GetPoint()->SetX(--x);
			break;
		case 2:
			monster->GetPoint()->SetY(++y);
			break;
		case 3:
			monster->GetPoint()->SetY(--y);
			break;
		case 4:
		default:
			break;
		}
	}
	checkAndSetTime();
}

void RandomController::checkAndSetTime()
{
	deathTime--;
	if (deathTime == 0)
	{
		isActive = !isActive;
	}
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;

}
