#ifndef __COMMON_HLSLI__
#define __COMMON_HLSLI__

struct VertexShaderInput
{
    float3 posModel : POSITION;
    float3 normalModel : NORMAL;
    float2 texcoord : TEXCOORD0;
};

struct PixelShaderInput
{
    float4 posProj : SV_POSITION;
    float3 normalModel : NORMAL;
    float2 texcoord : TEXCOORD0;
};

#endif