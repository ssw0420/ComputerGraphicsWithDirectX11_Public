#include "Common.hlsli"

Texture2D g_texture0 : register(t0);
SamplerState g_sampler : register(s0);

cbuffer BasicPixelConstantData : register(b0)
{
    bool useTexture;
    float3 dummy;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
    // return float4(input.normalWorld * 0.5 + 0.5, 1.0);
    // return float4(input.texcoord, 0.0, 1.0);
    
    if (useTexture)
    {
        return g_texture0.Sample(g_sampler, input.texcoord);
    }
        
    return float4(input.normalWorld * 0.5 + 0.5, 1.0);
}