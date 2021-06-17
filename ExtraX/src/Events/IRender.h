#pragma once
#ifndef _IRENDER_H_
#define _IRENDER_H_

#include <list>

namespace XX
{
	class IRender2D
	{
	public:
		virtual void Render2D() = 0;

		void Addto();

		void Remove();

	};


	class IRender3D
	{
	public:
		virtual void Render3D() = 0;

		void Addto();

		void Remove();

	};

	class Renderer2D
	{
		friend class IRender2D;
		friend class ExtraX;

	public:
		void Render();

		virtual ~Renderer2D();

	private:
		std::list<IRender2D*> _i_render2ds;
		std::list<IRender2D*>::iterator _current;
		std::list<IRender2D*>::iterator _next;

		Renderer2D();

		Renderer2D(const Renderer2D&) = delete;

		Renderer2D& operator=(const Renderer2D&) = delete;
	};

	class Renderer3D
	{
	friend class IRender3D;
	friend class ExtraX;

	public:
		void Render();

		virtual ~Renderer3D();

	private:
		std::list<IRender3D*> _i_render3ds;
		std::list<IRender3D*>::iterator _current;
		std::list<IRender3D*>::iterator _next;

		Renderer3D();

		Renderer3D(const Renderer3D&) = delete;

		Renderer3D& operator=(const Renderer3D&) = delete;
	};
}

#endif // !_IRENDER_H_