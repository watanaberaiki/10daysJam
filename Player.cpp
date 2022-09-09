#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	redTexture_ = TextureManager::Load("red.png");
	blueTexture_ = TextureManager::Load("blue.png");


	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.scale_ = { scale_,scale_,scale_ };
	worldTransform_.translation_ = { 0,10,0 };

}

void Player::Update(Map *map)
{
	Move();
	/*worldTransform_.translation_.y -= gravity;*/
	worldTransformUpdate(&worldTransform_);

	BlockManager(map);

}

void Player::Draw(ViewProjection viewProjection)
{
	if (becomeBlock == 1) {
		model_->Draw(worldTransform_, viewProjection, redTexture_);
	}
	else
	{
		model_->Draw(worldTransform_, viewProjection, blueTexture_);
	}

}

void Player::Move()
{

	if (becomeBlock == 0) {

		moveTimer++;

		if (moveTimer >= moveCoolTime) {

			//arowキーで移動
			if (input_->PushKey(DIK_LEFT))
			{
				move.x = -mSpeed[0];
			}
			else if (input_->PushKey(DIK_RIGHT))
			{
				move.x = mSpeed[0];
			}
			else
			{
				move.x = 0;
			}
			if (input_->PushKey(DIK_DOWN))
			{
				move.z = -mSpeed[2];
			}
			else if (input_->PushKey(DIK_UP))
			{
				move.z = mSpeed[2];
			}
			else
			{
				move.z = 0;
			}
			/*mSpeed[1] = -gravity;*/
			//move.y = mSpeed[1];

			worldTransform_.translation_ += move;
			moveTimer = 0;
		}

	}
}

void Player::OnMapCollision()
{
}

void Player::OnMapCollisionX()
{
	worldTransform_.translation_.x += 0.1;
}

void Player::OnMapCollisionY()
{
	worldTransform_.translation_.y += 0.1;
}

void Player::OnMapCollisionZ()
{
	worldTransform_.translation_.z += 0.1;
}

void Player::OnMapCollisionX2()
{
	worldTransform_.translation_.x -= 0.1;
}

void Player::OnMapCollisionY2()
{
	worldTransform_.translation_.y -= 0.1;
}

void Player::OnMapCollisionZ2()
{
	worldTransform_.translation_.z -= 0.1;
}

void Player::MoveSpeedSet()
{
	mSpeed[0] = moveSpeed;
	mSpeed[1] = -gravity;
	mSpeed[2] = moveSpeed;
}

//ブロック関係の処理まとめ
void Player::BlockManager(Map *map) {

	//ステージスタート時の初期化処理
	if (block == 2) {
		block = 0;

		//map_->SetMap();

		//Map情報取得
		for (int i = 0; i < blockY; i++)
		{
			for (int j = 0; j < blockZ; j++)
			{
				for (int k = 0; k < blockX; k++) {

					//プレイヤー位置初期化

					if (map->map[i][j][k] == PLAYER) {

						worldTransform_.translation_.x = blockSize * k;
						worldTransform_.translation_.y = blockSize * i;
						worldTransform_.translation_.z = blockSize * j;

					}
				}
			}
		}



	}

	keyTimer++;

	if (block == 0) {
		if (liftBlock == 0) {
			LiftBlock(map);
		}
		else {
			if (keyTimer >= keyCoolTime) {
				if (input_->PushKey(DIK_SPACE)) {
					block = 1;
					liftBlock = 0;
					keyTimer = 0;

				}
			}
		}
	}
	else {
		if (becomeBlock == 0) {
			BecomeBlock(map);
		}
		else {
			if (keyTimer >= keyCoolTime) {
				if (input_->PushKey(DIK_SPACE)) {
					block = 0;
					becomeBlock = 0;
					keyTimer = 0;
				}
			}
		}
	}


	posNum = PositionAcquisition();

	posNumX = (posNum.x + 0.5);
	posNumY = (posNum.y + 0.5);
	posNumZ = (posNum.z + 0.5);

	debugText_->SetPos(0, 60);
	debugText_->Printf("%f,%f,%f", posNum.x, posNum.y, posNum.z);

	debugText_->SetPos(0, 80);
	debugText_->Printf("%d,%d,%d", posNumX, posNumY, posNumZ);

}

//ブロックになる処理
void  Player::BecomeBlock(Map* map) {

	becomeBlock = 1;

	worldTransform_.translation_.x = (posNumX * blockSize);
	worldTransform_.translation_.z = (posNumZ * blockSize);

	if (map->map[0][posNumZ][posNumX] == BLUNK) {
		downBlock = 1;
		worldTransform_.translation_.y -= blockSize;
		map->map[0][posNumZ][posNumX] = BLOCK;
	}
	else {
		map->map[1][posNumZ][posNumX] = BLOCK;
	}
}

//ブロックを解除する処理
void Player::LiftBlock(Map *map) {

	liftBlock = 1;

	if (downBlock == 1) {
		downBlock = 0;
		worldTransform_.translation_.y += blockSize;

		map->map[0][posNumZ][posNumX] = BLUNK;
	}
	else {
		map->map[1][posNumZ][posNumX] = BLUNK;
	}

}

//位置取得
Vector3 Player::PositionAcquisition() {

	//位置情報からマップチップの番号を算出	
	Vector3 playerPosNum(0, 0, 0);

	playerPosNum.x = worldTransform_.translation_.x / blockSize;
	playerPosNum.y = worldTransform_.translation_.y / blockSize;
	playerPosNum.z = worldTransform_.translation_.z / blockSize;

	return playerPosNum;
}