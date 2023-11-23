#pragma once

// Header containing a stripped version of Windows.h

#ifndef FULL_WIN

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDICAPMASKS
#define OEMRESOURCE
#define NOCTLMGR
#define NODRAWTEXT
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOSCROLL
#define NOSERVICE
#define NOTEXTMETRIC
#define NOWH
#define NOKANJI
#define NOHELP
#define NODEFERWINDOWPOS
#define NORPC
#define NOPROXYSTUB
#define NOTAPE
#endif



#include <Windows.h>