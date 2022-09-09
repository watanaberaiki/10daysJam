#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("texture.jpg");
	textureHandle2 = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
	for (int i = 0; i < blockY; i++)
	{
		for (int j = 0; j < blockZ; j++)
		{
			for (int k = 0; k < blockX; k++)
			{
				worldTransform_[i][j][k].Initialize();
				worldTransform_[i][j][k].translation_.x = k * blockSize * blockScale;
				worldTransform_[i][j][k].translation_.y = i * blockSize * blockScale;
				worldTransform_[i][j][k].translation_.z = j * blockSize * blockScale;
				worldTransform_[i][j][k].scale_ = { blockScale,blockScale,blockScale };
				worldTransformUpdate(&worldTransform_[i][j][k]);
			}
		}
	}

	//自キャラ
	Player* newPlayer = new Player();
	newPlayer->Initialize(model_, textureHandle_);
	player_.reset(newPlayer);

	//ネコ
	Cat* newCat = new Cat();
	newCat->Initialize(model_, textureHandle_);
	cat_.reset(newCat);

	map_->Loding("map1.csv");
	savemap_->Loding("map1.csv");

	//ビュープロジェクションの初期化
	viewProjection_.eye = { 0,0,-50 };
	viewProjection_.Initialize();



	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
}

void GameScene::Update()
{


	MapCollision();

	//プレイヤー
	player_->Update(map_);
	
	//デバッグカメラ
	debugCamera_->Update();


	//ネコ
	cat_->Restore();

	if (input_->PushKey(DIK_Z)) {
		cat_->FastSpeed();
	}

	if (input_->PushKey(DIK_LSHIFT)) {
		cat_->Pause();
	}
	cat_->Update();

	if (input_->PushKey(DIK_RETURN)) {
		cat_->MapSet(map_);
	}

	////マップ
	//map_->SetMap(0);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	for (int i = 0; i < blockY; i++)
	{
		for (int j = 0; j < blockZ; j++)
		{
			for (int k = 0; k < blockX; k++)
			{
				if (savemap_->map[i][j][k] == 1)
				{
					model_->Draw(worldTransform_[i][j][k], debugCamera_->GetViewProjection(), textureHandle2);
				}
			}
		}
	}
	player_->Draw(debugCamera_->GetViewProjection());

	cat_->Draw(debugCamera_->GetViewProjection());
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::MapCollision()
{


	//座標を用意
	float leftplayer = player_->GetTranslation().x;
	float downplayer = player_->GetTranslation().y;
	float frontplayer = player_->GetTranslation().z;
	float rightplayer = player_->GetTranslation().x + player_->GetSize();
	float upplayer = player_->GetTranslation().y - player_->GetSize();
	float backplayer = player_->GetTranslation().z + player_->GetSize();

	float leftCat = cat_->GetTranslation().x;
	float downCat = cat_->GetTranslation().y- cat_->GetSize();
	float frontCat = cat_->GetTranslation().z;
	float rightCat = cat_->GetTranslation().x + cat_->GetSize();
	float upCat = cat_->GetTranslation().y ;
	float backCat = cat_->GetTranslation().z + cat_->GetSize();

	player_->MoveSpeedSet();

	/////////////
	//プレイヤー//
	/////////////

	//右に仮想的に移動して当たったら
	if (savemap_->mapcol(rightplayer, downplayer + player_->GetSize() / 2, frontplayer + 0.2) || savemap_->mapcol(rightplayer, downplayer + player_->GetSize() / 2, backplayer - player_->GetSize() / 2) && player_->GetMove().x > 0)
	{
		//１ピクセル先に壁が来るまで移動
		while ((savemap_->mapcol(rightplayer, downplayer + player_->GetSize() / 2, frontplayer + 0.2) || savemap_->mapcol(rightplayer, downplayer + player_->GetSize() / 2, backplayer - player_->GetSize() / 2)))
		{
			player_->OnMapCollisionX2();
			rightplayer = player_->GetTranslation().x + player_->GetSize();
			leftplayer = player_->GetTranslation().x;
		}
	}

	//左に仮想的に移動して当たったら
	if (savemap_->mapcol(leftplayer, downplayer + player_->GetSize() / 2, frontplayer + 0.2) || savemap_->mapcol(leftplayer, downplayer + player_->GetSize() / 2, backplayer - player_->GetSize() / 2) && player_->GetMove().x < 0)
	{
		//１ピクセル先に壁が来るまで移動
		while ((savemap_->mapcol(leftplayer, downplayer + player_->GetSize() / 2, frontplayer + 0.2) || savemap_->mapcol(leftplayer, downplayer + player_->GetSize() / 2, backplayer - player_->GetSize() / 2)))
		{
			player_->OnMapCollisionX();
			rightplayer = player_->GetTranslation().x + player_->GetSize();
			leftplayer = player_->GetTranslation().x;
		}
	}
	leftplayer = player_->GetTranslation().x;
	rightplayer = player_->GetTranslation().x + player_->GetSize();

	////y軸に対しての当たり判定
	////上に仮想的に移動して当たったら
	//if (map_->mapcol(left, up, front))
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((map_->mapcol(left, up, front)))
	//	{
	//		player_->OnMapCollisionY2();
	//		up = player_->GetTranslation().y - player_->GetSize();
	//		down = player_->GetTranslation().y;
	//	}
	//}

	//下に仮想的に移動して当たったら
	if (savemap_->mapcol(leftplayer, downplayer, frontplayer + 0.2))
	{
		//１ピクセル先に壁が来るまで移動
		while ((savemap_->mapcol(leftplayer, downplayer, frontplayer + 0.2)))
		{
			player_->OnMapCollisionY();
			upplayer = player_->GetTranslation().y - player_->GetSize();
			downplayer = player_->GetTranslation().y;
		}
	}
	upplayer = player_->GetTranslation().y - player_->GetSize();
	downplayer = player_->GetTranslation().y;


	//z軸に対しての当たり判定
	//奥に仮想的に移動して当たったら
	if (savemap_->mapcol(leftplayer, downplayer + player_->GetSize() / 2, backplayer) || savemap_->mapcol(rightplayer, downplayer + player_->GetSize() / 2, backplayer) && player_->GetMove().z > 0)
	{
		//１ピクセル先に壁が来るまで移動
		while ((savemap_->mapcol(leftplayer, downplayer + player_->GetSize() / 2, backplayer) || savemap_->mapcol(rightplayer, downplayer + player_->GetSize() / 2, backplayer)))
		{
			player_->OnMapCollisionZ2();
			frontplayer = player_->GetTranslation().z;
			backplayer = player_->GetTranslation().z + player_->GetSize();
		}
	}
	//手前に仮想的に移動して当たったら
	if (savemap_->mapcol(leftplayer, downplayer, frontplayer) || savemap_->mapcol(rightplayer, downplayer, frontplayer) && player_->GetMove().z < 0)
	{
		//１ピクセル先に壁が来るまで移動
		while ((savemap_->mapcol(leftplayer, downplayer, frontplayer - 0.2) || savemap_->mapcol(rightplayer, downplayer, frontplayer - 0.2)))
		{
			player_->OnMapCollisionZ();
			frontplayer = player_->GetTranslation().z;
			backplayer = player_->GetTranslation().z + player_->GetSize();
		}
	}

	debugText_->SetPos(0, 0);
	debugText_->Printf("%d,%d", frontplayer, backplayer);



	////////
	//ネコ//
	///////

	//右に仮想的に移動して当たったら
	if (map_->mapcol(rightCat + cat_->GetMoveSpeed(), downCat + cat_->GetSize() / 2, frontCat + 0.1) || map_->mapcol(rightCat + cat_->GetMoveSpeed(), downCat + cat_->GetSize() / 2, backCat - 0.1) && cat_->GetMove().x > 0)
	{
		cat_->OnMapCollision();
	}
	//穴判定
	else if (map_->mapcol(rightCat + cat_->GetMoveSpeed(), downCat - cat_->GetSize() / 2, frontCat + 0.1) != BLOCK || map_->mapcol(rightCat + cat_->GetMoveSpeed(), downCat - cat_->GetSize() / 2, backCat - 0.1) != BLOCK ) {
		if (cat_->GetMove().x > 0) {
			cat_->OnMapCollision();
		}
	}

	//左に仮想的に移動して当たったら
	if (map_->mapcol(leftCat - cat_->GetMoveSpeed(), downCat + cat_->GetSize() / 2, frontCat + 0.1) || map_->mapcol(leftCat - cat_->GetMoveSpeed(), downCat + cat_->GetSize() / 2, backCat - 0.1) && cat_->GetMove().x < 0)
	{
		cat_->OnMapCollision();
	}
	//穴判定
	else if (map_->mapcol(leftCat - cat_->GetMoveSpeed() - blockSize, downCat - cat_->GetSize() / 2, frontCat + 0.1) != BLOCK || map_->mapcol(leftCat - cat_->GetMoveSpeed() - blockSize, downCat - cat_->GetSize() / 2, backCat - 0.1) != BLOCK) {
		if (cat_->GetMove().x < 0) {
			cat_->OnMapCollision();
		}
	}

	////y軸に対しての当たり判定
	////上に仮想的に移動して当たったら
	//if (map_->mapcol(left, up, front))
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((map_->mapcol(left, up, front)))
	//	{
	//		player_->OnMapCollisionY2();
	//		up = player_->GetTranslation().y - player_->GetSize();
	//		down = player_->GetTranslation().y;
	//	}
	//}

	////下に仮想的に移動して当たったら
	//if (map_->mapcol(leftCat, downCat, frontCat + 0.1))
	//{
	//	//１ピクセル先に壁が来るまで移動
	//	while ((map_->mapcol(leftCat, downCat, frontCat + 0.1)))
	//	{
	//		upCat = cat_->GetTranslation().y - cat_->GetSize();
	//		downCat = cat_->GetTranslation().y;
	//	}
	//}
	//upCat = cat_->GetTranslation().y - cat_->GetSize();
	//downCat = cat_->GetTranslation().y;


	//z軸に対しての当たり判定
	//奥に仮想的に移動して当たったら
	if (map_->mapcol(leftCat, downCat + cat_->GetSize() / 2, backCat + cat_->GetMoveSpeed()) || map_->mapcol(rightCat, downCat + cat_->GetSize() / 2, backCat + cat_->GetMoveSpeed()) && cat_->GetMove().z > 0)
	{
		cat_->OnMapCollision();
	}
	//穴判定
	else if (map_->mapcol(leftCat , downCat - cat_->GetSize() / 2, backCat + cat_->GetMoveSpeed()) != BLOCK || map_->mapcol(rightCat , downCat - cat_->GetSize() / 2, backCat + cat_->GetMoveSpeed()) != BLOCK ) {

		if (cat_->GetMove().z > 0) {
			cat_->OnMapCollision();
		}
	}

	//手前に仮想的に移動して当たったら
	if (map_->mapcol(leftCat, downCat + cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed()) || map_->mapcol(rightCat, downCat + cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed()) && cat_->GetMove().z < 0)
	{
		cat_->OnMapCollision();
	}
	//穴判定
	else if (map_->mapcol(leftCat, downCat - cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed() - blockSize) != BLOCK || map_->mapcol(rightCat , downCat - cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed() - blockSize) != BLOCK) {
		if (cat_->GetMove().z < 0) {
			cat_->OnMapCollision();
		}
	}
}
