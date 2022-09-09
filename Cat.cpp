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

	worldTransform_.translation_ = { 4,2,0 };

}

//更新処理
void Cat::Update() {
	Move();

	worldTransformUpdate(&worldTransform_);


	debugText_->SetPos(0, 20);
	debugText_->Printf("%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
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
	moveSpeed = 0.03;
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

					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
					direction_ = Direction::back;
				}
				if (map->map[i][j][k] == CATLEFT) {

					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
					direction_ = Direction::left;
				}
				if (map->map[i][j][k] == CATRIGHT) {

					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
					direction_ = Direction::right;
				}
				if (map->map[i][j][k] == CATDOWN) {

					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
					direction_ = Direction::front;
				}
			}
		}
	}

}