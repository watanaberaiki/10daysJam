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
#define PI 3.141592653589

class Player
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);
	void Move();

	void OnMapCollision();
	void OnMapCollisionX();
	void OnMapCollisionY();
	void OnMapCollisionZ();
	void OnMapCollisionX2();
	void OnMapCollisionY2();
	void OnMapCollisionZ2();
	
	void MoveSpeedSet();
	void MoveStopX(){mSpeed[0] = 0.0f;};
	void MoveStopY(){mSpeed[1] = 0.0f;};
	void MoveStopZ() { mSpeed[2] = 0.0f; };

	//ゲッター
	Vector3 GetTranslation() { return worldTransform_.translation_; }
	Vector3 GetMove() { return move; }
	float GetSize() { return size; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//移動用ベクトル
	Vector3 move = { 0,0,0 };
	Vector3 roll = { 0,0,0 };
	Vector3 scale = { 0,0,0 };
	//速度
	float moveSpeed = 0.2;
	float mSpeed[3];
	float rollSpeed = 0.02 * PI;
	float scaleSpeed = 0.1;
	float gravity = 0.1;

	//プレイヤーの大きさ	倍率をいじる
	float scale_ = 0.9f;
	float size = scale_ * 2.0f;


};




