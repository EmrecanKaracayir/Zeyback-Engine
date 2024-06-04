#include "pch.hpp"

#include "Platform/Windows/GDI/Brush.hpp"

#include <windef.h>
#include <wingdi.h>

#include <stdexcept>

namespace Platform::Windows::GDI
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  Brush::Brush(COLORREF color) { initialize(color); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Destructor                                                     |*
  \*--------------------------------------------------------------------------*/

  Brush::~Brush() { cleanup(); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  auto Brush::reinitialize(COLORREF color) -> void
  {
    // Clean instance
    cleanup();

    // Initialize brush
    initialize(color);
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

  auto Brush::initialize(COLORREF color) -> void
  {
    try
    {
      // Create brush
      m_brush = {CreateSolidBrush(color)};

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
