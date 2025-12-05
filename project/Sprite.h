#pragma once
#include "DirectXCommon.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class SpriteCommon;



struct TransformationMatrix
{
	Matrix4x4 WVP;

	Matrix4x4 World;
};





struct Material
{
	Vector4 color;
	int32_t enableLighting;
	float padding[3];
	Matrix4x4 uvTransform;
};

//スプライト
class Sprite
{

	struct VertexData {
		Vector4 position;
		Vector2 texcoord;
		Vector3 normal;
	};

public://メンバ関数
	//初期化
	void Initialize(SpriteCommon*spriteCommon);

	void Update();

	void Draw();
private:
	SpriteCommon* spriteCommon = nullptr;
	
	DirectXCommon* dxCommon;

	VertexData* vertexData_;

	uint32_t* indexData;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

	D3D12_INDEX_BUFFER_VIEW indexBufferView;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;

	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite_;

	VertexData* vertexDataSprite_ = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_;

	Microsoft::WRL::ComPtr<ID3D12Resource> transformationMatrixResource;

	Matrix4x4* transformationMatrixData;

	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource;

	TransformationMatrix* wvpData = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceSprite;

	Material* materialSpriteData = nullptr;

	TransformationMatrix* transformationMatrixData_ = nullptr;

	struct Transform {
		Vector3 scale;
		Vector3 rotate;
		Vector3 translate;
	};

	Transform transformSprite{ {1.0f,1.0f,1.0f,},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Transform uvTransformSprite{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	

};

