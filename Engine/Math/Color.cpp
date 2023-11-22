#include "Color.h"
#include <stdexcept>
#include <format>

namespace Clone::Math
{
	const Color Color::BLACK       = Color(0, 0, 0, 1);
	const Color Color::WHITE       = Color(1, 1, 1, 1);
	const Color Color::TRANSPARENT = Color(0, 0, 0, 0);
	const Color Color::RED         = Color(1, 0, 0, 1);
	const Color Color::GREEN       = Color(0, 1, 0, 1);
	const Color Color::BLUE        = Color(0, 0, 1, 1);
	const Color Color::LIGHTGREY   = Color(0.8f, 0.8f, 0.8f, 1);
	const Color Color::GREY        = Color(0.5f, 0.5f, 0.5f, 1);
	const Color Color::DARKGREY    = Color(0.15f, 0.15f, 0.15f, 1);
	const Color Color::MAGENTA     = Color(1, 0, 1, 1);
	const Color Color::YELLOW      = Color(1, 0.92f, 0.016f, 1);
	const Color Color::CYAN        = Color(0, 1, 1, 1);

	Color::Color() noexcept
	{
		m_Red = 0.0f;
		m_Green = 0.0f;
		m_Blue = 0.0f;
		m_Alpha = 0.0f;
	}

	Color::Color(float r, float g, float b, float a) noexcept
		:
		m_Red(r),
		m_Green(g),
		m_Blue(b),
		m_Alpha(a)
	{}

	Color::Color(const Color& other) noexcept
	{
		m_Red = other.Red;
		m_Green = other.Green;
		m_Blue = other.Blue;
		m_Alpha = other.Alpha;
	}

	Color::Color(Color&& other) noexcept
	{
		m_Red = other.Red;
		m_Green = other.Green;
		m_Blue = other.Blue;
		m_Alpha = other.Alpha;
	}

	Color Color::Lerp(const Color& start, const Color& end, float time)
	{
		return start * (1.0f - time) + end * time;
	}

	float Color::ToGrayscale() const
	{
		return (Red + Green + Blue) / 3.0f;
	}

	float Color::MaxColorComponent() const
	{
		return Math::Max({ Red, Green, Blue });
	}

	std::string Color::ToString() const
	{
		return std::format("Color({:.2f}, {:.2f}, {:.2f}, {:.2f})", 
			Red, Green, Blue, Alpha);
	}

	inline float Color::operator[](int i) const
	{
		switch (i)
		{
		case 0:
			return Red;
		case 1:
			return Green;
		case 2:
			return Blue;
		case 3:
			return Alpha;
		default:
			throw std::out_of_range("Color::[] access out of range");
		}
	}
}