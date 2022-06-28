#include "Common.hlsl"


cbuffer LightBuffer : register(b6)
{
	LIGHT Light;
}

cbuffer MaterialBuffer : register(b7)
{
	MATERIAL Material;
}

cbuffer CameraParameterBuffer : register(b8)
{
	CameraParameter Camera;
}

cbuffer ExtraParameterBuffer : register(b9)
{
	ExtraParameter Extra;
}


Texture2D ShadowTexture : register(t0);

Texture2D DiffuseTexture : register(t1);

Texture2D NormalTexture : register(t2);

SamplerState SamplerState0 : register(s0);

SamplerState SamplerState1 : register(s1);

SamplerState SamplerState2 : register(s2);