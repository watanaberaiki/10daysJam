#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { scale_,scale_,scale_ };
	worldTransform_.translation_ = {0,10,0};
}

void Player::Update()
{
	Move();
	/*worldTransform_.translation_.y -= gravity;*/
	worldTransformUpdate(&worldTransform_);
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Player::Move()
{
	//arowキーで移動
	if (input_->PushKey(DIK_LEFT))
	{
		move.x = -mSpeed[0];
	}
	else if (input_->PushKey(DIK_RIGHT))
	{
		move.x = mSpeed[0];
	}
	else
	{
		move.x = 0;
	}
	if (input_->PushKey(DIK_DOWN))
	{
		move.z = -mSpeed[2];
	}
	else if (input_->PushKey(DIK_UP))
	{
		move.z = mSpeed[2];
	}
	else
	{
		move.z = 0;
	}

	

	mSpeed[1] = -gravity;
	move.y = mSpeed[1];

	worldTransform_.translation_ += move;
}

void Player::OnMapCollision()
{

}

void Player::OnMapCollisionX()
{
	worldTransform_.translation_.x += 0.1;
}

void Player::OnMapCollisionY()
{
	worldTransform_.translation_.y += 0.1;
}

void Player::OnMapCollisionZ()
{
	worldTransform_.translation_.z += 0.1;
}

void Player::OnMapCollisionX2()
{
	worldTransform_.translation_.x -= 0.1;
}

void Player::OnMapCollisionY2()
{
	worldTransform_.translation_.y -= 0.1;
	
}

void Player::OnMapCollisionZ2()
{
	worldTransform_.translation_.z -= 0.1;
}

void Player::MoveSpeedSet()
{
	mSpeed[0] = moveSpeed;
	mSpeed[1] = -gravity;
	mSpeed[2] = moveSpeed;
}

