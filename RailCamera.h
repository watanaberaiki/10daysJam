#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "vector"
#include "list"
#define PI 3.141592653589

class RailCamera
{
public:
	void Initialize(WorldTransform worldTransform);
	void Update(WorldTransform worldTransform);
	//モードを切り替える
	void modeManager();
	//モード
	void standBy();
	void Approach();	//接近、導入
	void Homing();		//追従
	void Operarion();	//操作
	//ゲッター
	ViewProjection GetViewProjection() { return viewProjection_; }
private:
	ViewProjection viewProjection_;
	WorldTransform worldTransform_;	//プレイヤーのワールドトランスフォーム
	//自機とカメラの距離
	float length = 20.0f;
	//カメラの角度
	float angleY = 0.3 * PI;	float angleX = 0.3 * PI;
	//接近モード用のタイマー
	//ゲーム中の処理
	float gameStartTimer = 0;
	float gameStartTime = 120;

public:
	//モード
	enum class Mode
	{
		standBy,	//待機
		Approach,	//接近、導入
		Horming,	//カメラ追従
		Operation	//操作
	};
	//モード
	size_t mode_ = static_cast<size_t>(Mode::standBy);
	//メンバ関数のポインタテーブル
	static void (RailCamera::* Mode_[])();
};