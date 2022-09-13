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
	//���[�h��؂�ւ���
	void modeManager();
	//���[�h
	void standBy();
	void Approach();	//�ڋ߁A����
	void Homing();		//�Ǐ]
	void Operarion();	//����
	//�Q�b�^�[
	ViewProjection GetViewProjection() { return viewProjection_; }
private:
	ViewProjection viewProjection_;
	WorldTransform worldTransform_;	//�v���C���[�̃��[���h�g�����X�t�H�[��
	//���@�ƃJ�����̋���
	float length = 20.0f;
	//�J�����̊p�x
	float angleY = 0.3 * PI;	float angleX = 0.3 * PI;
	//�ڋ߃��[�h�p�̃^�C�}�[
	//�Q�[�����̏���
	float gameStartTimer = 0;
	float gameStartTime = 120;

public:
	//���[�h
	enum class Mode
	{
		standBy,	//�ҋ@
		Approach,	//�ڋ߁A����
		Horming,	//�J�����Ǐ]
		Operation	//����
	};
	//���[�h
	size_t mode_ = static_cast<size_t>(Mode::standBy);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (RailCamera::* Mode_[])();
};