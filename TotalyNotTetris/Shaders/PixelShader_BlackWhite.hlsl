#pragma pack_matrix(row_major)

Texture2D color : register(t0);
Texture2D shadow : register(t1);
SamplerState filter : register(s0);
SamplerState shadowSampleType : register(s1);

struct OBJ_ATTRIBUTES
{
    float3 Kd; // diffuse reflectivity
    float d; // dissolve (transparency) 
    float3 Ks; // specular reflectivity
    float Ns; // specular exponent
};

cbuffer SceneData
{
    float4 sunDirection, sunColor, sunAmbient, camPosition;
    matrix viewMatrix, projectionMatrix, lightProjectionMatrix, lightViewMatrix;
};

cbuffer MeshData
{
    unsigned int useLight;
    unsigned int useDepth;
    unsigned int padding2;
    unsigned int padding3;
};

//StructuredBuffer<float4> PointLights;

struct OutputToRasterizer
{
    float4 posH : SV_Position;
    float4 posW : WORLD;
    float4 normW : NORMAL;
    float4 uv : UV;
    float4x4 worldMatrix : WMATRIX;
    OBJ_ATTRIBUTES material : MATERIAL;
    float4 lightProjPos : POSITION;
};

float4 main(OutputToRasterizer input) : SV_TARGET
{
    float4 result;
    float4 textureColor = color.Sample(filter, input.uv.xy, 1);
    
    float2 shadowTex;
    float shadowMapDepth;
    float depth;
    float4 shadowLightColor = float4(1, 1, 1, 1);
    float testColor = 1;
    input.lightProjPos.xyz /= input.lightProjPos.w;
    shadowTex.x = input.lightProjPos.x * 0.5f + 0.5f;
    shadowTex.y = input.lightProjPos.y * -0.5f + 0.5f;
    if (saturate(shadowTex.x) == shadowTex.x && saturate(shadowTex.y) == shadowTex.y)
    {
        shadowMapDepth = shadow.Sample(shadowSampleType, shadowTex).r;
        float s1 = shadow.Sample(shadowSampleType, shadowTex.xy + float2(1.0f / 8192, 0)).r;
        float s2 = shadow.Sample(shadowSampleType, shadowTex.xy + float2(0, 1.0f / 8192)).r;
        float s3 = shadow.Sample(shadowSampleType, shadowTex.xy + float2(1.0f / 8192, 1.0f / 8192)).r;

        depth = input.lightProjPos.z;
        
        float result0 = depth <= shadowMapDepth;
        float result1 = depth <= s1;
        float result2 = depth <= s2;
        float result3 = depth <= s3;
        
        float2 texelPos = 8192 * shadowTex.xy;
        float2 t = frac(texelPos);
        
        float res = lerp(lerp(result0, result1, t.x), lerp(result2, result3, t.x), t.y);
        

        if (res >= depth /* && depth > 0*/)
        {
            shadowLightColor = float4(1, 1, 1, 1);
        }
        else
        {
            shadowLightColor.rgb = float3(0.5, 0.5, 0.5) + res * 2;
        }
    }
    
    if (useLight == 1)
    {
        float ratio = saturate(dot(-sunDirection, input.normW));
    
        result = float4(sunColor.rgb * saturate(ratio + sunAmbient.xyz), 1);
    
        float4 viewDir = normalize(camPosition - input.posW);
        float4 directVec = reflect(sunDirection, input.normW);

        float dotResult = dot(viewDir, directVec);
        float clampResult = saturate(dotResult);
        float powResult = 0;
        if (input.material.Ns > 0)
        {
            powResult = pow(clampResult, input.material.Ns);
        }
        
        float intensity = max(powResult, 0);
        float4 specularColor = { saturate(sunColor.rgb * input.material.Ks.rgb * intensity), 1 };
    
        if (textureColor.r > 0 || textureColor.g > 0 || textureColor.b > 0)
        {
            result.rgb = saturate(result.rgb * textureColor.rgb + specularColor.rgb);
            result.a = input.material.d;
        }
        else
        {
            result.rgb = saturate(result.rgb * input.material.Kd.rgb + specularColor.rgb);
            result.a = input.material.d;
        }

        result.rgb = result.rgb * shadowLightColor.rgb;
    }
    else
    {
        if (textureColor.r > 0 || textureColor.g > 0 || textureColor.b > 0)
        {
            result.rgb = textureColor.rgb;
            result.a = input.material.d;
        }
        else
        {
            result.rgb = input.material.Kd.rgb,
            result.a = input.material.d;
        }
    }
    
    float mean = (result.r + result.g + result.b) / 3;
    result.rgb = mean;
    
    return result;
}