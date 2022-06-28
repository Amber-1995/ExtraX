#include "Common.hlsl"


cbuffer LightBuffer : register(b7)
{
	LIGHT Light;
}

cbuffer MaterialBuffer : register(b8)
{
	MATERIAL Material;
}

cbuffer CameraParameterBuffer : register(b9)
{
	CameraParameter Camera;
}

cbuffer ExtraParameterBuffer : register(b10)
{
	ExtraParameter Extra;
}


Texture2D ShadowTexture : register(t0);

Texture2D DiffuseTexture : register(t1);

Texture2D NormalTexture : register(t2);

SamplerState SamplerState0 : register(s0);

SamplerState SamplerState1 : register(s1);

SamplerState SamplerState2 : register(s2);