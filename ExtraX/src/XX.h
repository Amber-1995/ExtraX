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
		static Renderer renderer;

	};
}
#endif	/!_XX_H_
