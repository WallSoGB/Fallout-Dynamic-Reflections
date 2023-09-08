//
//
// Parameters:

sampler2D   NormalMap           : register(s0);
samplerCUBE EnvironmentCubeMap  : register(s1);
sampler2D   CustomEnvMask       : register(s3);
float4      AmbientColor        : register(c1);
float4      EnvToggles          : register(c27);


// Registers:
//
//   Name               Reg   Size
//   ------------------ ----- ----
//   AmbientColor       const_1       1
//   EnvToggles         const_27      1
//   NormalMap          texture_0       1
//   EnvironmentCubeMap texture_1       1
//   CustomEnvMask      texture_3       1
//


// Structures:

struct VS_INPUT {
    float4 texcoord_1       : TEXCOORD1_centroid;
    float4 texcoord_2       : TEXCOORD2_centroid;
    float4 texcoord_3       : TEXCOORD3_centroid;
    float2 tcCoord          : TEXCOORD0;
    float3 vVertexColor     : COLOR0;
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
    float3 q1;
    float3 vProcessedCubemap;
    float4 vNormalMap;
    float4 vEnvMask;
    float4 vCubemap;
    float4 cubeCoord;    

    vNormalMap.rgba = tex2D(NormalMap, IN.tcCoord.xy);
    vEnvMask.rgba = tex2D(CustomEnvMask, IN.tcCoord.xy);
    q1.xyz = normalize(expand(vNormalMap.rgb));
    vCubemap.xyz = float3(IN.texcoord_1.w, IN.texcoord_2.w, IN.texcoord_3.w);

    r0.z = dot(q1.xyz, IN.texcoord_3.xyz);
    r0.y = dot(q1.xyz, IN.texcoord_2.xyz);
    r0.x = dot(q1.xyz, IN.texcoord_1.xyz);

    cubeCoord.rgb = envreflect(normalize(r0.xyz), normalize(vCubemap.xyz));
    cubeCoord.a = lerp(0, 5, vEnvMask.a);
    vCubemap.rgba = texCUBElod(EnvironmentCubeMap, cubeCoord);

    // EnvToggles.w is 1 if mask is present
    // EnvToggles.z is env map scale
    // AmbientColor.a is fade
    vProcessedCubemap.rgb = (vCubemap.rgb * (lerp(vNormalMap.a, vEnvMask.x, EnvToggles.w) * EnvToggles.z)) * AmbientColor.rgba;

    OUT.vColor.a = 1;
    OUT.vColor.rgb = ((EnvToggles.x <= 0.0 ? vProcessedCubemap.rgb : (vProcessedCubemap.rgb * IN.vVertexColor.rgb)) * IN.texcoord_4.x);

    return OUT;
};