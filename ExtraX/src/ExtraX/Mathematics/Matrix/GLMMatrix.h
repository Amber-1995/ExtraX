#pragma once
#ifndef EXTRAX_GLM_MATRIX_H
#define EXTRAX_GLM_MATRIX_H


#include <ExtraX/Mathematics/Matrix/MatrixBase.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
namespace ExtraX::Mathematics::Base
{
	template<typename SCALAR, int M, int N>
	class Matrix<MATHEMATICS_LIB::GLM, SCALAR, M, N> : public MatrixBase<SCALAR,M,N,glm::mat<M,N, SCALAR, glm::qualifier::defaultp>>
	{
		template<MATHEMATICS_LIB, typename, int, int>friend class Matrix;
		friend class Math<MATHEMATICS_LIB::GLM>;
	private:
		using BaseType = MatrixBase<SCALAR, M, N, glm::mat<M, N, SCALAR, glm::qualifier::defaultp>>;
		using BaseType::_matrix;

	public:
		Matrix() :
			BaseType()
		{
		}

		template<typename ...ARGS> requires (sizeof...(ARGS) == M * N && std::conjunction<std::is_convertible<ARGS, SCALAR>...>::value)
		Matrix(ARGS ...args) :
			BaseType( args... )
		{
		}

		Matrix& operator=(const Matrix& other)
		{
			_matrix = other._matrix; 
			return *this;
		}

		Matrix& operator+=(const Matrix& other)
		{
			_matrix += other._matrix;
			return *this;
		}

		Matrix& operator-=(const Matrix& other)
		{
			_matrix -= other._matrix;
			return *this;
		}

		Matrix& operator*=(SCALAR value)
		{
			_matrix *= value;
			return *this;
		}

		Matrix& operator/=(SCALAR value)
		{
			_matrix /= value;
			return *this;
		}

		Matrix operator+()
		{
			return *this;
		}

		Matrix operator-()
		{
			Matrix result;
			result._matrix = -_matrix;
			return result;
		}

		Matrix operator+(const Matrix& other)
		{
			Matrix result;
			result._matrix = _matrix + other._matrix;
			return result;
		}

		Matrix operator-(const Matrix& other)
		{
			Matrix result;
			result._matrix = _matrix - other._matrix;
			return result;
		}

		Matrix operator*(SCALAR value)
		{
			Matrix result;
			result._matrix = _matrix * value;
			return result;
		}

		Matrix operator/(SCALAR value)
		{
			Matrix result;
			result._matrix = _matrix / value;
			return result;
		}

		template<size_t P>
		Matrix<MATHEMATICS_LIB::GLM, SCALAR,M, P> operator* (Matrix<MATHEMATICS_LIB::GLM, SCALAR, N, P>& other)
		{
			Matrix<MATHEMATICS_LIB::GLM, SCALAR, M, P> result;
			result._matrix = _matrix * other._matrix;
			return result;
		}

	};


}



#endif // !EXTRAX_GLM_MATRIX_H
