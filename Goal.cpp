#include "Goal.h"
#include <cassert>


//������
void Goal::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
}

//�X�V
void Goal::Update() {
	worldTransformUpdate(&worldTransform_);
}

//�`�揈��
void  Goal::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//�}�b�v�Z�b�g
void  Goal::MapSet(Map* map) {
	for (int i = 0; i < blockY; i++)
	{
		for (int j = 0; j < blockZ; j++)
		{
			for (int k = 0; k < blockX; k++) {
				if (map->map[i][j][k] == GOAL) {
					worldTransform_.translation_.x = blockSize * k;
					worldTransform_.translation_.y = blockSize * i;
					worldTransform_.translation_.z = blockSize * j;
				}
			}
		}
	}
}
