#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <functional>

namespace XX
{
	class XXVector3
	{
	public:
		float x;
		float y;
		float z;

		XXVector3();
		XXVector3(const XXVector3&);
		XXVector3(float x, float y, float z);

		float GetLength();

		operator DirectX::XMFLOAT3();
		operator DirectX::XMFLOAT3() const;

		XXVector3& operator += (const XXVector3&);
		XXVector3& operator -= (const XXVector3&);
		XXVector3& operator *= (float);
		XXVector3& operator /= (float);

		XXVector3 operator + () const;
		XXVector3 operator - () const;

		XXVector3 operator + (const XXVector3&) const;
		XXVector3 operator - (const XXVector3&) const;
		XXVector3 operator * (float) const;
		XXVector3 operator / (float) const;

		bool operator == (const XXVector3&) const;
		bool operator != (const XXVector3&) const;
	};

	class XXVector3P
	{
	public:
		const float& x;
		const float& y;
		const float& z;

		XXVector3P(DirectX::XMVECTOR& target, std::function<void()> refresh_target, float x = 0.0f, float y = 0.0f, float z = 0.0f);
		XXVector3P(const XXVector3P&) = delete;

		operator XX::XXVector3();
		operator DirectX::XMFLOAT3();
		operator DirectX::XMFLOAT3() const;

		XXVector3P& operator=(const XXVector3&);
		XXVector3P& operator=(const XXVector3P&);

		XXVector3P& operator += (const XXVector3&);
		XXVector3P& operator -= (const XXVector3&);
		XXVector3P& operator *= (float);
		XXVector3P& operator /= (float);

		XXVector3 operator + () const;
		XXVector3 operator - () const;

		XXVector3 operator + (const XXVector3&) const;
		XXVector3 operator - (const XXVector3&) const;
		XXVector3 operator * (float) const;
		XXVector3 operator / (float) const;

		bool operator == (const XXVector3&) const;
		bool operator != (const XXVector3&) const;


	private:
		DirectX::XMFLOAT3 _data;
		DirectX::XMVECTOR& _target;
		std::function<void()> _refresh_target;

		void _Refresh();
	};
}


#endif // !_VECTOR_H_
