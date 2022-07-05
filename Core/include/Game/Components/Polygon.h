#ifndef CORE_POLYGON2D_H
#define CORE_POLYGON2D_H

#include "Game/Module.h"
#include "Game/Event.h"
#include "Common/Graphics.h"
#include "Common/Asset.h"
#include "Transform.h"

namespace XX::Game::Components
{
	class Rect2D : public Component, public Event::IRender2D, public Event::IOnStart
	{
	private:
		Mesh _mesh;
		Shader _shader;
		Transform* _transform = nullptr;

		void Render2D(size_t thread) override;

		void OnStart() override;

	public:
		Rect2D();
	};
}



#endif // !CORE_POLYGON2D_H
