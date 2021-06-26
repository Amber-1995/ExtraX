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
	/*====================コンストラクターとデストラクター====================*/
	public:
		virtual ~Camera() = default;
	private:
		Camera();
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;

	/*==========================スタティックメンバー==========================*/
	public:
		static Camera* const& main_camera;
	private:
		static Camera* _main_camera;
	
	/*================================メンバー================================*/
	private:
		XMMATRIX _view_matrix;
		XMMATRIX _projection_matrix;

	/*================================メソッド================================*/
	public:
		void Update();

	/*================================フレンド================================*/
		friend class Component;
	};
	typedef std::shared_ptr<Camera> CameraPtr;
}

#endif // !_CAMERA_H_
