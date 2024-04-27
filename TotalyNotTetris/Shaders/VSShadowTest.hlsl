#pragma pack_matrix(row_major)
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

struct Vertex
{
    float4 position : POSITION;
    float4 uv : UV;
    float4 normal : NORMAL;
    float4x4 worldMatrix : WMATRIX;
    OBJ_ATTRIBUTES material : MATERIAL;
};


float4 main(Vertex input) : SV_POSITION
{
    float4 output = input.position;
    output = mul(output, input.worldMatrix);
    output = mul(output, lightViewMatrix);
    output = mul(output, lightProjectionMatrix);
    return output;
}