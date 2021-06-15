#pragma once
#ifndef _IRENDER_H_
#define _IRENDER_H_

#include <vector>

namespace XX
{
	class IRender
	{
	public:
		virtual void Render() = 0;

		void Init();

		void Uninit();

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
		std::vector<IRender*> _i_renders;

		Renderer();

		Renderer(const Renderer&) = delete;

		Renderer& operator=(const Renderer&) = delete;
	};
}

#endif // !_IRENDER_H_