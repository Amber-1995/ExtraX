#ifndef CORE_IRENDER_H
#define CORE_IRENDER_H

#include "Common/ExtraX.h"

namespace XX::Game::Event
{

	XXAPI class IRender2D

	{
	private:
		inline static std::list<IRender2D*> _new_list;

		inline static std::list<IRender2D*> _current_list;

		std::list<IRender2D*>::iterator _self;

	public:
		IRender2D();

		virtual ~IRender2D();

		virtual void Render2D(size_t thread_num) = 0;

		static void FramePreprocess();

		static void FrameProcess(size_t thread);
	};

	XXAPI class IRender3D
	{
	private:
		inline static std::list<IRender3D*> _new_list;

		inline static std::list<IRender3D*> _current_list;

		std::list<IRender3D*>::iterator _self;

	public:
		IRender3D();

		virtual ~IRender3D();

		virtual void Render3D(size_t thread_num) = 0;

		static void FramePreprocess();

		static void FrameProcess(size_t thread);
	};
}
#endif // !CORE_IUPDATE_H