#pragma once
#ifndef EXTRAX_RESOURCE_MANAGER_H
#define EXTRAX_RESOURCE_MANAGER_H

#include <ExtraX/Common.h>

namespace ExtraX
{
	template<typename RESOURCE>
	class ResourceManager
	{
	private:
		std::unordered_map<std::string, RESOURCE> _resources;

		void(*_release)(RESOURCE);

	public:
		ResourceManager(void(*release)(RESOURCE)) : _release(release)
		{
		}

		ResourceManager& operator=(const ResourceManager&) = delete;

		virtual ~ResourceManager() = default;

		bool IsExist(const char* key) const
		{
			return _resources.end() != _resources.find(key);
		}

		RESOURCE Get(const char* key)
		{
			return _resources[key];
		}

		void Add(const char* key, RESOURCE resource)
		{
			_resources[key] = resource;
		}

		void Remove(const char* key)
		{
			auto temp = _resources.find(key);
			if (temp != _resources.end())
			{
				_release(temp->second);
				_resources.erase(temp);
			}
		}

		void Clear()
		{
			for (auto& key_resource : _resources)
			{
				_release(key_resource.second);
			}
			_resources.clear();
		}

	};
}


#endif // !EXTRAX_RESOURCE_MANAGER_H
