float4 main( float4 pos : POSITION ) : SV_POSITION
{	
    
    return pos;
}

struct VertexShadeOutput
{
    float32_t4 position : SV_POSITION;
};

struct VertexShadeInput
{
    float32_t4 position : POSITION0;
};

VertexShaderOutput main(VertexShadeInput input)
{
    VertexShadeOutput output;
    
    output.position = input.position;
    return output;
}

