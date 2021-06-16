#pragma once
#ifndef _IRENDER_H_
#define _IRENDER_H_

#include <list>

namespace XX
{
	class IRender
	{
	public:
		virtual void Render() = 0;

		void Addto();

		void Remove();

		void Set2DMode();

		void SetCameraMode();

	private:

	};

	class Renderer
	{
	friend class IRender;
	friend class ExtraX;

	public:
		void Render();

		virtual ~Renderer();

	private:
		std::list<IRender*> _i_renders;
		std::list<IRender*>::iterator _current;
		std::list<IRender*>::iterator _next;

		Renderer();

		Renderer(const Renderer&) = delete;

		Renderer& operator=(const Renderer&) = delete;
	};
}

#endif // !_IRENDER_H_