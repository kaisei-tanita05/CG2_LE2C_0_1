#pragma once
#include <string>
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include "DirectXCommon.h"

class Object3dCommon;

class Object3d
{

	struct MaterialData
	{
		std::string textureFilePath;
		uint32_t textureindex = 0;
	};

	//頂点データ
	struct VertexData
	{
		Vector4 position;
		Vector2 texcoord;
		Vector3 normal;
	};

	struct ModelData
	{
		std::vector<VertexData>vertices;
		MaterialData material;
	};

	//マテリアルデータ
	struct Material
	{
		Vector4 color;
		int32_t enableLighting;
		float padding[3];
		Matrix4x4 uvTransform;
	};

	//座標変換行列データ
	struct TransformationMatrix
	{
		Matrix4x4 WVP;
		Matrix4x4 World;
	};

	struct DirectionalLight
	{
		Vector4 color;//!<ライトの色
		Vector3 direction;//!<ライトの向き
		float intensity;//!<輝度
	};

	struct Transform
	{
		Vector3 scale;
		Vector3 rotate;
		Vector3 translate;
	};

public://メンバ関数

	//初期化
	void Initialize(Object3dCommon* object3dCommon);

	//.mtlファイルの読み取り
	static MaterialData LoadMaterialTemplatefile(const std::string& directoryPath, const std::string& filePath);

	//.objファイルの読み取り
	static ModelData LoadObjFile(const std::string& directoryPath, const std::string& filePath);

private:
	Object3dCommon* object3dCommon = nullptr;

	//Objファイルのデータ
	ModelData modelData;

	//バッファリソース
	//バッファリソース内のデータを指すポインタ
	VertexData* vertexData = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;

	//バッファリソース内のデータを指すポインタ
	Material* materialData = nullptr;

	//Obj用のtransformationMatrix用のリソースを作る。matrix4x4　1つ分のサイズを用意する
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationMatrixResource;
	//データを書き込む
	TransformationMatrix* transformationMatrixData = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource = dxCommon_->CreateBufferResource(sizeof(DirectionalLight));

	DirectionalLight* directionalLightData = nullptr;


	//バッファリソースの使い道を補足するバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

	DirectXCommon* dxCommon_;

	Transform transform;

	Transform cameraTransform;

	void CreateVertexData();

	void CreateMaterialData();

	void CreateTransformData();

	void CreateEnableLightData();
};

