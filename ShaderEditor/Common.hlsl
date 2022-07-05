struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};


struct PS_IN
{
	float4 Position			: SV_POSITION;
	float4 Normal			: NORMAL0;
	float4 WorldPosition	: POSITION0;
	float4 Diffuse			: COLOR0;
	float2 TexCoord			: TEXCOORD0;
	float4 ShadowPosition	: POSITION1;
};

struct LIGHT
{
	bool Enable;
	int LightType;
	bool2 Dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
	float4 Position;
	float4 Angle;
	matrix View;
	matrix Projection;
};

struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	float3 Dummy;
};

struct TexcoordOffset
{
	float x;
	float y;
	float dummy[2];
};


struct CameraParameter
{
	float4 Position;
};

struct ExtraParameter
{
	float dummy[4];
};