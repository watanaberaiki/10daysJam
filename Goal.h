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
	//初期化
	void Initialize(Model* model);

	//描画処理
	void Draw(ViewProjection viewProjection);

	//更新
	void Update();

	//マップセット
	void MapSet(Map* map);

	//ゲッター
	Vector3 GetTranslation() { return worldTransform_.translation_; }

private:

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;


};

