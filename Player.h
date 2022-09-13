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
#define PI 3.141592653589

class Player
{
public:
	void Initialize(Model* model, uint32_t textureHandle, Map* map, Map* savemap);
	void Update(Map* map);
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
	void MoveStopX() { mSpeed[0] = 0.0f; };
	void MoveStopY() { mSpeed[1] = 0.0f; };
	void MoveStopZ() { mSpeed[2] = 0.0f; };

	//ゲッター
	WorldTransform GetWorldTransform() { return worldTransform_; }
	Vector3 GetTranslation() { return worldTransform_.translation_; }
	Vector3 GetMove() { return move; }
	float GetSize() { return size; }
	//追加部分↓

public:

	//ブロック関係の処理まとめ
	void BlockManager(Map* map);

	//ブロックになる処理
	void BecomeBlock(Map* map);

	//ブロックを解除する処理
	void LiftBlock(Map* map);

	//位置取得
	Vector3 PositionAcquisition();

	void RockBecomeBlock();
	void RockLiftBlock();

	Vector3 GetPosNum();

	void ReSet(Map* map, Map* savemap);

private:

	//ブロック化しているか 0,してない　1,してる 2,ステージ変更時の初期化処理
	int block = 0;

	//flag 通ったか
	int becomeBlock = 0;
	int liftBlock = 0;

	//　ブロックが下に下がっているか
	int downBlock = 0;
	//　ブロック化出来るか出来ないか 0出来る 1出来ない
	int rockBlock = 0;

	////map取得用
	//int map[blockY][blockZ][blockX] = {};

	//↑

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	uint32_t redTexture_ = 0u;
	uint32_t blueTexture_ = 0u;
	uint32_t blackTexture_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	//移動用ベクトル
	Vector3 move = { 0,0,0 };
	Vector3 roll = { 0,0,0 };
	Vector3 scale = { 0,0,0 };
	//速度
	float moveSpeed = 0.19;
	float mSpeed[3];
	float rollSpeed = 0.02 * PI;
	float scaleSpeed = 0.1;
	float gravity = 0.1;

	int moveCoolTime = 10;
	int moveTimer = 0;

	int keyCoolTime = 20;
	int keyTimer = 0;

	//プレイヤーの大きさ	倍率をいじる
	float scale_ = 0.99f;
	float size = scale_ * 2.0f;

	Vector3 posNum;

	int posNumX;
	int posNumY;
	int posNumZ;

};