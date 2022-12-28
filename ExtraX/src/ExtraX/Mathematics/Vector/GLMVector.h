#pragma once
#ifndef EXTRAX_GLM_VECTOR_H
#define EXTRAX_GLM_VECTOR_H

#include <ExtraX/Mathematics/Vector/VectorBase.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace ExtraX::Mathematics::Base
{
	template<typename SCALAR, int Size>
	class Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> : public VectorBase<SCALAR, Size, glm::vec<Size, SCALAR, glm::qualifier::defaultp>>
	{
		friend class Math<MATHEMATICS_LIB::GLM>;
		friend Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator+<MATHEMATICS_LIB::GLM, SCALAR, Size>(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&);
		friend Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator-<MATHEMATICS_LIB::GLM, SCALAR, Size>(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&);
		friend Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator+<MATHEMATICS_LIB::GLM, SCALAR, Size>(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&, const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&);
		friend Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator-<MATHEMATICS_LIB::GLM, SCALAR, Size>(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&, const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&);
		friend Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator*<MATHEMATICS_LIB::GLM, SCALAR, Size>(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&, SCALAR);
		friend Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator*<MATHEMATICS_LIB::GLM, SCALAR, Size>(SCALAR, const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&);
		friend Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator/<MATHEMATICS_LIB::GLM, SCALAR, Size>(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>&, SCALAR);
	private:
		using BaseType = VectorBase<SCALAR, Size, glm::vec<Size, SCALAR, glm::qualifier::defaultp>>;
		using BaseType::_vector;
	public:
		Vector():
			BaseType()
		{

		}

		template<typename ...ARGS> requires (sizeof...(ARGS) == Size && (std::conjunction<std::is_convertible<ARGS, SCALAR>...>::value))
		Vector(ARGS ...args) :
			BaseType(args...)
		{
		}

		Vector& operator=(const Vector& other)
		{
			_vector = other._vector;
			return *this;
		}

		Vector& operator+=(const Vector& other)
		{
			_vector += other._vector;
			return *this;
		}

		Vector& operator-=(const Vector& other)
		{
			_vector -= other._vector;
			return *this;
		}

		Vector& operator*=(SCALAR value)
		{
			_vector *= value;
			return *this;
		}

		Vector& operator/=(SCALAR value)
		{
			_vector /= value;
			return *this;
		}

	};

	template<typename SCALAR, int Size>
	Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator+(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v)
	{
		return v;
	}

	template<typename SCALAR, int Size>
	Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator-(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v)
	{
		Vector<SCALAR, Size> result;
		result._vector = -v._vector;
		return result;
	}

	template<typename SCALAR, int Size>
	Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator+(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v1, const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v2)
	{
		Vector<SCALAR, Size> result;
		result._vector = v1._vector + v2._vector;
		return result;
	}

	template<typename SCALAR, int Size>
	Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator-(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v1, const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v2)
	{
		Vector<SCALAR, Size> result;
		result._vector = v1._vector - v2._vector;
		return result;
	}

	template<typename SCALAR, int Size>
	Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator*(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v, SCALAR value)
	{
		Vector<SCALAR, Size> result;
		result._vector = v._vector * value;
		return result;
	}

	template<typename SCALAR, int Size>
	Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator*( SCALAR value, const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v)
	{
		Vector<SCALAR, Size> result;
		result._vector = v._vector * value;
		return result;
	}

	template<typename SCALAR, int Size>
	Vector<MATHEMATICS_LIB::GLM, SCALAR, Size> operator/(const Vector<MATHEMATICS_LIB::GLM, SCALAR, Size>& v, SCALAR value)
	{
		Vector<SCALAR, Size> result;
		result._vector = v._vector / value;
		return result;
	}
}

#endif // !EXTRAX_GLM_VECTOR_H

