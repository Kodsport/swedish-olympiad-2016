#pragma once

#if _DEBUG
#define assert(x) if (!(x)) __debugbreak()
#else
#include <cassert>
#endif


