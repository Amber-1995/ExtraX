#include "TestScene.h"

#include "../GameObjects/GameObject.h"
#include "../Components/Components.h"
#include "../Scripts/Scripts.h"
#include "../Data/Data.h"

XX::TestScene::TestScene()
{
	
	auto camera = GameObject::Create();
	{
		camera->transform->position = XXVector3(0, 10, -15);
		auto c = Component::Create<Camera>();
		camera->AddComponent(c);

		auto cc = Component::Create <CameraController>();
		camera->AddComponent(cc);

		auto skybox = Component::Create<Skybox>();
		skybox->SetTexture(
			"Assets\\Textures\\Skybox\\FluffballDayTop.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayBottom.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayLeft.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayRight.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayFront.jpg",
			"Assets\\Textures\\Skybox\\FluffballDayBack.jpg"
		);
		camera->AddComponent(skybox);
	}
	AddGameObject(camera);
	

	auto ground = GameObject::Create();
	{
		auto f = Component::Create<Field>(40.0f, 40.0f);
		ground->AddComponent(f);
	}
	AddGameObject(ground);

	auto billboard = GameObject::Create();
	{
		auto b = Component::Create<Billboard>(10.0f, 10.0f, "Assets\\Textures\\transparent.png");
		billboard->AddComponent(b);
		auto a2d = Component::Create<Animation2D>();
		a2d->SetTarget(b);
		a2d->AddAnimationClip("Assets\\Textures\\explosion.png", 4, 4, "explosion", 0, 15, true, "explosion");
		a2d->SetEnterAnimation("explosion");
		a2d->AddAnimationEvent("explosion", 15, [billboard]() {billboard->transform->position += {0.0f, 1.0f, 0.0f}; });
		billboard->AddComponent(a2d);
	}
	AddGameObject(billboard);

}
