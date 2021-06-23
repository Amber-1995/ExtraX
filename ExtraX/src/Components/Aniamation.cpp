#include "Aniamation.h"

XX::Animation2D::Animation2D() :
	_current_grid(0),
	_rate(10),
	_rate_scale(1)
{

}

void XX::Animation2D::Update()
{
	Animation2DClip& cc = _animation_clips_map[_current_clip];

	if (cc.next_clip_name == _next_clip || cc.has_exit_time) {
		_SetAnimation();
	}
	else {
		_NextClip();
		_SetAnimation();
	}
	_current_grid += _rate * _rate_scale * 0.017f;
	if (_current_grid > cc.end_grid - cc.start_grid + 1) {
		_NextClip();
	}

	auto e = _animation_events_map[_current_clip].find((int)_current_grid);
	if (e != _animation_events_map[_current_clip].end()) {
		(*e).second();
	}
}

void XX::Animation2D::SetTarget(SpritePtr target)
{
	_target_sprite = target;
}

void XX::Animation2D::AddAnimationClip(const std::string& texture, int div_x, int div_y, const std::string& clip_name, int start_grid, int end_grid, bool has_exit_time, const std::string& next_clip_name)
{
	Animation2DClip ac = {};
	ac.next_clip_name = next_clip_name;
	ac.has_exit_time = has_exit_time;
	ac.div_x = div_x;
	ac.div_y = div_y;
	ac.texture = Texture::Load(texture);
	ac.start_grid = start_grid;
	ac.end_grid = end_grid;

	_animation_clips_map[clip_name] = ac;
}

void XX::Animation2D::AddAnimationEvent(const std::string& clip_name, int grid_num, std::function<void()> event_fun)
{
	_animation_events_map[clip_name][grid_num] = event_fun;
}

void XX::Animation2D::SetEnterAnimation(std::string clip_name)
{
	_current_clip = clip_name;
	_next_clip = _animation_clips_map[_current_clip].next_clip_name;
	_current_grid = 0;
}

void XX::Animation2D::PlayeAnimation(std::string clip_name)
{
	_next_clip = clip_name;
}

void XX::Animation2D::PlayeAnimationForce(std::string clip_name)
{
	_current_clip = clip_name;
	_next_clip = _animation_clips_map[_current_clip].next_clip_name;
	_current_grid = 0;
}

void XX::Animation2D::_SetAnimation()
{
	Animation2DClip& cc = _animation_clips_map[_current_clip];
	int current_grid = (int)_current_grid;
	current_grid += cc.start_grid;
	float div_x = (float)cc.div_x;
	float div_y = (float)cc.div_y;
	int x = current_grid % cc.div_x;
	int y = current_grid / cc.div_y;

	XXVertex3D vertex[4];
	vertex[0].position = XXVector3(-0.5f, 0.5f, 0.0f);
	vertex[0].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[0].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].tex_coord = XXVector2(1.0f / div_x * (x + 0), 1.0f / div_y * (y + 0));

	vertex[1].position = XXVector3(0.5f, 0.5f, 0.0f);
	vertex[1].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[1].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].tex_coord = XXVector2(1.0f / div_x * (x + 1), 1.0f / div_y * (y + 0));

	vertex[2].position = XXVector3(-0.5f, -0.5f, 0.0f);
	vertex[2].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[2].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].tex_coord = XXVector2(1.0f / div_x * (x + 0), 1.0f / div_y * (y + 1));

	vertex[3].position = XXVector3(0.5f, -0.5f, 0.0f);
	vertex[3].normal = XXVector3(0.0f, 0.0f, -1.0f);
	vertex[3].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].tex_coord = XXVector2(1.0f / div_x * (x + 1), 1.0f / div_y * (y + 1));

	_target_sprite->SetTexture(cc.texture);
	_target_sprite->SetVertex(vertex);
}

void XX::Animation2D::_NextClip()
{
	_current_clip = _next_clip;
	_next_clip = _animation_clips_map[_current_clip].next_clip_name;
	_current_grid = 0.0f;
}
