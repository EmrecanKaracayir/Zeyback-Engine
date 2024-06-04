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
  using XGame = Game::Game;
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
    // Engine created, return the game creation result
    return XGame::getInstance().onCreate();
  }

  auto Engine::onStart() const noexcept -> void
  {
    // Start the game
    XGame::getInstance().onStart();
  }

  auto Engine::onResume() noexcept -> void
  {
    // Activate the game
    XGame::getInstance().onResume();

    // Set the state to running
    m_state = {State::RUNNING};
  }

  auto Engine::onHandleKeyInput() const noexcept -> void
  {
    // Handle key input in the game
    XGame::getInstance().onKeyInput();
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
      XGame::getInstance().onMouseMove(position);
      break;
    }
    case Event::Mouse::LBUTTON_UP:
    {
      // Forward left mouse button up to the game
      XGame::getInstance().onMouseButtonUp(position, Input::Mouse::LEFT_BUTTON);
      break;
    }
    case Event::Mouse::LBUTTON_DOWN:
    {
      // Forward left mouse button down to the game
      XGame::getInstance().onMouseButtonDown(
        position, Input::Mouse::LEFT_BUTTON
      );
      break;
    }
    case Event::Mouse::RBUTTON_UP:
    {
      // Forward right mouse button up to the game
      XGame::getInstance().onMouseButtonUp(
        position, Input::Mouse::RIGHT_BUTTON
      );
      break;
    }
    case Event::Mouse::RBUTTON_DOWN:
    {
      // Forward right mouse button down to the game
      XGame::getInstance().onMouseButtonDown(
        position, Input::Mouse::RIGHT_BUTTON
      );
      break;
    }
    }
  }

  auto Engine::onUpdate() noexcept -> void
  {
    // Update the game
    XGame::getInstance().onUpdate();
  }

  auto Engine::onRender(const GDI::DeviceContext& deviceContext
  ) const noexcept -> void
  {
    // Render the game
    XGame::getInstance().onRender(deviceContext);
  }

  auto Engine::onPause() noexcept -> void
  {
    // Deactivate the game
    XGame::getInstance().onPause();

    // Set the state to paused
    m_state = {State::PAUSED};
  }

  auto Engine::onStop() const noexcept -> void
  {
    // Stop the game
    XGame::getInstance().onStop();
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
