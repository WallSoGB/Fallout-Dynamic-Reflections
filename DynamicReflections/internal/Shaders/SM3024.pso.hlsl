//
//
// Parameters:

sampler2D CustomEnvMask : register(s3);
float4 EnvToggles : register(c11);
samplerCUBE EnvironmentCubeMap : register(s1);
float4 MatAlpha : register(c3);
sampler2D NormalMap : register(s0);


// Registers:
//
//   Name               Reg   Size
//   ------------------ ----- ----
//   MatAlpha           const_3       1
//   EnvToggles         const_11      1
//   NormalMap          texture_0       1
//   EnvironmentCubeMap texture_1       1
//   CustomEnvMask      texture_3       1
//


// Structures:

struct VS_INPUT {
    float4 texcoord_1 : TEXCOORD1_centroid;
    float4 texcoord_2 : TEXCOORD2_centroid;
    float4 texcoord_3 : TEXCOORD3_centroid;
    float2 NormalUV : TEXCOORD0;
    float3 VertexColor : COLOR0;
    float texcoord_4 : TEXCOORD4;
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

    const float4 const_0 = {-0.5, 0.5, 1, 0};

    float4 normals;
    float3 q1;
    float3 q35;
    float3 q5;
    float4 cubeMap;
    float4 envMask;
    float4 cubeCoord;

    normals.xyzw = tex2D(NormalMap, IN.NormalUV.xy);
    q1.xyz = normalize(normalize(expand(normals.xyz)) * const_0.yyz);
    envMask.xyz = normalize(float3(IN.texcoord_1.w, IN.texcoord_2.w, IN.texcoord_3.w));
    cubeMap.z = dot(q1.xyz, normalize(IN.texcoord_3.xyz));
    cubeMap.y = dot(q1.xyz, normalize(IN.texcoord_2.xyz));
    cubeMap.x = dot(q1.xyz, normalize(IN.texcoord_1.xyz));
    q35.xyz = normalize(cubeMap.xyz);

    envMask.xyzw = tex2D(CustomEnvMask, IN.NormalUV.xy);

    cubeCoord.rgb = ((2 * dot(q35.xyz, envMask.xyz)) * q35.xyz) - (envMask.xxyz * dot(q35.xyz, q35.xyz));
    cubeCoord.a = lerp(0, 5, envMask.a);

    cubeMap.xyzw = texCUBElod(EnvironmentCubeMap, cubeCoord);

    // EnvToggles.w is 1 if mask is present
    // EnvToggles.z is env map scale
    // AmbientColor.a is fade
    q5.rgb = ((cubeMap.rgb * (lerp(normals.w, envMask.x, EnvToggles.w) * EnvToggles.z)) * MatAlpha.x) * IN.VertexColor.rgb;

    OUT.color_0.a = 1;
    OUT.color_0.rgb = q5.rgb * IN.texcoord_4.x;

    return OUT;
};

// approximately 45 instruction slots used (3 texture, 42 arithmetic)
