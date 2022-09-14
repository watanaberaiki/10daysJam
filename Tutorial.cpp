#include "Tutorial.h"


void Tutorial::Initialize() {

	input_ = Input::GetInstance();;
	debugText_ = DebugText::GetInstance();

	textureHandleBlockTutorial_[0] = TextureManager::Load("tutorial/blockTutorial1.png");
	textureHandleBlockTutorial_[1] = TextureManager::Load("tutorial/blockTutorial2.png");
	textureHandleBlockTutorial_[2] = TextureManager::Load("tutorial/blockTutorial3.png");
	textureHandleBlockTutorial_[3] = TextureManager::Load("tutorial/blockTutorial4.png");
	textureHandleBlockTutorial_[4] = TextureManager::Load("tutorial/blockTutorial5.png");

	for (int i = 0; i < tutorialBlockVolume; i++) {

		//ステージセレクトスプライトの初期化
		blockTutorialSprite_[i] = Sprite::Create(textureHandleBlockTutorial_[i], tutorialPos_);
		//blockTutorialSprite_[i]->SetSize({ 1280,720 });
		//blockTutorialSprite_[i]->SetPosition(tutorialPos_);
	}

	textureHandleHoleTutorial_[0] = TextureManager::Load("tutorial/holeTutorial1.png");
	textureHandleHoleTutorial_[1] = TextureManager::Load("tutorial/holeTutorial2.png");

	for (int i = 0; i < tutorialHoleVolume; i++) {

		//ステージセレクトスプライトの初期化
		holeTutorialSprite_[i] = Sprite::Create(textureHandleHoleTutorial_[i], tutorialPos_);
		//blockTutorialSprite_[i]->SetSize({ 1280,720 });
		//blockTutorialSprite_[i]->SetPosition(tutorialPos_);
	}

}

void Tutorial::Update(int stage) {


	debugText_->SetPos(0, 100);
	debugText_->Printf("%d", faze_);

	stage_ = stage;

	if (stage == 1) {

		keyCoolTimer_++;

		//キー入力させる

		if (faze_ == 0) {

			if (input_->PushKey(DIK_UP) || input_->PushKey(DIK_DOWN) || input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_RIGHT)) {
				faze_ = 1;
			}

		}

		//自機のブロック化をさせる

		else if (faze_ == 1) {

			if (input_->PushKey(DIK_SPACE)) {
				faze_ = 2;
				keyCoolTimer_ = 0;
			}

		}

		//自機のブロックを解除させる

		else if (faze_ == 2) {

			if (input_->PushKey(DIK_SPACE) && keyCoolTime_ <= keyCoolTimer_) {
				faze_ = 3;
				disPlayTimer_ = 0;
			}


		}


		else if (faze_ == 3) {

			disPlayTimer_++;

			if (disPlayTimer_ >= displayTime_) {
				disPlayTimer_ = 0;
				faze_ = 4;
			}

		}

		//自機を動かしてゴールに導く

		else if (faze_ == 4) {

			//一定時間経過後目標を表示

			//disPlayTimer++;

			//if (disPlayTimer >= displayTime) {
			//	disPlayTimer = 0;
			//	ReSet();
			//}

		}

	}
	else if (stage == 2) {

		if (faze_ == 0) {

			disPlayTimer_++;

			if (disPlayTimer_ >= displayTime_) {
				disPlayTimer_ = 0;
				faze_ = 1;
			}

		}

		else if (faze_ == 1) {

		}


	}

}


void Tutorial::Draw() {

	if (stage_ == 1) {
		blockTutorialSprite_[faze_]->Draw();
	}
	else if (stage_ == 2) {
		holeTutorialSprite_[faze_]->Draw();
	}

}

void Tutorial::Reset() {

	faze_ = 0;
	disPlayTimer_ = 0;
	keyCoolTimer_ = 0;

}