#pragma once
#ifndef EXTRAX_DESIGN_PATTERN_H
#define EXTRAX_DESIGN_PATTERN_H


#include <ExtraX/Common.h>

namespace ExtraX
{

	template<typename INSTANCE_TYPE>
	class Singleton
	{
	private:
		inline static std::unique_ptr<INSTANCE_TYPE> _instance = nullptr;

		inline static INSTANCE_TYPE* CreateSingleton()
		{
			return new INSTANCE_TYPE();
		}


	public:
		Singleton() = delete;

		inline static INSTANCE_TYPE* GetSingleton()
		{
			if (_instance.get())
			{
				return _instance.get();
			}

			_instance.reset(CreateSingleton());
			return _instance.get();
		}
	};

	template<typename INSTANCE_TYPE>
	INSTANCE_TYPE& singleton = *Singleton<INSTANCE_TYPE>::GetSingleton();
}



#endif // !EXTRAX_DESIGN_PATTERN_H


