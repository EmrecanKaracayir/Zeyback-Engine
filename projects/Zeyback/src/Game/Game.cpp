#include "pch.hpp"

#include "Game/Game.hpp"

#include "Engine/Graphics/Texture.hpp"
#include "Engine/Input/Mouse.hpp"
#include "Engine/Math/Vector2.tpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"

#include <stdexcept>

// NOLINTBEGIN(clang-diagnostic-unused-value)

namespace
{
  // -------------------------< Namespace Aliases >-------------------------- //
  namespace Input = Engine::Input;
  namespace GDI   = Platform::Windows::GDI;

  // -------------------------< Using Declarations >------------------------- //
  template <typename T> requires std::is_arithmetic_v<T>
  using Vector2 = Engine::Math::Vector2<T>;
} // namespace

namespace Game
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Game::onCreate() noexcept -> bool
  {
    return true;
  }

  auto Game::onStart() noexcept -> void {}

  auto Game::onResume() noexcept -> void {}

  auto Game::onKeyInput() noexcept -> void {}

  auto Game::onMouseMove(Vector2<int> position) noexcept -> void { position; }

  auto Game::onMouseButtonDown(
    Vector2<int> position, Input::Mouse input
  ) noexcept -> void
  {
    position;
    input;
  }

  auto Game::onMouseButtonUp(Vector2<int> position, Input::Mouse input) noexcept
    -> void
  {
    position;
    input;
  }

  auto Game::onUpdate() noexcept -> void {}

  auto Game::onRender(const GDI::DeviceContext& deviceContext) noexcept -> void
  {
    try
    {
      tex1.render(deviceContext, 0, 0);
      // NOLINTNEXTLINE
      tex2.render(deviceContext, 100, 100);
    }
    catch (const std::runtime_error& error)
    {
      error;
    }
  }

  auto Game::onPause() noexcept -> void {}

  auto Game::onStop() noexcept -> void {}

  /*--------------------------------------------------------------------------*\
  *| [private]: Static methods                                                |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Game::getInstance() noexcept -> Game&
  {
    // NOLINTNEXTLINE
    static Game s_instance;
    return s_instance;
  }

} // namespace Game

// NOLINTEND(clang-diagnostic-unused-value)
