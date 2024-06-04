#include "pch.hpp"

#include "Platform/Windows/GDI/Bitmap.hpp"

#include "Engine/File/Util/path.hpp"

#include <minwindef.h>
#include <windef.h>
#include <wingdi.h>
#include <winnt.h>
#include <WinUser.h>

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <Support/util>

namespace Platform::Windows::GDI
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  Bitmap::Bitmap(const std::wstring& filePath) { initialize(filePath); }

  Bitmap::Bitmap(HDC deviceContext, std::int32_t width, std::int32_t height)
    : m_width{width}
    , m_height{height}
  {
    initialize(deviceContext);
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Destructor                                                     |*
  \*--------------------------------------------------------------------------*/

  Bitmap::~Bitmap() { cleanup(); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  auto Bitmap::reinitialize(const std::wstring& filePath) -> void
  {
    // Clean instance
    cleanup();

    // Initialize
    initialize(filePath);
  }

  auto Bitmap::reinitialize(
    HDC deviceContext, std::int32_t width, std::int32_t height
  ) -> void
  {
    // Clean instance
    cleanup();

    // Set fields
    m_width  = {width};
    m_height = {height};

    // Initialize
    initialize(deviceContext);
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Bitmap::getHandle() const -> HBITMAP
  {
    // Check if bitmap handle is nullptr
    if (m_bitmap == nullptr)
    {
      throw std::runtime_error{"Bitmap handle was nullptr!"};
    }

    // Return bitmap handle
    return m_bitmap;
  }

  [[nodiscard]]
  auto Bitmap::getWidth() const noexcept -> std::int32_t
  {
    return m_width;
  }

  [[nodiscard]]
  auto Bitmap::getHeight() const noexcept -> std::int32_t
  {
    return m_height;
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Methods                                                       |*
  \*--------------------------------------------------------------------------*/

  auto Bitmap::initialize(const std::wstring& filePath) -> void
  {
    try
    {
      // Get full path
      std::array<TCHAR, MAX_PATH> fullPath{};
      Engine::File::Util::getFullPath(filePath, fullPath);

      // Load the bitmap
      m_bitmap = {static_cast<HBITMAP>(
        LoadImage(nullptr, fullPath.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)
      )};

      // Check if bitmap is valid
      if (m_bitmap == nullptr)
      {
        throw std::runtime_error{"Failed to load bitmap!"};
      }

      // Get the bitmap information
      BITMAP bitmap{};

      // Check if the bitmap information was retrieved
      if (GetObject(m_bitmap, sizeof(BITMAP), &bitmap) == 0)
      {
        throw std::runtime_error{"Failed to get bitmap information!"};
      }

      // Set the width and height
      m_width  = {bitmap.bmWidth};
      m_height = {bitmap.bmHeight};
    }
    catch (...)
    {
      cleanup();
      throw;
    }
  }

  auto Bitmap::initialize(HDC deviceContext) -> void
  {
    try
    {
      // Create a bitmap
      m_bitmap = {CreateCompatibleBitmap(deviceContext, m_width, m_height)};

      // Check if bitmap is valid
      if (m_bitmap == nullptr)
      {
        throw std::runtime_error{"Failed to create bitmap!"};
      }
    }
    catch (...)
    {
      cleanup();
      throw;
    }
  }

  auto Bitmap::cleanup() noexcept -> void
  {
    // Check if bitmap was initialized
    if (m_bitmap != nullptr)
    {
      DeleteObject(m_bitmap);
    }

    // Reset fields
    m_bitmap = {};
    m_width  = {};
    m_height = {};
  }
} // namespace Platform::Windows::GDI
