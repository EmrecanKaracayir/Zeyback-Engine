#include "pch.hpp"

#include "Platform/Windows/GDI/Icon.hpp"

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

  Icon::Icon(HINSTANCE instance, std::uint16_t resourceId)
    : m_instance{instance}
  {
    initialize(MAKEINTRESOURCE(resourceId));
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Destructor                                                     |*
  \*--------------------------------------------------------------------------*/

  Icon::~Icon() noexcept { cleanup(); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  auto Icon::reinitialize(HINSTANCE instance, std::uint16_t resourceId) -> void
  {
    // Clean instance
    cleanup();

    // Set fields
    m_instance = {instance};

    // Initialize Icon
    initialize(MAKEINTRESOURCE(resourceId));
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Icon::getHandle() const -> HICON
  {
    // Check if icon handle is nullptr
    if (m_icon == nullptr)
    {
      throw std::runtime_error{"Icon handle was nullptr!"};
    }

    // Return icon handle
    return m_icon;
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Methods                                                       |*
  \*--------------------------------------------------------------------------*/

  auto Icon::initialize(const gsl::wzstring& resourceString) -> void
  {
    try
    {
      // Create Icon
      m_icon = {LoadIcon(m_instance, resourceString)};

      if (m_icon == nullptr)
      {
        throw std::runtime_error{"Failed to create icon!"};
      }
    }
    catch (...)
    {
      cleanup();
      throw;
    }
  }

  auto Icon::cleanup() noexcept -> void
  {
    // Platform handles object cleanup

    // Reset fields
    m_instance = {nullptr};
    m_icon     = {nullptr};
  }
} // namespace Platform::Windows::GDI
