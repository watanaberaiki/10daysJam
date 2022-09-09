#include "Cat.h"
#include <cassert>


//������
void Cat::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { scale_,scale_,scale_ };
	worldTransform_.translation_ = { 4,2,0 };

}

//�X�V����
void Cat::Update() {
	Move();

	worldTransformUpdate(&worldTransform_);
}

//�`�揈��
void Cat::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//�ړ�
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

//����������
void Cat::OnMapCollision() {
	if (direction_ == Direction::front) {
		direction_ = Direction::right;
		worldTransform_.translation_.z += 0.05;
		move = { 0,0,0 };
		whichdirection = 1;
	}
	else if (direction_ == Direction::right) {
		direction_ = Direction::back;
		worldTransform_.translation_.x -= 0.05;
		move = { 0,0,0 };
		whichdirection = 2;
	}
	else if (direction_ == Direction::back) {
		direction_ = Direction::left;
		worldTransform_.translation_.z -= 0.05;
		move = { 0,0,0 };
		whichdirection = 3;
	}
	else if (direction_ == Direction::left) {
		direction_ = Direction::front;
		worldTransform_.translation_.x += 0.05;
		move = { 0,0,0 };
		whichdirection = 0;
	}
}

void Cat::FastSpeed() {
	moveSpeed = 0.05;
}

void Cat::Restore() {
	moveSpeed = 0.01;
}

void Cat::Pause() {
	moveSpeed = 0;
}