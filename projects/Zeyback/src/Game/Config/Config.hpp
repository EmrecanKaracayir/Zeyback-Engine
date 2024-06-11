#pragma once

#include <wingdi.h>

#include <cstdint>
#include <Support/zstring>

// NOLINTBEGIN(clang-diagnostic-unused-const-variable)

namespace Game::Config
{
  // -----------------------< Window Configurations >------------------------ //
  constexpr gsl::cwzstring TITLE{L"Application Title"};
  constexpr std::int32_t   SCREEN_WIDTH{1'600};
  constexpr std::int32_t   SCREEN_HEIGHT{900};
  constexpr bool           START_FULLSCREEN{true};
  constexpr std::int64_t   FRAME_RATE{32};
  constexpr COLORREF       TITLE_BAR_COLOR{RGB(0, 0, 0)};

  // ----------------------< Graphics Configurations >----------------------- //
  constexpr std::uint32_t PIXEL_DEPTH{32};
  constexpr COLORREF      TRANSPARENT_COLOR{RGB(0, 0, 0)};

  // ------------------------< Input Configurations >------------------------ //
  constexpr std::uint16_t FULLSCREEN_TOGGLE_KEY{VK_F11};
} // namespace Game::Config

// NOLINTEND(clang-diagnostic-unused-const-variable)
