#pragma once

// Header containing a stripped version of Windows.h

#ifndef FULL_WIN

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#endif

#include <Windows.h>