#pragma once
#ifndef EXTRAX_VECTOR_BASE_H
#define EXTRAX_VECTOR_BASE_H


#include <ExtraX/Common.h>
#include <ExtraX/Mathematics/Swizzle.h>

namespace ExtraX::Mathematics::Base
{
	template<MATHEMATICS_LIB>
	class Math;

	template<typename SCALAR, int Size, typename VECTOR_TYPE = SCALAR[Size]>
	class VectorBase
	{
	protected:
		VECTOR_TYPE _vector;

		VectorBase() :
			_vector()
		{
		}

		template<typename ...ARGS> requires (sizeof...(ARGS) == Size && std::conjunction<std::is_convertible<ARGS, SCALAR>...>::value)
			VectorBase(ARGS ...args) :
			_vector{ args... }
		{
		}
	};

	template<typename SCALAR, typename VECTOR_TYPE> requires (sizeof(SCALAR) * 2 == sizeof(VECTOR_TYPE))
	class V2
	{
	protected:
		union
		{
			VECTOR_TYPE _vector;
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

		V2() :
			_vector()
		{
		}

		V2(SCALAR x, SCALAR y) :
			_vector(x, y)
		{
		}
	};

	template<typename SCALAR, typename VECTOR_TYPE> requires (sizeof(SCALAR) * 3 == sizeof(VECTOR_TYPE))
	class V3
	{
	protected:
		union
		{
			VECTOR_TYPE _vector;
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

		V3() :
			_vector()
		{
		}

		V3(SCALAR x, SCALAR y, SCALAR z) :
			_vector(x, y, z)
		{
		}
	};

	template<typename SCALAR, typename VECTOR_TYPE> requires (sizeof(SCALAR) * 4 == sizeof(VECTOR_TYPE))
	class V4
	{
	protected:
		union
		{
			VECTOR_TYPE _vector;
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

		V4() :
			_vector()
		{
		}

		V4(SCALAR x, SCALAR y, SCALAR z, SCALAR w) :
			_vector(x, y, z, w)
		{
		}

	};

	template<typename SCALAR, typename VECTOR_TYPE>
	class VectorBase<SCALAR, 2, VECTOR_TYPE> : public V2<SCALAR, VECTOR_TYPE>
	{
	private:
		using BaseType = V2<SCALAR, VECTOR_TYPE>;
	protected:
		using BaseType::_vector;
	public:
		using BaseType::x;
		using BaseType::y;
		using BaseType::xx;
		using BaseType::xy;
		using BaseType::yx;
		using BaseType::yy;
		using BaseType::xxx;
		using BaseType::xxy;
		using BaseType::xyx;
		using BaseType::xyy;
		using BaseType::yxx;
		using BaseType::yxy;
		using BaseType::yyx;
		using BaseType::yyy;
		using BaseType::xxxx;
		using BaseType::xxxy;
		using BaseType::xxyx;
		using BaseType::xxyy;
		using BaseType::xyxx;
		using BaseType::xyxy;
		using BaseType::xyyx;
		using BaseType::xyyy;
		using BaseType::yxxx;
		using BaseType::yxxy;
		using BaseType::yxyx;
		using BaseType::yxyy;
		using BaseType::yyxx;
		using BaseType::yyxy;
		using BaseType::yyyx;
		using BaseType::yyyy;

	protected:
		VectorBase() :
			BaseType()
		{
		}

		VectorBase(SCALAR x, SCALAR y) :
			BaseType(x, y)
		{
		}
	};

	template<typename SCALAR, typename VECTOR_TYPE>
	class VectorBase<SCALAR, 3, VECTOR_TYPE> : public V3<SCALAR, VECTOR_TYPE>
	{
	private:
		using BaseType = V3<SCALAR, VECTOR_TYPE>;
	protected:
		using BaseType::_vector;
	public:
	
		using BaseType::x;
		using BaseType::y;
		using BaseType::z;
		
		using BaseType::xx;
		using BaseType::xy;
		using BaseType::xz;
		using BaseType::yx;
		using BaseType::yy;
		using BaseType::yz;
		using BaseType::zx;
		using BaseType::zy;
		using BaseType::zz;

		using BaseType::xxx;
		using BaseType::xxy;
		using BaseType::xxz;
		using BaseType::xyx;
		using BaseType::xyy;
		using BaseType::xyz;
		using BaseType::xzx;
		using BaseType::xzy;
		using BaseType::xzz;
		using BaseType::yxx;
		using BaseType::yxy;
		using BaseType::yxz;
		using BaseType::yyx;
		using BaseType::yyy;
		using BaseType::yyz;
		using BaseType::yzx;
		using BaseType::yzy;
		using BaseType::yzz;
		using BaseType::zxx;
		using BaseType::zxy;
		using BaseType::zxz;
		using BaseType::zyx;
		using BaseType::zyy;
		using BaseType::zyz;
		using BaseType::zzx;
		using BaseType::zzy;
		using BaseType::zzz;

		using BaseType::xxxx;
		using BaseType::xxxy;
		using BaseType::xxxz;
		using BaseType::xxyx;
		using BaseType::xxyy;
		using BaseType::xxyz;
		using BaseType::xxzx;
		using BaseType::xxzy;
		using BaseType::xxzz;
		using BaseType::xyxx;
		using BaseType::xyxy;
		using BaseType::xyxz;
		using BaseType::xyyx;
		using BaseType::xyyy;
		using BaseType::xyyz;
		using BaseType::xyzx;
		using BaseType::xyzy;
		using BaseType::xyzz;
		using BaseType::xzxx;
		using BaseType::xzxy;
		using BaseType::xzxz;
		using BaseType::xzyx;
		using BaseType::xzyy;
		using BaseType::xzyz;
		using BaseType::xzzx;
		using BaseType::xzzy;
		using BaseType::xzzz;
		using BaseType::yxxx;
		using BaseType::yxxy;
		using BaseType::yxxz;
		using BaseType::yxyx;
		using BaseType::yxyy;
		using BaseType::yxyz;
		using BaseType::yxzx;
		using BaseType::yxzy;
		using BaseType::yxzz;
		using BaseType::yyxx;
		using BaseType::yyxy;
		using BaseType::yyxz;
		using BaseType::yyyx;
		using BaseType::yyyy;
		using BaseType::yyyz;
		using BaseType::yyzx;
		using BaseType::yyzy;
		using BaseType::yyzz;
		using BaseType::yzxx;
		using BaseType::yzxy;
		using BaseType::yzxz;
		using BaseType::yzyx;
		using BaseType::yzyy;
		using BaseType::yzyz;
		using BaseType::yzzx;
		using BaseType::yzzy;
		using BaseType::yzzz;
		using BaseType::zxxx;
		using BaseType::zxxy;
		using BaseType::zxxz;
		using BaseType::zxyx;
		using BaseType::zxyy;
		using BaseType::zxyz;
		using BaseType::zxzx;
		using BaseType::zxzy;
		using BaseType::zxzz;
		using BaseType::zyxx;
		using BaseType::zyxy;
		using BaseType::zyxz;
		using BaseType::zyyx;
		using BaseType::zyyy;
		using BaseType::zyyz;
		using BaseType::zyzx;
		using BaseType::zyzy;
		using BaseType::zyzz;
		using BaseType::zzxx;
		using BaseType::zzxy;
		using BaseType::zzxz;
		using BaseType::zzyx;
		using BaseType::zzyy;
		using BaseType::zzyz;
		using BaseType::zzzx;
		using BaseType::zzzy;
		using BaseType::zzzz;

	protected:
		VectorBase() :
			BaseType()
		{
		}

		VectorBase(SCALAR x, SCALAR y, SCALAR z) :
			BaseType(x, y, z)
		{
		}
	};

	template<typename SCALAR, typename VECTOR_TYPE>
	class VectorBase<SCALAR, 4, VECTOR_TYPE> : public V4<SCALAR, VECTOR_TYPE>
	{
	private:
		using BaseType = V4<SCALAR, VECTOR_TYPE>;

	protected:
		using BaseType::_vector;

	public:
		using BaseType::x;
		using BaseType::y;
		using BaseType::z;
		using BaseType::w;
		
		using BaseType::xx;
		using BaseType::xy;
		using BaseType::xz;
		using BaseType::xw;
		using BaseType::yx;
		using BaseType::yy;
		using BaseType::yz;
		using BaseType::yw;
		using BaseType::zx;
		using BaseType::zy;
		using BaseType::zz;
		using BaseType::zw;
		using BaseType::wx;
		using BaseType::wy;
		using BaseType::wz;
		using BaseType::ww;

		using BaseType::xxx;
		using BaseType::xxy;
		using BaseType::xxz;
		using BaseType::xxw;
		using BaseType::xyx;
		using BaseType::xyy;
		using BaseType::xyz;
		using BaseType::xyw;
		using BaseType::xzx;
		using BaseType::xzy;
		using BaseType::xzz;
		using BaseType::xzw;
		using BaseType::xwx;
		using BaseType::xwy;
		using BaseType::xwz;
		using BaseType::xww;
		using BaseType::yxx;
		using BaseType::yxy;
		using BaseType::yxz;
		using BaseType::yxw;
		using BaseType::yyx;
		using BaseType::yyy;
		using BaseType::yyz;
		using BaseType::yyw;
		using BaseType::yzx;
		using BaseType::yzy;
		using BaseType::yzz;
		using BaseType::yzw;
		using BaseType::ywx;
		using BaseType::ywy;
		using BaseType::ywz;
		using BaseType::yww;
		using BaseType::zxx;
		using BaseType::zxy;
		using BaseType::zxz;
		using BaseType::zxw;
		using BaseType::zyx;
		using BaseType::zyy;
		using BaseType::zyz;
		using BaseType::zyw;
		using BaseType::zzx;
		using BaseType::zzy;
		using BaseType::zzz;
		using BaseType::zzw;
		using BaseType::zwx;
		using BaseType::zwy;
		using BaseType::zwz;
		using BaseType::zww;
		using BaseType::wxx;
		using BaseType::wxy;
		using BaseType::wxz;
		using BaseType::wxw;
		using BaseType::wyx;
		using BaseType::wyy;
		using BaseType::wyz;
		using BaseType::wyw;
		using BaseType::wzx;
		using BaseType::wzy;
		using BaseType::wzz;
		using BaseType::wzw;
		using BaseType::wwx;
		using BaseType::wwy;
		using BaseType::wwz;
		using BaseType::www;

		using BaseType::xxxx;
		using BaseType::xxxy;
		using BaseType::xxxz;
		using BaseType::xxxw;
		using BaseType::xxyx;
		using BaseType::xxyy;
		using BaseType::xxyz;
		using BaseType::xxyw;
		using BaseType::xxzx;
		using BaseType::xxzy;
		using BaseType::xxzz;
		using BaseType::xxzw;
		using BaseType::xxwx;
		using BaseType::xxwy;
		using BaseType::xxwz;
		using BaseType::xxww;
		using BaseType::xyxx;
		using BaseType::xyxy;
		using BaseType::xyxz;
		using BaseType::xyxw;
		using BaseType::xyyx;
		using BaseType::xyyy;
		using BaseType::xyyz;
		using BaseType::xyyw;
		using BaseType::xyzx;
		using BaseType::xyzy;
		using BaseType::xyzz;
		using BaseType::xyzw;
		using BaseType::xywx;
		using BaseType::xywy;
		using BaseType::xywz;
		using BaseType::xyww;
		using BaseType::xzxx;
		using BaseType::xzxy;
		using BaseType::xzxz;
		using BaseType::xzxw;
		using BaseType::xzyx;
		using BaseType::xzyy;
		using BaseType::xzyz;
		using BaseType::xzyw;
		using BaseType::xzzx;
		using BaseType::xzzy;
		using BaseType::xzzz;
		using BaseType::xzzw;
		using BaseType::xzwx;
		using BaseType::xzwy;
		using BaseType::xzwz;
		using BaseType::xzww;
		using BaseType::xwxx;
		using BaseType::xwxy;
		using BaseType::xwxz;
		using BaseType::xwxw;
		using BaseType::xwyx;
		using BaseType::xwyy;
		using BaseType::xwyz;
		using BaseType::xwyw;
		using BaseType::xwzx;
		using BaseType::xwzy;
		using BaseType::xwzz;
		using BaseType::xwzw;
		using BaseType::xwwx;
		using BaseType::xwwy;
		using BaseType::xwwz;
		using BaseType::xwww;
		using BaseType::yxxx;
		using BaseType::yxxy;
		using BaseType::yxxz;
		using BaseType::yxxw;
		using BaseType::yxyx;
		using BaseType::yxyy;
		using BaseType::yxyz;
		using BaseType::yxyw;
		using BaseType::yxzx;
		using BaseType::yxzy;
		using BaseType::yxzz;
		using BaseType::yxzw;
		using BaseType::yxwx;
		using BaseType::yxwy;
		using BaseType::yxwz;
		using BaseType::yxww;
		using BaseType::yyxx;
		using BaseType::yyxy;
		using BaseType::yyxz;
		using BaseType::yyxw;
		using BaseType::yyyx;
		using BaseType::yyyy;
		using BaseType::yyyz;
		using BaseType::yyyw;
		using BaseType::yyzx;
		using BaseType::yyzy;
		using BaseType::yyzz;
		using BaseType::yyzw;
		using BaseType::yywx;
		using BaseType::yywy;
		using BaseType::yywz;
		using BaseType::yyww;
		using BaseType::yzxx;
		using BaseType::yzxy;
		using BaseType::yzxz;
		using BaseType::yzxw;
		using BaseType::yzyx;
		using BaseType::yzyy;
		using BaseType::yzyz;
		using BaseType::yzyw;
		using BaseType::yzzx;
		using BaseType::yzzy;
		using BaseType::yzzz;
		using BaseType::yzzw;
		using BaseType::yzwx;
		using BaseType::yzwy;
		using BaseType::yzwz;
		using BaseType::yzww;
		using BaseType::ywxx;
		using BaseType::ywxy;
		using BaseType::ywxz;
		using BaseType::ywxw;
		using BaseType::ywyx;
		using BaseType::ywyy;
		using BaseType::ywyz;
		using BaseType::ywyw;
		using BaseType::ywzx;
		using BaseType::ywzy;
		using BaseType::ywzz;
		using BaseType::ywzw;
		using BaseType::ywwx;
		using BaseType::ywwy;
		using BaseType::ywwz;
		using BaseType::ywww;
		using BaseType::zxxx;
		using BaseType::zxxy;
		using BaseType::zxxz;
		using BaseType::zxxw;
		using BaseType::zxyx;
		using BaseType::zxyy;
		using BaseType::zxyz;
		using BaseType::zxyw;
		using BaseType::zxzx;
		using BaseType::zxzy;
		using BaseType::zxzz;
		using BaseType::zxzw;
		using BaseType::zxwx;
		using BaseType::zxwy;
		using BaseType::zxwz;
		using BaseType::zxww;
		using BaseType::zyxx;
		using BaseType::zyxy;
		using BaseType::zyxz;
		using BaseType::zyxw;
		using BaseType::zyyx;
		using BaseType::zyyy;
		using BaseType::zyyz;
		using BaseType::zyyw;
		using BaseType::zyzx;
		using BaseType::zyzy;
		using BaseType::zyzz;
		using BaseType::zyzw;
		using BaseType::zywx;
		using BaseType::zywy;
		using BaseType::zywz;
		using BaseType::zyww;
		using BaseType::zzxx;
		using BaseType::zzxy;
		using BaseType::zzxz;
		using BaseType::zzxw;
		using BaseType::zzyx;
		using BaseType::zzyy;
		using BaseType::zzyz;
		using BaseType::zzyw;
		using BaseType::zzzx;
		using BaseType::zzzy;
		using BaseType::zzzz;
		using BaseType::zzzw;
		using BaseType::zzwx;
		using BaseType::zzwy;
		using BaseType::zzwz;
		using BaseType::zzww;
		using BaseType::zwxx;
		using BaseType::zwxy;
		using BaseType::zwxz;
		using BaseType::zwxw;
		using BaseType::zwyx;
		using BaseType::zwyy;
		using BaseType::zwyz;
		using BaseType::zwyw;
		using BaseType::zwzx;
		using BaseType::zwzy;
		using BaseType::zwzz;
		using BaseType::zwzw;
		using BaseType::zwwx;
		using BaseType::zwwy;
		using BaseType::zwwz;
		using BaseType::zwww;
		using BaseType::wxxx;
		using BaseType::wxxy;
		using BaseType::wxxz;
		using BaseType::wxxw;
		using BaseType::wxyx;
		using BaseType::wxyy;
		using BaseType::wxyz;
		using BaseType::wxyw;
		using BaseType::wxzx;
		using BaseType::wxzy;
		using BaseType::wxzz;
		using BaseType::wxzw;
		using BaseType::wxwx;
		using BaseType::wxwy;
		using BaseType::wxwz;
		using BaseType::wxww;
		using BaseType::wyxx;
		using BaseType::wyxy;
		using BaseType::wyxz;
		using BaseType::wyxw;
		using BaseType::wyyx;
		using BaseType::wyyy;
		using BaseType::wyyz;
		using BaseType::wyyw;
		using BaseType::wyzx;
		using BaseType::wyzy;
		using BaseType::wyzz;
		using BaseType::wyzw;
		using BaseType::wywx;
		using BaseType::wywy;
		using BaseType::wywz;
		using BaseType::wyww;
		using BaseType::wzxx;
		using BaseType::wzxy;
		using BaseType::wzxz;
		using BaseType::wzxw;
		using BaseType::wzyx;
		using BaseType::wzyy;
		using BaseType::wzyz;
		using BaseType::wzyw;
		using BaseType::wzzx;
		using BaseType::wzzy;
		using BaseType::wzzz;
		using BaseType::wzzw;
		using BaseType::wzwx;
		using BaseType::wzwy;
		using BaseType::wzwz;
		using BaseType::wzww;
		using BaseType::wwxx;
		using BaseType::wwxy;
		using BaseType::wwxz;
		using BaseType::wwxw;
		using BaseType::wwyx;
		using BaseType::wwyy;
		using BaseType::wwyz;
		using BaseType::wwyw;
		using BaseType::wwzx;
		using BaseType::wwzy;
		using BaseType::wwzz;
		using BaseType::wwzw;
		using BaseType::wwwx;
		using BaseType::wwwy;
		using BaseType::wwwz;
		using BaseType::wwww;

	protected:
		VectorBase() :
			BaseType()
		{
		}

		VectorBase(SCALAR x, SCALAR y, SCALAR z, SCALAR w) :
			BaseType(x, y, z, w)
		{
		}

	};

	template<MATHEMATICS_LIB, typename SCALAR, int Size>
	class Vector;
}


#endif // !EXTRAX_VECTOR_BASE_H

