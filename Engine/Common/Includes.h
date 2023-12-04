#pragma once

#include <string>
#include <string_view>
#include <format>
#include <vector>
#include <list>
#include <queue>
#include <bitset>
#include <memory>
#include <algorithm>
#include <ranges>
#include <execution>
#include <stdexcept>
#include <functional>
#include <utility>
#include <type_traits>
#include <tchar.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <future>
#include <wrl/client.h>

namespace rn = std::ranges;
namespace views = std::ranges::views;

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

#include "Common/Check.h"
#include "Common/Defines.h"
#include "Common/Property.h"
#include "Tools/Logger.h"
#include "Tools/StringHelper.h"
#include "Tools/Timer.h"