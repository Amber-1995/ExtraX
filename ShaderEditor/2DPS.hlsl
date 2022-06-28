#include "ConstantPS.hlsl"

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	outDiffuse = DiffuseTexture.Sample(SamplerState0, In.TexCoord);
	outDiffuse *= In.Diffuse;
}