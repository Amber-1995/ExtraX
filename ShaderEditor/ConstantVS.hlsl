#include "Common.hlsl"

cbuffer ViewBuffer2D : register(b0)
{
	matrix View2D;
}

cbuffer ProjectionBuffer2D : register(b1)
{
	matrix Projection2D;
}

cbuffer ViewBuffer : register(b2)
{
	matrix View;
}

cbuffer ProjectionBuffer : register(b3)
{
	matrix Projection;
}

cbuffer WorldBuffer : register(b4)
{
	matrix World;
}

cbuffer TexcoordOffsetBuffer : register(b5)
{
	TexcoordOffset Offset;
}
