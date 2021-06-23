#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "Sprite.h"
#include "Billboard.h"

#include <vector>

namespace XX 
{
	struct Animation2DClip
	{
		std::string clip_name;
		int clip_hash;

		std::string next_clip_name;
		int next_clip_hash;

		bool has_exit_time;

		int start_grid;
		int end_grid;

		TexturePtr texture;
		int div_x;
		int div_y;
	};

	class Animation2D : public Component , public IUpdate
	{
	public:
		void Update() override;

		void SetTarget(SpritePtr target);

		void AddAnimationClip(
			const std::string& texture,int div_x,int div_y,
			const std::string& clip_name,int start_grid,int end_grid,
			bool has_exit_time, const std::string& next_clip_name
		);

		void SetEnterAnimation(int clip_hash);
		void SetEnterAnimation(std::string clip_name);

		void PlayeAnimation(int clip_hash);
		void PlayeAnimation(std::string clip_name);
		void PlayeAnimationForce(int clip_hash);
		void PlayeAnimationForce(std::string clip_name);

	private:
		SpritePtr _target_sprite;

		std::list<Animation2DClip> _animation_clip_list;

		Animation2DClip _current_clip;

		Animation2DClip _next_clip;
		
		float _current_grid;
	
		float _rate;
		float _rate_scale;

		bool _is_played;

		Animation2D();

		void _SetAnimation();

		void _NextClip();

		friend class Component;

	};
}

#endif // !_ANIMATION_H_
