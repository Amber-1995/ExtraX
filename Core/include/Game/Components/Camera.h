#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include "Common/ExtraX.h"
#include "Common/Math.h"
#include "Game/Module.h"
#include "Game/Event/Event.h"
#include "Transform.h"

namespace XX::Game::Components
{
	XXAPI class Camera : public Component, public Event::IOnStart, public Event::IOnTransform
	{
	private:
		inline static Camera* _main_camera = nullptr;

		Math::Matrix _view_matrix = DirectX::XMMatrixIdentity();

		Math::Matrix _projection_matrix = DirectX::XMMatrixIdentity();

		Transform* _transform = nullptr;

		void OnStart() override;

		void OnTransform() override;

	public:
		Camera();

		void SetMainCamera();

		static void Set(size_t thread);

	};
}

#endif //!CORE_CAMERA_H