#pragma once
#include <initializer_list>
#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>
#include <algorithm>

namespace Clone::Math
{
	static constexpr float PI = static_cast<float>(M_PI);
	static constexpr float PI_HALF = static_cast<float>(M_PI_2);
	static constexpr float EPSILON = FLT_EPSILON;
	static constexpr float DEG2RAD = static_cast<float>(M_PI) / 180.f;
	static constexpr float RAD2DEG = 180.f * static_cast<float>(M_1_PI);

	/// <summary>
	/// Return the absolute value of the input number
	/// </summary>
	/// <typeparam name="T">Numeric type</typeparam>
	/// <param name="number">Input number</param>
	template <typename T>
	static T Abs(T number) { return number < 0 ? -number : number; }
	template <typename T>
	static T Clamp(T start, T end, T number) { return number < start ? start : (number > end ? end : number); }
	template <typename T>
	static T Max(std::initializer_list<T> numbers) { return std::max(numbers); }
	template <typename T>
	static T Min(std::initializer_list<T> numbers) { return std::min(numbers); }
	template <typename T>
	static T Square(T number) { return number * number; }

	static float ACos(float number);
	static float ASin(float number);
	static float ATan(float number);
	static float ATan2(float y, float x);
	static float Ceil(float number);
	static float Floor(float number);
	static int FloorToInt(float number);
	static int CeilToInt(float number);
	static float Clamp01(float number) { return Clamp(0.0f, 1.0f, number); }
	static int ClosestPowerOfTwo(int number);
	static int NextPowerOfTwo(int number);
	static float Sin(float number);
	static float Cos(float number);
	static float Tan(float number);
	static float Exp(float number);
	static float Lerp(float start, float end, float time);
	static float LerpUnclamped(float start, float end, float time);
	static float InverseLerp(float start, float end, float number);
	static float Ln(float number, float base);
	static float Log(float number);
	static float Log10(float number);
	static float Max(float a, float b);	
	static float Min(float a, float b);
	static float MoveTowards(float current, float target, float maxDelta);
	static float Pow(float number, float power);
	static float Repeat(float t, float length);
	static float Round(float number);
	static int RoundToInt(float number);
	static int Sign(float number);
	static float SmoothStep(float start, float end, float number);
	static float Sqrt(float number);
	static bool FuzzyEquals(float a, float b);
}