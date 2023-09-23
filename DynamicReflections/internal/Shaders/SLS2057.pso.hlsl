// Parameters:

sampler2D       NormalMap           : register(s0);
samplerCUBE     EnvironmentCubeMap  : register(s1);
sampler2D       CustomEnvMask       : register(s3);
float4          AmbientColor        : register(c1);
float4          EnvToggles          : register(c27);

// Structures:

struct VS_INPUT {
    float4 texcoord_1       : TEXCOORD1_centroid;
    float4 texcoord_2       : TEXCOORD2_centroid;
    float4 texcoord_3       : TEXCOORD3_centroid;
    float2 TextureCoords    : TEXCOORD0;
    float3 VertexColor      : COLOR0;
    float  texcoord_4       : TEXCOORD4;
};

struct VS_OUTPUT {
    float4 vColor : COLOR0;
};

// Code:

VS_OUTPUT main(VS_INPUT IN) {
    VS_OUTPUT OUT;

#define	expand(v)		(((v) - 0.5) / 0.5)
#define	compress(v)		(((v) * 0.5) + 0.5)
#define	envreflect(i, n)	((2 * dot(i, n)) * (i)) - ((n) * dot(i, i))

    float3 r0;
    float3 vProcessedNormals;
    float3 vProcessedCubemap;
    float4 vNormalMap;
    float4 vEnvMask;
    float4 vCubemap;
    float4 cubeCoord; 

    vNormalMap.rgba = tex2D(NormalMap, IN.TextureCoords.xy);
    vEnvMask.rgba   = tex2D(CustomEnvMask, IN.TextureCoords.xy);

    vProcessedNormals.xyz = normalize(expand(vNormalMap.rgb));
    vProcessedNormals.xy = vProcessedNormals.xy * EnvToggles.y;
    vProcessedNormals.xyz = normalize(vProcessedNormals.xyz);

    vCubemap.rgb = float3(IN.texcoord_1.w, IN.texcoord_2.w, IN.texcoord_3.w);

    r0.z = dot(vProcessedNormals.xyz, IN.texcoord_3.xyz);
    r0.y = dot(vProcessedNormals.xyz, IN.texcoord_2.xyz);
    r0.x = dot(vProcessedNormals.xyz, IN.texcoord_1.xyz);

    cubeCoord.xyz = envreflect(normalize(r0.xyz), normalize(vCubemap.rgb));
    cubeCoord.w = 0;

    // Negative iMaskState means mask has alpha channel
    if (EnvToggles.w < 0.0) {
        cubeCoord.w = lerp(0, 9, pow(vEnvMask.a, 0.5));
    }
    
    vCubemap.rgba = texCUBElod(EnvironmentCubeMap, cubeCoord);

    // iMaskState is 1 if mask is present
    // EnvToggles.z is env map scale
    // AmbientColor.a is fade
    vProcessedCubemap.rgb = vCubemap.rgb * (lerp(vNormalMap.a, vEnvMask.r, abs(EnvToggles.w)) * EnvToggles.z) * AmbientColor.rgba;

    OUT.vColor.a = 1;
    OUT.vColor.rgb = ((EnvToggles.x <= 0.0 ? vProcessedCubemap.rgb : (vProcessedCubemap.rgb * IN.VertexColor.rgb)) * IN.texcoord_4.x);

    return OUT;
};