#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "Sprite.h"
#include "Billboard.h"

#include <map>
#include <functional>

namespace XX 
{

	struct Animation2DClip
	{
		TexturePtr texture;
		int div_x;
		int div_y;
		int start_grid;
		int end_grid;
		bool has_exit_time;
		std::string next_clip_name;
	};

	class Animation2D : public Component , public IUpdate
	{
	/*====================コンストラクターとデストラクター====================*/
	public:
		virtual ~Animation2D() = default;
	private:
		Animation2D();
		Animation2D(const Animation2D&) = delete;
		Animation2D& operator=(const Animation2D&) = delete;

	/*================================メンバー================================*/
	private:
		SpritePtr _target_sprite;
		std::unordered_map<std::string, Animation2DClip> _animation_clips_map;
		std::unordered_map < std::string, std::unordered_map<int, std::function<void()>>> _animation_events_map;
		std::string _current_clip;
		std::string _next_clip;
		float _current_grid;
		float _rate;
		float _rate_scale;

	/*================================メソッド================================*/
	public:
		void Update() override;
		void SetTarget(SpritePtr target);
		void AddAnimationClip(
			const std::string& texture, int div_x, int div_y,
			const std::string& clip_name, int start_grid, int end_grid,
			bool has_exit_time, const std::string& next_clip_name
		);
		void AddAnimationEvent(const std::string& clip_name, int grid_num, std::function<void()> event_fun);
		void SetEnterAnimation(std::string clip_name);
		void PlayeAnimation(std::string clip_name);
		void PlayeAnimationForce(std::string clip_name);
	private:
		void _SetAnimation();
		void _NextClip();

	/*================================フレンド================================*/
		friend class Component;
	};
	typedef std::shared_ptr<Animation2D> Animation2DPtr;
}

#endif // !_ANIMATION_H_
