#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <d3d12.h>
#include "WorldTransform.h"

//WorldTransform�̍X�V
void worldTransformUpdate(WorldTransform* worldTransform_);
//WorldTransform�̂ƃx�N�g���̊|���Z
void worldTransformScale(Vector3* vector_, WorldTransform* worldTransform_);
void worldTransformMove(Vector3* vector_, WorldTransform* worldTransform_);
void worldTransformRoll(Vector3* vector_, WorldTransform* worldTransform_);
void vecWorldTransform(Vector3* vector_, WorldTransform* worldTransform_);

//�x�N�g���̒�����Ԃ��֐�
float vector3Length(Vector3 vector_);
//���K�������l��Ԃ��֐�
Vector3 vector3Normalize(Vector3 vector_);
