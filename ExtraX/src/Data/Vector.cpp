#include "Vector.h"

XX::XXVector3::XXVector3():
	x(0.0f),y(0.0f),z(0.0f)
{

}

XX::XXVector3::XXVector3(const XXVector3& other) :
	x(other.x), y(other.y), z(other.z)
{

}

XX::XXVector3::XXVector3(float x, float y, float z) :
	x(x), y(y), z(z)
{

}

float XX::XXVector3::GetLength()
{
	return sqrtf(x*x+y*y+z*z);
}

XX::XXVector3::operator DirectX::XMFLOAT3()
{ 
	return DirectX::XMFLOAT3(x, y, z);
}

XX::XXVector3::operator DirectX::XMFLOAT3() const
{
	return DirectX::XMFLOAT3(x, y, z);
}

XX::XXVector3& XX::XXVector3::operator+=(const XXVector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

XX::XXVector3& XX::XXVector3::operator-=(const XXVector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

XX::XXVector3& XX::XXVector3::operator*=(float other)
{
	x *= other;
	y *= other;
	z *= other;

	return *this;
}

XX::XXVector3& XX::XXVector3::operator/=(float other)
{
	x /= other;
	y /= other;
	z /= other;

	return *this;
}

XX::XXVector3 XX::XXVector3::operator+() const
{
	return XXVector3(x,y,z);
}

XX::XXVector3 XX::XXVector3::operator-() const
{
	return XXVector3(-x, -y, -z);
}

XX::XXVector3 XX::XXVector3::operator+(const XXVector3& other) const
{
	return XXVector3(x + other.x, y + other.y, z + other.z);
}

XX::XXVector3 XX::XXVector3::operator-(const XXVector3& other) const
{
	return XXVector3(x - other.x, y - other.y, z - other.z);
}

XX::XXVector3 XX::XXVector3::operator*(float other) const
{
	return XXVector3(x * other, y * other, z * other);
}

XX::XXVector3 XX::XXVector3::operator/(float other) const
{
	return XXVector3(x / other, y / other, z / other);
}

bool XX::XXVector3::operator==(const XXVector3& other) const
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

bool XX::XXVector3::operator!=(const XXVector3& other) const
{
	return (x != other.x) || (y != other.y) || (z != other.z);
}


//=================================================================================================================================================

XX::XXVector3P::XXVector3P(DirectX::XMVECTOR& target, std::function<void()> refresh_target, float x, float y, float z) :
	_data(x, y, z),
	_target(target),
	_refresh_target(refresh_target),
	x(_data.x), y(_data.y), z(_data.z)
{
	_Refresh();
}

XX::XXVector3P& XX::XXVector3P::operator=(const XXVector3& other)
{
	_data.x = other.x;
	_data.y = other.y;
	_data.z = other.z;

	_Refresh();
	return *this;
}

XX::XXVector3P& XX::XXVector3P::operator=(const XXVector3P& other)
{
	_data.x = other.x;
	_data.y = other.y;
	_data.z = other.z;

	_Refresh();
	return *this;
}

XX::XXVector3P::operator XX::XXVector3()
{
	return XX::XXVector3(_data.x, _data.y, _data.z);
}

XX::XXVector3P::operator DirectX::XMFLOAT3()
{
	return DirectX::XMFLOAT3(_data.x, _data.y, _data.z);
}

XX::XXVector3P::operator DirectX::XMFLOAT3() const
{
	return DirectX::XMFLOAT3(_data.x, _data.y, _data.z);
}

XX::XXVector3P& XX::XXVector3P::operator+=(const XXVector3& other)
{
	_data.x += other.x;
	_data.y += other.y;
	_data.z += other.z;
	_Refresh();

	return *this;
}

XX::XXVector3P& XX::XXVector3P::operator-=(const XXVector3& other)
{
	_data.x -= other.x;
	_data.y -= other.y;
	_data.z -= other.z;
	_Refresh();

	return *this;
}

XX::XXVector3P& XX::XXVector3P::operator*=(float other)
{
	_data.x *= other;
	_data.y *= other;
	_data.z *= other;
	_Refresh();

	return *this;
}

XX::XXVector3P& XX::XXVector3P::operator/=(float other)
{
	_data.x /= other;
	_data.y /= other;
	_data.z /= other;
	_Refresh();

	return *this;
}

XX::XXVector3 XX::XXVector3P::operator+() const
{
	return XXVector3(x, y, z);
}

XX::XXVector3 XX::XXVector3P::operator-() const
{
	return XXVector3(-x, -y, -z);
}

XX::XXVector3 XX::XXVector3P::operator+(const XXVector3& other) const
{
	return XXVector3(x + other.x, y + other.y, z + other.z);
}

XX::XXVector3 XX::XXVector3P::operator-(const XXVector3& other) const
{
	return XXVector3(x - other.x, y - other.y, z - other.z);
}

XX::XXVector3 XX::XXVector3P::operator*(float other) const
{
	return XXVector3(x * other, y * other, z * other);
}

XX::XXVector3 XX::XXVector3P::operator/(float other) const
{
	return XXVector3(x / other, y / other, z / other);
}

bool XX::XXVector3P::operator==(const XXVector3& other) const
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

bool XX::XXVector3P::operator!=(const XXVector3& other) const
{
	return (x != other.x) || (y != other.y) || (z != other.z);
}

void XX::XXVector3P::_Refresh()
{
	_target = DirectX::XMLoadFloat3(&_data);
	_refresh_target();
}
