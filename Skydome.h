#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class Skydome
{
public:
	//�����œV���̃T�C�Y���w��
	void Initialize(Model* model, float r);
	void Update();
	void Draw(ViewProjection viewProjection);
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	//�V���̑傫��
	float r_;
};

