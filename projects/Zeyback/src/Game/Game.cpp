#include "pch.hpp"

#include "Game/Game.hpp"

#include "Engine/Graphics/Texture.hpp"
#include "Engine/Input/Mouse.hpp"
#include "Engine/Math/Vector2.tpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"

// NOLINTBEGIN(clang-diagnostic-unused-value)

namespace
{
  // -------------------------< Namespace Aliases >-------------------------- //
  namespace Input = Engine::Input;
  namespace Math  = Engine::Math;
  namespace GDI   = Platform::Windows::GDI;
} // namespace

namespace Game
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Destructor                                                     |*
  \*--------------------------------------------------------------------------*/

  Game::~Game() noexcept { onDestroy(); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Game::onCreate() noexcept -> bool
  {
    try
    {
      m_loadedTexture.reinitialize(L"assets\\placeholder.bmp", true);
      // NOLINTNEXTLINE
      m_createdTexture.reinitialize(100, 100, GDI::Color(255, 0, 0), false);
    }
    catch (...)
    {
      return false;
    }

    return true;
  }

  auto Game::onStart() noexcept -> void {}

  auto Game::onResume() noexcept -> void {}

  auto Game::onKeyInput() noexcept -> void {}

  auto Game::onMouseMove(const Math::Vector2<int>& position) noexcept -> void
  {
    position;
  }

  auto Game::onMouseButtonDown(
    const Math::Vector2<int>& position, Input::Mouse input
  ) noexcept -> void
  {
    position;
    input;
  }

  auto Game::onMouseButtonUp(
    const Math::Vector2<int>& position, Input::Mouse input
  ) noexcept -> void
  {
    position;
    input;
  }

  auto Game::onUpdate() noexcept -> void {}

  auto Game::onRender(const GDI::DeviceContext& deviceContext) -> void
  {
    m_loadedTexture.render(deviceContext, 0, 0);
    // NOLINTNEXTLINE
    m_loadedTexture.render(deviceContext, 1'552, 0);
    // NOLINTNEXTLINE
    m_loadedTexture.render(deviceContext, 0, 852);
    // NOLINTNEXTLINE
    m_loadedTexture.render(deviceContext, 1'552, 852);
    // NOLINTNEXTLINE
    m_createdTexture.render(deviceContext, 750, 400);
  }

  auto Game::onPause() noexcept -> void {}

  auto Game::onStop() noexcept -> void {}

  auto Game::onDestroy() noexcept -> void {}

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

  /*--------------------------------------------------------------------------*\
  *| [private]: Methods                                                       |*
  \*--------------------------------------------------------------------------*/

} // namespace Game

// NOLINTEND(clang-diagnostic-unused-value)
