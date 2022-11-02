#pragma once
#include "Sprite.h"
#include "GeometryObject.h"
#include "GeometryObjectManager.h"
#include "FbxModelObject.h"
#include "WorldTransform.h"

//�X�v���C�g�폜
void SpriteDelete(Sprite* sp){
	delete sp;
	sp = nullptr;
}

//�􉽊w�I�u�W�F�N�g�폜
void GeometryDelete(GeometryObject* obj, WorldTransform& worldtransform){
	delete obj;
	obj = nullptr;
	worldtransform = {};
}

//FBX�I�u�W�F�N�g�폜
void FBXDelete(FbxModelObject* obj, FbxModelManager* model, WorldTransform& worldtransform){
	delete obj;
	delete model;
	obj = nullptr;
	model = nullptr;
	worldtransform = {};
}

template<class T> void SafeDelete(T* p){
	delete p;
	p = nullptr;
}