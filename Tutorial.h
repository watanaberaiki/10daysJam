#pragma once
#include "Input.h"
#include "Cat.h"
#include "Sprite.h"
#include "DebugText.h"
#include "SafeDelete.h"
#include "WorldTransform.h"

class Tutorial
{

public:

	void Initialize();

	void Update(int stage);

	void Reset();

	void Draw();

private:

	int faze_ = 0;
	int keyCoolTime_ = 100;
	int keyCoolTimer_ = 0;

	int displayTime_ = 1000;
	int disPlayTimer_ = 0;

	int stage_ = 0;

	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	//画像
	Vector2 tutorialPos_ = Vector2(50, 350);

	//ステージ1画像
	static const int tutorialBlockVolume = 5;
	uint32_t textureHandleBlockTutorial_[tutorialBlockVolume];
	Sprite* blockTutorialSprite_[tutorialBlockVolume];

	//ステージ2画像
	static const int tutorialHoleVolume = 2;
	uint32_t textureHandleHoleTutorial_[tutorialHoleVolume];
	Sprite* holeTutorialSprite_[tutorialHoleVolume];

};
