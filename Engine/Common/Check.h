#pragma once
#include <cassert>
namespace Clone::Common
{
#define CLONE_CHECK(x) assert(x)
#define CLONE_CHECK_IMPL(a, b, op) assert((a)op(b))

#define CLONE_CHECK_EQ(a, b) CLONE_CHECK_IMPL(a, b, ==)
#define CLONE_CHECK_NE(a, b) CLONE_CHECK_IMPL(a, b, !=)
#define CLONE_CHECK_GT(a, b) CLONE_CHECK_IMPL(a, b, >)
#define CLONE_CHECK_GE(a, b) CLONE_CHECK_IMPL(a, b, >=)
#define CLONE_CHECK_LT(a, b) CLONE_CHECK_IMPL(a, b, <)
#define CLONE_CHECK_LE(a, b) CLONE_CHECK_IMPL(a, b, <=)
}