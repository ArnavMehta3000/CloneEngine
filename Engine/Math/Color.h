#pragma once
#include "Common/Property.h"
#include "Math/Util.h"
#include <string>

namespace Clone::Math
{
	class Color
	{
		CLONE_AUTO_PROPERTY(float, Red)
		CLONE_AUTO_PROPERTY(float, Green)
		CLONE_AUTO_PROPERTY(float, Blue)
		CLONE_AUTO_PROPERTY(float, Alpha)

		static const Color BLACK;
		static const Color WHITE;
		static const Color TRANSPARENT;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color LIGHTGREY;
		static const Color GREY;
		static const Color DARKGREY;
		static const Color MAGENTA;
		static const Color YELLOW;
		static const Color CYAN;

	public:
		Color() noexcept;
		Color(float r, float g, float b, float a = 1.0) noexcept;
		Color(const Color& other) noexcept;
		Color(Color&& other) noexcept;

		static Color Lerp(const Color& start, const Color& end, float time);
		float ToGrayscale() const;
		float MaxColorComponent() const;
		std::string ToString() const;

		inline Color& operator=(const Color& c) noexcept
		{
			Red = c.Red;
			Green = c.Green;
			Blue = c.Blue;
			Alpha = c.Alpha;
			return *this;
		}

		inline Color& operator=(const Color&& c) noexcept
		{
			Red = c.Red;
			Green = c.Green;
			Blue = c.Blue;
			Alpha = c.Alpha;
			return *this;
		}

		inline float operator[](int i) const;

		inline bool operator==(const Color& rhs) const 
		{
			return Red == rhs.Red && Green == rhs.Green && Blue == rhs.Blue && Alpha == rhs.Alpha;
		}

		inline bool operator!=(const Color& rhs) const { return !(*this == rhs); }

		inline Color operator+(const Color& rhs) const 
		{
			return Color(Math::Clamp01(Red + rhs.Red), 
						 Math::Clamp01(Green + rhs.Green),
						 Math::Clamp01(Blue + rhs.Blue),
						 Math::Clamp01(Alpha + rhs.Alpha));
		}

		inline Color operator-(const Color& rhs) const 
		{
			return Color(Math::Clamp01(Red - rhs.Red),
						 Math::Clamp01(Green - rhs.Green),
						 Math::Clamp01(Blue - rhs.Blue),
						 Math::Clamp01(Alpha - rhs.Alpha));
		}

		inline Color operator*(const Color& rhs) const 
		{
			return Color(Math::Clamp01(Red * rhs.Red),
						 Math::Clamp01(Green * rhs.Green),
						 Math::Clamp01(Blue * rhs.Blue),
						 Math::Clamp01(Alpha * rhs.Alpha));
		}

		inline Color operator*(const float rhs) const 
		{
			return Color(Math::Clamp01(Red * rhs), 
						 Math::Clamp01(Green * rhs),
						 Math::Clamp01(Blue * rhs), 
						 Math::Clamp01(Alpha * rhs));
		}

		friend inline Color operator*(const float lhs, const Color& rhs) 
		{
			return rhs * lhs;
		}

		inline Color operator/(const Color& rhs) const 
		{
			return Color(Math::Clamp01(Red / rhs.Red),
						 Math::Clamp01(Green / rhs.Green),
						 Math::Clamp01(Blue / rhs.Blue),
						 Math::Clamp01(Alpha / rhs.Alpha));
		}
	};
}