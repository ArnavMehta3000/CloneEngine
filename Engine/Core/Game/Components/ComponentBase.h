#pragma once
#include "Math/SimpleMath.h"
#include <string>
#include <memory>
#include <type_traits>

namespace Clone::Game { class Entity; }

namespace Clone::Components
{
	struct ComponentBase
	{
		explicit ComponentBase(std::string_view name)
			:
			ComponentName(name)
		{}

		const std::string ComponentName;
	};

	template <typename T>
	concept ConceptComponent = std::is_base_of_v<Clone::Components::ComponentBase, T>;
}