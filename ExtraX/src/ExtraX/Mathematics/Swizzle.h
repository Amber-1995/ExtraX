#pragma once
#ifndef EXTRAX_SWIZZLE_H
#define EXTRAX_SWIZZLE_H

#include <ExtraX/Common.h>
#include <initializer_list>

namespace ExtraX::Mathematics::Base
{
	template <typename SCALAR, int Size, int... Subscript>
	class Swizzle
	{
		template <typename, int, int...> friend class Swizzle;
	private:
		SCALAR _data[Size];

	public:
		Swizzle& operator=(SCALAR value)
		{
			((_data[Subscript] = value), ...);
			return *this;
		}

		Swizzle& operator=(std::initializer_list<SCALAR> args)
		{
			int i = 0;
			((_data[Subscript] = args.begin()[i], ++i), ...);
			return *this;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle& operator=(Swizzle<SCALAR, N, S...>& swizzle)
		{
			((_data[Subscript] = swizzle._data[S]), ...);
			return *this;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle& operator=(Swizzle<SCALAR, N, S...>&& swizzle)
		{
			((_data[Subscript] = swizzle._data[S]), ...);
			return *this;
		}

		Swizzle& operator+=(SCALAR value)
		{
			((_data[Subscript] += value), ...);
			return *this;
		}

		Swizzle& operator+=(std::initializer_list<SCALAR> args)
		{
			int i = 0;
			((_data[Subscript] += args.begin()[i], ++i), ...);
			return *this;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle& operator+=(Swizzle<SCALAR, N, S...>& swizzle)
		{
			((_data[Subscript] += swizzle._data[S]), ...);
			return *this;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle& operator+=(Swizzle<SCALAR, N, S...>&& swizzle)
		{
			((_data[Subscript] += swizzle._data[S]), ...);
			return *this;
		}

		Swizzle& operator-=(SCALAR value)
		{
			((_data[Subscript] -= value), ...);
			return *this;
		}

		Swizzle& operator-=(std::initializer_list<SCALAR> args)
		{
			int i = 0;
			((_data[Subscript] -= args.begin()[i], ++i), ...);
			return *this;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle& operator-=(Swizzle<SCALAR, N, S...>& swizzle)
		{
			((_data[Subscript] -= swizzle._data[S]), ...);
			return *this;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle& operator-=(Swizzle<SCALAR, N, S...>&& swizzle)
		{
			((_data[Subscript] -= swizzle._data[S]), ...);
			return *this;
		}

		Swizzle& operator*=(SCALAR value)
		{
			((_data[Subscript] *= value), ...);
			return *this;
		}

		Swizzle& operator/=(SCALAR value)
		{
			((_data[Subscript] /= value), ...);
			return *this;
		}

		Swizzle operator+()
		{
			return *this;
		}

		Swizzle operator-()
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] = -_data[Subscript]), ...);
			return result;
		}

		Swizzle operator+(SCALAR value)
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] += value), ...);
			return result;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle operator+(Swizzle<SCALAR, N, S...>& swizzle)
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] += swizzle._data[S]), ...);
			return result;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle operator+(Swizzle<SCALAR, N, S...>&& swizzle)
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] += swizzle._data[S]), ...);
			return result;
		}

		Swizzle operator-(SCALAR value)
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] -= value), ...);
			return result;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle operator-(Swizzle<SCALAR, N, S...>& swizzle)
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] -= swizzle._data[S]), ...);
			return result;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
		Swizzle operator-(Swizzle<SCALAR, N, S...>&& swizzle)
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] -= swizzle._data[S]), ...);
			return result;
		}

		Swizzle operator*(SCALAR value)
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] *= value), ...);
			return result;
		}

		Swizzle operator/(SCALAR value)
		{
			Swizzle<SCALAR, Size, Subscript...> result = *this;
			((result._data[Subscript] /= value), ...);
			return result;
		}

	};

}


#endif // !EXTRAX_SWIZZLE_H

