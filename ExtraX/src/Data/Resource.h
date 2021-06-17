#pragma once
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#pragma warning(push)
#pragma warning(disable:4005)
#include <d3d11.h>
#pragma warning(pop)

#include <map>
#include <string>

namespace XX
{
	template<class T >
	class Resource
	{
	public:
		static T* Load(std::string file_name);

		virtual void Apply() = 0;

	protected:
		static std::map<std :: string, T*> _resources;
	};

	template<class T>
	inline T* Resource<T>::Load(std::string file_name)
	{
		if (_resources.count(file_name) != 0)
		{
			return _resources[file_name];
		}

		T* new_texture = new T(file_name);
		_resources[file_name] = new_texture;

		return new_texture;
	}

}

#endif // !_RESOURCE_H_
