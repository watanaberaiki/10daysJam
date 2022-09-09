#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Matrix.h"
#include "memory"
#include "list"

enum direction {
	front,		//�O
	right,		//�E
	back,		//���
	left		//��
};

class Cat
{
public:
	//������
	void Initialize(Model* model, uint32_t textureHandle);
	
	//�X�V����
	void Update();

	//�`�揈��
	void Draw(ViewProjection viewProjection);
	
	//�ړ�
	void Move();

	//����������
	void OnMapCollision();

	//������
	void FastSpeed();

	//�ꎞ��~
	void Pause();

	//���ɖ߂�
	void Restore();

	//�Q�b�^�[
	Vector3 GetTranslation() { return worldTransform_.translation_; }
	Vector3 GetMove() { return move; }
	float GetSize() { return size; }
	float GetMoveSpeed() { return moveSpeed; }

private:
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`��
	uint32_t textureHandle_ = 0u;
	
	Input* input_ = nullptr;
	
	DebugText* debugText_ = nullptr;


	//�ړ��p�x�N�g��
	Vector3 move = { 0,0,0 };
	Vector3 roll = { 0,0,0 };
	Vector3 scale = { 0,0,0 };
	//���x
	float moveSpeed = 0.01;


	float gravity = 0.1;

	//�v���C���[�̑傫��	�{����������
	float scale_ = 0.9f;
	float size = scale_ * 2.0f;

	//����
	direction direction_ = direction::back;

	//�����`�F�b�N
	int whichdirection = 2;

	//�N�[���^�C��
	int cooltime = 0;
};
