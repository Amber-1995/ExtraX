#pragma once
#ifndef EXTRAX_GLM_QUATERNION_H
#define EXTRAX_GLM_QUATERNION_H

#include <ExtraX/Mathematics/Quaternion/QuaternionBase.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace ExtraX::Mathematics::Base
{
	template<typename SCALAR>
	class Quaternion<MATHEMATICS_LIB::GLM, SCALAR> : public QuaternionBase<SCALAR,glm::qua<SCALAR,glm::qualifier::defaultp>>
	{
		friend class Math<MATHEMATICS_LIB::GLM>;
	private:
		using BaseType = QuaternionBase<SCALAR, glm::qua<SCALAR, glm::qualifier::defaultp>>;
		using BaseType::_quaternion;
	public:
		using BaseType::x;
		using BaseType::y;
		using BaseType::z;
		using BaseType::w;
		Quaternion() :
			BaseType()
		{
		}

		Quaternion(SCALAR x, SCALAR y, SCALAR z, SCALAR w):
			BaseType(x, y, z, w)
		{
		}

	};

}



#endif //!EXTRAX_GLM_QUATERNION_H