#pragma once
#ifndef _IRENDER_H_
#define _IRENDER_H_

#include <list>
#include "Event.h"
#include <thread>
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
		int _num_of_processors;
		std::atomic<UINT> _start_symble;
		UINT _start_mask;
		std::thread** _update_thread;
		void _Update(int num);

		Renderer2D();
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
		int _num_of_processors;
		std::atomic<UINT> _start_symble;
		UINT _start_mask;
		std::thread** _update_thread;
		void _Update(int num);


		Renderer3D();
		Renderer3D(const Renderer3D&) = delete;
		Renderer3D& operator=(const Renderer3D&) = delete;

		friend class ExtraX;
	};
}

#endif // !_IRENDER_H_