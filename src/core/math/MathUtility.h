#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

class MathUtility
{
public:
	template <class A, class B>
	static A maximum(const A& a, const B& b);

	template <class A, class B>
	static A minimum(const A& a, const B& b);
};

template <class A, class B>
A MathUtility::maximum(const A& a, const B& b)
{
	if (a >= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

template <class A, class B>
A MathUtility::minimum(const A& a, const B& b)
{
	if (a <= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

#endif // MATH_UTILITY_H