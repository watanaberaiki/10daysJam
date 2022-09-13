#include "Goal.h"
#include <cassert>


//初期化
void Goal::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
}

//更新
void Goal::Update() {
	worldTransformUpdate(&worldTransform_);
}

//描画処理
void  Goal::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//マップセット
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
