#include "pch.hpp"

#include "App/App.hpp"

#include "Engine/Engine.hpp"
#include "Engine/Event/Mouse.hpp"
#include "Game/Config/Config.hpp"
#include "Game/Resource/resource.hpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"

#include <minwindef.h>
#include <sal.h>
#include <sysinfoapi.h>
#include <windef.h>
#include <windowsx.h>
#include <wingdi.h>
#include <WinUser.h>

#include <cstdint>
#include <stdexcept>
#include <Support/util>

// TODO(EmrecanKaracayir): onRender gets called before onCreate fix it.

namespace
{
  // -------------------------< Namespace Aliases >-------------------------- //
  namespace Event  = Engine::Event;
  namespace Config = Game::Config;
  namespace GDI    = Platform::Windows::GDI;

  // -------------------------< Using Declarations >------------------------- //
  using Zeyback = Engine::Engine;
} // namespace

namespace App
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto App::onCreate(HINSTANCE instance) noexcept -> bool
  {
    // Set the instance handle
    m_instance = {instance};

    // Load icon
    m_appIcon = {LoadIcon(instance, MAKEINTRESOURCE(IDIC_APP))};

    // If the icon is null, return false
    if (m_appIcon == nullptr)
    {
      return false;
    }

    // Load cursors
    m_pointerCursor = {LoadCursor(instance, MAKEINTRESOURCE(IDCC_POINTER))};

    // If the cursor is null, return false
    if (m_pointerCursor == nullptr)
    {
      return false;
    }

    // Create the window class
    WNDCLASSEX windowClass{};
    windowClass.cbSize        = {sizeof(WNDCLASSEX)};
    windowClass.style         = {CS_HREDRAW bitor CS_VREDRAW};
    windowClass.lpfnWndProc   = {windowProcedure};
    windowClass.cbClsExtra    = {};
    windowClass.cbWndExtra    = {};
    windowClass.hInstance     = {instance};
    windowClass.hIcon         = {m_appIcon};
    windowClass.hIconSm       = {m_appIcon};
    windowClass.hCursor       = {m_pointerCursor};
    windowClass.hbrBackground = {GetSysColorBrush(COLOR_WINDOW)};
    windowClass.lpszMenuName  = {nullptr};
    windowClass.lpszClassName = {Config::TITLE};

    // Register the window class
    if (not RegisterClassEx(&windowClass))
    {
      return false;
    }

    // Create the window
    if (not createWindow(windowClass))
    {
      return false;
    }

    // Show and update the window
    ShowWindow(m_window, SW_SHOW);
    UpdateWindow(m_window);

    // App created, return the engine creation result
    return Zeyback::getInstance().onCreate();
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Static methods                                                |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto App::getInstance() noexcept -> App&
  {
    static App s_instance{};
    return s_instance;
  }

  [[nodiscard]]
  auto CALLBACK App::windowProcedure(
    _In_ HWND window, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam
  ) -> LRESULT
  {
    // Initialize heavy objects
    PAINTSTRUCT paintStruct{};

    // Message handling
    switch (message)
    {
    case WM_CREATE:
    {
      // Start the engine
      Zeyback::getInstance().onStart();
      return 0;
    }
    case WM_SETCURSOR:
    {
      // Set the cursor to the pointer cursor
      SetCursor(getInstance().m_pointerCursor);
      return 0;
    }
    case WM_ACTIVATE:
    {
      // Pause or resume the engine based on window activation
      if (wParam != WA_INACTIVE)
      {
        // Fullscreen handling
        if (Config::FULLSCREEN)
        {
          // Change the display settings
          getInstance().changeDisplaySettingsEx(true);

          // Show the window
          ShowWindow(window, SW_SHOW);
        }

        // Activate the engine
        Zeyback::getInstance().onResume();
      }
      else
      {
        // Deactivate the engine
        Zeyback::getInstance().onPause();

        // Fullscreen handling
        if (Config::FULLSCREEN)
        {
          // Restore the display settings
          getInstance().changeDisplaySettingsEx(false);

          // Minimize the window
          ShowWindow(window, SW_MINIMIZE);
        }
      }
      return 0;
    }
    case WM_PAINT:
    {
      // Get device context by beginning paint
      const GDI::DeviceContext deviceContext{
        GDI::DeviceContext::Action::ACCESS, BeginPaint(window, &paintStruct)
      };

      // Render in engine
      Zeyback::getInstance().onRender(deviceContext);

      // End the paint
      EndPaint(window, &paintStruct);
      return 0;
    }
    case WM_LBUTTONDOWN:
    {
      // Handle left mouse button down
      Zeyback::getInstance().onHandleMouseInput(
        GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Event::Mouse::LBUTTON_DOWN
      );
      return 0;
    }
    case WM_LBUTTONUP:
    {
      // Handle left mouse button up
      Zeyback::getInstance().onHandleMouseInput(
        GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Event::Mouse::LBUTTON_UP
      );
      return 0;
    }
    case WM_RBUTTONDOWN:
    {
      // Handle right mouse button down
      Zeyback::getInstance().onHandleMouseInput(
        GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Event::Mouse::RBUTTON_DOWN
      );
      return 0;
    }
    case WM_RBUTTONUP:
    {
      // Handle right mouse button up
      Zeyback::getInstance().onHandleMouseInput(
        GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Event::Mouse::RBUTTON_UP
      );
      return 0;
    }
    case WM_MOUSEMOVE:
    {
      // Handle mouse movement
      Zeyback::getInstance().onHandleMouseInput(
        GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), Event::Mouse::MOVE
      );
      return 0;
    }
    case WM_DESTROY:
    {
      // Stop the engine
      Zeyback::getInstance().onStop();

      // Fullscreen handling
      if (Config::FULLSCREEN)
      {
        // Restore the display settings
        getInstance().changeDisplaySettingsEx(false);
      }

      // Post a quit message
      PostQuitMessage(0);
      return 0;
    }
    default:
    {
      break;
    }
    }

    // Pass the message to the default window procedure
    return DefWindowProc(window, message, wParam, lParam);
  }

  [[nodiscard]]
  auto App::run() noexcept -> WPARAM
  {
    // Message loop variables
    MSG           message{};
    std::uint64_t tickCount{};
    std::uint64_t tickTrigger{};

    // Message loop
    while (true)
    {
      if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
      {
        // If the message is WM_QUIT, exit the loop
        if (message.message == WM_QUIT)
        {
          break;
        }

        // Translate the message and dispatch it to the window procedure
        TranslateMessage(&message);
        DispatchMessage(&message);
      }
      else
      {
        // Check if the engine is running
        if (Zeyback::getInstance().getState() == Zeyback::State::RUNNING)
        {
          // Get the current tick count
          tickCount = {GetTickCount64()};

          // Check if game cycle has elapsed
          if (tickCount > tickTrigger)
          {
            // Update the tick trigger
            tickTrigger = {tickCount + Config::FRAME_RATE};

            // Update the engine
            Zeyback::getInstance().onHandleKeyInput();
            Zeyback::getInstance().onUpdate();
          }
        }
      }
    }

    // Return the wParam of the WM_QUIT message
    return message.wParam;
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Methods                                                       |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto App::createWindow(const WNDCLASSEX& windowClass) noexcept -> bool
  {
    // Window variables for fullscreen mode
    std::uint32_t windowStyle{WS_POPUP};
    std::int32_t  windowWidth{Config::SCREEN_WIDTH};
    std::int32_t  windowHeight{Config::SCREEN_HEIGHT};
    int           windowX{};
    int           windowY{};

    // Prepare non-fullscreen window
    if (not Config::FULLSCREEN)
    {
      // Alter window style
      windowStyle = {WS_POPUPWINDOW bitor WS_CAPTION bitor WS_MINIMIZEBOX};

      // Adjust the window size
      RECT rect{0, 0, windowWidth, windowHeight};
      AdjustWindowRectEx(
        &rect,
        windowStyle,
        static_cast<BOOL>(windowClass.lpszMenuName != nullptr),
        0
      );

      // Calculate and alter the window size
      windowWidth  = {rect.right - rect.left};
      windowHeight = {rect.bottom - rect.top};

      // Get the dimensions of the screen
      const int screenWidth{GetSystemMetrics(SM_CXSCREEN)};
      const int screenHeight{GetSystemMetrics(SM_CYSCREEN)};

      // Calculate and alter the position to center the window
      windowX = {(screenWidth - windowWidth) / 2};
      windowY = {(screenHeight - windowHeight) / 2};
    }
    else
    {
      // Initialize the device mode
      m_deviceMode.dmSize      = {sizeof(m_deviceMode)};
      m_deviceMode.dmPelsWidth = {gsl::narrow_cast<std::uint32_t>(windowWidth)};
      m_deviceMode.dmPelsHeight = {gsl::narrow_cast<std::uint32_t>(windowHeight)
      };
      m_deviceMode.dmBitsPerPel = {Config::PIXEL_DEPTH};
      m_deviceMode.dmFields     = {
        DM_PELSWIDTH bitor DM_PELSHEIGHT bitor DM_BITSPERPEL
      };

      // Change the display settings
      if (not changeDisplaySettings(true))
      {
        return false;
      }
    }

    // Create the window
    m_window = {CreateWindow(
      windowClass.lpszClassName,
      Config::TITLE,
      windowStyle,
      windowX,
      windowY,
      windowWidth,
      windowHeight,
      nullptr,
      nullptr,
      m_instance,
      nullptr
    )};

    // If the window handle is null, return false
    if (m_window == nullptr)
    {
      if (Config::FULLSCREEN)
      {
        if (not changeDisplaySettings(false))
        {
          return false;
        }
      }
      return false;
    }

    // Return true if the window was created successfully
    return true;
  }

  [[nodiscard]]
  auto App::changeDisplaySettings(bool custom) noexcept -> bool
  {
    if (custom)
    {
      // Change the display settings
      if (ChangeDisplaySettings(&m_deviceMode, CDS_FULLSCREEN)
          != DISP_CHANGE_SUCCESSFUL)
      {
        return false;
      }
    }
    else
    {
      // Restore the display settings
      ChangeDisplaySettings(nullptr, 0);

      /*[Remark]:
       *-----------------------------------------------------------------------*
       |   We should be checking the return value of ChangeDisplaySettings but,|
       | sometimes call fails and causes the program to crash. We will ignore  |
       | the return value for now and hope for the best.                       |
       *----------------------------------------------------------------------*/
    }
    return true;
  }

  auto App::changeDisplaySettingsEx(bool custom) -> void
  {
    if (not changeDisplaySettings(custom))
    {
      throw std::runtime_error("Failed to change display settings!");
    }
  }
} // namespace App
