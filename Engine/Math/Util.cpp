#include "Util.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

namespace Clone::Math
{
	float ACos(float number)
	{
		return acosf(number);
	}

	float ASin(float number)
	{
		return asinf(number);;
	}
	float ATan(float number)
	{
		return atanf(number);
	}
	float ATan2(float y, float x)
	{
		return atan2f(y, x);
	}
	float Ceil(float number)
	{
		return ceilf(number);
	}
	float Floor(float number)
	{
		return floorf(number);
	}
	int FloorToInt(float number)
	{
		return static_cast<int>(floorf(number));
	}
	int CeilToInt(float number)
	{
		return static_cast<int>(ceilf(number));
	}
	int ClosestPowerOfTwo(int number)
	{
		if (number < 0)
			throw std::out_of_range("Utility::ClosestPowerOfTwo => Negative numbers are not supported.");
		
		int ceil = number - 1;
		for (size_t i = 1; i < sizeof(ceil) * CHAR_BIT; i *= 2) 
		{
			ceil |= ceil >> i;
		}
		++ceil;
		int floor = ceil >> 1;
		if (abs(number - ceil) < abs(number - floor)) 
		{
			return ceil;
		}
		else 
		{
			return floor;
		}
	}
	int NextPowerOfTwo(int number)
	{
		if (number < 0)
			throw std::out_of_range("Util::NextPowerOfTwo => Negative numbers are not supported.");

		int ceil = number - 1;
		for (size_t i = 1; i < sizeof(ceil) * CHAR_BIT; i *= 2) 
		{
			ceil |= ceil >> i;
		}
		++ceil;
		return ceil;
	}
	float Sin(float number)
	{
		return sinf(number);
	}
	float Cos(float number)
	{
		return cosf(number);
	}
	float Tan(float number)
	{
		return tanf(number);
	}
	float Exp(float number)
	{
		return expf(number);
	}
	float Lerp(float start, float end, float time)
	{
		return 0.0f;
	}
	float LerpUnclamped(float start, float end, float time)
	{
		time = Clamp01(time);
		return start * (1 - time) + time * end;
	}
	float InverseLerp(float start, float end, float number)
	{
		return (number - start) / (end - start);
	}
	float Ln(float number)
	{
		return logf(number);
	}
	float Log(float number, float base)
	{
		return static_cast<float>(logf(number) / log(base));
	}
	float Log10(float number)
	{
		return log10f(number);
	}
	float Max(float a, float b)
	{
		return std::max(a, b);
	}
	float Min(float a, float b)
	{
		return std::min(a, b);
	}
	float MoveTowards(float current, float target, float maxDelta)
	{
		return std::min(current + maxDelta, target);
	}
	float Pow(float number, float power)
	{
		return powf(number, power);
	}
	float Repeat(float t, float length)
	{
		return t - floorf(t / length) * length;
	}
	float Round(float number)
	{
		return roundf(number);
	}
	int RoundToInt(float number)
	{
		return static_cast<int>(roundf(number));;
	}
	int Sign(float number)
	{
		return (number > 0) - (number < 0);
	}
	float SmoothStep(float start, float end, float number)
	{
		number = Clamp01((number - start) / (end - start));
		return Square(number) * (3 - 2 * number);
	}
	float Sqrt(float number)
	{
		return sqrtf(number);
	}
	bool FuzzyEquals(float a, float b)
	{
		return Abs(a - b) < EPSILON;
	}
}