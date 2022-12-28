#pragma once
#ifndef EXTRAX_MATRIX_BASE_H
#define EXTRAX_MATRIX_BASE_H

#include <ExtraX/Common.h>
namespace ExtraX::Mathematics::Base
{
	template<MATHEMATICS_LIB>
	class Math;

	template<typename SCALAR, int M, int N, typename MATRIX_TYPE = SCALAR[M][N]> requires(sizeof(MATRIX_TYPE) == M * N * sizeof(SCALAR))
	class MatrixBase
	{
	protected:
		MATRIX_TYPE _matrix;

		MatrixBase() :
			 _matrix()
		{
		}

		template<typename ...ARGS> requires (sizeof...(ARGS) == M * N && std::conjunction<std::is_convertible<ARGS, SCALAR>...>::value)
		MatrixBase(ARGS ...args) :
			_matrix{ args... }
		{
		}
	};

	template<MATHEMATICS_LIB, typename SCALAR, int M, int N>
	class Matrix;
}



#endif // !EXTRAX_MATRIX_BASE_H

