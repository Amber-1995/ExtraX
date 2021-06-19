#pragma once
#ifndef _COLOR_H_
#define _COLOR_H_
#include <DirectXMath.h>

namespace XX
{
	class XXColor
	{
	public:
		float r;
		float g;
		float b;
		float a;

		XXColor();
		XXColor(const XXColor&);
		XXColor(float r, float g, float b, float a);

		operator DirectX::XMFLOAT4();

		XXColor& operator += (const XXColor&);
		XXColor& operator -= (const XXColor&);
		XXColor& operator *= (float);
		XXColor& operator /= (float);

		XXColor operator + () const;
		XXColor operator - () const;

		XXColor operator + (const XXColor&) const;
		XXColor operator - (const XXColor&) const;
		XXColor operator * (float) const;
		XXColor operator / (float) const;

		bool operator == (const XXColor&) const;
		bool operator != (const XXColor&) const;
	};
}

#endif // !_COLOR_H_
