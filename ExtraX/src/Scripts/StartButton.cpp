#include "StartButton.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Scenes/TestScene.h"




void XX::StartButton::Start()
{
	_animation2d = game_object->GetComponent<Animation2D>();
}

void XX::StartButton::Update()
{
	XXVector2 mp = ExtraX::input.GetMousePosition();

	if (mp.x > 390 && mp.x < 890 &&
		mp.y > 235 && mp.y < 485)
	{
		_animation2d->PlayeAnimation("1");
		if (ExtraX::input.GetButton(M_LETT_BUTTON))
		{
			ExtraX::game.NextScene(ScenePtr(new TestScene02()));
		}
	}
	else
	{
		_animation2d->PlayeAnimation("0");
	}
}