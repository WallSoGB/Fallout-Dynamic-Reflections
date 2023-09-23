// Parameters:

sampler2D NormalMap : register(s0);
samplerCUBE EnvironmentCubeMap : register(s1);
sampler2D CustomEnvMask : register(s3);
float4 MatAlpha : register(c3);
float4 EnvToggles : register(c11);

// Structures:

struct VS_INPUT {
    float4 texcoord_1 : TEXCOORD1_centroid;
    float4 texcoord_2 : TEXCOORD2_centroid;
    float4 texcoord_3 : TEXCOORD3_centroid;
    float2 NormalUV : TEXCOORD0;
    float3 color_0 : COLOR0;
    float texcoord_4 : TEXCOORD4;
};

struct VS_OUTPUT {
    float4 vColor : COLOR0;
};

// Code:

VS_OUTPUT main(VS_INPUT IN) {
    VS_OUTPUT OUT;

#define	expand(v)		(((v) - 0.5) / 0.5)
#define	compress(v)		(((v) * 0.5) + 0.5)

    const float4 const_0 = {-0.5, 0.5, 1, 0};

    float3 q1;
    float3 q35;
    float3 q5;
    float4 vCubemap;
    float4 r2;
    float4 vNormalMap;
    float4 vEnvMask;
    float4 cubeCoord;

    vNormalMap.rgba = tex2D(NormalMap, IN.NormalUV.xy);
    vEnvMask.rgba = tex2D(CustomEnvMask, IN.NormalUV.xy);

    q1.xyz = normalize(normalize(expand(vNormalMap.rgb)) * const_0.yyz);
    r2.xyz = normalize(-(float3(IN.texcoord_1.w, IN.texcoord_2.w, IN.texcoord_3.w)));
    vCubemap.z = dot(q1.xyz, normalize(IN.texcoord_3.xyz));
    vCubemap.y = dot(q1.xyz, normalize(IN.texcoord_2.xyz));
    vCubemap.x = dot(q1.xyz, normalize(IN.texcoord_1.xyz));
    q35.xyz = normalize(vCubemap.xyz);

    cubeCoord.xyz = ((2 * dot(q35.xyz, r2.xyz)) * q35.xyz) - (r2.xxyz * dot(q35.xyz, q35.xyz));
    cubeCoord.w = 0;

    // Negative EnvToggles.w means mask has alpha channel
    if (EnvToggles.w < 0.0) {
        cubeCoord.w = lerp(0, 9, pow(vEnvMask.a, 0.5));
    }

    vCubemap.xyzw = texCUBElod(EnvironmentCubeMap, cubeCoord);

    // EnvToggles.w is 1 if mask is present
    // EnvToggles.z is env map scale
    // MatAlpha.a is fade
    q5.rgb = ((vCubemap.rgb * (lerp(vNormalMap.a, vEnvMask.x, abs(EnvToggles.w)) * EnvToggles.z)) * MatAlpha.x) * IN.color_0.rgb;

    OUT.vColor.a = 1;
    OUT.vColor.rgb = q5.rgb * IN.texcoord_4.x;

    return OUT;
};