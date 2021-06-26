#pragma once
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "Sprite.h"

namespace XX
{

	class Billboard : public Sprite3D
	{
	/*====================コンストラクターとデストラクター====================*/
	public:
		virtual ~Billboard() = default;
	private:
		Billboard(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);
		Billboard(const Billboard&) = delete;
		Billboard& operator=(const Billboard&) = delete;

	/*================================メソッド================================*/
	public:
		void Render3D() override;

	/*================================フレンド================================*/
		friend class Component;
	};

}



#endif // !_BILLBOARD_H_
