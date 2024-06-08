#include "pch.hpp"

#include "Platform/Windows/GDI/DeviceContext.hpp"

#include "Engine/Math/Rectangle.tpp"
#include "Game/Config/config.hpp"

#include <windef.h>
#include <wingdi.h>
#include <WinUser.h>

#include <cstdint>
#include <stdexcept>

namespace
{
  // -------------------------< Namespace Aliases >-------------------------- //
  namespace Config = Game::Config;
  namespace Math   = Engine::Math;
} // namespace

namespace Platform::Windows::GDI
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  DeviceContext::DeviceContext(Action action, HDC deviceContext)
    : m_action{action}
  {
    initialize(deviceContext);
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Destructor                                                     |*
  \*--------------------------------------------------------------------------*/

  DeviceContext::~DeviceContext() noexcept { cleanup(); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  auto DeviceContext::reinitialize(Action action, HDC deviceContext) -> void
  {
    // Clean instance
    cleanup();

    // Set fields
    m_action = {action};

    // Initialize device context
    initialize(deviceContext);
  }

  auto DeviceContext::selectObject(HGDIOBJ object) const -> void
  {
    if (SelectObject(m_deviceContext, object) == nullptr)
    {
      throw std::runtime_error{"Failed to select object!"};
    }
  }

  auto DeviceContext::transferBits(
    const DeviceContext&                 source,
    const Math::Rectangle<std::int32_t>& sourceArea,
    const Math::Rectangle<std::int32_t>& destinationArea,
    bool                                 transparency
  ) const -> void
  {
    if (transparency)
    {
      // Check if the bits are transferred
      if (TransparentBlt(
            getHandle(),
            destinationArea.getX(),
            destinationArea.getY(),
            destinationArea.getWidth(),
            destinationArea.getHeight(),
            source.getHandle(),
            sourceArea.getX(),
            sourceArea.getY(),
            sourceArea.getWidth(),
            sourceArea.getHeight(),
            Config::TRANSPARENT_COLOR
          )
          == 0)
      {
        throw std::runtime_error{"Failed to transfer bits!"};
      }
    }
    else
    {
      // Check if the bits are transferred
      if (BitBlt(
            getHandle(),
            destinationArea.getX(),
            destinationArea.getY(),
            destinationArea.getWidth(),
            destinationArea.getHeight(),
            source.getHandle(),
            sourceArea.getX(),
            sourceArea.getY(),
            SRCCOPY
          )
          == 0)
      {
        throw std::runtime_error{"Failed to transfer bits!"};
      }
    }
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto DeviceContext::getHandle() const -> HDC
  {
    // Check if device context handle is nullptr
    if (m_deviceContext == nullptr)
    {
      throw std::runtime_error{"Device context handle was nullptr!"};
    }

    // Return device context handle
    return m_deviceContext;
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Methods                                                       |*
  \*--------------------------------------------------------------------------*/

  auto DeviceContext::initialize(HDC deviceContext) -> void
  {
    try
    {
      // Assign device context based on type
      switch (m_action)
      {
      case Action::CREATE:
      {
        m_deviceContext = {CreateCompatibleDC(deviceContext)};
        break;
      }
      case Action::ACQUIRE:
      {
        m_deviceContext = {GetDC(nullptr)};
        break;
      }
      case Action::ACCESS:
      {
        m_deviceContext = {deviceContext};
        break;
      }
      }

      // Check if device context is valid
      if (m_deviceContext == nullptr)
      {
        throw std::runtime_error{
          "Failed to create/acquire/access device context!"
        };
      }

      // Save device context state
      m_savedState = {SaveDC(m_deviceContext)};

      // Check if device context state was saved
      if (m_savedState == 0)
      {
        throw std::runtime_error{"Failed to save device context state!"};
      }
    }
    catch (...)
    {
      cleanup();
      throw;
    }
  }

  auto DeviceContext::cleanup() noexcept -> void
  {
    // Check if device context was initialized
    if (m_deviceContext != nullptr)
    {
      // Check if device context state was saved
      if (m_savedState != 0)
      {
        // Restore device context state
        RestoreDC(m_deviceContext, m_savedState);
      }

      // Clean device context
      switch (m_action)
      {
      case Action::CREATE:
      {
        DeleteDC(m_deviceContext);
        break;
      }
      case Action::ACQUIRE:
      {
        ReleaseDC(nullptr, m_deviceContext);
        break;
      }
      case Action::ACCESS:
      {
        /*[Remark]:
         *---------------------------------------------------------------------*
         |   We should be releasing the device context of the window that was  |
         | passed to us. However, we only use our window's device context in   |
         | specific places where releasing resources are managed by the API.   |
         |   Example: BeginPaint and EndPaint functions.                       |
         *--------------------------------------------------------------------*/
        break;
      }
      }
    }

    // Reset fields
    m_action        = {Action::CREATE};
    m_deviceContext = {nullptr};
    m_savedState    = {};
  }
} // namespace Platform::Windows::GDI
