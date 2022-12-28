#pragma once
#ifndef EXTRAX_GLM_MATHEMATICS_BASE_H
#define EXTRAX_GLM_MATHEMATICS_BASE_H


#include <ExtraX/Mathematics/Color/ColorBase.h>
#include <ExtraX/Mathematics/Matrix/GLMMatrix.h>
#include <ExtraX/Mathematics/Quaternion/GLMQuternion.h>
#include <ExtraX/Mathematics/Vector/GLMVector.h>


namespace ExtraX::Mathematics::Base
{
	
	template<>
	class Math<MATHEMATICS_LIB::GLM>
	{
	public:
		Math() = delete;
	};


}





#endif // !EXTRAX_GLM_MATHEMATICS_BASE_H
