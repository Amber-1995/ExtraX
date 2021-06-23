#pragma once
#ifndef _IRENDER_H_
#define _IRENDER_H_

#include <list>
#include "Event.h"

namespace XX
{
	class IRender2D : public Event<IRender2D>
	{
	public:
		virtual void Render2D() = 0;
	};


	class IRender3D : public Event<IRender3D>
	{
	public:
		virtual void Render3D() = 0;
	};



	class Renderer2D : public EventManager<IRender2D>
	{
	public:
		virtual ~Renderer2D() = default;

		void Render();

	private:
		Renderer2D() = default;
		Renderer2D(const Renderer2D&) = delete;
		Renderer2D& operator=(const Renderer2D&) = delete;

		friend class ExtraX;
	};

	class Renderer3D : public EventManager<IRender3D>
	{
	public:
		virtual ~Renderer3D() = default;

		void Render();

	private:
		Renderer3D() = default;
		Renderer3D(const Renderer3D&) = delete;
		Renderer3D& operator=(const Renderer3D&) = delete;

		friend class ExtraX;
	};
}

#endif // !_IRENDER_H_