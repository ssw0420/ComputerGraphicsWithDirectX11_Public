#include "Common.hlsli"

float4 main(PixelShaderInput input) : SV_TARGET
{
    return float4(input.normalModel * 0.5 + 0.5, 1.0);
}