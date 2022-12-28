#pragma once
#ifndef EXTRAX_MATHEMATICS_H
#define EXTRAX_MATHEMATICS_H


#include <ExtraX/Mathematics/GLMMathematics.h>


namespace ExtraX::Mathematics
{
	using Color = Base::Color<DEFAULT_MATHEMATICS_LIB, DEFAULT_COLOR_SCALAR_TYPE>;

	template<int M,int N>
	using Matrix = Base::Matrix<DEFAULT_MATHEMATICS_LIB, DEFAULT_MATRIX_SCALAR_TYPE, M, N>;

	using Quaternion = Base::Quaternion<DEFAULT_MATHEMATICS_LIB, DEFAULT_QUATERNION_SCALAR_TYPE>;

	template<int Size>
	using Vector = Base::Vector<DEFAULT_MATHEMATICS_LIB, DEFAULT_VECTOR_SCALAR_TYPE, Size>;

	using Math = Base::Math<DEFAULT_MATHEMATICS_LIB>;
}


#endif // !EXTRAX_MATHEMATICS_H
