#pragma once
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "Sprite.h"

namespace XX
{

	class Billboard : public Sprite3D
	{
	public:
		void Render3D() override;

	public:
		Billboard(float width, float height, const std::string& texture_file);

		friend class Component;
	};

}



#endif // !_BILLBOARD_H_