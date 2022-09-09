#include "Cat.h"
#include <cassert>


//初期化
void Cat::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { scale_,scale_,scale_ };

}

//更新処理
void Cat::Update() {
	Move();

	worldTransformUpdate(&worldTransform_);
}

//描画処理
void Cat::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//移動
void Cat::Move() {

	if (direction_ == Direction::front) {
		move.z = -moveSpeed;
	}
	else if (direction_ == Direction::right) {
		move.x = moveSpeed;
	}
	else if (direction_ == Direction::back) {
		move.z = moveSpeed;
	}
	else if (direction_ == Direction::left) {
		move.x = -moveSpeed;
	}
	worldTransform_.translation_ += move;

}

//当たったら
void Cat::OnMapCollision() {
	if (direction_ == Direction::front) {
		direction_ = Direction::right;
		worldTransform_.translation_.z += 0.1;
		move = { 0,0,0 };
		whichdirection = 1;
	}
	else if (direction_ == Direction::right) {
		direction_ = Direction::back;
		worldTransform_.translation_.x -= 0.1;
		move = { 0,0,0 };
		whichdirection = 2;
	}
	else if (direction_ == Direction::back) {
		direction_ = Direction::left;
		worldTransform_.translation_.z -= 0.1;
		move = { 0,0,0 };
		whichdirection = 3;
	}
	else if (direction_ == Direction::left) {
		direction_ = Direction::front;
		worldTransform_.translation_.x += 0.1;
		move = { 0,0,0 };
		whichdirection = 0;
	}
}

void Cat::FastSpeed() {
	moveSpeed = 0.1;
}

void Cat::Restore() {
	moveSpeed = 0.05;
}

void Cat::Pause() {
	moveSpeed = 0;
}

void Cat::MapSet(Map* map) {

	for (int i = 0; i < blockY; i++)
	{
		for (int j = 0; j < blockZ; j++)
		{
			for (int k = 0; k < blockX; k++) {

				//プレイヤー位置初期化

				if (map->map[i][j][k] == CATUP) {
					direction_ = Direction::back;
					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;

				}
				if (map->map[i][j][k] == CATLEFT) {
					direction_ = Direction::left;
					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;

				}
				if (map->map[i][j][k] == CATRIGHT) {
					direction_ = Direction::right;
					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;

				}
				if (map->map[i][j][k] == CATDOWN) {
					direction_ = Direction::front;
					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;

				}
			}
		}
	}

}