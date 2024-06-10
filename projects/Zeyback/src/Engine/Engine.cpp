#include "pch.hpp"

#include "Engine/Engine.hpp"

#include "Engine/Event/Mouse.hpp"
#include "Engine/Input/Mouse.hpp"
#include "Engine/Math/Vector2.tpp"
#include "Game/Game.hpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"

namespace
{
  // -------------------------< Namespace Aliases >-------------------------- //
  namespace GDI = Platform::Windows::GDI;

  // -------------------------< Using Declarations >------------------------- //
  using SandboxGame = Game::Game;
} // namespace

// NOLINTBEGIN(readability-convert-member-functions-to-static)

namespace Engine
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Engine::onCreate() noexcept -> bool
  {
    // Create the game
    return SandboxGame::getInstance().onCreate();
  }

  auto Engine::onStart() const noexcept -> void
  {
    // Start the game
    SandboxGame::getInstance().onStart();
  }

  auto Engine::onResume() noexcept -> void
  {
    // Activate the game
    SandboxGame::getInstance().onResume();

    // Set the state to running
    m_state = {State::RUNNING};
  }

  auto Engine::onHandleKeyInput() const noexcept -> void
  {
    // Handle key input in the game
    SandboxGame::getInstance().onKeyInput();
  }

  auto Engine::onHandleMouseInput(int x, int y, Event::Mouse event)
    const noexcept -> void
  {
    // Create mouse position vector
    const Math::Vector2<int> position{x, y};

    // Parse the mouse event
    switch (event)
    {
    case Event::Mouse::MOVE:
    {
      // Forward mouse move to the game
      SandboxGame::getInstance().onMouseMove(position);
      break;
    }
    case Event::Mouse::LBUTTON_UP:
    {
      // Forward left mouse button up to the game
      SandboxGame::getInstance().onMouseButtonUp(
        position, Input::Mouse::LEFT_BUTTON
      );
      break;
    }
    case Event::Mouse::LBUTTON_DOWN:
    {
      // Forward left mouse button down to the game
      SandboxGame::getInstance().onMouseButtonDown(
        position, Input::Mouse::LEFT_BUTTON
      );
      break;
    }
    case Event::Mouse::RBUTTON_UP:
    {
      // Forward right mouse button up to the game
      SandboxGame::getInstance().onMouseButtonUp(
        position, Input::Mouse::RIGHT_BUTTON
      );
      break;
    }
    case Event::Mouse::RBUTTON_DOWN:
    {
      // Forward right mouse button down to the game
      SandboxGame::getInstance().onMouseButtonDown(
        position, Input::Mouse::RIGHT_BUTTON
      );
      break;
    }
    }
  }

  auto Engine::onUpdate() noexcept -> void
  {
    // Update the game
    SandboxGame::getInstance().onUpdate();
  }

  auto Engine::onRender(const GDI::DeviceContext& deviceContext
  ) const noexcept -> void
  {
    try
    {
      // Render the game
      SandboxGame::getInstance().onRender(deviceContext);
    }
    // NOLINTNEXTLINE
    catch (...)
    {
      // TODO(EmrecanKaracayir): Log the exception
    }
  }

  auto Engine::onPause() noexcept -> void
  {
    // Deactivate the game
    SandboxGame::getInstance().onPause();

    // Set the state to paused
    m_state = {State::PAUSED};
  }

  auto Engine::onStop() const noexcept -> void
  {
    // Stop the game
    SandboxGame::getInstance().onStop();
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Engine::getState() const noexcept -> State
  {
    return m_state;
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Static methods                                                |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Engine::getInstance() noexcept -> Engine&
  {
    // NOLINTNEXTLINE
    static Engine s_instance;
    return s_instance;
  }
} // namespace Engine

// NOLINTEND(readability-convert-member-functions-to-static)
