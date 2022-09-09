#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	redTexture_ = TextureManager::Load("red.png");
	blueTexture_ = TextureManager::Load("blue.png");


	//�V���O���g���C���X�^���X���擾����
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

			//arow�L�[�ňړ�
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

//�u���b�N�֌W�̏����܂Ƃ�
void Player::BlockManager(Map *map) {

	//�X�e�[�W�X�^�[�g���̏���������
	if (block == 2) {
		block = 0;

		//map_->SetMap();

		//Map���擾
		for (int i = 0; i < blockY; i++)
		{
			for (int j = 0; j < blockZ; j++)
			{
				for (int k = 0; k < blockX; k++) {

					//�v���C���[�ʒu������

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

//�u���b�N�ɂȂ鏈��
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

//�u���b�N���������鏈��
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

//�ʒu�擾
Vector3 Player::PositionAcquisition() {

	//�ʒu��񂩂�}�b�v�`�b�v�̔ԍ����Z�o	
	Vector3 playerPosNum(0, 0, 0);

	playerPosNum.x = worldTransform_.translation_.x / blockSize;
	playerPosNum.y = worldTransform_.translation_.y / blockSize;
	playerPosNum.z = worldTransform_.translation_.z / blockSize;

	return playerPosNum;
}