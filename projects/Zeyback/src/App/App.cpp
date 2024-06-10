#include "pch.hpp"

#include "App/App.hpp"

#include "Engine/Engine.hpp"
#include "Engine/Event/Mouse.hpp"
#include "Game/Config/config.hpp"
#include "Game/Resource/resource.hpp"
#include "Platform/Windows/GDI/Cursor.hpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"
#include "Platform/Windows/GDI/Icon.hpp"

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
    // Create the engine
    if (not Zeyback::getInstance().onCreate())
    {
      return false;
    }

    // Create the application
    try
    {
      // Set the instance handle
      m_instance = {instance};

      // Load icon
      m_icon.reinitialize(instance, IDIC_APP);

      // Load cursor
      m_cursor.reinitialize(instance, IDCC_POINTER);

      // Create window
      createWindow();

      return true;
    }
    catch (...)
    {
      return false;
    }
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Static methods                                                |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto App::getInstance() noexcept -> App&
  {
    // NOLINTNEXTLINE
    static App s_instance;
    return s_instance;
  }

  [[nodiscard]]
  auto CALLBACK App::windowProcedure(
    _In_ HWND window, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam
  ) -> LRESULT
  {
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
      SetCursor(getInstance().m_cursor.getHandle());
      return 0;
    }
    case WM_ACTIVATE:
    {
      // Pause or resume the engine based on window activation
      if (wParam != WA_INACTIVE)
      {
        // Fullscreen handling
        if (getInstance().m_fullscreen)
        {
          // Change the display settings
          getInstance().changeDisplaySettings(true);

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
        if (getInstance().m_fullscreen)
        {
          // Restore the display settings
          getInstance().changeDisplaySettings(false);

          // Minimize the window
          ShowWindow(window, SW_MINIMIZE);
        }
      }
      return 0;
    }
    case WM_PAINT:
    {
      // Initialize paint structure
      PAINTSTRUCT paintStruct{};

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
    case WM_KEYDOWN:
    {
      if (wParam == VK_F11)
      {
        getInstance().m_fullscreen
          ? getInstance().exitFullscreen()
          : getInstance().enterFullscreen();
      }
      break;
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
      if (getInstance().m_fullscreen)
      {
        // Restore the display settings
        getInstance().changeDisplaySettings(false);
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

  auto App::createWindow() -> void
  {
    // Initialize the window class
    WNDCLASSEX windowClass{};
    windowClass.cbSize        = {sizeof(WNDCLASSEX)};
    windowClass.style         = {CS_HREDRAW bitor CS_VREDRAW};
    windowClass.lpfnWndProc   = {windowProcedure};
    windowClass.cbClsExtra    = {};
    windowClass.cbWndExtra    = {};
    windowClass.hInstance     = {m_instance};
    windowClass.hIcon         = {m_icon.getHandle()};
    windowClass.hIconSm       = {m_icon.getHandle()};
    windowClass.hCursor       = {m_cursor.getHandle()};
    windowClass.hbrBackground = {GetSysColorBrush(COLOR_WINDOW)};
    windowClass.lpszMenuName  = {nullptr};
    windowClass.lpszClassName = {Config::TITLE};

    // Register the window class
    if (not RegisterClassEx(&windowClass))
    {
      throw std::runtime_error{"Failed to register window class!"};
    }

    // Window variables for fullscreen mode
    std::uint32_t windowStyle{WS_POPUPWINDOW};
    int           windowX{};
    int           windowY{};
    std::int32_t  windowWidth{Config::SCREEN_WIDTH};
    std::int32_t  windowHeight{Config::SCREEN_HEIGHT};

    // Initialize the device mode
    m_deviceMode.dmSize       = {sizeof(m_deviceMode)};
    m_deviceMode.dmPelsWidth  = {gsl::narrow_cast<std::uint32_t>(windowWidth)};
    m_deviceMode.dmPelsHeight = {gsl::narrow_cast<std::uint32_t>(windowHeight)};
    m_deviceMode.dmBitsPerPel = {Config::PIXEL_DEPTH};
    m_deviceMode.dmFields     = {
      DM_PELSWIDTH bitor DM_PELSHEIGHT bitor DM_BITSPERPEL
    };

    // Prepare non-fullscreen window
    if (not m_fullscreen)
    {
      // Alter window style
      windowStyle = {WS_POPUPWINDOW bitor WS_CAPTION bitor WS_MINIMIZEBOX};

      // Adjust the window size
      RECT rect{0, 0, windowWidth, windowHeight};
      AdjustWindowRect(&rect, windowStyle, static_cast<BOOL>(false));

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
      // Change display settings for fullscreen
      changeDisplaySettings(true);
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
      // If was fullscreen, revert display settings
      if (m_fullscreen)
      {
        changeDisplaySettings(false);
      }

      // Unregister the window class
      if (UnregisterClass(windowClass.lpszClassName, m_instance) == 0)
      {
        throw std::runtime_error{"Failed to unregister window class!"};
      }

      // Throw the exception
      throw std::runtime_error{"Failed to create window!"};
    }

    // Show window
    ShowWindow(m_window, SW_SHOW);

    // Update window
    if (UpdateWindow(m_window) == 0)
    {
      throw std::runtime_error{"Failed to update window!"};
    }
  }

  auto App::changeDisplaySettings(bool custom) -> void
  {
    if (custom)
    {
      // Change the display settings
      if (ChangeDisplaySettings(&m_deviceMode, CDS_FULLSCREEN)
          != DISP_CHANGE_SUCCESSFUL)
      {
        throw std::runtime_error("Failed to change display settings!");
      }
    }
    else
    {
      // Restore the display settings
      ChangeDisplaySettings(nullptr, 0);

      /*[Remark]:
       *-----------------------------------------------------------------------*
       |   We should be checking the return value of the ChangeDisplaySettings |
       | but, sometimes call seems to fail and causes our program to crash. We |
       | will ignore the return value for now and hope for the best.           |
       *----------------------------------------------------------------------*/
    }
  }

  auto App::enterFullscreen() -> void
  {
    // Window variables for fullscreen mode
    constexpr std::uint32_t WINDOW_STYLE{WS_POPUPWINDOW};
    constexpr int           WINDOW_X{};
    constexpr int           WINDOW_Y{};
    constexpr std::int32_t  WINDOW_WIDTH{Config::SCREEN_WIDTH};
    constexpr std::int32_t  WINDOW_HEIGHT{Config::SCREEN_HEIGHT};

    // Change window style
    if (SetWindowLongPtr(m_window, GWL_STYLE, WINDOW_STYLE) == 0)
    {
      throw std::runtime_error{"Failed to change window style!"};
    }

    // Change window size and position
    if (SetWindowPos(
          m_window,
          nullptr,
          WINDOW_X,
          WINDOW_Y,
          WINDOW_WIDTH,
          WINDOW_HEIGHT,
          SWP_FRAMECHANGED bitor SWP_SHOWWINDOW
        )
        == 0)
    {
      throw std::runtime_error{"Failed to change window size and position!"};
    }

    // Change the display settings
    changeDisplaySettings(true);

    m_fullscreen = {true};
  }

  auto App::exitFullscreen() -> void
  {
    // Restore the display settings
    changeDisplaySettings(false);

    // Window variables for windowed mode
    constexpr std::uint32_t WINDOW_STYLE{
      WS_POPUPWINDOW bitor WS_CAPTION bitor WS_MINIMIZEBOX
    };
    int          windowX{};
    int          windowY{};
    std::int32_t windowWidth{Config::SCREEN_WIDTH};
    std::int32_t windowHeight{Config::SCREEN_HEIGHT};

    // Adjust the window size
    RECT rect{0, 0, windowWidth, windowHeight};
    AdjustWindowRect(&rect, WINDOW_STYLE, static_cast<BOOL>(false));

    // Calculate and alter the window size
    windowWidth  = {rect.right - rect.left};
    windowHeight = {rect.bottom - rect.top};

    // Get the dimensions of the screen
    const int screenWidth{GetSystemMetrics(SM_CXSCREEN)};
    const int screenHeight{GetSystemMetrics(SM_CYSCREEN)};

    // Calculate and alter the position to center the window
    windowX = {(screenWidth - windowWidth) / 2};
    windowY = {(screenHeight - windowHeight) / 2};

    // Change window style
    if (SetWindowLongPtr(m_window, GWL_STYLE, WINDOW_STYLE) == 0)
    {
      throw std::runtime_error{"Failed to change window style!"};
    }

    // Change window size and position
    if (SetWindowPos(
          m_window,
          nullptr,
          windowX,
          windowY,
          windowWidth,
          windowHeight,
          SWP_FRAMECHANGED bitor SWP_SHOWWINDOW
        )
        == 0)
    {
      throw std::runtime_error{"Failed to change window size and position!"};
    }

    m_fullscreen = {false};
  }
} // namespace App
