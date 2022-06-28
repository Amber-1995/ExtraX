#ifndef CORE_IONTRANSFORM_H
#define CORE_IONTRANSFORM_H


#include "Common/ExtraX.h"


namespace XX::Game::Event
{
	class IOnTransform
	{
	public:
		virtual ~IOnTransform() = default;

		virtual void OnTransform() = 0;
	};

	class IOnTranslate
	{
	public:
		virtual ~IOnTranslate() = default;

		virtual void OnTranslate() = 0;
	};

	class IOnRotate
	{
	public:
		virtual ~IOnRotate() = default;

		virtual void OnRotate() = 0;
	};

	class IOnScale
	{
	public:
		virtual ~IOnScale() = default;

		virtual void OnScale() = 0;
	};
}

#endif // !CORE_IONTRANSFORM_H

