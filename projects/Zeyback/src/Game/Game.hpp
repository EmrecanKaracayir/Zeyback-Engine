#pragma once

#include "Engine/Engine.hpp"
#include "Engine/Graphics/Texture.hpp"
#include "Engine/Input/Mouse.hpp"
#include "Engine/Math/Vector2.tpp"
#include "Game/Interface/IGame.hpp"
#include "Platform/Windows/GDI/Color.hpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"

namespace
{
  // -------------------------< Namespace Aliases >-------------------------- //
  namespace Graphics = Engine::Graphics;
  namespace Input    = Engine::Input;
  namespace Math     = Engine::Math;
  namespace GDI      = Platform::Windows::GDI;
} // namespace

namespace Game
{
  class Game : public IGame
  {
  public:
    /*------------------------------------------------------------------------*\
    *| [public]: Types                                                        |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Constructors                                                 |*
    \*------------------------------------------------------------------------*/

    Game(const Game&) noexcept = delete;
    Game(Game&&) noexcept      = delete;

    /*------------------------------------------------------------------------*\
    *| [public]: Destructor                                                   |*
    \*------------------------------------------------------------------------*/

    ~Game() noexcept override;

    /*------------------------------------------------------------------------*\
    *| [public]: Operators                                                    |*
    \*------------------------------------------------------------------------*/

    auto operator=(const Game&) noexcept -> Game& = delete;
    auto operator=(Game&&) noexcept -> Game&      = delete;

    /*------------------------------------------------------------------------*\
    *| [public]: Static methods                                               |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Static fields                                                |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Methods                                                      |*
    \*------------------------------------------------------------------------*/

    [[nodiscard]]
    auto onCreate() noexcept -> bool final;
    auto onStart() noexcept -> void final;
    auto onResume() noexcept -> void final;
    auto onKeyInput() noexcept -> void final;
    auto onMouseMove(const Math::Vector2<int>& position) noexcept -> void final;
    auto onMouseButtonDown(
      const Math::Vector2<int>& position, Input::Mouse input
    ) noexcept -> void final;
    auto onMouseButtonUp(
      const Math::Vector2<int>& position, Input::Mouse input
    ) noexcept -> void final;
    auto onUpdate() noexcept -> void final;
    auto onRender(const GDI::DeviceContext& deviceContext) -> void final;
    auto onPause() noexcept -> void final;
    auto onStop() noexcept -> void final;
    auto onDestroy() noexcept -> void final;

    /*------------------------------------------------------------------------*\
    *| [public]: Fields                                                       |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Accessors                                                    |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Mutators                                                     |*
    \*------------------------------------------------------------------------*/
  protected:
    /*------------------------------------------------------------------------*\
    *| [protected]: Types                                                     |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [protected]: Constructors                                              |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [protected]: Destructor                                                |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [protected]: Operators                                                 |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [protected]: Static methods                                            |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [protected]: Static fields                                             |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [protected]: Methods                                                   |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [protected]: Fields                                                    |*
    \*------------------------------------------------------------------------*/
  private:
    /*------------------------------------------------------------------------*\
    *| [private]: Types                                                       |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Constructors                                                |*
    \*------------------------------------------------------------------------*/

    Game() noexcept = default;

    /*------------------------------------------------------------------------*\
    *| [private]: Destructor                                                  |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Operators                                                   |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Static methods                                              |*
    \*------------------------------------------------------------------------*/

    [[nodiscard]]
    static auto getInstance() noexcept -> Game&;

    /*------------------------------------------------------------------------*\
    *| [private]: Static fields                                               |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Methods                                                     |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Fields                                                      |*
    \*------------------------------------------------------------------------*/

    Graphics::Texture m_loadedTexture;
    Graphics::Texture m_createdTexture;

    /*------------------------------------------------------------------------*\
    *| [private]: Friends                                                     |*
    \*------------------------------------------------------------------------*/

    friend class Engine::Engine;
  };
} // namespace Game
