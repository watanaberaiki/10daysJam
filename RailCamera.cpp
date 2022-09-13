#include "RailCamera.h"
#include "math.h"
#include <cassert>
#define PI 3.141592653589

void RailCamera::Initialize(WorldTransform worldTransform)
{
	viewProjection_.Initialize();
	float x, y, z;

	//Žw’è‚µ‚½Šp“x‚Å‰ñ“]
	x = worldTransform_.translation_.x + (sin(-angleY + (PI / 2)) * cos(-angleX - (PI / 2)) * length);
	y = worldTransform_.translation_.y + (cos(-angleY + (PI / 2)) * length);
	z = worldTransform_.translation_.z + (sin(-angleY + (PI / 2)) * sin(-angleX - (PI / 2)) * length);

	if (sin(angleY) <= 0)
	{
		viewProjection_.up = { 0,-1,0 };
	}
	else
	{
		viewProjection_.up = { 0,1,0 };
	}
	viewProjection_.eye = { x,y,z };
	viewProjection_.target = { 10, -6, 10 };
	viewProjection_.Initialize();
}

void RailCamera::Update(WorldTransform worldTransform)
{
	worldTransform_ = worldTransform;
	(this->*Mode_[mode_])();
}

void (RailCamera::* RailCamera::Mode_[])() =
{
	&RailCamera::standBy,
	&RailCamera::Approach,
	&RailCamera::Homing,
	&RailCamera::Operarion,
};


void RailCamera::standBy()
{
	//float x, y, z;

	////Žw’è‚µ‚½Šp“x‚Å‰ñ“]
	//x = worldTransform_.translation_.x + (sin(-angleY + (PI / 2)) * cos(-angleX - (PI / 2)) * length);
	//y = worldTransform_.translation_.y + (cos(-angleY + (PI / 2)) * length);
	//z = worldTransform_.translation_.z + (sin(-angleY + (PI / 2)) * sin(-angleX - (PI / 2)) * length);

	//if (sin(angleY) <= 0)
	//{
	//	viewProjection_.up = { 0,-1,0 };
	//}
	//else
	//{
	//	viewProjection_.up = { 0,1,0 };
	//}
	//viewProjection_.eye = { x,y,z };
	//viewProjection_.target = { 10, -6, 10 };
	//viewProjection_.Initialize();
}

void RailCamera::Approach()
{
	Vector3 points[9] =
	{
		{1,1,1},
		{1,1,1},
		{1,1,1},
		{1,1,1},
		{1,1,1},
		{1,1,1},
		{1,1,1},
		{1,1,1},
		{1,1,1},
	};
	viewProjection_.target = { worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z };
	viewProjection_.Initialize();
}

void RailCamera::Homing()
{
	float x, y, z;

	//ƒvƒŒƒCƒ„[‚ÌŠp“x‚É‡‚í‚¹‚ÄƒJƒƒ‰‚ð‰ñ“]
	/*x = worldTransform.translation_.x + (sin(-worldTransform.rotation_.x + (PI / 2)) * cos(-worldTransform.rotation_.y - (PI / 2)) * length);
	y = worldTransform.translation_.y + (cos(-worldTransform.rotation_.x + (PI / 2)) * length);
	z = worldTransform.translation_.z + (sin(-worldTransform.rotation_.x + (PI / 2)) * sin(-worldTransform.rotation_.y - (PI / 2)) * length);*/

	//Žw’è‚µ‚½Šp“x‚Å‰ñ“]
	x = worldTransform_.translation_.x + (sin(-angleY + (PI / 2)) * cos(-angleX - (PI / 2)) * length);
	y = worldTransform_.translation_.y + (cos(-angleY + (PI / 2)) * length);
	z = worldTransform_.translation_.z + (sin(-angleY + (PI / 2)) * sin(-angleX - (PI / 2)) * length);

	if (sin(angleY) <= 0)
	{
		viewProjection_.up = { 0,-1,0 };
	}
	else
	{
		viewProjection_.up = { 0,1,0 };
	}
	viewProjection_.eye = { x,y,z };
	viewProjection_.target = { worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z };
	viewProjection_.Initialize();
}

void RailCamera::Operarion()
{
}
