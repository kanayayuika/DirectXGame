// PixelShader(CG2_02_00_16P)
struct Material
{
    float4 color;
};
ConstantBuffer<Material> gMaterial : register(b0);// CG2_02_01_6P

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main()
{
    PixelShaderOutput output;
    output.color = gMaterial.color;
    return output;
}