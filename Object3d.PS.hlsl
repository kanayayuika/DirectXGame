#include "Object3d.hlsli"

struct Material
{
    float4 color;  
    
};
ConstantBuffer<Material> gMaterial : register(b0);//bというのはConstantBufferを意味する、0は番号

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    output.color = gMaterial.color;
    return output;
}




 