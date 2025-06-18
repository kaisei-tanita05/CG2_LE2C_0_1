#include "Object3d.hlsli"
#define float32_t4x4 float4x4
#define float32_t4 float4
#define float32_t2 float2


struct TransformationMatrix
{
    float32_t4x4 WVP;
    //float32_t4x4 World;
};

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);

//struct VertexShaderOutput
//{
//    float32_t4 position : SV_POSITION;
//};

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    output.position = mul(input.position,gTransformationMatrix.WVP);
    output.texcoord = input.texcoord;
    return output;
}

