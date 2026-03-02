#include "object3d.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// PixelShader(CG2_02_00_16P)
struct Material
{
    float32_t4 color;
    int32_t enableLighting;
    float32_t4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0); // CG2_02_01_6P

struct DirectionalLight
{
    float32_t4 color;
    float32_t3 direction;
    float intensity;
};
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f,1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    PixelShaderOutput output;
    if (gMaterial.enableLighting != 0)
    {
        float32_t3 N = normalize(input.normal);
        float32_t3 L = normalize(-gDirectionalLight.direction);
        float NdotL = dot(N, L);
        float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
        cos = saturate(cos);
        
        output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;
    }
    else
    {
        output.color = gMaterial.color * textureColor;
    }
    return output;
}