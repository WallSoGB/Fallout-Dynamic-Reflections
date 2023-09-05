//
//
// Parameters:

float4      AmbientColor        : register(c1);
sampler2D   CustomEnvMask       : register(s3);
float4      EnvToggles          : register(c27);
samplerCUBE EnvironmentCubeMap  : register(s1);
sampler2D   NormalMap           : register(s0);


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
    float4  texcoord_1   : TEXCOORD1_centroid;
    float4  texcoord_2   : TEXCOORD2_centroid;
    float4  texcoord_3   : TEXCOORD3_centroid;
    float2  NormalUV     : TEXCOORD0;
    float3  VertexColor  : COLOR0;
    float   texcoord_4   : TEXCOORD4;
};

struct VS_OUTPUT {
    float4 color_0 : COLOR0;
};

// Code:

VS_OUTPUT main(VS_INPUT IN) {
    VS_OUTPUT OUT;

#define	expand(v)		(((v) - 0.5) / 0.5)
#define	compress(v)		(((v) * 0.5) + 0.5)
#define	envreflect(i, n)	((2 * dot(i, n)) * (i)) - ((n) * dot(i, i))

    float3 q1;
    float3 q4;
    float3 r0;
    
    float4 normals;
    float4 cubeMap;
    float4 envMask;
    float4 cubeCoord;

    normals.rgba = tex2D(NormalMap, IN.NormalUV.xy);
    envMask.rgba = tex2D(CustomEnvMask, IN.NormalUV.xy);
    q1.xyz = normalize(expand(normals.rgb));
    r0.z = dot(q1.xyz, IN.texcoord_3.xyz);
    r0.y = dot(q1.xyz, IN.texcoord_2.xyz);
    r0.x = dot(q1.xyz, IN.texcoord_1.xyz);

    cubeMap.z = -IN.texcoord_3.w;
    cubeMap.y = -IN.texcoord_2.w;
    cubeMap.x = -IN.texcoord_1.w;

    cubeCoord.xyz = envreflect(normalize(r0.xyz), normalize(cubeMap.xyz));
    cubeCoord.a = lerp(0, 5, envMask.a);
    cubeMap.rgba = texCUBElod(EnvironmentCubeMap, cubeCoord);

    // EnvToggles.w is 1 if mask is present
    // EnvToggles.z is env map scale
    // AmbientColor.a is fade
    q4.rgb = (cubeMap.rgb * (lerp(normals.a, envMask.r, EnvToggles.w) * EnvToggles.z)) * AmbientColor.rgba;

    OUT.color_0.a = 1;
    OUT.color_0.rgb = ((EnvToggles.x <= 0.0 ? q4.rgb : (q4.rgb * IN.VertexColor.rgb)) * IN.texcoord_4.x);

    return OUT;
};