#pragma pack_matrix(row_major)

struct OBJ_ATTRIBUTES
{
	float3    Kd; // diffuse reflectivity
	float	    d; // dissolve (transparency) 
	float3    Ks; // specular reflectivity
	float       Ns; // specular exponent
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

struct Vertex
{
	float4 position : POSITION;
	float4 uv : UV;
	float4 normal : NORMAL;
    float4x4 worldMatrix : WMATRIX;
    OBJ_ATTRIBUTES material : MATERIAL;
};

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

OutputToRasterizer main(Vertex inputVertex)
{
    float4 outPos = inputVertex.position;
    outPos = mul(outPos, inputVertex.worldMatrix);
    outPos = mul(outPos, viewMatrix);
    outPos = mul(outPos, projectionMatrix);
	
    float4 worldPos = mul(inputVertex.position, inputVertex.worldMatrix);
    inputVertex.normal = normalize(mul(inputVertex.normal, inputVertex.worldMatrix));
    
    float4 outLightProj = inputVertex.position;
    outLightProj = mul(outLightProj, inputVertex.worldMatrix);
    outLightProj = mul(outLightProj, lightViewMatrix);
    outLightProj = mul(outLightProj, lightProjectionMatrix);
	
    OutputToRasterizer output = { outPos, worldPos, inputVertex.normal, inputVertex.uv, inputVertex.worldMatrix, inputVertex.material, outLightProj };
    
    if (useDepth == 0)
    {
        output.posH.z = output.posH.w;
    }
	
    return output;
}