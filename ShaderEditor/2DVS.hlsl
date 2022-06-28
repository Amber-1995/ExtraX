#include "ConstantVS.hlsl"

void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World2D, View2D);
	wvp = mul(wvp, Projection2D);

	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse;

}