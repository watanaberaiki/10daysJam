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
#include "Map.h"

class Goal
{
public:
	//������
	void Initialize(Model* model);

	//�`�揈��
	void Draw(ViewProjection viewProjection);

	//�X�V
	void Update();

	//�}�b�v�Z�b�g
	void MapSet(Map* map);

	//�Q�b�^�[
	Vector3 GetTranslation() { return worldTransform_.translation_; }

private:

	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;

	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;


};

