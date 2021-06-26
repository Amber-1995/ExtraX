#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Component.h"
#include "../Events/Events.h"
#include "../Data/Data.h"


using DirectX::XMMATRIX;

namespace XX
{
	class Camera : public Component
	{
	/*====================�R���X�g���N�^�[�ƃf�X�g���N�^�[====================*/
	public:
		virtual ~Camera() = default;
	private:
		Camera();
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;

	/*==========================�X�^�e�B�b�N�����o�[==========================*/
	public:
		static Camera* const& main_camera;
	private:
		static Camera* _main_camera;
	
	/*================================�����o�[================================*/
	private:
		XMMATRIX _view_matrix;
		XMMATRIX _projection_matrix;

	/*================================���\�b�h================================*/
	public:
		void Update();

	/*================================�t�����h================================*/
		friend class Component;
	};
	typedef std::shared_ptr<Camera> CameraPtr;
}

#endif // !_CAMERA_H_
