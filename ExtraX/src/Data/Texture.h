#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"
#include "ExtraXType.h"
#include <string>

namespace XX
{
	class Texture : public Resource<Texture>
	{
	public:
		void Apply() override;

		virtual ~Texture() = default;
	private:
		ID3D11ShaderResourceViewPtr _texture;

		ID3D11ResourcePtr _texture_resource;

		Texture(const std::string& file_name);

		friend class Resource<Texture>;
	};

	typedef std::shared_ptr<Texture> TexturePtr;
	std::unordered_map<std::string, TexturePtr> Texture::_resources;
}


#endif // !_TEXTURE_H_
