#pragma once
#ifndef _XX_H_
#define _XX_H_
#include "Graphics.h"
#include "Events/IUpdate.h"
#include "Events/IRender.h"

namespace XX
{
	class ExtraX
	{
	public:
		static Graphics graphics;
		static Updater updater;
		static Renderer3D renderer3d;
		static Renderer2D renderer2d;

	};
}
#endif	/!_XX_H_
