#pragma once
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "Sprite.h"

namespace XX
{

	class Billboard : public Sprite3D
	{
	/*====================�R���X�g���N�^�[�ƃf�X�g���N�^�[====================*/
	public:
		virtual ~Billboard() = default;
	private:
		Billboard(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);
		Billboard(const Billboard&) = delete;
		Billboard& operator=(const Billboard&) = delete;

	/*================================���\�b�h================================*/
	public:
		void Render3D() override;

	/*================================�t�����h================================*/
		friend class Component;
	};

}



#endif // !_BILLBOARD_H_
