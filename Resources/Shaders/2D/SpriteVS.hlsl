#include "Sprite.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL,float2 uv : TEXCOORD, float4 col : COLOR)
{
    VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
    output.svpos = mul(matWorld, pos);
    output.normal = normal;
    output.uv = uv;
    output.color = col;
    return output;
}