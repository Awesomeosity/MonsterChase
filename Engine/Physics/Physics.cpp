#include "Physics.h"
#include "PhysicsData.h"
#include "../Types/Point2D.h"
void Physics::calcNewPos(float dt_ms, PhysicsData* data, Point2D forces)
{
	Point2D currPos = data->GetCurrentPos();
	Point2D prevPos = data->GetPrevPos();
	float mass = data->GetMass();
	float drag = data->GetDrag();

	Point2D newPos = (currPos * (2.0f - drag)) - prevPos + ((forces / mass) * dt_ms) / 1000.0f;

	data->UpdatePrevPos(newPos);
}
