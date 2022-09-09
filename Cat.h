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

enum class Direction {
	front,		//前
	right,		//右
	back,		//後ろ
	left		//左
};

class Cat
{
public:
	//初期化
	void Initialize(Model* model, uint32_t textureHandle);
	
	//更新処理
	void Update();

	//描画処理
	void Draw(ViewProjection viewProjection);
	
	//移動
	void Move();

	//当たったら
	void OnMapCollision();

	//早送り
	void FastSpeed();

	//一時停止
	void Pause();

	//元に戻す
	void Restore();

	void MapSet(Map* map);

	//ゲッター
	Vector3 GetTranslation() { return worldTransform_.translation_; }
	Vector3 GetMove() { return move; }
	float GetSize() { return size; }
	float GetMoveSpeed() { return moveSpeed; }
	Direction GetDirection() { return direction_; }

private:
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャ
	uint32_t textureHandle_ = 0u;
	
	Input* input_ = nullptr;
	
	DebugText* debugText_ = nullptr;


	//移動用ベクトル
	Vector3 move = { 0,0,0 };
	Vector3 roll = { 0,0,0 };
	Vector3 scale = { 0,0,0 };
	//速度
	float moveSpeed;

	//プレイヤーの大きさ	倍率をいじる
	float scale_ = 0.8f;
	float size = scale_ * 2.0f;

	//方向
	Direction direction_=Direction::back;

	//方向チェック
	int whichdirection = 2;

	//クールタイム
	int cooltime = 0;
};

