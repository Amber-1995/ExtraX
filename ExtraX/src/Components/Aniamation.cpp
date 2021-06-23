#include "Aniamation.h"

XX::Animation2D::Animation2D() :
	_current_grid(0),
	_rate(10),
	_rate_scale(1),
	_is_played(false)
{

}

void XX::Animation2D::Update()
{
	if (_current_clip.next_clip_hash == _next_clip.clip_hash) {
		_current_grid += _rate * _rate_scale * 0.017f;
		_SetAnimation();
		_is_played = _current_grid >= _current_clip.end_grid - _current_clip.start_grid;
		if (_is_played) {
			_NextClip();
		}
	}
	else if(_current_clip.has_exit_time){
		_current_grid += _rate * _rate_scale * 0.017f;
		_SetAnimation();
		_is_played = _current_grid >= _current_clip.end_grid - _current_clip.start_grid;
		if (_is_played) {
			_NextClip();
		}
	}
	else{
		_NextClip();
		_current_grid += _rate * _rate_scale * 0.017f;
		_SetAnimation();
		_is_played = _current_grid >= _current_clip.end_grid - _current_clip.start_grid;
		if (_is_played) {
			_NextClip();
		}
	}
}

void XX::Animation2D::SetTarget(SpritePtr target)
{
	_target_sprite = target;
}

void XX::Animation2D::AddAnimationClip(const std::string& texture, int div_x, int div_y, const std::string& clip_name, int start_grid, int end_grid, bool has_exit_time, const std::string& next_clip_name)
{
	Animation2DClip ac = {};
	ac.clip_name = clip_name;
	ac.clip_hash = (int)std::hash<std::string>{}(clip_name);
	ac.next_clip_name = next_clip_name;
	ac.next_clip_hash = (int)std::hash<std::string>{}(next_clip_name);
	ac.has_exit_time = has_exit_time;
	ac.div_x = div_x;
	ac.div_y = div_y;
	ac.texture = Texture::Load(texture);
	ac.start_grid = start_grid;
	ac.end_grid = end_grid;

	_animation_clip_list.push_front(ac);
}

void XX::Animation2D::SetEnterAnimation(int clip_hash)
{
	for (Animation2DClip ac : _animation_clip_list){

		if (ac.clip_hash == clip_hash) {
			_current_clip = _next_clip = ac;
			for (Animation2DClip ac2 : _animation_clip_list)
			{
				if (ac2.clip_hash == _current_clip.next_clip_hash) {
					_next_clip = ac2;
					break;
				}
			}
			break;
		}
	}
}

void XX::Animation2D::SetEnterAnimation(std::string clip_name)
{
	int clip_hash = (int)std::hash<std::string>{}(clip_name);
	SetEnterAnimation(clip_hash);
}

void XX::Animation2D::PlayeAnimation(int clip_hash)
{
	for (Animation2DClip ac : _animation_clip_list) {
		if (ac.clip_hash == clip_hash) {
			_next_clip = ac;
		}
	}
}

void XX::Animation2D::PlayeAnimation(std::string clip_name)
{
	int clip_hash = (int)std::hash<std::string>{}(clip_name);
	PlayeAnimation(clip_hash);
}

void XX::Animation2D::PlayeAnimationForce(int clip_hash)
{
	_is_played = false;
	_current_grid = 0.0f;

	for (Animation2DClip ac : _animation_clip_list) {
		if (ac.clip_hash == clip_hash) {
			_current_clip = ac;
			for (Animation2DClip ac2 : _animation_clip_list)
			{
				if (ac2.clip_hash == _current_clip.next_clip_hash) {
					_next_clip = ac2;
					break;
				}
			}
			break;
		}
	}
}

void XX::Animation2D::PlayeAnimationForce(std::string clip_name)
{
	int clip_hash = (int)std::hash<std::string>{}(clip_name);
	PlayeAnimationForce(clip_hash);
}

void XX::Animation2D::_SetAnimation()
{
	int current_grid = (int)_current_grid;
	current_grid += _current_clip.start_grid;
	float div_x = (float)_current_clip.div_x;
	float div_y = (float)_current_clip.div_y;
	int x = current_grid % _current_clip.div_x;
	int y = current_grid / _current_clip.div_y;

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

	_target_sprite->SetTexture(_current_clip.texture);
	_target_sprite->SetVertex(vertex);
}

void XX::Animation2D::_NextClip()
{
	_current_clip = _next_clip;
	for (Animation2DClip ac : _animation_clip_list){
		if (_current_clip.next_clip_hash == ac.next_clip_hash){
			_next_clip = ac;
		}
	}
	_current_grid = 0.0f;
	_is_played = false;
}
