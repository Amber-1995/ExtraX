#pragma once
#ifndef _RESOURCE_H_
#define _RESOURCE_H_


#include <d3d11.h>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <memory>

#include "../Helper.h"

namespace XX
{
	template<class T>
	class Resource
	{
	public:
		static std::shared_ptr<T> Load(std::string file_name);

		virtual void Apply() = 0;
	protected:
		static std::unordered_map<std::string, std::shared_ptr<T>> _resources;

	};

	template<class T>
	inline std::shared_ptr<T> Resource<T>::Load(std::string file_name)
	{
		std::wstring wide = std::filesystem::absolute(file_name);
		std::string full_path = StringHelper::ToNarrow(wide);

		auto target = _resources.find(full_path);
		if (target != _resources.end()){
			return target->second;
		}


		std::shared_ptr<T> res(new T(file_name));
		_resources[full_path] = res;

		return res;
	}
}

#endif // !_RESOURCE_H_
