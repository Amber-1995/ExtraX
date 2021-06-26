#pragma once
#ifndef _HELPER_H_
#define _HELPER_H_

#include <string>

namespace XX
{
	class StringHelper
	{
	public:
		static std::wstring StringToWide(std::string str);
		static std::string GetDirectoryFromPath(const std::string& filepath);
		static std::string GetFileExtension(const std::string& filename);
	};
}


#endif // !_HELPER_H_
