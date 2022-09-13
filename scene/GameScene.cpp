#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("texture.jpg");
	textureHandleGround = TextureManager::Load("ground.png");
	textureHandleWall = TextureManager::Load("wall.png");
	model_ = Model::Create();
	//マップの座標の初期化
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

	//タイトルの画像
	textureHandleTitle_ = TextureManager::Load("title.png");
	textureHandleCurtain_ = TextureManager::Load("curtain.png");
	titleSprite_ = Sprite::Create(textureHandleTitle_, { 0,0 });
	titleSprite_->SetSize({ 1280,720 });
	curtainSprite_ = Sprite::Create(textureHandleCurtain_, curtainPos_);
	curtainSprite_->SetSize({ 1280,720 });


	//ステージセレクトの画像の読み込み
	textureHandleNum_[0] = TextureManager::Load("number/0.png");
	textureHandleNum_[1] = TextureManager::Load("number/1.png");
	textureHandleNum_[2] = TextureManager::Load("number/2.png");
	textureHandleNum_[3] = TextureManager::Load("number/3.png");
	textureHandleNum_[4] = TextureManager::Load("number/4.png");
	textureHandleNum_[5] = TextureManager::Load("number/5.png");
	textureHandleNum_[6] = TextureManager::Load("number/6.png");
	/*textureHandleNum_[7] = TextureManager::Load("7.png");
	textureHandleNum_[8] = TextureManager::Load("8.png");
	textureHandleNum_[9] = TextureManager::Load("9.png");*/
	for (int i = 0; i < stageVolume; i++)
	{
		//ステージセレクトスプライトの初期化
		stageSelectSprite_[i] = Sprite::Create(textureHandleNum_[i + 1], stageSelectPos_[i]);
		//スプライトの座標
		stageSelectPos_[i] = { 540 + (i * stageSlectDistance) ,200 };
		stageSelectSprite_[i]->SetPosition(stageSelectPos_[i]);
		//スプライトのサイズ
		if (i == 0)
		{
			stageSelectSca_[i] = { stageSelectScale ,stageSelectScale };
			stageSelectSprite_[i]->SetSize(stageSelectSca_[i]);
		}
		else
		{
			stageSelectSca_[i] = { stageSelectScale2 ,stageSelectScale2 };
			stageSelectSprite_[i]->SetSize(stageSelectSca_[i]);
		}
	}

	//クリア画像の読み込み
	textureHandleClear_ = TextureManager::Load("clear.png");
	stageClear_ = Sprite::Create(textureHandleClear_, { 0, 0 });

	//ステージセレクト用のモデルの座標の初期化

	map_->Loding("map/map1.csv");
	savemap_->Loding("map/map1.csv");
	//自キャラ
	Player* newPlayer = new Player();
	newPlayer->Initialize(model_, textureHandle_, map_, savemap_);
	player_.reset(newPlayer);

	//ネコ
	Cat* newCat = new Cat();
	newCat->Initialize(model_, textureHandle_);
	cat_.reset(newCat);


	//ビュープロジェクションの初期化
	viewProjection_.eye = { 0,0,-50 };
	viewProjection_.Initialize();

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//レールカメラの生成
	RailCamera* newRailCamera = new RailCamera();
	newRailCamera->Initialize(player_->GetWorldTransform());
	railCamera_.reset(newRailCamera);

	//天球
	modelSkydome_ = Model::CreateFromOBJ("Skydome", true);
	Skydome* newSkydome = new Skydome();
	newSkydome->Initialize(modelSkydome_, 100);
	skydome_.reset(newSkydome);

	//ゴール
	modelGoal_ = Model::CreateFromOBJ("homered", true);
	Goal* newGoal = new Goal();
	newGoal->Initialize(modelGoal_);
	goal_.reset(newGoal);



	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
}

void GameScene::Update()
{
	//デバッグカメラ
	debugCamera_->Update();
	//シーンごとの処理
	(this->*Scene_[scene_])();
	//天球
	skydome_->Update();
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

	if (scene_ == static_cast<size_t>(Scene::Title))
	{
		TitleDrawSprite();
	}
	else if (scene_ == static_cast<size_t>(Scene::Select))
	{
		SelectDrawSprite();
	}

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
#pragma endregion
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//シーンごとに描画を変更
	if (scene_ == static_cast<size_t>(Scene::Title))
	{
		TitleDraw();
	}
	else if (scene_ == static_cast<size_t>(Scene::Select))
	{
		SelectDraw();
	}
	else if (scene_ == static_cast<size_t>(Scene::Game))
	{
		GameDraw();
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	if (scene_ == static_cast<size_t>(Scene::Title))
	{
		TitleDrawSprite();
	}
	else if (scene_ == static_cast<size_t>(Scene::Select))
	{
		SelectDrawSprite();
	}
	else if (scene_ == static_cast<size_t>(Scene::Game)) {
		GameDrawSprite();
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

//タイトル画面の処理
void GameScene::Title()
{
	//スペースキーを押したらカーテンをおろす
	if (input_->TriggerKey(DIK_SPACE)) {
		curtainFlag = true;
	}
	//カーテンの座標移動
	if (curtainFlag)
	{
		curtainTimer++;
		curtainPos_ += {0, 720.0f / curtainTime};
		curtainSprite_->SetPosition(curtainPos_);
	}
	//タイマーが一定時間経ったらセレクトシーンへ
	if (curtainTimer >= curtainTime)
	{
		curtainTimer = 0;
		scene_ = static_cast<size_t>(Scene::Select);
	}
}
//タイトル画面の描画
void GameScene::TitleDraw()
{
	skydome_->Draw(debugCamera_->GetViewProjection());
}

void GameScene::TitleDrawSprite()
{
	titleSprite_->Draw();
	curtainSprite_->Draw();
}

//ステージセレクト画面の処理
void GameScene::Select()
{
	//カーテンの座標移動
	if (curtainFlag)
	{
		curtainTimer++;
		curtainPos_ -= {0, 720.0f / curtainTime};
		curtainSprite_->SetPosition(curtainPos_);
	}
	//タイマーが一定時間経ったらステージセレクトできるように
	if (curtainTimer >= curtainTime)
	{
		curtainTimer = 0;
		curtainFlag = false;
	}

	//arrowキーでステージセレクト
	if (input_->TriggerKey(DIK_RIGHT) && stage_ < stageVolume && select == false && curtainFlag == false) {
		oldStage_ = stage_;	//古いステージを保存
		stage_++;	//ステージを1つ進める
		select = true;
	}
	if (input_->TriggerKey(DIK_LEFT) && stage_ > 1 && select == false && curtainFlag == false) {
		oldStage_ = stage_;	//古いステージを保存
		stage_--;	//ステージを一つ戻す
		select = true;
	}

	//ステージセレクト画面のモデル移動中
	if (select == true)
	{
		//タイマー
		stageSelectTimer++;
		//ステージセレクト画面のモデルの処理
		for (int i = 0; i < stageVolume; i++)
		{
			//移動
			if (stage_ > oldStage_)
			{
				stageSelectPos_[i].x -= stageSlectDistance / stageSelectTime;
				stageSelectSprite_[i]->SetPosition(stageSelectPos_[i]);
			}
			else
			{
				stageSelectPos_[i].x += stageSlectDistance / stageSelectTime;
				stageSelectSprite_[i]->SetPosition(stageSelectPos_[i]);
			}
			//倍率の変化
			float s = stageSelectScale - stageSelectScale2;
			if (stage_ == i + 1)
			{
				stageSelectSca_[i] += {s / stageSelectTime, s / stageSelectTime};
				stageSelectSprite_[i]->SetSize(stageSelectSca_[i]);
			}
			if (stage_ > oldStage_ && stage_ == i + 2)
			{
				stageSelectSca_[i] -= {s / stageSelectTime, s / stageSelectTime};
				stageSelectSprite_[i]->SetSize(stageSelectSca_[i]);
			}
			if (stage_ < oldStage_ && stage_ == i)
			{
				stageSelectSca_[i] -= {s / stageSelectTime, s / stageSelectTime};
				stageSelectSprite_[i]->SetSize(stageSelectSca_[i]);
			}
		}
	}
	//タイマーが指定時間まで経過したらフラグを戻す
	if (stageSelectTimer > stageSelectTime)
	{
		select = false;
		stageSelectTimer = 0;
	}

	//ステージセレクトの時点でマップを読み込む
	map_->LodingSave(stage_);
	savemap_->LodingSave(stage_);
	//プレイヤーのリセット
	player_->ReSet(map_, savemap_);
	cat_->MapSet(map_);
	goal_->MapSet(map_);


	////ゴール
	//if (input_->PushKey(DIK_RETURN)) {
	//	map_->Loding("map1.csv");
	//	savemap_->Loding("map1.csv");
	//	cat_->MapSet(map_);
	//	goal_->MapSet(map_);
	//}


	//スペースキーを押したらゲームへ
	if (input_->TriggerKey(DIK_SPACE)) {
		scene_ = static_cast<size_t>(Scene::Game);
	}

	debugText_->SetPos(0, 20);
	debugText_->Printf("%d,%d",oldStage_,stage_);
}
//ステージセレクト画面の描画
void GameScene::SelectDraw()
{
	skydome_->Draw(debugCamera_->GetViewProjection());
}

void GameScene::SelectDrawSprite()
{
	for (int i = 0; i < stageVolume; i++)
	{
		stageSelectSprite_[i]->Draw();
	}
	curtainSprite_->Draw();
	//for (int i = 0; i < 2; i++)
	//{
	//	biginerSprite_[i]->Draw();
	//}
}

//ゲームの処理
void GameScene::Game()
{
	// レールカメラ
	railCamera_->Update(player_->GetWorldTransform());
	railCamera_->mode_ = static_cast<size_t>(RailCamera::Mode::standBy);

	//判定の処理
	MapCollision();

	if (isgoal == 0) {
		//プレイヤー
		player_->Update(map_);

		//ゴール
		goal_->Update();

		//ネコ
		cat_->Restore();
		if (input_->PushKey(DIK_Z)) {
			cat_->FastSpeed();
		}
		if (input_->PushKey(DIK_LSHIFT)) {
			cat_->Pause();
		}
		cat_->Update();

	}
	//ゴールしたらスペースでセレクト画面
	else if (isgoal == 1) {
		if (input_->TriggerKey(DIK_SPACE)) {
			isgoal = 0;
			if (stage_ == stageVolume) {
				scene_ = static_cast<size_t>(Scene::Select);
			}
			else {
				//次のステージ
				stage_++;
				//ステージセレクトの時点でマップを読み込む
				map_->LodingSave(stage_);
				savemap_->LodingSave(stage_);
				//プレイヤーのリセット
				player_->ReSet(map_, savemap_);
				cat_->MapSet(map_);
				goal_->MapSet(map_);
			}
		}
	}
	//Rでセレクト画面へ戻る
	if (input_->TriggerKey(DIK_R)) {
		scene_ = static_cast<size_t>(Scene::Select);
		oldStage_ = 0;
		stage_ = 1;
		isgoal = 0;
	}
}

//ゲームの描画
void GameScene::GameDraw()
{
	skydome_->Draw(railCamera_->GetViewProjection());
	//マップの描画
	for (int i = 0; i < blockY; i++)
	{
		for (int j = 0; j < blockZ; j++)
		{
			for (int k = 0; k < blockX; k++)
			{
				if (savemap_->map[i][j][k] == 1)
				{
					if (i == 1) {
						model_->Draw(worldTransform_[i][j][k], railCamera_->GetViewProjection(), textureHandleWall);
					}
					else {
						model_->Draw(worldTransform_[i][j][k], railCamera_->GetViewProjection(), textureHandleGround);
					}
				}
			}
		}
	}
	//プレイヤーの描画
	player_->Draw(railCamera_->GetViewProjection());
	//猫の描画
	cat_->Draw(railCamera_->GetViewProjection());
	//ゴールの描画
	goal_->Draw(railCamera_->GetViewProjection());

}

void GameScene::GameDrawSprite() {
	if (isgoal == 1) {
		stageClear_->Draw();
	}
}

//メンバ関数のポインタテーブル
void (GameScene::* GameScene::Scene_[])() =
{
	&GameScene::Title,
	&GameScene::Select,
	&GameScene::Game,
};

//判定
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
	float downCat = cat_->GetTranslation().y;
	float frontCat = cat_->GetTranslation().z;
	float rightCat = cat_->GetTranslation().x + cat_->GetSize();
	float upCat = cat_->GetTranslation().y - cat_->GetSize();
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

	////////
	//ネコ//
	///////

	////////
	//ネコ//
	///////

	//右に仮想的に移動して当たったら
	if (map_->mapcol(rightCat + cat_->GetMoveSpeed(), downCat + cat_->GetSize() / 2, frontCat + 0.1) || map_->mapcol(rightCat + cat_->GetMoveSpeed(), downCat + cat_->GetSize() / 2, backCat - 0.1))
	{
		if (cat_->GetDirection() == Direction::right) {
			cat_->OnMapCollision();
		}
	}
	//穴判定
	else if (map_->mapcol(rightCat + cat_->GetMoveSpeed(), downCat - cat_->GetSize() / 2, frontCat + 0.1) != BLOCK || map_->mapcol(rightCat + cat_->GetMoveSpeed(), downCat - cat_->GetSize() / 2, backCat - 0.1) != BLOCK) {
		if (cat_->GetDirection() == Direction::right) {
			cat_->OnMapCollision();
		}
	}

	//左に仮想的に移動して当たったら
	if (map_->mapcol(leftCat - cat_->GetMoveSpeed(), downCat + cat_->GetSize() / 2, frontCat + 0.1) || map_->mapcol(leftCat - cat_->GetMoveSpeed(), downCat + cat_->GetSize() / 2, backCat - 0.1))
	{
		if (cat_->GetDirection() == Direction::left) {
			cat_->OnMapCollision();
		}
	}
	//穴判定
	else if (map_->mapcol(leftCat - cat_->GetMoveSpeed() - blockSize, downCat - cat_->GetSize() / 2, frontCat + 0.1) == BLOCK || map_->mapcol(leftCat - cat_->GetMoveSpeed() - blockSize, downCat - cat_->GetSize() / 2, backCat - 0.1) == BLOCK) {

		if (map_->mapcol(leftCat - cat_->GetMoveSpeed(), downCat - cat_->GetSize() / 2, frontCat + 0.1) != BLOCK || map_->mapcol(leftCat - cat_->GetMoveSpeed(), downCat - cat_->GetSize() / 2, backCat - 0.1) != BLOCK) {

			if (cat_->GetDirection() == Direction::left) {
				cat_->OnMapCollision();
			}
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
	if (map_->mapcol(leftCat + 0.1, downCat + cat_->GetSize() / 2, backCat + cat_->GetMoveSpeed()) || map_->mapcol(rightCat - 0.1, downCat + cat_->GetSize() / 2, backCat + cat_->GetMoveSpeed()))
	{
		if (cat_->GetDirection() == Direction::back) {
			cat_->OnMapCollision();
		}
	}
	//穴判定
	else if (map_->mapcol(leftCat + 0.1, downCat - cat_->GetSize() / 2, backCat + cat_->GetMoveSpeed()) != BLOCK || map_->mapcol(rightCat - 0.1, downCat - cat_->GetSize() / 2, backCat + cat_->GetMoveSpeed()) != BLOCK) {

		if (cat_->GetDirection() == Direction::back) {
			cat_->OnMapCollision();
		}
	}

	//手前に仮想的に移動して当たったら
	if (map_->mapcol(leftCat + 0.1, downCat + cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed()) || map_->mapcol(rightCat - 0.1, downCat + cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed()))
	{
		if (cat_->GetDirection() == Direction::front) {
			cat_->OnMapCollision();
		}
	}
	//穴判定
	else if (map_->mapcol(leftCat + 0.1, downCat - cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed() - blockSize) == BLOCK || map_->mapcol(rightCat - 0.1, downCat - cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed() - blockSize) == BLOCK) {

		if (map_->mapcol(leftCat + 0.1, downCat - cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed()) != BLOCK || map_->mapcol(rightCat - 0.1, downCat - cat_->GetSize() / 2, frontCat - cat_->GetMoveSpeed()) != BLOCK) {

			if (cat_->GetDirection() == Direction::front) {
				cat_->OnMapCollision();
			}
		}
	}

	//ゴール判定
	if (leftCat) {
		if (goal_->GetTranslation().x - 1 < cat_->GetTranslation().x + (cat_->GetSize() / 2) && cat_->GetTranslation().x - (cat_->GetSize() / 2) < goal_->GetTranslation().x + 1) {
			if (goal_->GetTranslation().z - 1 < cat_->GetTranslation().z + (cat_->GetSize() / 2) && cat_->GetTranslation().z - (cat_->GetSize() / 2) < goal_->GetTranslation().z + 1) {
				isgoal = 1;
			}
		}
	}

	//自機と猫

	Vector3 playerPos = Vector3(player_->GetPosNum().x * blockSize, player_->GetPosNum().y * blockSize, player_->GetPosNum().z * blockSize);

	Vector3 catPos = cat_->GetTranslation();


	if (playerPos.x - (player_->GetSize() / 2) < catPos.x + (cat_->GetSize() / 2) && catPos.x - (cat_->GetSize() / 2) < playerPos.x + (player_->GetSize() / 2)) {

		if (playerPos.z - (player_->GetSize() / 2) < catPos.z + (cat_->GetSize() / 2) && catPos.z - (cat_->GetSize() / 2) < playerPos.z + (player_->GetSize() / 2)) {

			player_->RockBecomeBlock();

		}
		else {
			player_->RockLiftBlock();
		}
	}
	else {
		player_->RockLiftBlock();
	}
}