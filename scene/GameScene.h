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
#include "DebugCamera.h"
#include "Matrix.h"
#include "list"
#include "Player.h"
#include "Map.h"
#include "Cat.h"
#include "math.h"
#include "RailCamera.h"
#include "Goal.h"
#include "Skydome.h"
#include "Tutorial.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//当たり判定
	void MapCollision();

	//シーンごとの処理
	void Title();
	void Select();
	void Game();
	//シーンごとの描画処理
	void TitleDraw();
	void TitleDrawSprite();
	void SelectDraw();
	void SelectDrawSprite();
	void GameDraw();
	void GameDrawSprite();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	Model* model_;

	//ビュープロジェクション
	ViewProjection viewProjection_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	uint32_t textureHandleGround = 0;

	uint32_t textureHandleWall = 0;
	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//レールカメラ
	std::unique_ptr<RailCamera>railCamera_;

	//プレイヤー
	std::unique_ptr<Player> player_;

	//ネコ
	std::unique_ptr<Cat> cat_;
	Model* modelCat_;
	Model* modelCatWalk_;
	Model* modelCatWalkReverse_;

	//マップ
	Map* map_ = new Map;
	Map* savemap_ = new Map;
	//マップの座標
	WorldTransform worldTransform_[10][10][10];
	Map* map[blockY][blockZ][blockX] = {};

	//シーン
	enum class Scene
	{
		Title,	//タイトル
		Select,	//ステージ選択
		Game	//操作
	};
	//シーン	最初がタイトル
	size_t scene_ = static_cast<size_t>(Scene::Title);
	//メンバ関数のポインタテーブル
	static void (GameScene::* Scene_[])();

	//タイトル関連
	//テクスチャハンドル
	uint32_t textureHandleTitle_;
	uint32_t textureHandleCurtain_;
	//スプライト
	Sprite* titleSprite_;
	Sprite* curtainSprite_;
	//カーテンの座標
	Vector2  curtainPos_{ 0,-720 };
	//カーテンのタイマー
	float curtainTimer = 0.0f;
	float curtainTime = 60.0f;
	//フラグ
	bool curtainFlag = false;

	//ステージ関連
	int32_t stage_ = 1;	//現在のステージを保存しておくための変数
	static const int stageVolume = 6;	//ステージの総数
	//ステージセレクト画面
	int32_t oldStage_;	//保存用の変数
	WorldTransform worldTransformStageSelect_[stageVolume];	//ステージセレクト画面用の座標
	float stageSlectDistance = 300.0f;	//ステージセレクト画面の隣のオブジェクトとの距離
	float stageSelectScale = 200.0f;	//現在のステージのモデルの大きさ
	float stageSelectScale2 = 100.0f;	//他のステージのモデルの大きさ
	float stageSelectTimer = 0.0f;	//ステージセレクト用のタイマー
	float stageSelectTime = 60.0f;	//ステージセレクト用にかかる時間
	bool select = false;	//モデルが移動中かのフラグ
	//テクスチャハンドル
	uint32_t textureHandleNum_[stageVolume + 1];
	//スプライト
	Sprite* stageSelectSprite_[stageVolume + 1];
	//初心者マークのテクスチャハンドル
	uint32_t textureHandleBiginer_;
	//初心者マークのスプライト
	Sprite* biginerSprite_[2];
	//スプライトの座標
	Vector2 stageSelectPos_[stageVolume + 1];
	Vector2 stageSelectSca_[stageVolume + 1];

	//テクスチャハンドル
	uint32_t textureHandleClear_ = 0;
	//ステージクリアスプライト
	Sprite* stageClear_=0;

	//ゴール
	std::unique_ptr<Goal> goal_;
	Model* modelGoal_;
	int isgoal = 0;

	//天球
	std::unique_ptr<Skydome>skydome_;
	Model* modelSkydome_;

	Tutorial* tutorial_;
};