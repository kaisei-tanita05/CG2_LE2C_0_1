#include "Object3d.h"
#include "Object3dCommon.h"
#include "Matrix4x4.h"
#include "TextureManager.h"

using namespace MatrixMath;

void Object3d::Initialize(Object3dCommon* object3dCommon)
{
	this->object3dCommon = object3dCommon;

	//モデル読み込み
	modelData = LoadObjFile("resource", "plane.obj");

	CreateVertexData();

	CreateMaterialData();

	CreateTransformData();

	CreateEnableLightData();

	//.objの参照しているテクスチャファイル読み込み
	TextureManager::GetInstance()->LoadTexture(modelData.material.textureFilePath);
	//読み込んだテクスチャの番号の取得
	modelData.material.textureindex = TextureManager::GetInstance()->GetTextureIndexByFilePath(modelData.material.textureFilePath);

	//Transform変数を作る
	transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	cameraTransform = { {1.0f,1.0f,1.0f},{0.3f,0.0f,0.0f},{0.0f,4.0f,-10.0f} };
}

void Object3d::CreateVertexData() 
{
	vertexResource = dxCommon_->CreateBufferResource(sizeof(VertexData) * modelData.vertices.size());

	// リソースの先頭のアドレスから作成する
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点6つ分のサイズ
	vertexBufferView.SizeInBytes = sizeof(VertexData) * modelData.vertices.size();
	// 1頂点あたりのサイズ
	vertexBufferView.StrideInBytes = sizeof(VertexData);

	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	std::memcpy(vertexData, modelData.vertices.data(), sizeof(VertexData) * modelData.vertices.size());//頂点データをリソースにコピー
}

void Object3d::CreateMaterialData() 
{
	materialResource = dxCommon_->CreateBufferResource(sizeof(Material));
	// 書き込むためのアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 今回は白を書き込んでいる
	materialData->color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	materialData->enableLighting = true;

	materialData->uvTransform = MakeIdentity4x4();
}

void Object3d::CreateTransformData() 
{
	transformationMatrixResource = dxCommon_->CreateBufferResource(sizeof(Matrix4x4));
	//書き込むためのアドレスを取得
	transformationMatrixResource->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixData));
	//単位行列を書き込んでおく
	transformationMatrixData->WVP = MakeIdentity4x4();
	transformationMatrixData->World = MakeIdentity4x4();
}

void Object3d::CreateEnableLightData() 
{
	directionalLightResource = dxCommon_->CreateBufferResource(sizeof(DirectionalLight));
	directionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));

	directionalLightData->color = { 1.0f,1.0f,1.0f,1.0f };

	directionalLightData->direction = { 0.0f,-1.0f,0.0f };

	directionalLightData->intensity = 1.0f;
}