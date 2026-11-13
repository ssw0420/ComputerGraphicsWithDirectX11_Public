#ifndef __COMMON_HLSLI__
#define __COMMON_HLSLI__

#define MAX_LIGHTS 3
#define NUM_DIR_LIGHTS 1
#define NUM_POINT_LIGHTS 1
#define NUM_SPOT_LIGHTS 1

struct Material
{
    float3 ambient;
    float shininess;
    float3 diffuse;
    float dummy1;
    float3 specular;
    float dummy2;
};

struct Light
{
    float3 strength;
    float fallOffStart;
    float3 direction;
    float fallOffEnd;
    float3 position;
    float spotPower;
};

float3 ComputeBlinnPhong(float3 receivedStrength, float3 toLight, float3 normal, float3 toEye, Material mat)
{
    float3 halfway = normalize(toEye + toLight);
    float hdotn = dot(halfway, normal);
    float3 specular = mat.specular * pow(max(hdotn, 0.0f), mat.shininess);

    return mat.ambient + (mat.diffuse + specular) * receivedStrength;

}

float3 ComputeDirectionalLight(Light L, Material mat, float3 normal, float3 toEye)
{
    float3 toLight = -L.direction;

    float ndotl = max(dot(toLight, normal), 0.0f);
    float3 receivedStrength = L.strength * ndotl;
    
    return ComputeBlinnPhong(receivedStrength, toLight, normal, toEye, mat);

}

float ComputeAttenuation(float d, float fallOffStart, float fallOffEnd)
{
    return saturate((fallOffEnd - d) / (fallOffEnd - fallOffStart));

}

float3 ComputePointLight(Light L, Material mat, float3 pos, float3 normal, float3 toEye)
{
    float3 toLight = L.position - pos;
    
    float d = length(toLight);
    
    if (d > L.fallOffEnd)
    {
        return float3(0.0, 0.0, 0.0);
    }
    else
    {
        toLight /= d;
        
        float ndotl = max(dot(toLight, normal), 0.0);
        float3 receivedStrength = L.strength * ndotl;
        
        float att = ComputeAttenuation(d, L.fallOffStart, L.fallOffEnd);
        receivedStrength *= att;

        return ComputeBlinnPhong(receivedStrength, toLight, normal, toEye, mat);

    }

}

float3 ComputeSpotLight(Light L, Material mat, float3 pos, float3 normal, float3 toEye)
{
    float3 toLight = L.position - pos;
    
    float d = length(toLight);
    
    if (d > L.fallOffEnd)
    {
        return float3(0.0, 0.0, 0.0);
    }
    else
    {
        toLight /= d;
        
        float ndotl = max(dot(toLight, normal), 0.0f);
        float3 receivedStrength = L.strength * ndotl;
        
        float att = ComputeAttenuation(d, L.fallOffStart, L.fallOffEnd);
        receivedStrength *= att;
        
        float spotFactor = pow(max(-dot(toLight, L.direction), 0.0f), L.spotPower);
        receivedStrength *= spotFactor;
        
        return ComputeBlinnPhong(receivedStrength, toLight, normal, toEye, mat);
    }
}

struct VertexShaderInput
{
    float3 posModel : POSITION;
    float3 normalModel : NORMAL;
    float2 texcoord : TEXCOORD0;
};

struct PixelShaderInput
{
    float4 posProj : SV_POSITION;
    float3 posWorld : POSTION;
    float3 normalWorld : NORMAL;
    float2 texcoord : TEXCOORD0;
    float3 color : COLOR;
};

#endif