#pragma once

// NOLINTBEGIN(misc-include-cleaner)

#pragma region Platform specific includes

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
  #define NOMINMAX
#endif

#include <Windows.h>

#pragma endregion

#pragma region Standard library includes

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma endregion

// NOLINTEND(misc-include-cleaner)
