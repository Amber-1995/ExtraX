#pragma once
#ifndef EXTRAX_QUATERNION_BASE_H
#define EXTRAX_QUATERNION_BASE_H

#include <ExtraX/Common.h>

namespace ExtraX::Mathematics::Base
{
	template<MATHEMATICS_LIB>
	class Math;

	template< typename SCALAR, typename QUATERNION_TYPE = SCALAR[4] > requires(sizeof(QUATERNION_TYPE) == sizeof(SCALAR) * 4)
	class QuaternionBase
	{
	protected:
		union
		{
			QUATERNION_TYPE _quaternion;
			struct
			{
				SCALAR x;
				SCALAR y;
				SCALAR z;
				SCALAR w;
			};
		};

		QuaternionBase():
			_quaternion()
		{
		}

		QuaternionBase(SCALAR x, SCALAR y, SCALAR z, SCALAR w) :
			_quaternion(w,x,y,z)
		{
		}
	};

	template<MATHEMATICS_LIB, typename SCALAR>
	class Quaternion;
}



#endif // !EXTRAX_QUATERNION_BASE_H
