#include "Common.hlsli"

cbuffer BasicVertexConstantData : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
}

PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput output;
    
    output.posProj = float4(input.posModel * 0.5 + float3(0.0, 0.0, 0.6), 1.0);
    
    float4 pos = float4(input.posModel, 1.0f);
    pos = mul(pos, model);
    pos = mul(pos, view);
    pos = mul(pos, projection);
    output.posProj = pos;
    
    output.normalModel = input.normalModel;
    output.texcoord = input.texcoord;

    return output;
}