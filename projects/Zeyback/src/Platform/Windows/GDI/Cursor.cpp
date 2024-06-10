#include "pch.hpp"

#include "Platform/Windows/GDI/Cursor.hpp"

#include <minwindef.h>
#include <windef.h>
#include <WinUser.h>

#include <cstdint>
#include <stdexcept>
#include <Support/zstring>

namespace Platform::Windows::GDI
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  Cursor::Cursor(HINSTANCE instance, std::uint16_t resourceId)
    : m_instance{instance}
  {
    initialize(MAKEINTRESOURCE(resourceId));
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Destructor                                                     |*
  \*--------------------------------------------------------------------------*/

  Cursor::~Cursor() noexcept { cleanup(); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  auto Cursor::reinitialize(HINSTANCE instance, std::uint16_t resourceId)
    -> void
  {
    // Clean instance
    cleanup();

    // Set fields
    m_instance = {instance};

    // Initialize cursor
    initialize(MAKEINTRESOURCE(resourceId));
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Cursor::getHandle() const -> HCURSOR
  {
    // Check if cursor handle is nullptr
    if (m_cursor == nullptr)
    {
      throw std::runtime_error{"Cursor handle was nullptr!"};
    }

    // Return cursor handle
    return m_cursor;
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Methods                                                       |*
  \*--------------------------------------------------------------------------*/

  auto Cursor::initialize(const gsl::wzstring& resourceString) -> void
  {
    try
    {
      // Create Cursor
      m_cursor = {LoadCursor(m_instance, resourceString)};

      if (m_cursor == nullptr)
      {
        throw std::runtime_error{"Failed to create cursor!"};
      }
    }
    catch (...)
    {
      cleanup();
      throw;
    }
  }

  auto Cursor::cleanup() noexcept -> void
  {
    // Platform handles object cleanup

    // Reset fields
    m_instance = {nullptr};
    m_cursor   = {nullptr};
  }
} // namespace Platform::Windows::GDI
