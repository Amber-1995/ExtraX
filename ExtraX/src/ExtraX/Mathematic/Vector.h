#pragma once
#ifndef EXTRAX_VECTOR_H
#define EXTRAX_VECTOR_H



#include <ExtraX/Mathematic/MathematicBase.h>





namespace ExtraX::Mathematic::Base
{
	template<typename SCALAR, int Size>
	class Vector : public VectorBase<SCALAR, Size>
	{
	public:
		Vector() = default;

		template<typename ...ARGS> requires (sizeof...(ARGS) == Size && (std::conjunction<std::is_convertible<ARGS, T>...>::value))
		Vector(ARGS ...args) :
			VectorBase<SCALAR, Size>(args...)
		{
		}

		virtual ~Vector() = default;

		Vector& operator=(const Vector& other)
		{
			return *this;
		}

		Vector& operator+=(const Vector& other)
		{
			return *this;
		}

		Vector& operator-=(const Vector& other)
		{
			return *this;
		}

		Vector& operator*=(const Vector& other)
		{
			return *this;
		}

		Vector& operator/=(const Vector& other)
		{
			return *this;
		}
			
	};

	template<typename SCALAR, int Size>
	Vector<SCALAR, Size> operator+(const Vector<SCALAR, Size>& v)
	{
		return v;
	}

	template<typename SCALAR, int Size>
	Vector<SCALAR, Size> operator-(const Vector<SCALAR, Size>& v)
	{

	}

	template<typename SCALAR, int Size>
	Vector<SCALAR, Size> operator+(const Vector<SCALAR, Size>& v1, const Vector<SCALAR, Size>& v2)
	{

	}

	template<typename SCALAR, int Size>
	Vector<SCALAR, Size> operator-(const Vector<SCALAR, Size>& v1, const Vector<SCALAR, Size>& v2)
	{

	}

	template<typename SCALAR, int Size>
	Vector<SCALAR, Size> operator*(const Vector<SCALAR, Size>& v1, const Vector<SCALAR, Size>& v2)
	{

	}

	template<typename SCALAR, int Size>
	Vector<SCALAR, Size> operator/(const Vector<SCALAR, Size>& v1, const Vector<SCALAR, Size>& v2)
	{

	}
}

namespace ExtraX::Mathematic
{
	template<int Size>
	using Vector = Base::Vector<DEFAULT_VECTOR_SCALAR_TYPE, Size>;
}

#endif // !EXTRAX_VECTOR_H

