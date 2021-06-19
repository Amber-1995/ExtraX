#include "Color.h"


XX::XXColor::XXColor() :
	r(0.0f), g(0.0f), b(0.0f), a(0.0f)
{

}

XX::XXColor::XXColor(const XXColor& other) :
	r(other.r), g(other.g), b(other.b), a(other.a)
{

}

XX::XXColor::XXColor(float r, float g, float b, float a) :
	r(r), g(g), b(b), a(a)
{

}

XX::XXColor::operator DirectX::XMFLOAT4()
{
	return DirectX::XMFLOAT4(r, g, b, a);
}

XX::XXColor& XX::XXColor::operator+=(const XXColor& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;

	return *this;
}

XX::XXColor& XX::XXColor::operator-=(const XXColor& other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	a -= other.a;

	return *this;
}

XX::XXColor& XX::XXColor::operator*=(float other)
{
	r *= other;
	g *= other;
	b *= other;
	a *= other;

	return *this;
}

XX::XXColor& XX::XXColor::operator/=(float other)
{
	r /= other;
	g /= other;
	b /= other;
	a /= other;

	return *this;
}

XX::XXColor XX::XXColor::operator+() const
{
	return XXColor(r, g, b, a);
}

XX::XXColor XX::XXColor::operator-() const
{
	return XXColor(-r, -g, -b, -a);
}

XX::XXColor XX::XXColor::operator+(const XXColor& other) const
{
	return XXColor(r + other.r, g + other.g, b + other.b, a + other.a);
}

XX::XXColor XX::XXColor::operator-(const XXColor& other) const
{
	return XXColor(r - other.r, g - other.g, b - other.b, a - other.a);
}

XX::XXColor XX::XXColor::operator*(float other) const
{
	return XXColor(r * other, g * other, b * other, a * other);
}

XX::XXColor XX::XXColor::operator/(float other) const
{
	return XXColor(r / other, g / other, b / other, a / other);
}

bool XX::XXColor::operator==(const XXColor& other) const
{
	return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
}

bool XX::XXColor::operator!=(const XXColor& other) const
{
	return (r != other.r) || (g != other.g) || (b != other.b) || (a != other.a);
}