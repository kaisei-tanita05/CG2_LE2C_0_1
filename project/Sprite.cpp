#include "Sprite.h"
#include "SpriteCommon.h"

using namespace MatrixMath;

void Sprite::Initialize(SpriteCommon* spriteCommon)
{
	//引数を受け取ってメンバ変数に記録する
	this->spriteCommon = spriteCommon;

	// Sprite用の頂点リソースを作る
	vertexResource_ = dxCommon->CreateBufferResource(sizeof(VertexData) * 6);

	
	// リソースの先頭のアドレスから作成する
	vertexBufferViewSprite_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点6つ分のサイズ
	vertexBufferViewSprite_.SizeInBytes = sizeof(VertexData) * 6;
	// 1頂点あたりのサイズ
	vertexBufferViewSprite_.StrideInBytes = sizeof(VertexData);

	// 書き込むためのアドレス取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	// 1枚目の三角形
	// 左下
	vertexData_[0].position = { 0.0f,360.0f,0.0f,1.0f };
	vertexData_[0].texcoord = { 0.0f,1.0f };
	vertexData_[0].normal = { 0.0f,0.0f,-1.0f };

	//左上
	vertexData_[1].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexData_[1].texcoord = { 0.0f,0.0f };
	vertexData_[1].normal = { 0.0f,0.0f,-1.0f };

	//右下
	vertexData_[2].position = { 640.0f,360.0f,0.0f,1.0f };
	vertexData_[2].texcoord = { 1.0f,1.0f };
	vertexData_[2].normal = { 0.0f,0.0f,-1.0f };

	//右上
	vertexData_[3].position = { 640.0f,0.0f,0.0f,1.0f };
	vertexData_[3].texcoord = { 1.0f,0.0f };
	vertexData_[3].normal = { 0.0f,0.0f,-1.0f };


	indexResource_ = dxCommon->CreateBufferResource(sizeof(uint32_t) * 6);

	//リソースの先頭のアドレスから使う
	indexBufferView.BufferLocation = indexResource_->GetGPUVirtualAddress();

	//使用するするリソースのサイズはインデックス6つ分のサイズ
	indexBufferView.SizeInBytes = sizeof(uint32_t) * 6;

	//インデックスはuint32_tとする
	indexBufferView.Format = DXGI_FORMAT_R32_UINT;

	//インデックスにリソースデータを書き込む
	
	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1;	indexData[4] = 3; indexData[5] = 2;

#pragma endregion


	// Sprite用のTransformationMatirx用のリソースを作る。Matrix4x4 一つ分のサイズを用意する
	transformationMatrixResource= dxCommon->CreateBufferResource(sizeof(TransformationMatrix));
	// データを書き込む

	// 書き込むためのアドレスを取得
	transformationMatrixResource->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixData));

	*transformationMatrixData = MakeIdentity4x4();

#pragma region WVP

	// WVB用のリソースを作る。Matrix4x4 一つ分のサイズを用意する
	wvpResource = dxCommon->CreateBufferResource(sizeof(TransformationMatrix));

	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));


	// 単位行列を書き込んでおく
	wvpData->WVP = MakeIdentity4x4();




#pragma endregion

#pragma region Sprite用のマテリアル

	materialResourceSprite = dxCommon->CreateBufferResource(sizeof(Material));

	materialResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&materialSpriteData));

	materialSpriteData->uvTransform = MakeIdentity4x4();


	*materialSpriteData = {};

	materialSpriteData->color = Vector4{ 1.0f,1.0f,1.0f,1.0f };


	//SpriteはLightingしないのでfalseを設定する

	materialSpriteData->enableLighting = false;

	// Sprite
	Matrix4x4 worldMatrixSprite = MakeAffine(transformSprite.scale, transformSprite.rotate, transformSprite.translate);
	Matrix4x4 viewMatrixSprite = MakeIdentity4x4();
	Matrix4x4 projectionMatrixSprite = Orthographic(0.0f, 0.0f, float(WinApp::kClientWidth), float(WinApp::kClientHeight), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrixSprite = Multipty(worldMatrixSprite, Multipty(viewMatrixSprite, projectionMatrixSprite));
	*transformationMatrixData = worldViewProjectionMatrixSprite;
}

void Sprite::Update() {

}

void Sprite::Draw()
{


	// Spriteの描画
	dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU);
	dxCommon->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite); // VBVを設定
	// マテリアルCBuffer
	dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSprite->GetGPUVirtualAddress());
	dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprite->GetGPUVirtualAddress());

	// 描画！(DraoCall/ドローコール)
	dxCommon->GetCommandList()->DrawInstanced(6, 1, 0, 0);


	dxCommon->GetCommandList()->IASetIndexBuffer(&indexBufferViewSprite);//IBVを設定

	//描画!(DrawCall/ドローコー)6個のインデックスを使用し1つのインスタンスを描画。その他は当面0で良い
	dxCommon->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);

}
