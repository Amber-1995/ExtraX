#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"


namespace XX
{
	class Texture : public Resource<Texture>
	{
	public:
		void Apply() override;

	private:

		ID3D11ShaderResourceView* _texture;

		Texture(const std::string& file_name);

		virtual ~Texture() = default;

		friend class Resource<Texture>;
	};

	std::map<std::string, Texture*> Texture::_resources;

}


#endif // !_TEXTURE_H_
