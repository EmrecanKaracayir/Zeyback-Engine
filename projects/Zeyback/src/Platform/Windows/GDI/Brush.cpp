#include "pch.hpp"

#include "Platform/Windows/GDI/Brush.hpp"

#include "Engine/Math/Rectangle.tpp"
#include "Platform/Windows/GDI/Color.hpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"

#include <windef.h>
#include <wingdi.h>
#include <WinUser.h>

#include <cstdint>
#include <stdexcept>

namespace
{
  // -------------------------< Namespace Aliases >-------------------------- //
  namespace Math = Engine::Math;
} // namespace

namespace Platform::Windows::GDI
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  Brush::Brush(const Color& color) { initialize(color); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Destructor                                                     |*
  \*--------------------------------------------------------------------------*/

  Brush::~Brush() noexcept { cleanup(); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  auto Brush::reinitialize(const Color& color) -> void
  {
    // Clean instance
    cleanup();

    // Initialize brush
    initialize(color);
  }

  auto Brush::fillRect(
    const DeviceContext&                 deviceContext,
    const Math::Rectangle<std::int32_t>& rectangle
  ) const -> void
  {
    // Create WinAPI Rect
    const RECT rect{
      rectangle.getLeft(),
      rectangle.getTop(),
      rectangle.getRight(),
      rectangle.getBottom()
    };

    // Fill rectangle
    FillRect(deviceContext.getHandle(), &rect, m_brush);
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Brush::getHandle() const -> HBRUSH
  {
    // Check if brush handle is nullptr
    if (m_brush == nullptr)
    {
      throw std::runtime_error{"Brush handle was nullptr!"};
    }

    // Return brush handle
    return m_brush;
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Methods                                                       |*
  \*--------------------------------------------------------------------------*/

  auto Brush::initialize(const Color& color) -> void
  {
    try
    {
      // Create brush
      m_brush = {CreateSolidBrush(color.getReference())};

      if (m_brush == nullptr)
      {
        throw std::runtime_error{"Failed to create brush!"};
      }
    }
    catch (...)
    {
      cleanup();
      throw;
    }
  }

  auto Brush::cleanup() noexcept -> void
  {
    // Check if brush was initialized
    if (m_brush != nullptr)
    {
      DeleteObject(m_brush);
    }

    // Reset fields
    m_brush = {nullptr};
  }
} // namespace Platform::Windows::GDI
