#pragma once

#include <cstdint>

namespace Engine::Event
{
  enum class Mouse : std::uint8_t
  {
    MOVE,
    LBUTTON_UP,
    LBUTTON_DOWN,
    RBUTTON_UP,
    RBUTTON_DOWN,
  };
} // namespace Engine::Event
