#ifndef CORE_PROPERTY_H
#define CORE_PROPERTY_H

namespace XX
{

	template<class T, class P, void(P::*Set)(const T&), T(P::*Get)()>
	class Property
	{
	private:
		P* const _p;
	public:
		Property(P* const p): _p(p){}

		operator T() const
		{
			return (_p->*Get)();
		}

		T operator()() const
		{
			return (_p->*Get)();
		}

		auto operator=(const T& value) const
		{
			(_p->*Set)(value);
			return (_p->*Get)();
		}

		auto operator+=(const T& value) const
		{
			(_p->*Set)((_p->*Get)() + value);
			return (_p->*Get)();
		}

		auto operator-=(const T& value) const
		{
			(_p->*Set)((_p->*Get)() - value);
			return (_p->*Get)();
		}

		auto operator*=(const T& value) const
		{
			(_p->*Set)((_p->*Get)() * value);
			return (_p->*Get)();
		}

		auto operator/=(const T& value) const
		{
			(_p->*Set)((_p->*Get)() * value);
			return (_p->*Get)();
		}

		auto operator+(const T& value) const
		{
			return (_p->*Get)() + value;
		}

		auto operator-(const T& value) const
		{
			return (_p->*Get)() - value;
		}

		auto operator*(const T& value) const
		{
			return (_p->*Get)() * value;
		}

		auto operator/(const T& value) const
		{
			return (_p->*Get)() / value;
		}
	};
}






#endif // !PROPERTY_H

