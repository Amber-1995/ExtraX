#include "Common.hlsl"

cbuffer WorldBuffer2D : register(b0)
{
	matrix World2D;
}

cbuffer ViewBuffer2D : register(b1)
{
	matrix View2D;
}

cbuffer ProjectionBuffer2D : register(b2)
{
	matrix Projection2D;
}

cbuffer WorldBuffer : register(b3)
{
	matrix World;
}

cbuffer ViewBuffer : register(b4)
{
	matrix View;
}

cbuffer ProjectionBuffer : register(b5)
{
	matrix Projection;
}

cbuffer TexCoordOffsetBuffer : register(b6)
{
	float2 TexCoordOffset;
}
