#include "Common.hlsli"

Texture2D g_texture0 : register(t0);
SamplerState g_sampler : register(s0);

cbuffer BasicPixelConstantData : register(b0)
{
    float3 eyeWorld;
    bool useTexture;
    Material material;
    Light lights[MAX_LIGHTS];
};

float4 main(PixelShaderInput input) : SV_TARGET
{
    // return float4(input.normalWorld * 0.5 + 0.5, 1.0);
    // return float4(input.texcoord, 0.0, 1.0);
    
    float3 toEye = normalize(eyeWorld - input.posWorld);
    
    float3 lighting = float3(0.0, 0.0, 0.0);
    
    int i = 0;
    
    [unroll]
    for (i = 0; i < NUM_DIR_LIGHTS; ++i)
    {
        lighting += ComputeDirectionalLight(lights[i], material, input.normalWorld, toEye);

    }
    
    [unroll]
    for (i = NUM_DIR_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; ++i)
    {
        lighting += ComputePointLight(lights[i], material, input.posWorld, input.normalWorld, toEye);
    }
    
    [unroll]
    for (i = NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS + NUM_SPOT_LIGHTS; ++i)
    {
        lighting += ComputeSpotLight(lights[i], material, input.posWorld, input.normalWorld, toEye);
    }
    
    if (useTexture)
    {
        //return g_texture0.Sample(g_sampler, input.texcoord);
        float4 texturecolor = g_texture0.Sample(g_sampler, input.texcoord);
        clip(texturecolor.a - 0.5);
        
        return float4(lighting, 1.0) * texturecolor;

    }
        
    //return float4(input.normalWorld * 0.5 + 0.5, 1.0);
    return float4(lighting, 1.0);

}