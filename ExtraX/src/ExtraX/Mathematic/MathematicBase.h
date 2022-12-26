#pragma once
#ifndef EXTRAX_MATHEMATIC_BASE_H
#define EXTRAX_MATHEMATIC_BASE_H


#include <ExtraX/Common.h>


namespace ExtraX::Mathematic::Base
{
	template <typename SCALAR, int Size, int... Subscript>
	class Swizzle
	{
		template <typename, int, int...> friend class Swizzle;
	private:
		SCALAR _data[Size];

	public:
		Swizzle& operator= (SCALAR& value)
		{
			((_data[Subscript] = value), ...);
			return *this;
		}

		Swizzle& operator= (SCALAR&& value)
		{
			((_data[Subscript] = value), ...);
			return *this;
		}

		Swizzle& operator= (std::array<SCALAR, sizeof...(Subscript)>& args)
		{
			int i = 0;
			((_data[Subscript] = args[i], ++i), ...);
			return *this;
		}

		Swizzle& operator= (std::array<SCALAR, sizeof...(Subscript)>&& args)
		{
			int i = 0;
			((_data[Subscript] = args[i], ++i), ...);
			return *this;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
			Swizzle& operator= (Swizzle<SCALAR, N, S...>& swizzle)
		{
			((_data[Subscript] = swizzle._data[S]), ...);
			return *this;
		}

		template<int N, int... S> requires(sizeof...(S) == sizeof...(Subscript))
			Swizzle& operator= (Swizzle<SCALAR, N, S...>&& swizzle)
		{
			((_data[Subscript] = swizzle._data[S]), ...);
			return *this;
		}
	};

	template<typename SCALAR, int Size>
	class VectorBase
	{
	public:
		SCALAR _vector[Size];

		VectorBase()
		{
			ZeroMemory(_vector, sizeof(SCALAR) * Size);
		}

		template<typename ...ARGS> requires (sizeof...(ARGS) == Size && std::conjunction<std::is_convertible<ARGS, T>...>::value)
		VectorBase(ARGS ...args) :
			_vector{ args... }
		{
		}

		virtual ~VectorBase() = default;

	};

	template<typename SCALAR>
	class VectorBase<SCALAR, 2>
	{
	public:
		union
		{
			SCALAR _vector[2];
			struct
			{
				SCALAR x;
				SCALAR y;
			};

			Swizzle< SCALAR, 2, 0, 0 > xx;
			Swizzle< SCALAR, 2, 0, 1 > xy;
			Swizzle< SCALAR, 2, 1, 0 > yx;
			Swizzle< SCALAR, 2, 1, 1 > yy;
		
			Swizzle< SCALAR, 2, 0, 0, 0 > xxx;
			Swizzle< SCALAR, 2, 0, 0, 1 > xxy;
			Swizzle< SCALAR, 2, 0, 1, 0 > xyx;
			Swizzle< SCALAR, 2, 0, 1, 1 > xyy;
			Swizzle< SCALAR, 2, 1, 0, 0 > yxx;
			Swizzle< SCALAR, 2, 1, 0, 1 > yxy;
			Swizzle< SCALAR, 2, 1, 1, 0 > yyx;
			Swizzle< SCALAR, 2, 1, 1, 1 > yyy;

			Swizzle< SCALAR, 2, 0, 0, 0, 0 > xxxx;
			Swizzle< SCALAR, 2, 0, 0, 0, 1 > xxxy;
			Swizzle< SCALAR, 2, 0, 0, 1, 0 > xxyx;
			Swizzle< SCALAR, 2, 0, 0, 1, 1 > xxyy;
			Swizzle< SCALAR, 2, 0, 1, 0, 0 > xyxx;
			Swizzle< SCALAR, 2, 0, 1, 0, 1 > xyxy;
			Swizzle< SCALAR, 2, 0, 1, 1, 0 > xyyx;
			Swizzle< SCALAR, 2, 0, 1, 1, 1 > xyyy;
			Swizzle< SCALAR, 2, 1, 0, 0, 0 > yxxx;
			Swizzle< SCALAR, 2, 1, 0, 0, 1 > yxxy;
			Swizzle< SCALAR, 2, 1, 0, 1, 0 > yxyx;
			Swizzle< SCALAR, 2, 1, 0, 1, 1 > yxyy;
			Swizzle< SCALAR, 2, 1, 1, 0, 0 > yyxx;
			Swizzle< SCALAR, 2, 1, 1, 0, 1 > yyxy;
			Swizzle< SCALAR, 2, 1, 1, 1, 0 > yyyx;
			Swizzle< SCALAR, 2, 1, 1, 1, 1 > yyyy;
		};

	protected:
		VectorBase()
		{
			ZeroMemory(_vector, sizeof(SCALAR) * 2);
		}

		VectorBase(SCALAR x, SCALAR y) :
			x(x),y(y)
		{
		}

		virtual ~VectorBase() = default;

	};

	template<typename SCALAR>
	class VectorBase<SCALAR, 3>
	{
	public:
		union
		{
			SCALAR _vector[3];
			struct
			{
				SCALAR x;
				SCALAR y;
				SCALAR z;
			};
			Swizzle< SCALAR, 3, 0, 0 > xx;
			Swizzle< SCALAR, 3, 0, 1 > xy;
			Swizzle< SCALAR, 3, 0, 2 > xz;
			Swizzle< SCALAR, 3, 1, 0 > yx;
			Swizzle< SCALAR, 3, 1, 1 > yy;
			Swizzle< SCALAR, 3, 1, 2 > yz;
			Swizzle< SCALAR, 3, 2, 0 > zx;
			Swizzle< SCALAR, 3, 2, 1 > zy;
			Swizzle< SCALAR, 3, 2, 2 > zz;

			Swizzle< SCALAR, 3, 0, 0, 0 > xxx;
			Swizzle< SCALAR, 3, 0, 0, 1 > xxy;
			Swizzle< SCALAR, 3, 0, 0, 2 > xxz;
			Swizzle< SCALAR, 3, 0, 1, 0 > xyx;
			Swizzle< SCALAR, 3, 0, 1, 1 > xyy;
			Swizzle< SCALAR, 3, 0, 1, 2 > xyz;
			Swizzle< SCALAR, 3, 0, 2, 0 > xzx;
			Swizzle< SCALAR, 3, 0, 2, 1 > xzy;
			Swizzle< SCALAR, 3, 0, 2, 2 > xzz;
			Swizzle< SCALAR, 3, 1, 0, 0 > yxx;
			Swizzle< SCALAR, 3, 1, 0, 1 > yxy;
			Swizzle< SCALAR, 3, 1, 0, 2 > yxz;
			Swizzle< SCALAR, 3, 1, 1, 0 > yyx;
			Swizzle< SCALAR, 3, 1, 1, 1 > yyy;
			Swizzle< SCALAR, 3, 1, 1, 2 > yyz;
			Swizzle< SCALAR, 3, 1, 2, 0 > yzx;
			Swizzle< SCALAR, 3, 1, 2, 1 > yzy;
			Swizzle< SCALAR, 3, 1, 2, 2 > yzz;
			Swizzle< SCALAR, 3, 2, 0, 0 > zxx;
			Swizzle< SCALAR, 3, 2, 0, 1 > zxy;
			Swizzle< SCALAR, 3, 2, 0, 2 > zxz;
			Swizzle< SCALAR, 3, 2, 1, 0 > zyx;
			Swizzle< SCALAR, 3, 2, 1, 1 > zyy;
			Swizzle< SCALAR, 3, 2, 1, 2 > zyz;
			Swizzle< SCALAR, 3, 2, 2, 0 > zzx;
			Swizzle< SCALAR, 3, 2, 2, 1 > zzy;
			Swizzle< SCALAR, 3, 2, 2, 2 > zzz;

			Swizzle< SCALAR, 3, 0, 0, 0, 0 > xxxx;
			Swizzle< SCALAR, 3, 0, 0, 0, 1 > xxxy;
			Swizzle< SCALAR, 3, 0, 0, 0, 2 > xxxz;
			Swizzle< SCALAR, 3, 0, 0, 1, 0 > xxyx;
			Swizzle< SCALAR, 3, 0, 0, 1, 1 > xxyy;
			Swizzle< SCALAR, 3, 0, 0, 1, 2 > xxyz;
			Swizzle< SCALAR, 3, 0, 0, 2, 0 > xxzx;
			Swizzle< SCALAR, 3, 0, 0, 2, 1 > xxzy;
			Swizzle< SCALAR, 3, 0, 0, 2, 2 > xxzz;
			Swizzle< SCALAR, 3, 0, 1, 0, 0 > xyxx;
			Swizzle< SCALAR, 3, 0, 1, 0, 1 > xyxy;
			Swizzle< SCALAR, 3, 0, 1, 0, 2 > xyxz;
			Swizzle< SCALAR, 3, 0, 1, 1, 0 > xyyx;
			Swizzle< SCALAR, 3, 0, 1, 1, 1 > xyyy;
			Swizzle< SCALAR, 3, 0, 1, 1, 2 > xyyz;
			Swizzle< SCALAR, 3, 0, 1, 2, 0 > xyzx;
			Swizzle< SCALAR, 3, 0, 1, 2, 1 > xyzy;
			Swizzle< SCALAR, 3, 0, 1, 2, 2 > xyzz;
			Swizzle< SCALAR, 3, 0, 2, 0, 0 > xzxx;
			Swizzle< SCALAR, 3, 0, 2, 0, 1 > xzxy;
			Swizzle< SCALAR, 3, 0, 2, 0, 2 > xzxz;
			Swizzle< SCALAR, 3, 0, 2, 1, 0 > xzyx;
			Swizzle< SCALAR, 3, 0, 2, 1, 1 > xzyy;
			Swizzle< SCALAR, 3, 0, 2, 1, 2 > xzyz;
			Swizzle< SCALAR, 3, 0, 2, 2, 0 > xzzx;
			Swizzle< SCALAR, 3, 0, 2, 2, 1 > xzzy;
			Swizzle< SCALAR, 3, 0, 2, 2, 2 > xzzz;
			Swizzle< SCALAR, 3, 1, 0, 0, 0 > yxxx;
			Swizzle< SCALAR, 3, 1, 0, 0, 1 > yxxy;
			Swizzle< SCALAR, 3, 1, 0, 0, 2 > yxxz;
			Swizzle< SCALAR, 3, 1, 0, 1, 0 > yxyx;
			Swizzle< SCALAR, 3, 1, 0, 1, 1 > yxyy;
			Swizzle< SCALAR, 3, 1, 0, 1, 2 > yxyz;
			Swizzle< SCALAR, 3, 1, 0, 2, 0 > yxzx;
			Swizzle< SCALAR, 3, 1, 0, 2, 1 > yxzy;
			Swizzle< SCALAR, 3, 1, 0, 2, 2 > yxzz;
			Swizzle< SCALAR, 3, 1, 1, 0, 0 > yyxx;
			Swizzle< SCALAR, 3, 1, 1, 0, 1 > yyxy;
			Swizzle< SCALAR, 3, 1, 1, 0, 2 > yyxz;
			Swizzle< SCALAR, 3, 1, 1, 1, 0 > yyyx;
			Swizzle< SCALAR, 3, 1, 1, 1, 1 > yyyy;
			Swizzle< SCALAR, 3, 1, 1, 1, 2 > yyyz;
			Swizzle< SCALAR, 3, 1, 1, 2, 0 > yyzx;
			Swizzle< SCALAR, 3, 1, 1, 2, 1 > yyzy;
			Swizzle< SCALAR, 3, 1, 1, 2, 2 > yyzz;
			Swizzle< SCALAR, 3, 1, 2, 0, 0 > yzxx;
			Swizzle< SCALAR, 3, 1, 2, 0, 1 > yzxy;
			Swizzle< SCALAR, 3, 1, 2, 0, 2 > yzxz;
			Swizzle< SCALAR, 3, 1, 2, 1, 0 > yzyx;
			Swizzle< SCALAR, 3, 1, 2, 1, 1 > yzyy;
			Swizzle< SCALAR, 3, 1, 2, 1, 2 > yzyz;
			Swizzle< SCALAR, 3, 1, 2, 2, 0 > yzzx;
			Swizzle< SCALAR, 3, 1, 2, 2, 1 > yzzy;
			Swizzle< SCALAR, 3, 1, 2, 2, 2 > yzzz;
			Swizzle< SCALAR, 3, 2, 0, 0, 0 > zxxx;
			Swizzle< SCALAR, 3, 2, 0, 0, 1 > zxxy;
			Swizzle< SCALAR, 3, 2, 0, 0, 2 > zxxz;
			Swizzle< SCALAR, 3, 2, 0, 1, 0 > zxyx;
			Swizzle< SCALAR, 3, 2, 0, 1, 1 > zxyy;
			Swizzle< SCALAR, 3, 2, 0, 1, 2 > zxyz;
			Swizzle< SCALAR, 3, 2, 0, 2, 0 > zxzx;
			Swizzle< SCALAR, 3, 2, 0, 2, 1 > zxzy;
			Swizzle< SCALAR, 3, 2, 0, 2, 2 > zxzz;
			Swizzle< SCALAR, 3, 2, 1, 0, 0 > zyxx;
			Swizzle< SCALAR, 3, 2, 1, 0, 1 > zyxy;
			Swizzle< SCALAR, 3, 2, 1, 0, 2 > zyxz;
			Swizzle< SCALAR, 3, 2, 1, 1, 0 > zyyx;
			Swizzle< SCALAR, 3, 2, 1, 1, 1 > zyyy;
			Swizzle< SCALAR, 3, 2, 1, 1, 2 > zyyz;
			Swizzle< SCALAR, 3, 2, 1, 2, 0 > zyzx;
			Swizzle< SCALAR, 3, 2, 1, 2, 1 > zyzy;
			Swizzle< SCALAR, 3, 2, 1, 2, 2 > zyzz;
			Swizzle< SCALAR, 3, 2, 2, 0, 0 > zzxx;
			Swizzle< SCALAR, 3, 2, 2, 0, 1 > zzxy;
			Swizzle< SCALAR, 3, 2, 2, 0, 2 > zzxz;
			Swizzle< SCALAR, 3, 2, 2, 1, 0 > zzyx;
			Swizzle< SCALAR, 3, 2, 2, 1, 1 > zzyy;
			Swizzle< SCALAR, 3, 2, 2, 1, 2 > zzyz;
			Swizzle< SCALAR, 3, 2, 2, 2, 0 > zzzx;
			Swizzle< SCALAR, 3, 2, 2, 2, 1 > zzzy;
			Swizzle< SCALAR, 3, 2, 2, 2, 2 > zzzz;
		};

		VectorBase()
		{
			ZeroMemory(_vector, sizeof(SCALAR) * 3);
		}

		VectorBase(ScalarType x, ScalarType y, ScalarType z) :
			x(x),y(y),z(z)
		{
		}

		virtual ~VectorBase() = default;

	};

	template<typename SCALAR>
	class VectorBase<SCALAR, 4>
	{
	public:
		union
		{
			SCALAR _vector[4];
			struct
			{
				SCALAR x;
				SCALAR y;
				SCALAR z;
				SCALAR w;
			};
			Swizzle< SCALAR, 4, 0, 0 > xx;
			Swizzle< SCALAR, 4, 0, 1 > xy;
			Swizzle< SCALAR, 4, 0, 2 > xz;
			Swizzle< SCALAR, 4, 0, 3 > xw;
			Swizzle< SCALAR, 4, 1, 0 > yx;
			Swizzle< SCALAR, 4, 1, 1 > yy;
			Swizzle< SCALAR, 4, 1, 2 > yz;
			Swizzle< SCALAR, 4, 1, 3 > yw;
			Swizzle< SCALAR, 4, 2, 0 > zx;
			Swizzle< SCALAR, 4, 2, 1 > zy;
			Swizzle< SCALAR, 4, 2, 2 > zz;
			Swizzle< SCALAR, 4, 2, 3 > zw;
			Swizzle< SCALAR, 4, 3, 0 > wx;
			Swizzle< SCALAR, 4, 3, 1 > wy;
			Swizzle< SCALAR, 4, 3, 2 > wz;
			Swizzle< SCALAR, 4, 3, 3 > ww;

			Swizzle< SCALAR, 4, 0, 0, 0 > xxx;
			Swizzle< SCALAR, 4, 0, 0, 1 > xxy;
			Swizzle< SCALAR, 4, 0, 0, 2 > xxz;
			Swizzle< SCALAR, 4, 0, 0, 3 > xxw;
			Swizzle< SCALAR, 4, 0, 1, 0 > xyx;
			Swizzle< SCALAR, 4, 0, 1, 1 > xyy;
			Swizzle< SCALAR, 4, 0, 1, 2 > xyz;
			Swizzle< SCALAR, 4, 0, 1, 3 > xyw;
			Swizzle< SCALAR, 4, 0, 2, 0 > xzx;
			Swizzle< SCALAR, 4, 0, 2, 1 > xzy;
			Swizzle< SCALAR, 4, 0, 2, 2 > xzz;
			Swizzle< SCALAR, 4, 0, 2, 3 > xzw;
			Swizzle< SCALAR, 4, 0, 3, 0 > xwx;
			Swizzle< SCALAR, 4, 0, 3, 1 > xwy;
			Swizzle< SCALAR, 4, 0, 3, 2 > xwz;
			Swizzle< SCALAR, 4, 0, 3, 3 > xww;
			Swizzle< SCALAR, 4, 1, 0, 0 > yxx;
			Swizzle< SCALAR, 4, 1, 0, 1 > yxy;
			Swizzle< SCALAR, 4, 1, 0, 2 > yxz;
			Swizzle< SCALAR, 4, 1, 0, 3 > yxw;
			Swizzle< SCALAR, 4, 1, 1, 0 > yyx;
			Swizzle< SCALAR, 4, 1, 1, 1 > yyy;
			Swizzle< SCALAR, 4, 1, 1, 2 > yyz;
			Swizzle< SCALAR, 4, 1, 1, 3 > yyw;
			Swizzle< SCALAR, 4, 1, 2, 0 > yzx;
			Swizzle< SCALAR, 4, 1, 2, 1 > yzy;
			Swizzle< SCALAR, 4, 1, 2, 2 > yzz;
			Swizzle< SCALAR, 4, 1, 2, 3 > yzw;
			Swizzle< SCALAR, 4, 1, 3, 0 > ywx;
			Swizzle< SCALAR, 4, 1, 3, 1 > ywy;
			Swizzle< SCALAR, 4, 1, 3, 2 > ywz;
			Swizzle< SCALAR, 4, 1, 3, 3 > yww;
			Swizzle< SCALAR, 4, 2, 0, 0 > zxx;
			Swizzle< SCALAR, 4, 2, 0, 1 > zxy;
			Swizzle< SCALAR, 4, 2, 0, 2 > zxz;
			Swizzle< SCALAR, 4, 2, 0, 3 > zxw;
			Swizzle< SCALAR, 4, 2, 1, 0 > zyx;
			Swizzle< SCALAR, 4, 2, 1, 1 > zyy;
			Swizzle< SCALAR, 4, 2, 1, 2 > zyz;
			Swizzle< SCALAR, 4, 2, 1, 3 > zyw;
			Swizzle< SCALAR, 4, 2, 2, 0 > zzx;
			Swizzle< SCALAR, 4, 2, 2, 1 > zzy;
			Swizzle< SCALAR, 4, 2, 2, 2 > zzz;
			Swizzle< SCALAR, 4, 2, 2, 3 > zzw;
			Swizzle< SCALAR, 4, 2, 3, 0 > zwx;
			Swizzle< SCALAR, 4, 2, 3, 1 > zwy;
			Swizzle< SCALAR, 4, 2, 3, 2 > zwz;
			Swizzle< SCALAR, 4, 2, 3, 3 > zww;
			Swizzle< SCALAR, 4, 3, 0, 0 > wxx;
			Swizzle< SCALAR, 4, 3, 0, 1 > wxy;
			Swizzle< SCALAR, 4, 3, 0, 2 > wxz;
			Swizzle< SCALAR, 4, 3, 0, 3 > wxw;
			Swizzle< SCALAR, 4, 3, 1, 0 > wyx;
			Swizzle< SCALAR, 4, 3, 1, 1 > wyy;
			Swizzle< SCALAR, 4, 3, 1, 2 > wyz;
			Swizzle< SCALAR, 4, 3, 1, 3 > wyw;
			Swizzle< SCALAR, 4, 3, 2, 0 > wzx;
			Swizzle< SCALAR, 4, 3, 2, 1 > wzy;
			Swizzle< SCALAR, 4, 3, 2, 2 > wzz;
			Swizzle< SCALAR, 4, 3, 2, 3 > wzw;
			Swizzle< SCALAR, 4, 3, 3, 0 > wwx;
			Swizzle< SCALAR, 4, 3, 3, 1 > wwy;
			Swizzle< SCALAR, 4, 3, 3, 2 > wwz;
			Swizzle< SCALAR, 4, 3, 3, 3 > www;

			Swizzle< SCALAR, 4, 0, 0, 0, 0 > xxxx;
			Swizzle< SCALAR, 4, 0, 0, 0, 1 > xxxy;
			Swizzle< SCALAR, 4, 0, 0, 0, 2 > xxxz;
			Swizzle< SCALAR, 4, 0, 0, 0, 3 > xxxw;
			Swizzle< SCALAR, 4, 0, 0, 1, 0 > xxyx;
			Swizzle< SCALAR, 4, 0, 0, 1, 1 > xxyy;
			Swizzle< SCALAR, 4, 0, 0, 1, 2 > xxyz;
			Swizzle< SCALAR, 4, 0, 0, 1, 3 > xxyw;
			Swizzle< SCALAR, 4, 0, 0, 2, 0 > xxzx;
			Swizzle< SCALAR, 4, 0, 0, 2, 1 > xxzy;
			Swizzle< SCALAR, 4, 0, 0, 2, 2 > xxzz;
			Swizzle< SCALAR, 4, 0, 0, 2, 3 > xxzw;
			Swizzle< SCALAR, 4, 0, 0, 3, 0 > xxwx;
			Swizzle< SCALAR, 4, 0, 0, 3, 1 > xxwy;
			Swizzle< SCALAR, 4, 0, 0, 3, 2 > xxwz;
			Swizzle< SCALAR, 4, 0, 0, 3, 3 > xxww;
			Swizzle< SCALAR, 4, 0, 1, 0, 0 > xyxx;
			Swizzle< SCALAR, 4, 0, 1, 0, 1 > xyxy;
			Swizzle< SCALAR, 4, 0, 1, 0, 2 > xyxz;
			Swizzle< SCALAR, 4, 0, 1, 0, 3 > xyxw;
			Swizzle< SCALAR, 4, 0, 1, 1, 0 > xyyx;
			Swizzle< SCALAR, 4, 0, 1, 1, 1 > xyyy;
			Swizzle< SCALAR, 4, 0, 1, 1, 2 > xyyz;
			Swizzle< SCALAR, 4, 0, 1, 1, 3 > xyyw;
			Swizzle< SCALAR, 4, 0, 1, 2, 0 > xyzx;
			Swizzle< SCALAR, 4, 0, 1, 2, 1 > xyzy;
			Swizzle< SCALAR, 4, 0, 1, 2, 2 > xyzz;
			Swizzle< SCALAR, 4, 0, 1, 2, 3 > xyzw;
			Swizzle< SCALAR, 4, 0, 1, 3, 0 > xywx;
			Swizzle< SCALAR, 4, 0, 1, 3, 1 > xywy;
			Swizzle< SCALAR, 4, 0, 1, 3, 2 > xywz;
			Swizzle< SCALAR, 4, 0, 1, 3, 3 > xyww;
			Swizzle< SCALAR, 4, 0, 2, 0, 0 > xzxx;
			Swizzle< SCALAR, 4, 0, 2, 0, 1 > xzxy;
			Swizzle< SCALAR, 4, 0, 2, 0, 2 > xzxz;
			Swizzle< SCALAR, 4, 0, 2, 0, 3 > xzxw;
			Swizzle< SCALAR, 4, 0, 2, 1, 0 > xzyx;
			Swizzle< SCALAR, 4, 0, 2, 1, 1 > xzyy;
			Swizzle< SCALAR, 4, 0, 2, 1, 2 > xzyz;
			Swizzle< SCALAR, 4, 0, 2, 1, 3 > xzyw;
			Swizzle< SCALAR, 4, 0, 2, 2, 0 > xzzx;
			Swizzle< SCALAR, 4, 0, 2, 2, 1 > xzzy;
			Swizzle< SCALAR, 4, 0, 2, 2, 2 > xzzz;
			Swizzle< SCALAR, 4, 0, 2, 2, 3 > xzzw;
			Swizzle< SCALAR, 4, 0, 2, 3, 0 > xzwx;
			Swizzle< SCALAR, 4, 0, 2, 3, 1 > xzwy;
			Swizzle< SCALAR, 4, 0, 2, 3, 2 > xzwz;
			Swizzle< SCALAR, 4, 0, 2, 3, 3 > xzww;
			Swizzle< SCALAR, 4, 0, 3, 0, 0 > xwxx;
			Swizzle< SCALAR, 4, 0, 3, 0, 1 > xwxy;
			Swizzle< SCALAR, 4, 0, 3, 0, 2 > xwxz;
			Swizzle< SCALAR, 4, 0, 3, 0, 3 > xwxw;
			Swizzle< SCALAR, 4, 0, 3, 1, 0 > xwyx;
			Swizzle< SCALAR, 4, 0, 3, 1, 1 > xwyy;
			Swizzle< SCALAR, 4, 0, 3, 1, 2 > xwyz;
			Swizzle< SCALAR, 4, 0, 3, 1, 3 > xwyw;
			Swizzle< SCALAR, 4, 0, 3, 2, 0 > xwzx;
			Swizzle< SCALAR, 4, 0, 3, 2, 1 > xwzy;
			Swizzle< SCALAR, 4, 0, 3, 2, 2 > xwzz;
			Swizzle< SCALAR, 4, 0, 3, 2, 3 > xwzw;
			Swizzle< SCALAR, 4, 0, 3, 3, 0 > xwwx;
			Swizzle< SCALAR, 4, 0, 3, 3, 1 > xwwy;
			Swizzle< SCALAR, 4, 0, 3, 3, 2 > xwwz;
			Swizzle< SCALAR, 4, 0, 3, 3, 3 > xwww;
			Swizzle< SCALAR, 4, 1, 0, 0, 0 > yxxx;
			Swizzle< SCALAR, 4, 1, 0, 0, 1 > yxxy;
			Swizzle< SCALAR, 4, 1, 0, 0, 2 > yxxz;
			Swizzle< SCALAR, 4, 1, 0, 0, 3 > yxxw;
			Swizzle< SCALAR, 4, 1, 0, 1, 0 > yxyx;
			Swizzle< SCALAR, 4, 1, 0, 1, 1 > yxyy;
			Swizzle< SCALAR, 4, 1, 0, 1, 2 > yxyz;
			Swizzle< SCALAR, 4, 1, 0, 1, 3 > yxyw;
			Swizzle< SCALAR, 4, 1, 0, 2, 0 > yxzx;
			Swizzle< SCALAR, 4, 1, 0, 2, 1 > yxzy;
			Swizzle< SCALAR, 4, 1, 0, 2, 2 > yxzz;
			Swizzle< SCALAR, 4, 1, 0, 2, 3 > yxzw;
			Swizzle< SCALAR, 4, 1, 0, 3, 0 > yxwx;
			Swizzle< SCALAR, 4, 1, 0, 3, 1 > yxwy;
			Swizzle< SCALAR, 4, 1, 0, 3, 2 > yxwz;
			Swizzle< SCALAR, 4, 1, 0, 3, 3 > yxww;
			Swizzle< SCALAR, 4, 1, 1, 0, 0 > yyxx;
			Swizzle< SCALAR, 4, 1, 1, 0, 1 > yyxy;
			Swizzle< SCALAR, 4, 1, 1, 0, 2 > yyxz;
			Swizzle< SCALAR, 4, 1, 1, 0, 3 > yyxw;
			Swizzle< SCALAR, 4, 1, 1, 1, 0 > yyyx;
			Swizzle< SCALAR, 4, 1, 1, 1, 1 > yyyy;
			Swizzle< SCALAR, 4, 1, 1, 1, 2 > yyyz;
			Swizzle< SCALAR, 4, 1, 1, 1, 3 > yyyw;
			Swizzle< SCALAR, 4, 1, 1, 2, 0 > yyzx;
			Swizzle< SCALAR, 4, 1, 1, 2, 1 > yyzy;
			Swizzle< SCALAR, 4, 1, 1, 2, 2 > yyzz;
			Swizzle< SCALAR, 4, 1, 1, 2, 3 > yyzw;
			Swizzle< SCALAR, 4, 1, 1, 3, 0 > yywx;
			Swizzle< SCALAR, 4, 1, 1, 3, 1 > yywy;
			Swizzle< SCALAR, 4, 1, 1, 3, 2 > yywz;
			Swizzle< SCALAR, 4, 1, 1, 3, 3 > yyww;
			Swizzle< SCALAR, 4, 1, 2, 0, 0 > yzxx;
			Swizzle< SCALAR, 4, 1, 2, 0, 1 > yzxy;
			Swizzle< SCALAR, 4, 1, 2, 0, 2 > yzxz;
			Swizzle< SCALAR, 4, 1, 2, 0, 3 > yzxw;
			Swizzle< SCALAR, 4, 1, 2, 1, 0 > yzyx;
			Swizzle< SCALAR, 4, 1, 2, 1, 1 > yzyy;
			Swizzle< SCALAR, 4, 1, 2, 1, 2 > yzyz;
			Swizzle< SCALAR, 4, 1, 2, 1, 3 > yzyw;
			Swizzle< SCALAR, 4, 1, 2, 2, 0 > yzzx;
			Swizzle< SCALAR, 4, 1, 2, 2, 1 > yzzy;
			Swizzle< SCALAR, 4, 1, 2, 2, 2 > yzzz;
			Swizzle< SCALAR, 4, 1, 2, 2, 3 > yzzw;
			Swizzle< SCALAR, 4, 1, 2, 3, 0 > yzwx;
			Swizzle< SCALAR, 4, 1, 2, 3, 1 > yzwy;
			Swizzle< SCALAR, 4, 1, 2, 3, 2 > yzwz;
			Swizzle< SCALAR, 4, 1, 2, 3, 3 > yzww;
			Swizzle< SCALAR, 4, 1, 3, 0, 0 > ywxx;
			Swizzle< SCALAR, 4, 1, 3, 0, 1 > ywxy;
			Swizzle< SCALAR, 4, 1, 3, 0, 2 > ywxz;
			Swizzle< SCALAR, 4, 1, 3, 0, 3 > ywxw;
			Swizzle< SCALAR, 4, 1, 3, 1, 0 > ywyx;
			Swizzle< SCALAR, 4, 1, 3, 1, 1 > ywyy;
			Swizzle< SCALAR, 4, 1, 3, 1, 2 > ywyz;
			Swizzle< SCALAR, 4, 1, 3, 1, 3 > ywyw;
			Swizzle< SCALAR, 4, 1, 3, 2, 0 > ywzx;
			Swizzle< SCALAR, 4, 1, 3, 2, 1 > ywzy;
			Swizzle< SCALAR, 4, 1, 3, 2, 2 > ywzz;
			Swizzle< SCALAR, 4, 1, 3, 2, 3 > ywzw;
			Swizzle< SCALAR, 4, 1, 3, 3, 0 > ywwx;
			Swizzle< SCALAR, 4, 1, 3, 3, 1 > ywwy;
			Swizzle< SCALAR, 4, 1, 3, 3, 2 > ywwz;
			Swizzle< SCALAR, 4, 1, 3, 3, 3 > ywww;
			Swizzle< SCALAR, 4, 2, 0, 0, 0 > zxxx;
			Swizzle< SCALAR, 4, 2, 0, 0, 1 > zxxy;
			Swizzle< SCALAR, 4, 2, 0, 0, 2 > zxxz;
			Swizzle< SCALAR, 4, 2, 0, 0, 3 > zxxw;
			Swizzle< SCALAR, 4, 2, 0, 1, 0 > zxyx;
			Swizzle< SCALAR, 4, 2, 0, 1, 1 > zxyy;
			Swizzle< SCALAR, 4, 2, 0, 1, 2 > zxyz;
			Swizzle< SCALAR, 4, 2, 0, 1, 3 > zxyw;
			Swizzle< SCALAR, 4, 2, 0, 2, 0 > zxzx;
			Swizzle< SCALAR, 4, 2, 0, 2, 1 > zxzy;
			Swizzle< SCALAR, 4, 2, 0, 2, 2 > zxzz;
			Swizzle< SCALAR, 4, 2, 0, 2, 3 > zxzw;
			Swizzle< SCALAR, 4, 2, 0, 3, 0 > zxwx;
			Swizzle< SCALAR, 4, 2, 0, 3, 1 > zxwy;
			Swizzle< SCALAR, 4, 2, 0, 3, 2 > zxwz;
			Swizzle< SCALAR, 4, 2, 0, 3, 3 > zxww;
			Swizzle< SCALAR, 4, 2, 1, 0, 0 > zyxx;
			Swizzle< SCALAR, 4, 2, 1, 0, 1 > zyxy;
			Swizzle< SCALAR, 4, 2, 1, 0, 2 > zyxz;
			Swizzle< SCALAR, 4, 2, 1, 0, 3 > zyxw;
			Swizzle< SCALAR, 4, 2, 1, 1, 0 > zyyx;
			Swizzle< SCALAR, 4, 2, 1, 1, 1 > zyyy;
			Swizzle< SCALAR, 4, 2, 1, 1, 2 > zyyz;
			Swizzle< SCALAR, 4, 2, 1, 1, 3 > zyyw;
			Swizzle< SCALAR, 4, 2, 1, 2, 0 > zyzx;
			Swizzle< SCALAR, 4, 2, 1, 2, 1 > zyzy;
			Swizzle< SCALAR, 4, 2, 1, 2, 2 > zyzz;
			Swizzle< SCALAR, 4, 2, 1, 2, 3 > zyzw;
			Swizzle< SCALAR, 4, 2, 1, 3, 0 > zywx;
			Swizzle< SCALAR, 4, 2, 1, 3, 1 > zywy;
			Swizzle< SCALAR, 4, 2, 1, 3, 2 > zywz;
			Swizzle< SCALAR, 4, 2, 1, 3, 3 > zyww;
			Swizzle< SCALAR, 4, 2, 2, 0, 0 > zzxx;
			Swizzle< SCALAR, 4, 2, 2, 0, 1 > zzxy;
			Swizzle< SCALAR, 4, 2, 2, 0, 2 > zzxz;
			Swizzle< SCALAR, 4, 2, 2, 0, 3 > zzxw;
			Swizzle< SCALAR, 4, 2, 2, 1, 0 > zzyx;
			Swizzle< SCALAR, 4, 2, 2, 1, 1 > zzyy;
			Swizzle< SCALAR, 4, 2, 2, 1, 2 > zzyz;
			Swizzle< SCALAR, 4, 2, 2, 1, 3 > zzyw;
			Swizzle< SCALAR, 4, 2, 2, 2, 0 > zzzx;
			Swizzle< SCALAR, 4, 2, 2, 2, 1 > zzzy;
			Swizzle< SCALAR, 4, 2, 2, 2, 2 > zzzz;
			Swizzle< SCALAR, 4, 2, 2, 2, 3 > zzzw;
			Swizzle< SCALAR, 4, 2, 2, 3, 0 > zzwx;
			Swizzle< SCALAR, 4, 2, 2, 3, 1 > zzwy;
			Swizzle< SCALAR, 4, 2, 2, 3, 2 > zzwz;
			Swizzle< SCALAR, 4, 2, 2, 3, 3 > zzww;
			Swizzle< SCALAR, 4, 2, 3, 0, 0 > zwxx;
			Swizzle< SCALAR, 4, 2, 3, 0, 1 > zwxy;
			Swizzle< SCALAR, 4, 2, 3, 0, 2 > zwxz;
			Swizzle< SCALAR, 4, 2, 3, 0, 3 > zwxw;
			Swizzle< SCALAR, 4, 2, 3, 1, 0 > zwyx;
			Swizzle< SCALAR, 4, 2, 3, 1, 1 > zwyy;
			Swizzle< SCALAR, 4, 2, 3, 1, 2 > zwyz;
			Swizzle< SCALAR, 4, 2, 3, 1, 3 > zwyw;
			Swizzle< SCALAR, 4, 2, 3, 2, 0 > zwzx;
			Swizzle< SCALAR, 4, 2, 3, 2, 1 > zwzy;
			Swizzle< SCALAR, 4, 2, 3, 2, 2 > zwzz;
			Swizzle< SCALAR, 4, 2, 3, 2, 3 > zwzw;
			Swizzle< SCALAR, 4, 2, 3, 3, 0 > zwwx;
			Swizzle< SCALAR, 4, 2, 3, 3, 1 > zwwy;
			Swizzle< SCALAR, 4, 2, 3, 3, 2 > zwwz;
			Swizzle< SCALAR, 4, 2, 3, 3, 3 > zwww;
			Swizzle< SCALAR, 4, 3, 0, 0, 0 > wxxx;
			Swizzle< SCALAR, 4, 3, 0, 0, 1 > wxxy;
			Swizzle< SCALAR, 4, 3, 0, 0, 2 > wxxz;
			Swizzle< SCALAR, 4, 3, 0, 0, 3 > wxxw;
			Swizzle< SCALAR, 4, 3, 0, 1, 0 > wxyx;
			Swizzle< SCALAR, 4, 3, 0, 1, 1 > wxyy;
			Swizzle< SCALAR, 4, 3, 0, 1, 2 > wxyz;
			Swizzle< SCALAR, 4, 3, 0, 1, 3 > wxyw;
			Swizzle< SCALAR, 4, 3, 0, 2, 0 > wxzx;
			Swizzle< SCALAR, 4, 3, 0, 2, 1 > wxzy;
			Swizzle< SCALAR, 4, 3, 0, 2, 2 > wxzz;
			Swizzle< SCALAR, 4, 3, 0, 2, 3 > wxzw;
			Swizzle< SCALAR, 4, 3, 0, 3, 0 > wxwx;
			Swizzle< SCALAR, 4, 3, 0, 3, 1 > wxwy;
			Swizzle< SCALAR, 4, 3, 0, 3, 2 > wxwz;
			Swizzle< SCALAR, 4, 3, 0, 3, 3 > wxww;
			Swizzle< SCALAR, 4, 3, 1, 0, 0 > wyxx;
			Swizzle< SCALAR, 4, 3, 1, 0, 1 > wyxy;
			Swizzle< SCALAR, 4, 3, 1, 0, 2 > wyxz;
			Swizzle< SCALAR, 4, 3, 1, 0, 3 > wyxw;
			Swizzle< SCALAR, 4, 3, 1, 1, 0 > wyyx;
			Swizzle< SCALAR, 4, 3, 1, 1, 1 > wyyy;
			Swizzle< SCALAR, 4, 3, 1, 1, 2 > wyyz;
			Swizzle< SCALAR, 4, 3, 1, 1, 3 > wyyw;
			Swizzle< SCALAR, 4, 3, 1, 2, 0 > wyzx;
			Swizzle< SCALAR, 4, 3, 1, 2, 1 > wyzy;
			Swizzle< SCALAR, 4, 3, 1, 2, 2 > wyzz;
			Swizzle< SCALAR, 4, 3, 1, 2, 3 > wyzw;
			Swizzle< SCALAR, 4, 3, 1, 3, 0 > wywx;
			Swizzle< SCALAR, 4, 3, 1, 3, 1 > wywy;
			Swizzle< SCALAR, 4, 3, 1, 3, 2 > wywz;
			Swizzle< SCALAR, 4, 3, 1, 3, 3 > wyww;
			Swizzle< SCALAR, 4, 3, 2, 0, 0 > wzxx;
			Swizzle< SCALAR, 4, 3, 2, 0, 1 > wzxy;
			Swizzle< SCALAR, 4, 3, 2, 0, 2 > wzxz;
			Swizzle< SCALAR, 4, 3, 2, 0, 3 > wzxw;
			Swizzle< SCALAR, 4, 3, 2, 1, 0 > wzyx;
			Swizzle< SCALAR, 4, 3, 2, 1, 1 > wzyy;
			Swizzle< SCALAR, 4, 3, 2, 1, 2 > wzyz;
			Swizzle< SCALAR, 4, 3, 2, 1, 3 > wzyw;
			Swizzle< SCALAR, 4, 3, 2, 2, 0 > wzzx;
			Swizzle< SCALAR, 4, 3, 2, 2, 1 > wzzy;
			Swizzle< SCALAR, 4, 3, 2, 2, 2 > wzzz;
			Swizzle< SCALAR, 4, 3, 2, 2, 3 > wzzw;
			Swizzle< SCALAR, 4, 3, 2, 3, 0 > wzwx;
			Swizzle< SCALAR, 4, 3, 2, 3, 1 > wzwy;
			Swizzle< SCALAR, 4, 3, 2, 3, 2 > wzwz;
			Swizzle< SCALAR, 4, 3, 2, 3, 3 > wzww;
			Swizzle< SCALAR, 4, 3, 3, 0, 0 > wwxx;
			Swizzle< SCALAR, 4, 3, 3, 0, 1 > wwxy;
			Swizzle< SCALAR, 4, 3, 3, 0, 2 > wwxz;
			Swizzle< SCALAR, 4, 3, 3, 0, 3 > wwxw;
			Swizzle< SCALAR, 4, 3, 3, 1, 0 > wwyx;
			Swizzle< SCALAR, 4, 3, 3, 1, 1 > wwyy;
			Swizzle< SCALAR, 4, 3, 3, 1, 2 > wwyz;
			Swizzle< SCALAR, 4, 3, 3, 1, 3 > wwyw;
			Swizzle< SCALAR, 4, 3, 3, 2, 0 > wwzx;
			Swizzle< SCALAR, 4, 3, 3, 2, 1 > wwzy;
			Swizzle< SCALAR, 4, 3, 3, 2, 2 > wwzz;
			Swizzle< SCALAR, 4, 3, 3, 2, 3 > wwzw;
			Swizzle< SCALAR, 4, 3, 3, 3, 0 > wwwx;
			Swizzle< SCALAR, 4, 3, 3, 3, 1 > wwwy;
			Swizzle< SCALAR, 4, 3, 3, 3, 2 > wwwz;
			Swizzle< SCALAR, 4, 3, 3, 3, 3 > wwww;
		};

		VectorBase()
		{
			ZeroMemory(_vector, sizeof(SCALAR) * 4);
		}

		VectorBase(ScalarType x, ScalarType y, ScalarType z, ScalarType w) :
			x(x),y(y),z(z),w(w)
		{
		}

		virtual ~VectorBase() = default;

	};

	template<typename SCALAR>
	class ColorBase
	{
	public:
		union
		{
			SCALAR color[4];
			struct
			{
				SCALAR r;
				SCALAR g;
				SCALAR b;
				SCALAR a;
			};
			Swizzle< SCALAR, 4, 0, 0 > rr;
			Swizzle< SCALAR, 4, 0, 1 > rg;
			Swizzle< SCALAR, 4, 0, 2 > rb;
			Swizzle< SCALAR, 4, 0, 3 > ra;
			Swizzle< SCALAR, 4, 1, 0 > gr;
			Swizzle< SCALAR, 4, 1, 1 > gg;
			Swizzle< SCALAR, 4, 1, 2 > gb;
			Swizzle< SCALAR, 4, 1, 3 > ga;
			Swizzle< SCALAR, 4, 2, 0 > br;
			Swizzle< SCALAR, 4, 2, 1 > bg;
			Swizzle< SCALAR, 4, 2, 2 > bb;
			Swizzle< SCALAR, 4, 2, 3 > ba;
			Swizzle< SCALAR, 4, 3, 0 > ar;
			Swizzle< SCALAR, 4, 3, 1 > ag;
			Swizzle< SCALAR, 4, 3, 2 > ab;
			Swizzle< SCALAR, 4, 3, 3 > aa;

			Swizzle< SCALAR, 4, 0, 0, 0 > rrr;
			Swizzle< SCALAR, 4, 0, 0, 1 > rrg;
			Swizzle< SCALAR, 4, 0, 0, 2 > rrb;
			Swizzle< SCALAR, 4, 0, 0, 3 > rra;
			Swizzle< SCALAR, 4, 0, 1, 0 > rgr;
			Swizzle< SCALAR, 4, 0, 1, 1 > rgg;
			Swizzle< SCALAR, 4, 0, 1, 2 > rgb;
			Swizzle< SCALAR, 4, 0, 1, 3 > rga;
			Swizzle< SCALAR, 4, 0, 2, 0 > rbr;
			Swizzle< SCALAR, 4, 0, 2, 1 > rbg;
			Swizzle< SCALAR, 4, 0, 2, 2 > rbb;
			Swizzle< SCALAR, 4, 0, 2, 3 > rba;
			Swizzle< SCALAR, 4, 0, 3, 0 > rar;
			Swizzle< SCALAR, 4, 0, 3, 1 > rag;
			Swizzle< SCALAR, 4, 0, 3, 2 > rab;
			Swizzle< SCALAR, 4, 0, 3, 3 > raa;
			Swizzle< SCALAR, 4, 1, 0, 0 > grr;
			Swizzle< SCALAR, 4, 1, 0, 1 > grg;
			Swizzle< SCALAR, 4, 1, 0, 2 > grb;
			Swizzle< SCALAR, 4, 1, 0, 3 > gra;
			Swizzle< SCALAR, 4, 1, 1, 0 > ggr;
			Swizzle< SCALAR, 4, 1, 1, 1 > ggg;
			Swizzle< SCALAR, 4, 1, 1, 2 > ggb;
			Swizzle< SCALAR, 4, 1, 1, 3 > gga;
			Swizzle< SCALAR, 4, 1, 2, 0 > gbr;
			Swizzle< SCALAR, 4, 1, 2, 1 > gbg;
			Swizzle< SCALAR, 4, 1, 2, 2 > gbb;
			Swizzle< SCALAR, 4, 1, 2, 3 > gba;
			Swizzle< SCALAR, 4, 1, 3, 0 > gar;
			Swizzle< SCALAR, 4, 1, 3, 1 > gag;
			Swizzle< SCALAR, 4, 1, 3, 2 > gab;
			Swizzle< SCALAR, 4, 1, 3, 3 > gaa;
			Swizzle< SCALAR, 4, 2, 0, 0 > brr;
			Swizzle< SCALAR, 4, 2, 0, 1 > brg;
			Swizzle< SCALAR, 4, 2, 0, 2 > brb;
			Swizzle< SCALAR, 4, 2, 0, 3 > bra;
			Swizzle< SCALAR, 4, 2, 1, 0 > bgr;
			Swizzle< SCALAR, 4, 2, 1, 1 > bgg;
			Swizzle< SCALAR, 4, 2, 1, 2 > bgb;
			Swizzle< SCALAR, 4, 2, 1, 3 > bga;
			Swizzle< SCALAR, 4, 2, 2, 0 > bbr;
			Swizzle< SCALAR, 4, 2, 2, 1 > bbg;
			Swizzle< SCALAR, 4, 2, 2, 2 > bbb;
			Swizzle< SCALAR, 4, 2, 2, 3 > bba;
			Swizzle< SCALAR, 4, 2, 3, 0 > bar;
			Swizzle< SCALAR, 4, 2, 3, 1 > bag;
			Swizzle< SCALAR, 4, 2, 3, 2 > bab;
			Swizzle< SCALAR, 4, 2, 3, 3 > baa;
			Swizzle< SCALAR, 4, 3, 0, 0 > arr;
			Swizzle< SCALAR, 4, 3, 0, 1 > arg;
			Swizzle< SCALAR, 4, 3, 0, 2 > arb;
			Swizzle< SCALAR, 4, 3, 0, 3 > ara;
			Swizzle< SCALAR, 4, 3, 1, 0 > agr;
			Swizzle< SCALAR, 4, 3, 1, 1 > agg;
			Swizzle< SCALAR, 4, 3, 1, 2 > agb;
			Swizzle< SCALAR, 4, 3, 1, 3 > aga;
			Swizzle< SCALAR, 4, 3, 2, 0 > abr;
			Swizzle< SCALAR, 4, 3, 2, 1 > abg;
			Swizzle< SCALAR, 4, 3, 2, 2 > abb;
			Swizzle< SCALAR, 4, 3, 2, 3 > aba;
			Swizzle< SCALAR, 4, 3, 3, 0 > aar;
			Swizzle< SCALAR, 4, 3, 3, 1 > aag;
			Swizzle< SCALAR, 4, 3, 3, 2 > aab;
			Swizzle< SCALAR, 4, 3, 3, 3 > aaa;

			Swizzle< SCALAR, 4, 0, 0, 0, 0 > rrrr;
			Swizzle< SCALAR, 4, 0, 0, 0, 1 > rrrg;
			Swizzle< SCALAR, 4, 0, 0, 0, 2 > rrrb;
			Swizzle< SCALAR, 4, 0, 0, 0, 3 > rrra;
			Swizzle< SCALAR, 4, 0, 0, 1, 0 > rrgr;
			Swizzle< SCALAR, 4, 0, 0, 1, 1 > rrgg;
			Swizzle< SCALAR, 4, 0, 0, 1, 2 > rrgb;
			Swizzle< SCALAR, 4, 0, 0, 1, 3 > rrga;
			Swizzle< SCALAR, 4, 0, 0, 2, 0 > rrbr;
			Swizzle< SCALAR, 4, 0, 0, 2, 1 > rrbg;
			Swizzle< SCALAR, 4, 0, 0, 2, 2 > rrbb;
			Swizzle< SCALAR, 4, 0, 0, 2, 3 > rrba;
			Swizzle< SCALAR, 4, 0, 0, 3, 0 > rrar;
			Swizzle< SCALAR, 4, 0, 0, 3, 1 > rrag;
			Swizzle< SCALAR, 4, 0, 0, 3, 2 > rrab;
			Swizzle< SCALAR, 4, 0, 0, 3, 3 > rraa;
			Swizzle< SCALAR, 4, 0, 1, 0, 0 > rgrr;
			Swizzle< SCALAR, 4, 0, 1, 0, 1 > rgrg;
			Swizzle< SCALAR, 4, 0, 1, 0, 2 > rgrb;
			Swizzle< SCALAR, 4, 0, 1, 0, 3 > rgra;
			Swizzle< SCALAR, 4, 0, 1, 1, 0 > rggr;
			Swizzle< SCALAR, 4, 0, 1, 1, 1 > rggg;
			Swizzle< SCALAR, 4, 0, 1, 1, 2 > rggb;
			Swizzle< SCALAR, 4, 0, 1, 1, 3 > rgga;
			Swizzle< SCALAR, 4, 0, 1, 2, 0 > rgbr;
			Swizzle< SCALAR, 4, 0, 1, 2, 1 > rgbg;
			Swizzle< SCALAR, 4, 0, 1, 2, 2 > rgbb;
			Swizzle< SCALAR, 4, 0, 1, 2, 3 > rgba;
			Swizzle< SCALAR, 4, 0, 1, 3, 0 > rgar;
			Swizzle< SCALAR, 4, 0, 1, 3, 1 > rgag;
			Swizzle< SCALAR, 4, 0, 1, 3, 2 > rgab;
			Swizzle< SCALAR, 4, 0, 1, 3, 3 > rgaa;
			Swizzle< SCALAR, 4, 0, 2, 0, 0 > rbrr;
			Swizzle< SCALAR, 4, 0, 2, 0, 1 > rbrg;
			Swizzle< SCALAR, 4, 0, 2, 0, 2 > rbrb;
			Swizzle< SCALAR, 4, 0, 2, 0, 3 > rbra;
			Swizzle< SCALAR, 4, 0, 2, 1, 0 > rbgr;
			Swizzle< SCALAR, 4, 0, 2, 1, 1 > rbgg;
			Swizzle< SCALAR, 4, 0, 2, 1, 2 > rbgb;
			Swizzle< SCALAR, 4, 0, 2, 1, 3 > rbga;
			Swizzle< SCALAR, 4, 0, 2, 2, 0 > rbbr;
			Swizzle< SCALAR, 4, 0, 2, 2, 1 > rbbg;
			Swizzle< SCALAR, 4, 0, 2, 2, 2 > rbbb;
			Swizzle< SCALAR, 4, 0, 2, 2, 3 > rbba;
			Swizzle< SCALAR, 4, 0, 2, 3, 0 > rbar;
			Swizzle< SCALAR, 4, 0, 2, 3, 1 > rbag;
			Swizzle< SCALAR, 4, 0, 2, 3, 2 > rbab;
			Swizzle< SCALAR, 4, 0, 2, 3, 3 > rbaa;
			Swizzle< SCALAR, 4, 0, 3, 0, 0 > rarr;
			Swizzle< SCALAR, 4, 0, 3, 0, 1 > rarg;
			Swizzle< SCALAR, 4, 0, 3, 0, 2 > rarb;
			Swizzle< SCALAR, 4, 0, 3, 0, 3 > rara;
			Swizzle< SCALAR, 4, 0, 3, 1, 0 > ragr;
			Swizzle< SCALAR, 4, 0, 3, 1, 1 > ragg;
			Swizzle< SCALAR, 4, 0, 3, 1, 2 > ragb;
			Swizzle< SCALAR, 4, 0, 3, 1, 3 > raga;
			Swizzle< SCALAR, 4, 0, 3, 2, 0 > rabr;
			Swizzle< SCALAR, 4, 0, 3, 2, 1 > rabg;
			Swizzle< SCALAR, 4, 0, 3, 2, 2 > rabb;
			Swizzle< SCALAR, 4, 0, 3, 2, 3 > raba;
			Swizzle< SCALAR, 4, 0, 3, 3, 0 > raar;
			Swizzle< SCALAR, 4, 0, 3, 3, 1 > raag;
			Swizzle< SCALAR, 4, 0, 3, 3, 2 > raab;
			Swizzle< SCALAR, 4, 0, 3, 3, 3 > raaa;
			Swizzle< SCALAR, 4, 1, 0, 0, 0 > grrr;
			Swizzle< SCALAR, 4, 1, 0, 0, 1 > grrg;
			Swizzle< SCALAR, 4, 1, 0, 0, 2 > grrb;
			Swizzle< SCALAR, 4, 1, 0, 0, 3 > grra;
			Swizzle< SCALAR, 4, 1, 0, 1, 0 > grgr;
			Swizzle< SCALAR, 4, 1, 0, 1, 1 > grgg;
			Swizzle< SCALAR, 4, 1, 0, 1, 2 > grgb;
			Swizzle< SCALAR, 4, 1, 0, 1, 3 > grga;
			Swizzle< SCALAR, 4, 1, 0, 2, 0 > grbr;
			Swizzle< SCALAR, 4, 1, 0, 2, 1 > grbg;
			Swizzle< SCALAR, 4, 1, 0, 2, 2 > grbb;
			Swizzle< SCALAR, 4, 1, 0, 2, 3 > grba;
			Swizzle< SCALAR, 4, 1, 0, 3, 0 > grar;
			Swizzle< SCALAR, 4, 1, 0, 3, 1 > grag;
			Swizzle< SCALAR, 4, 1, 0, 3, 2 > grab;
			Swizzle< SCALAR, 4, 1, 0, 3, 3 > graa;
			Swizzle< SCALAR, 4, 1, 1, 0, 0 > ggrr;
			Swizzle< SCALAR, 4, 1, 1, 0, 1 > ggrg;
			Swizzle< SCALAR, 4, 1, 1, 0, 2 > ggrb;
			Swizzle< SCALAR, 4, 1, 1, 0, 3 > ggra;
			Swizzle< SCALAR, 4, 1, 1, 1, 0 > gggr;
			Swizzle< SCALAR, 4, 1, 1, 1, 1 > gggg;
			Swizzle< SCALAR, 4, 1, 1, 1, 2 > gggb;
			Swizzle< SCALAR, 4, 1, 1, 1, 3 > ggga;
			Swizzle< SCALAR, 4, 1, 1, 2, 0 > ggbr;
			Swizzle< SCALAR, 4, 1, 1, 2, 1 > ggbg;
			Swizzle< SCALAR, 4, 1, 1, 2, 2 > ggbb;
			Swizzle< SCALAR, 4, 1, 1, 2, 3 > ggba;
			Swizzle< SCALAR, 4, 1, 1, 3, 0 > ggar;
			Swizzle< SCALAR, 4, 1, 1, 3, 1 > ggag;
			Swizzle< SCALAR, 4, 1, 1, 3, 2 > ggab;
			Swizzle< SCALAR, 4, 1, 1, 3, 3 > ggaa;
			Swizzle< SCALAR, 4, 1, 2, 0, 0 > gbrr;
			Swizzle< SCALAR, 4, 1, 2, 0, 1 > gbrg;
			Swizzle< SCALAR, 4, 1, 2, 0, 2 > gbrb;
			Swizzle< SCALAR, 4, 1, 2, 0, 3 > gbra;
			Swizzle< SCALAR, 4, 1, 2, 1, 0 > gbgr;
			Swizzle< SCALAR, 4, 1, 2, 1, 1 > gbgg;
			Swizzle< SCALAR, 4, 1, 2, 1, 2 > gbgb;
			Swizzle< SCALAR, 4, 1, 2, 1, 3 > gbga;
			Swizzle< SCALAR, 4, 1, 2, 2, 0 > gbbr;
			Swizzle< SCALAR, 4, 1, 2, 2, 1 > gbbg;
			Swizzle< SCALAR, 4, 1, 2, 2, 2 > gbbb;
			Swizzle< SCALAR, 4, 1, 2, 2, 3 > gbba;
			Swizzle< SCALAR, 4, 1, 2, 3, 0 > gbar;
			Swizzle< SCALAR, 4, 1, 2, 3, 1 > gbag;
			Swizzle< SCALAR, 4, 1, 2, 3, 2 > gbab;
			Swizzle< SCALAR, 4, 1, 2, 3, 3 > gbaa;
			Swizzle< SCALAR, 4, 1, 3, 0, 0 > garr;
			Swizzle< SCALAR, 4, 1, 3, 0, 1 > garg;
			Swizzle< SCALAR, 4, 1, 3, 0, 2 > garb;
			Swizzle< SCALAR, 4, 1, 3, 0, 3 > gara;
			Swizzle< SCALAR, 4, 1, 3, 1, 0 > gagr;
			Swizzle< SCALAR, 4, 1, 3, 1, 1 > gagg;
			Swizzle< SCALAR, 4, 1, 3, 1, 2 > gagb;
			Swizzle< SCALAR, 4, 1, 3, 1, 3 > gaga;
			Swizzle< SCALAR, 4, 1, 3, 2, 0 > gabr;
			Swizzle< SCALAR, 4, 1, 3, 2, 1 > gabg;
			Swizzle< SCALAR, 4, 1, 3, 2, 2 > gabb;
			Swizzle< SCALAR, 4, 1, 3, 2, 3 > gaba;
			Swizzle< SCALAR, 4, 1, 3, 3, 0 > gaar;
			Swizzle< SCALAR, 4, 1, 3, 3, 1 > gaag;
			Swizzle< SCALAR, 4, 1, 3, 3, 2 > gaab;
			Swizzle< SCALAR, 4, 1, 3, 3, 3 > gaaa;
			Swizzle< SCALAR, 4, 2, 0, 0, 0 > brrr;
			Swizzle< SCALAR, 4, 2, 0, 0, 1 > brrg;
			Swizzle< SCALAR, 4, 2, 0, 0, 2 > brrb;
			Swizzle< SCALAR, 4, 2, 0, 0, 3 > brra;
			Swizzle< SCALAR, 4, 2, 0, 1, 0 > brgr;
			Swizzle< SCALAR, 4, 2, 0, 1, 1 > brgg;
			Swizzle< SCALAR, 4, 2, 0, 1, 2 > brgb;
			Swizzle< SCALAR, 4, 2, 0, 1, 3 > brga;
			Swizzle< SCALAR, 4, 2, 0, 2, 0 > brbr;
			Swizzle< SCALAR, 4, 2, 0, 2, 1 > brbg;
			Swizzle< SCALAR, 4, 2, 0, 2, 2 > brbb;
			Swizzle< SCALAR, 4, 2, 0, 2, 3 > brba;
			Swizzle< SCALAR, 4, 2, 0, 3, 0 > brar;
			Swizzle< SCALAR, 4, 2, 0, 3, 1 > brag;
			Swizzle< SCALAR, 4, 2, 0, 3, 2 > brab;
			Swizzle< SCALAR, 4, 2, 0, 3, 3 > braa;
			Swizzle< SCALAR, 4, 2, 1, 0, 0 > bgrr;
			Swizzle< SCALAR, 4, 2, 1, 0, 1 > bgrg;
			Swizzle< SCALAR, 4, 2, 1, 0, 2 > bgrb;
			Swizzle< SCALAR, 4, 2, 1, 0, 3 > bgra;
			Swizzle< SCALAR, 4, 2, 1, 1, 0 > bggr;
			Swizzle< SCALAR, 4, 2, 1, 1, 1 > bggg;
			Swizzle< SCALAR, 4, 2, 1, 1, 2 > bggb;
			Swizzle< SCALAR, 4, 2, 1, 1, 3 > bgga;
			Swizzle< SCALAR, 4, 2, 1, 2, 0 > bgbr;
			Swizzle< SCALAR, 4, 2, 1, 2, 1 > bgbg;
			Swizzle< SCALAR, 4, 2, 1, 2, 2 > bgbb;
			Swizzle< SCALAR, 4, 2, 1, 2, 3 > bgba;
			Swizzle< SCALAR, 4, 2, 1, 3, 0 > bgar;
			Swizzle< SCALAR, 4, 2, 1, 3, 1 > bgag;
			Swizzle< SCALAR, 4, 2, 1, 3, 2 > bgab;
			Swizzle< SCALAR, 4, 2, 1, 3, 3 > bgaa;
			Swizzle< SCALAR, 4, 2, 2, 0, 0 > bbrr;
			Swizzle< SCALAR, 4, 2, 2, 0, 1 > bbrg;
			Swizzle< SCALAR, 4, 2, 2, 0, 2 > bbrb;
			Swizzle< SCALAR, 4, 2, 2, 0, 3 > bbra;
			Swizzle< SCALAR, 4, 2, 2, 1, 0 > bbgr;
			Swizzle< SCALAR, 4, 2, 2, 1, 1 > bbgg;
			Swizzle< SCALAR, 4, 2, 2, 1, 2 > bbgb;
			Swizzle< SCALAR, 4, 2, 2, 1, 3 > bbga;
			Swizzle< SCALAR, 4, 2, 2, 2, 0 > bbbr;
			Swizzle< SCALAR, 4, 2, 2, 2, 1 > bbbg;
			Swizzle< SCALAR, 4, 2, 2, 2, 2 > bbbb;
			Swizzle< SCALAR, 4, 2, 2, 2, 3 > bbba;
			Swizzle< SCALAR, 4, 2, 2, 3, 0 > bbar;
			Swizzle< SCALAR, 4, 2, 2, 3, 1 > bbag;
			Swizzle< SCALAR, 4, 2, 2, 3, 2 > bbab;
			Swizzle< SCALAR, 4, 2, 2, 3, 3 > bbaa;
			Swizzle< SCALAR, 4, 2, 3, 0, 0 > barr;
			Swizzle< SCALAR, 4, 2, 3, 0, 1 > barg;
			Swizzle< SCALAR, 4, 2, 3, 0, 2 > barb;
			Swizzle< SCALAR, 4, 2, 3, 0, 3 > bara;
			Swizzle< SCALAR, 4, 2, 3, 1, 0 > bagr;
			Swizzle< SCALAR, 4, 2, 3, 1, 1 > bagg;
			Swizzle< SCALAR, 4, 2, 3, 1, 2 > bagb;
			Swizzle< SCALAR, 4, 2, 3, 1, 3 > baga;
			Swizzle< SCALAR, 4, 2, 3, 2, 0 > babr;
			Swizzle< SCALAR, 4, 2, 3, 2, 1 > babg;
			Swizzle< SCALAR, 4, 2, 3, 2, 2 > babb;
			Swizzle< SCALAR, 4, 2, 3, 2, 3 > baba;
			Swizzle< SCALAR, 4, 2, 3, 3, 0 > baar;
			Swizzle< SCALAR, 4, 2, 3, 3, 1 > baag;
			Swizzle< SCALAR, 4, 2, 3, 3, 2 > baab;
			Swizzle< SCALAR, 4, 2, 3, 3, 3 > baaa;
			Swizzle< SCALAR, 4, 3, 0, 0, 0 > arrr;
			Swizzle< SCALAR, 4, 3, 0, 0, 1 > arrg;
			Swizzle< SCALAR, 4, 3, 0, 0, 2 > arrb;
			Swizzle< SCALAR, 4, 3, 0, 0, 3 > arra;
			Swizzle< SCALAR, 4, 3, 0, 1, 0 > argr;
			Swizzle< SCALAR, 4, 3, 0, 1, 1 > argg;
			Swizzle< SCALAR, 4, 3, 0, 1, 2 > argb;
			Swizzle< SCALAR, 4, 3, 0, 1, 3 > arga;
			Swizzle< SCALAR, 4, 3, 0, 2, 0 > arbr;
			Swizzle< SCALAR, 4, 3, 0, 2, 1 > arbg;
			Swizzle< SCALAR, 4, 3, 0, 2, 2 > arbb;
			Swizzle< SCALAR, 4, 3, 0, 2, 3 > arba;
			Swizzle< SCALAR, 4, 3, 0, 3, 0 > arar;
			Swizzle< SCALAR, 4, 3, 0, 3, 1 > arag;
			Swizzle< SCALAR, 4, 3, 0, 3, 2 > arab;
			Swizzle< SCALAR, 4, 3, 0, 3, 3 > araa;
			Swizzle< SCALAR, 4, 3, 1, 0, 0 > agrr;
			Swizzle< SCALAR, 4, 3, 1, 0, 1 > agrg;
			Swizzle< SCALAR, 4, 3, 1, 0, 2 > agrb;
			Swizzle< SCALAR, 4, 3, 1, 0, 3 > agra;
			Swizzle< SCALAR, 4, 3, 1, 1, 0 > aggr;
			Swizzle< SCALAR, 4, 3, 1, 1, 1 > aggg;
			Swizzle< SCALAR, 4, 3, 1, 1, 2 > aggb;
			Swizzle< SCALAR, 4, 3, 1, 1, 3 > agga;
			Swizzle< SCALAR, 4, 3, 1, 2, 0 > agbr;
			Swizzle< SCALAR, 4, 3, 1, 2, 1 > agbg;
			Swizzle< SCALAR, 4, 3, 1, 2, 2 > agbb;
			Swizzle< SCALAR, 4, 3, 1, 2, 3 > agba;
			Swizzle< SCALAR, 4, 3, 1, 3, 0 > agar;
			Swizzle< SCALAR, 4, 3, 1, 3, 1 > agag;
			Swizzle< SCALAR, 4, 3, 1, 3, 2 > agab;
			Swizzle< SCALAR, 4, 3, 1, 3, 3 > agaa;
			Swizzle< SCALAR, 4, 3, 2, 0, 0 > abrr;
			Swizzle< SCALAR, 4, 3, 2, 0, 1 > abrg;
			Swizzle< SCALAR, 4, 3, 2, 0, 2 > abrb;
			Swizzle< SCALAR, 4, 3, 2, 0, 3 > abra;
			Swizzle< SCALAR, 4, 3, 2, 1, 0 > abgr;
			Swizzle< SCALAR, 4, 3, 2, 1, 1 > abgg;
			Swizzle< SCALAR, 4, 3, 2, 1, 2 > abgb;
			Swizzle< SCALAR, 4, 3, 2, 1, 3 > abga;
			Swizzle< SCALAR, 4, 3, 2, 2, 0 > abbr;
			Swizzle< SCALAR, 4, 3, 2, 2, 1 > abbg;
			Swizzle< SCALAR, 4, 3, 2, 2, 2 > abbb;
			Swizzle< SCALAR, 4, 3, 2, 2, 3 > abba;
			Swizzle< SCALAR, 4, 3, 2, 3, 0 > abar;
			Swizzle< SCALAR, 4, 3, 2, 3, 1 > abag;
			Swizzle< SCALAR, 4, 3, 2, 3, 2 > abab;
			Swizzle< SCALAR, 4, 3, 2, 3, 3 > abaa;
			Swizzle< SCALAR, 4, 3, 3, 0, 0 > aarr;
			Swizzle< SCALAR, 4, 3, 3, 0, 1 > aarg;
			Swizzle< SCALAR, 4, 3, 3, 0, 2 > aarb;
			Swizzle< SCALAR, 4, 3, 3, 0, 3 > aara;
			Swizzle< SCALAR, 4, 3, 3, 1, 0 > aagr;
			Swizzle< SCALAR, 4, 3, 3, 1, 1 > aagg;
			Swizzle< SCALAR, 4, 3, 3, 1, 2 > aagb;
			Swizzle< SCALAR, 4, 3, 3, 1, 3 > aaga;
			Swizzle< SCALAR, 4, 3, 3, 2, 0 > aabr;
			Swizzle< SCALAR, 4, 3, 3, 2, 1 > aabg;
			Swizzle< SCALAR, 4, 3, 3, 2, 2 > aabb;
			Swizzle< SCALAR, 4, 3, 3, 2, 3 > aaba;
			Swizzle< SCALAR, 4, 3, 3, 3, 0 > aaar;
			Swizzle< SCALAR, 4, 3, 3, 3, 1 > aaag;
			Swizzle< SCALAR, 4, 3, 3, 3, 2 > aaab;
			Swizzle< SCALAR, 4, 3, 3, 3, 3 > aaaa;
		};

		ColorBase()
		{
			ZeroMemory(color, sizeof(SCALAR) * 4);
		}

		ColorBase(SCALAR r, SCALAR g, SCALAR b, SCALAR a) :
			r(r), g(g), b(b), a(a)
		{
		}

		virtual ~ColorBase() = default;

	};

	template<typename SCALAR>
	class QuaternionBase
	{
	public:
		union
		{
			SCALAR _quaternion[4];
			struct
			{
				SCALAR x;
				SCALAR y;
				SCALAR z;
				SCALAR w;
			};
			Swizzle< SCALAR, 4, 0, 0 > xx;
			Swizzle< SCALAR, 4, 0, 1 > xy;
			Swizzle< SCALAR, 4, 0, 2 > xz;
			Swizzle< SCALAR, 4, 0, 3 > xw;
			Swizzle< SCALAR, 4, 1, 0 > yx;
			Swizzle< SCALAR, 4, 1, 1 > yy;
			Swizzle< SCALAR, 4, 1, 2 > yz;
			Swizzle< SCALAR, 4, 1, 3 > yw;
			Swizzle< SCALAR, 4, 2, 0 > zx;
			Swizzle< SCALAR, 4, 2, 1 > zy;
			Swizzle< SCALAR, 4, 2, 2 > zz;
			Swizzle< SCALAR, 4, 2, 3 > zw;
			Swizzle< SCALAR, 4, 3, 0 > wx;
			Swizzle< SCALAR, 4, 3, 1 > wy;
			Swizzle< SCALAR, 4, 3, 2 > wz;
			Swizzle< SCALAR, 4, 3, 3 > ww;

			Swizzle< SCALAR, 4, 0, 0, 0 > xxx;
			Swizzle< SCALAR, 4, 0, 0, 1 > xxy;
			Swizzle< SCALAR, 4, 0, 0, 2 > xxz;
			Swizzle< SCALAR, 4, 0, 0, 3 > xxw;
			Swizzle< SCALAR, 4, 0, 1, 0 > xyx;
			Swizzle< SCALAR, 4, 0, 1, 1 > xyy;
			Swizzle< SCALAR, 4, 0, 1, 2 > xyz;
			Swizzle< SCALAR, 4, 0, 1, 3 > xyw;
			Swizzle< SCALAR, 4, 0, 2, 0 > xzx;
			Swizzle< SCALAR, 4, 0, 2, 1 > xzy;
			Swizzle< SCALAR, 4, 0, 2, 2 > xzz;
			Swizzle< SCALAR, 4, 0, 2, 3 > xzw;
			Swizzle< SCALAR, 4, 0, 3, 0 > xwx;
			Swizzle< SCALAR, 4, 0, 3, 1 > xwy;
			Swizzle< SCALAR, 4, 0, 3, 2 > xwz;
			Swizzle< SCALAR, 4, 0, 3, 3 > xww;
			Swizzle< SCALAR, 4, 1, 0, 0 > yxx;
			Swizzle< SCALAR, 4, 1, 0, 1 > yxy;
			Swizzle< SCALAR, 4, 1, 0, 2 > yxz;
			Swizzle< SCALAR, 4, 1, 0, 3 > yxw;
			Swizzle< SCALAR, 4, 1, 1, 0 > yyx;
			Swizzle< SCALAR, 4, 1, 1, 1 > yyy;
			Swizzle< SCALAR, 4, 1, 1, 2 > yyz;
			Swizzle< SCALAR, 4, 1, 1, 3 > yyw;
			Swizzle< SCALAR, 4, 1, 2, 0 > yzx;
			Swizzle< SCALAR, 4, 1, 2, 1 > yzy;
			Swizzle< SCALAR, 4, 1, 2, 2 > yzz;
			Swizzle< SCALAR, 4, 1, 2, 3 > yzw;
			Swizzle< SCALAR, 4, 1, 3, 0 > ywx;
			Swizzle< SCALAR, 4, 1, 3, 1 > ywy;
			Swizzle< SCALAR, 4, 1, 3, 2 > ywz;
			Swizzle< SCALAR, 4, 1, 3, 3 > yww;
			Swizzle< SCALAR, 4, 2, 0, 0 > zxx;
			Swizzle< SCALAR, 4, 2, 0, 1 > zxy;
			Swizzle< SCALAR, 4, 2, 0, 2 > zxz;
			Swizzle< SCALAR, 4, 2, 0, 3 > zxw;
			Swizzle< SCALAR, 4, 2, 1, 0 > zyx;
			Swizzle< SCALAR, 4, 2, 1, 1 > zyy;
			Swizzle< SCALAR, 4, 2, 1, 2 > zyz;
			Swizzle< SCALAR, 4, 2, 1, 3 > zyw;
			Swizzle< SCALAR, 4, 2, 2, 0 > zzx;
			Swizzle< SCALAR, 4, 2, 2, 1 > zzy;
			Swizzle< SCALAR, 4, 2, 2, 2 > zzz;
			Swizzle< SCALAR, 4, 2, 2, 3 > zzw;
			Swizzle< SCALAR, 4, 2, 3, 0 > zwx;
			Swizzle< SCALAR, 4, 2, 3, 1 > zwy;
			Swizzle< SCALAR, 4, 2, 3, 2 > zwz;
			Swizzle< SCALAR, 4, 2, 3, 3 > zww;
			Swizzle< SCALAR, 4, 3, 0, 0 > wxx;
			Swizzle< SCALAR, 4, 3, 0, 1 > wxy;
			Swizzle< SCALAR, 4, 3, 0, 2 > wxz;
			Swizzle< SCALAR, 4, 3, 0, 3 > wxw;
			Swizzle< SCALAR, 4, 3, 1, 0 > wyx;
			Swizzle< SCALAR, 4, 3, 1, 1 > wyy;
			Swizzle< SCALAR, 4, 3, 1, 2 > wyz;
			Swizzle< SCALAR, 4, 3, 1, 3 > wyw;
			Swizzle< SCALAR, 4, 3, 2, 0 > wzx;
			Swizzle< SCALAR, 4, 3, 2, 1 > wzy;
			Swizzle< SCALAR, 4, 3, 2, 2 > wzz;
			Swizzle< SCALAR, 4, 3, 2, 3 > wzw;
			Swizzle< SCALAR, 4, 3, 3, 0 > wwx;
			Swizzle< SCALAR, 4, 3, 3, 1 > wwy;
			Swizzle< SCALAR, 4, 3, 3, 2 > wwz;
			Swizzle< SCALAR, 4, 3, 3, 3 > www;

			Swizzle< SCALAR, 4, 0, 0, 0, 0 > xxxx;
			Swizzle< SCALAR, 4, 0, 0, 0, 1 > xxxy;
			Swizzle< SCALAR, 4, 0, 0, 0, 2 > xxxz;
			Swizzle< SCALAR, 4, 0, 0, 0, 3 > xxxw;
			Swizzle< SCALAR, 4, 0, 0, 1, 0 > xxyx;
			Swizzle< SCALAR, 4, 0, 0, 1, 1 > xxyy;
			Swizzle< SCALAR, 4, 0, 0, 1, 2 > xxyz;
			Swizzle< SCALAR, 4, 0, 0, 1, 3 > xxyw;
			Swizzle< SCALAR, 4, 0, 0, 2, 0 > xxzx;
			Swizzle< SCALAR, 4, 0, 0, 2, 1 > xxzy;
			Swizzle< SCALAR, 4, 0, 0, 2, 2 > xxzz;
			Swizzle< SCALAR, 4, 0, 0, 2, 3 > xxzw;
			Swizzle< SCALAR, 4, 0, 0, 3, 0 > xxwx;
			Swizzle< SCALAR, 4, 0, 0, 3, 1 > xxwy;
			Swizzle< SCALAR, 4, 0, 0, 3, 2 > xxwz;
			Swizzle< SCALAR, 4, 0, 0, 3, 3 > xxww;
			Swizzle< SCALAR, 4, 0, 1, 0, 0 > xyxx;
			Swizzle< SCALAR, 4, 0, 1, 0, 1 > xyxy;
			Swizzle< SCALAR, 4, 0, 1, 0, 2 > xyxz;
			Swizzle< SCALAR, 4, 0, 1, 0, 3 > xyxw;
			Swizzle< SCALAR, 4, 0, 1, 1, 0 > xyyx;
			Swizzle< SCALAR, 4, 0, 1, 1, 1 > xyyy;
			Swizzle< SCALAR, 4, 0, 1, 1, 2 > xyyz;
			Swizzle< SCALAR, 4, 0, 1, 1, 3 > xyyw;
			Swizzle< SCALAR, 4, 0, 1, 2, 0 > xyzx;
			Swizzle< SCALAR, 4, 0, 1, 2, 1 > xyzy;
			Swizzle< SCALAR, 4, 0, 1, 2, 2 > xyzz;
			Swizzle< SCALAR, 4, 0, 1, 2, 3 > xyzw;
			Swizzle< SCALAR, 4, 0, 1, 3, 0 > xywx;
			Swizzle< SCALAR, 4, 0, 1, 3, 1 > xywy;
			Swizzle< SCALAR, 4, 0, 1, 3, 2 > xywz;
			Swizzle< SCALAR, 4, 0, 1, 3, 3 > xyww;
			Swizzle< SCALAR, 4, 0, 2, 0, 0 > xzxx;
			Swizzle< SCALAR, 4, 0, 2, 0, 1 > xzxy;
			Swizzle< SCALAR, 4, 0, 2, 0, 2 > xzxz;
			Swizzle< SCALAR, 4, 0, 2, 0, 3 > xzxw;
			Swizzle< SCALAR, 4, 0, 2, 1, 0 > xzyx;
			Swizzle< SCALAR, 4, 0, 2, 1, 1 > xzyy;
			Swizzle< SCALAR, 4, 0, 2, 1, 2 > xzyz;
			Swizzle< SCALAR, 4, 0, 2, 1, 3 > xzyw;
			Swizzle< SCALAR, 4, 0, 2, 2, 0 > xzzx;
			Swizzle< SCALAR, 4, 0, 2, 2, 1 > xzzy;
			Swizzle< SCALAR, 4, 0, 2, 2, 2 > xzzz;
			Swizzle< SCALAR, 4, 0, 2, 2, 3 > xzzw;
			Swizzle< SCALAR, 4, 0, 2, 3, 0 > xzwx;
			Swizzle< SCALAR, 4, 0, 2, 3, 1 > xzwy;
			Swizzle< SCALAR, 4, 0, 2, 3, 2 > xzwz;
			Swizzle< SCALAR, 4, 0, 2, 3, 3 > xzww;
			Swizzle< SCALAR, 4, 0, 3, 0, 0 > xwxx;
			Swizzle< SCALAR, 4, 0, 3, 0, 1 > xwxy;
			Swizzle< SCALAR, 4, 0, 3, 0, 2 > xwxz;
			Swizzle< SCALAR, 4, 0, 3, 0, 3 > xwxw;
			Swizzle< SCALAR, 4, 0, 3, 1, 0 > xwyx;
			Swizzle< SCALAR, 4, 0, 3, 1, 1 > xwyy;
			Swizzle< SCALAR, 4, 0, 3, 1, 2 > xwyz;
			Swizzle< SCALAR, 4, 0, 3, 1, 3 > xwyw;
			Swizzle< SCALAR, 4, 0, 3, 2, 0 > xwzx;
			Swizzle< SCALAR, 4, 0, 3, 2, 1 > xwzy;
			Swizzle< SCALAR, 4, 0, 3, 2, 2 > xwzz;
			Swizzle< SCALAR, 4, 0, 3, 2, 3 > xwzw;
			Swizzle< SCALAR, 4, 0, 3, 3, 0 > xwwx;
			Swizzle< SCALAR, 4, 0, 3, 3, 1 > xwwy;
			Swizzle< SCALAR, 4, 0, 3, 3, 2 > xwwz;
			Swizzle< SCALAR, 4, 0, 3, 3, 3 > xwww;
			Swizzle< SCALAR, 4, 1, 0, 0, 0 > yxxx;
			Swizzle< SCALAR, 4, 1, 0, 0, 1 > yxxy;
			Swizzle< SCALAR, 4, 1, 0, 0, 2 > yxxz;
			Swizzle< SCALAR, 4, 1, 0, 0, 3 > yxxw;
			Swizzle< SCALAR, 4, 1, 0, 1, 0 > yxyx;
			Swizzle< SCALAR, 4, 1, 0, 1, 1 > yxyy;
			Swizzle< SCALAR, 4, 1, 0, 1, 2 > yxyz;
			Swizzle< SCALAR, 4, 1, 0, 1, 3 > yxyw;
			Swizzle< SCALAR, 4, 1, 0, 2, 0 > yxzx;
			Swizzle< SCALAR, 4, 1, 0, 2, 1 > yxzy;
			Swizzle< SCALAR, 4, 1, 0, 2, 2 > yxzz;
			Swizzle< SCALAR, 4, 1, 0, 2, 3 > yxzw;
			Swizzle< SCALAR, 4, 1, 0, 3, 0 > yxwx;
			Swizzle< SCALAR, 4, 1, 0, 3, 1 > yxwy;
			Swizzle< SCALAR, 4, 1, 0, 3, 2 > yxwz;
			Swizzle< SCALAR, 4, 1, 0, 3, 3 > yxww;
			Swizzle< SCALAR, 4, 1, 1, 0, 0 > yyxx;
			Swizzle< SCALAR, 4, 1, 1, 0, 1 > yyxy;
			Swizzle< SCALAR, 4, 1, 1, 0, 2 > yyxz;
			Swizzle< SCALAR, 4, 1, 1, 0, 3 > yyxw;
			Swizzle< SCALAR, 4, 1, 1, 1, 0 > yyyx;
			Swizzle< SCALAR, 4, 1, 1, 1, 1 > yyyy;
			Swizzle< SCALAR, 4, 1, 1, 1, 2 > yyyz;
			Swizzle< SCALAR, 4, 1, 1, 1, 3 > yyyw;
			Swizzle< SCALAR, 4, 1, 1, 2, 0 > yyzx;
			Swizzle< SCALAR, 4, 1, 1, 2, 1 > yyzy;
			Swizzle< SCALAR, 4, 1, 1, 2, 2 > yyzz;
			Swizzle< SCALAR, 4, 1, 1, 2, 3 > yyzw;
			Swizzle< SCALAR, 4, 1, 1, 3, 0 > yywx;
			Swizzle< SCALAR, 4, 1, 1, 3, 1 > yywy;
			Swizzle< SCALAR, 4, 1, 1, 3, 2 > yywz;
			Swizzle< SCALAR, 4, 1, 1, 3, 3 > yyww;
			Swizzle< SCALAR, 4, 1, 2, 0, 0 > yzxx;
			Swizzle< SCALAR, 4, 1, 2, 0, 1 > yzxy;
			Swizzle< SCALAR, 4, 1, 2, 0, 2 > yzxz;
			Swizzle< SCALAR, 4, 1, 2, 0, 3 > yzxw;
			Swizzle< SCALAR, 4, 1, 2, 1, 0 > yzyx;
			Swizzle< SCALAR, 4, 1, 2, 1, 1 > yzyy;
			Swizzle< SCALAR, 4, 1, 2, 1, 2 > yzyz;
			Swizzle< SCALAR, 4, 1, 2, 1, 3 > yzyw;
			Swizzle< SCALAR, 4, 1, 2, 2, 0 > yzzx;
			Swizzle< SCALAR, 4, 1, 2, 2, 1 > yzzy;
			Swizzle< SCALAR, 4, 1, 2, 2, 2 > yzzz;
			Swizzle< SCALAR, 4, 1, 2, 2, 3 > yzzw;
			Swizzle< SCALAR, 4, 1, 2, 3, 0 > yzwx;
			Swizzle< SCALAR, 4, 1, 2, 3, 1 > yzwy;
			Swizzle< SCALAR, 4, 1, 2, 3, 2 > yzwz;
			Swizzle< SCALAR, 4, 1, 2, 3, 3 > yzww;
			Swizzle< SCALAR, 4, 1, 3, 0, 0 > ywxx;
			Swizzle< SCALAR, 4, 1, 3, 0, 1 > ywxy;
			Swizzle< SCALAR, 4, 1, 3, 0, 2 > ywxz;
			Swizzle< SCALAR, 4, 1, 3, 0, 3 > ywxw;
			Swizzle< SCALAR, 4, 1, 3, 1, 0 > ywyx;
			Swizzle< SCALAR, 4, 1, 3, 1, 1 > ywyy;
			Swizzle< SCALAR, 4, 1, 3, 1, 2 > ywyz;
			Swizzle< SCALAR, 4, 1, 3, 1, 3 > ywyw;
			Swizzle< SCALAR, 4, 1, 3, 2, 0 > ywzx;
			Swizzle< SCALAR, 4, 1, 3, 2, 1 > ywzy;
			Swizzle< SCALAR, 4, 1, 3, 2, 2 > ywzz;
			Swizzle< SCALAR, 4, 1, 3, 2, 3 > ywzw;
			Swizzle< SCALAR, 4, 1, 3, 3, 0 > ywwx;
			Swizzle< SCALAR, 4, 1, 3, 3, 1 > ywwy;
			Swizzle< SCALAR, 4, 1, 3, 3, 2 > ywwz;
			Swizzle< SCALAR, 4, 1, 3, 3, 3 > ywww;
			Swizzle< SCALAR, 4, 2, 0, 0, 0 > zxxx;
			Swizzle< SCALAR, 4, 2, 0, 0, 1 > zxxy;
			Swizzle< SCALAR, 4, 2, 0, 0, 2 > zxxz;
			Swizzle< SCALAR, 4, 2, 0, 0, 3 > zxxw;
			Swizzle< SCALAR, 4, 2, 0, 1, 0 > zxyx;
			Swizzle< SCALAR, 4, 2, 0, 1, 1 > zxyy;
			Swizzle< SCALAR, 4, 2, 0, 1, 2 > zxyz;
			Swizzle< SCALAR, 4, 2, 0, 1, 3 > zxyw;
			Swizzle< SCALAR, 4, 2, 0, 2, 0 > zxzx;
			Swizzle< SCALAR, 4, 2, 0, 2, 1 > zxzy;
			Swizzle< SCALAR, 4, 2, 0, 2, 2 > zxzz;
			Swizzle< SCALAR, 4, 2, 0, 2, 3 > zxzw;
			Swizzle< SCALAR, 4, 2, 0, 3, 0 > zxwx;
			Swizzle< SCALAR, 4, 2, 0, 3, 1 > zxwy;
			Swizzle< SCALAR, 4, 2, 0, 3, 2 > zxwz;
			Swizzle< SCALAR, 4, 2, 0, 3, 3 > zxww;
			Swizzle< SCALAR, 4, 2, 1, 0, 0 > zyxx;
			Swizzle< SCALAR, 4, 2, 1, 0, 1 > zyxy;
			Swizzle< SCALAR, 4, 2, 1, 0, 2 > zyxz;
			Swizzle< SCALAR, 4, 2, 1, 0, 3 > zyxw;
			Swizzle< SCALAR, 4, 2, 1, 1, 0 > zyyx;
			Swizzle< SCALAR, 4, 2, 1, 1, 1 > zyyy;
			Swizzle< SCALAR, 4, 2, 1, 1, 2 > zyyz;
			Swizzle< SCALAR, 4, 2, 1, 1, 3 > zyyw;
			Swizzle< SCALAR, 4, 2, 1, 2, 0 > zyzx;
			Swizzle< SCALAR, 4, 2, 1, 2, 1 > zyzy;
			Swizzle< SCALAR, 4, 2, 1, 2, 2 > zyzz;
			Swizzle< SCALAR, 4, 2, 1, 2, 3 > zyzw;
			Swizzle< SCALAR, 4, 2, 1, 3, 0 > zywx;
			Swizzle< SCALAR, 4, 2, 1, 3, 1 > zywy;
			Swizzle< SCALAR, 4, 2, 1, 3, 2 > zywz;
			Swizzle< SCALAR, 4, 2, 1, 3, 3 > zyww;
			Swizzle< SCALAR, 4, 2, 2, 0, 0 > zzxx;
			Swizzle< SCALAR, 4, 2, 2, 0, 1 > zzxy;
			Swizzle< SCALAR, 4, 2, 2, 0, 2 > zzxz;
			Swizzle< SCALAR, 4, 2, 2, 0, 3 > zzxw;
			Swizzle< SCALAR, 4, 2, 2, 1, 0 > zzyx;
			Swizzle< SCALAR, 4, 2, 2, 1, 1 > zzyy;
			Swizzle< SCALAR, 4, 2, 2, 1, 2 > zzyz;
			Swizzle< SCALAR, 4, 2, 2, 1, 3 > zzyw;
			Swizzle< SCALAR, 4, 2, 2, 2, 0 > zzzx;
			Swizzle< SCALAR, 4, 2, 2, 2, 1 > zzzy;
			Swizzle< SCALAR, 4, 2, 2, 2, 2 > zzzz;
			Swizzle< SCALAR, 4, 2, 2, 2, 3 > zzzw;
			Swizzle< SCALAR, 4, 2, 2, 3, 0 > zzwx;
			Swizzle< SCALAR, 4, 2, 2, 3, 1 > zzwy;
			Swizzle< SCALAR, 4, 2, 2, 3, 2 > zzwz;
			Swizzle< SCALAR, 4, 2, 2, 3, 3 > zzww;
			Swizzle< SCALAR, 4, 2, 3, 0, 0 > zwxx;
			Swizzle< SCALAR, 4, 2, 3, 0, 1 > zwxy;
			Swizzle< SCALAR, 4, 2, 3, 0, 2 > zwxz;
			Swizzle< SCALAR, 4, 2, 3, 0, 3 > zwxw;
			Swizzle< SCALAR, 4, 2, 3, 1, 0 > zwyx;
			Swizzle< SCALAR, 4, 2, 3, 1, 1 > zwyy;
			Swizzle< SCALAR, 4, 2, 3, 1, 2 > zwyz;
			Swizzle< SCALAR, 4, 2, 3, 1, 3 > zwyw;
			Swizzle< SCALAR, 4, 2, 3, 2, 0 > zwzx;
			Swizzle< SCALAR, 4, 2, 3, 2, 1 > zwzy;
			Swizzle< SCALAR, 4, 2, 3, 2, 2 > zwzz;
			Swizzle< SCALAR, 4, 2, 3, 2, 3 > zwzw;
			Swizzle< SCALAR, 4, 2, 3, 3, 0 > zwwx;
			Swizzle< SCALAR, 4, 2, 3, 3, 1 > zwwy;
			Swizzle< SCALAR, 4, 2, 3, 3, 2 > zwwz;
			Swizzle< SCALAR, 4, 2, 3, 3, 3 > zwww;
			Swizzle< SCALAR, 4, 3, 0, 0, 0 > wxxx;
			Swizzle< SCALAR, 4, 3, 0, 0, 1 > wxxy;
			Swizzle< SCALAR, 4, 3, 0, 0, 2 > wxxz;
			Swizzle< SCALAR, 4, 3, 0, 0, 3 > wxxw;
			Swizzle< SCALAR, 4, 3, 0, 1, 0 > wxyx;
			Swizzle< SCALAR, 4, 3, 0, 1, 1 > wxyy;
			Swizzle< SCALAR, 4, 3, 0, 1, 2 > wxyz;
			Swizzle< SCALAR, 4, 3, 0, 1, 3 > wxyw;
			Swizzle< SCALAR, 4, 3, 0, 2, 0 > wxzx;
			Swizzle< SCALAR, 4, 3, 0, 2, 1 > wxzy;
			Swizzle< SCALAR, 4, 3, 0, 2, 2 > wxzz;
			Swizzle< SCALAR, 4, 3, 0, 2, 3 > wxzw;
			Swizzle< SCALAR, 4, 3, 0, 3, 0 > wxwx;
			Swizzle< SCALAR, 4, 3, 0, 3, 1 > wxwy;
			Swizzle< SCALAR, 4, 3, 0, 3, 2 > wxwz;
			Swizzle< SCALAR, 4, 3, 0, 3, 3 > wxww;
			Swizzle< SCALAR, 4, 3, 1, 0, 0 > wyxx;
			Swizzle< SCALAR, 4, 3, 1, 0, 1 > wyxy;
			Swizzle< SCALAR, 4, 3, 1, 0, 2 > wyxz;
			Swizzle< SCALAR, 4, 3, 1, 0, 3 > wyxw;
			Swizzle< SCALAR, 4, 3, 1, 1, 0 > wyyx;
			Swizzle< SCALAR, 4, 3, 1, 1, 1 > wyyy;
			Swizzle< SCALAR, 4, 3, 1, 1, 2 > wyyz;
			Swizzle< SCALAR, 4, 3, 1, 1, 3 > wyyw;
			Swizzle< SCALAR, 4, 3, 1, 2, 0 > wyzx;
			Swizzle< SCALAR, 4, 3, 1, 2, 1 > wyzy;
			Swizzle< SCALAR, 4, 3, 1, 2, 2 > wyzz;
			Swizzle< SCALAR, 4, 3, 1, 2, 3 > wyzw;
			Swizzle< SCALAR, 4, 3, 1, 3, 0 > wywx;
			Swizzle< SCALAR, 4, 3, 1, 3, 1 > wywy;
			Swizzle< SCALAR, 4, 3, 1, 3, 2 > wywz;
			Swizzle< SCALAR, 4, 3, 1, 3, 3 > wyww;
			Swizzle< SCALAR, 4, 3, 2, 0, 0 > wzxx;
			Swizzle< SCALAR, 4, 3, 2, 0, 1 > wzxy;
			Swizzle< SCALAR, 4, 3, 2, 0, 2 > wzxz;
			Swizzle< SCALAR, 4, 3, 2, 0, 3 > wzxw;
			Swizzle< SCALAR, 4, 3, 2, 1, 0 > wzyx;
			Swizzle< SCALAR, 4, 3, 2, 1, 1 > wzyy;
			Swizzle< SCALAR, 4, 3, 2, 1, 2 > wzyz;
			Swizzle< SCALAR, 4, 3, 2, 1, 3 > wzyw;
			Swizzle< SCALAR, 4, 3, 2, 2, 0 > wzzx;
			Swizzle< SCALAR, 4, 3, 2, 2, 1 > wzzy;
			Swizzle< SCALAR, 4, 3, 2, 2, 2 > wzzz;
			Swizzle< SCALAR, 4, 3, 2, 2, 3 > wzzw;
			Swizzle< SCALAR, 4, 3, 2, 3, 0 > wzwx;
			Swizzle< SCALAR, 4, 3, 2, 3, 1 > wzwy;
			Swizzle< SCALAR, 4, 3, 2, 3, 2 > wzwz;
			Swizzle< SCALAR, 4, 3, 2, 3, 3 > wzww;
			Swizzle< SCALAR, 4, 3, 3, 0, 0 > wwxx;
			Swizzle< SCALAR, 4, 3, 3, 0, 1 > wwxy;
			Swizzle< SCALAR, 4, 3, 3, 0, 2 > wwxz;
			Swizzle< SCALAR, 4, 3, 3, 0, 3 > wwxw;
			Swizzle< SCALAR, 4, 3, 3, 1, 0 > wwyx;
			Swizzle< SCALAR, 4, 3, 3, 1, 1 > wwyy;
			Swizzle< SCALAR, 4, 3, 3, 1, 2 > wwyz;
			Swizzle< SCALAR, 4, 3, 3, 1, 3 > wwyw;
			Swizzle< SCALAR, 4, 3, 3, 2, 0 > wwzx;
			Swizzle< SCALAR, 4, 3, 3, 2, 1 > wwzy;
			Swizzle< SCALAR, 4, 3, 3, 2, 2 > wwzz;
			Swizzle< SCALAR, 4, 3, 3, 2, 3 > wwzw;
			Swizzle< SCALAR, 4, 3, 3, 3, 0 > wwwx;
			Swizzle< SCALAR, 4, 3, 3, 3, 1 > wwwy;
			Swizzle< SCALAR, 4, 3, 3, 3, 2 > wwwz;
			Swizzle< SCALAR, 4, 3, 3, 3, 3 > wwww;
		};

		QuaternionBase()
		{
			ZeroMemory(_quaternion, sizeof(SCALAR) * 4);
		}

		QuaternionBase(SCALAR x, SCALAR y, SCALAR z, SCALAR w) :
			x(x), y(y), z(z), w(w)
		{
		}

		virtual ~QuaternionBase() = default;

	};

	template<typename SCALAR, size_t M, size_t N>
	class Matrix
	{
	public:
		union
		{
			SCALAR matrix[M][N];
			SCALAR _data[M * N];
		};


		Matrix()
		{
			ZeroMemory(_data, sizeof(SCALAR) * M * N);
		}

		template<typename ...ARGS> requires (sizeof...(ARGS) == M * N && std::conjunction<std::is_convertible<ARGS, T>...>::value)
		Matrix(ARGS ...args) :
			_data{ args... }
		{

		}
	};
}

namespace ExtraX::Mathematic
{
	class Math;
}



#endif // !EXTRAX_MATHEMATIC_BASE_H
