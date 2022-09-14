#include "Cat.h"
#include <cassert>


//������
void Cat::Initialize(Model* model, Model* model2, Model* model3) {
	assert(model);

	model_ = model;
	modelWalk_ = model2;
	modelWalk2_ = model3;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { scale_,scale_,scale_ };

	worldTransform_.translation_ = { 4,2,0 };

}

//�X�V����
void Cat::Update() {
	modelChengeTimer_++;

	if (modelChengeTimer_ >= modelChengeTime_) {
		modelChengeTimer_ = 0;
		modelChenge++;
	}
	Move();

	worldTransformUpdate(&worldTransform_);


	debugText_->SetPos(0, 20);
	debugText_->Printf("%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}


//�`�揈��
void Cat::Draw(ViewProjection viewProjection) {

	if (modelChenge % 4 == 0) {
		model_->Draw(worldTransform_, viewProjection);

	}
	else if (modelChenge % 4 == 1) {
		modelWalk_->Draw(worldTransform_, viewProjection);
	}
	else if (modelChenge % 4 == 2) {
		model_->Draw(worldTransform_, viewProjection);
	}
	else if (modelChenge % 4 == 3) {
		modelWalk2_->Draw(worldTransform_, viewProjection);
	}

}

//�ړ�
void Cat::Move() {


	if (direction_ == Direction::front && worldTransform_.translation_.z <= 0) {
		OnMapCollision();
	}

	if (direction_ == Direction::left && worldTransform_.translation_.x <= 0) {
		OnMapCollision();
	}

	if (direction_ == Direction::front) {
		worldTransform_.rotation_ = { 0, 135, 0 };
		move.z = -moveSpeed;
	}
	else if (direction_ == Direction::right) {
		worldTransform_.rotation_ = { 0, GetDegree(180), 0 };
		move.x = moveSpeed;
	}
	else if (direction_ == Direction::back) {
		worldTransform_.rotation_ = { 0,0, 0 };
		move.z = moveSpeed;
	}
	else if (direction_ == Direction::left) {
		worldTransform_.rotation_ = { 0, GetDegree(-180), 0 };
		move.x = -moveSpeed;
	}
	worldTransform_.translation_ += move;




}

//����������
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

				//�v���C���[�ʒu������

				if (map->map[i][j][k] == CATUP) {

					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
					move = { 0,0,0 };
					direction_ = Direction::back;
				}
				if (map->map[i][j][k] == CATLEFT) {

					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
					move = { 0,0,0 };
					direction_ = Direction::left;
				}
				if (map->map[i][j][k] == CATRIGHT) {

					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
					move = { 0,0,0 };
					direction_ = Direction::right;
				}
				if (map->map[i][j][k] == CATDOWN) {

					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
					move = { 0,0,0 };
					direction_ = Direction::front;
				}
			}
		}
	}

}


float Cat::GetDegree(float r) {
	r = (r * 180.0f) / 3.14;

	return r;
}