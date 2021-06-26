#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"

namespace XX
{
	class Sprite : public Component
	{
	/*====================�R���X�g���N�^�[�ƃf�X�g���N�^�[====================*/
	public:
		virtual ~Sprite() = default;
	protected:
		Sprite(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

	/*================================�����o�[================================*/
	public:
		const float& width;
		const float& height;
	protected:
		float _width;
		float _height;
		VertexShaderPtr _vertex_shader;
		PixelShaderPtr _pixel_shader;
		MeshPtr _mesh;
		DirectX::XMMATRIX _adj_matrix;

	/*================================���\�b�h================================*/
	public:
		void SetTexture(TexturePtr texture);
		void SetVertex(const XXVertex3D* vertex_data);
	};
	typedef std::shared_ptr<Sprite> SpritePtr;




	class Sprite2D : public Sprite, public IRender2D
	{
	/*====================�R���X�g���N�^�[�ƃf�X�g���N�^�[====================*/
	public:
		virtual ~Sprite2D() = default;
	private:
		Sprite2D(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);
		Sprite2D(const Sprite2D&) = delete;
		Sprite2D& operator=(const Sprite2D&) = delete;

	/*================================���\�b�h================================*/
	public:
		void Render2D() override;

	/*================================�t�����h================================*/
		friend class Component;
	};
	typedef std::shared_ptr<Sprite2D> Sprite2DPtr;





	class Sprite3D : public Sprite, public IRender3D
	{
	/*====================�R���X�g���N�^�[�ƃf�X�g���N�^�[====================*/
	public:
		virtual ~Sprite3D() = default;
	protected:
		Sprite3D(float width, float height, const std::string& texture_file = DEFAULT_TEXTRUE);
		Sprite3D(const Sprite3D&) = delete;
		Sprite3D& operator=(const Sprite3D&) = delete;
	
	/*================================���\�b�h================================*/
	public:
		void Render3D() override;

	/*================================�t�����h================================*/
		friend class Component;
	};
	typedef std::shared_ptr<Sprite3D> Sprite3DPtr;

}

#endif // !_SPRITE_H_

