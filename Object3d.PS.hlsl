#include "object3d.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// PixelShader(CG2_02_00_16P)
struct Material
{
    float32_t4 color;
};
ConstantBuffer<Material> gMaterial : register(b0); // CG2_02_01_6P

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    PixelShaderOutput output;
    output.color = gMaterial.color * textureColor;
    return output;
}