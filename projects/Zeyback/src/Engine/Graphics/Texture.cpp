#include "pch.hpp"

#include "Engine/Graphics/Texture.hpp"

#include "Engine/Math/Rectangle.tpp"
#include "Platform/Windows/GDI/Bitmap.hpp"
#include "Platform/Windows/GDI/Brush.hpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"

#include <windef.h>
#include <WinUser.h>

#include <cstdint>
#include <string>
#include <Support/util>

namespace
{
  // -------------------------< Namespace Aliases >-------------------------- //
  namespace GDI = Platform::Windows::GDI;
} // namespace

namespace Engine::Graphics
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  Texture::Texture(const std::wstring& filePath, bool transparency)
    : m_transparency{transparency}
  {
    initialize(filePath);
  }

  Texture::Texture(
    std::int32_t width, std::int32_t height, COLORREF color, bool transparency
  )
    : m_transparency{transparency}
  {
    initialize(width, height, color);
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Destructor                                                     |*
  \*--------------------------------------------------------------------------*/

  Texture::~Texture() { cleanup(); }

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  auto Texture::reinitialize(const std::wstring& filePath, bool transparency)
    -> void
  {
    // Clean instance
    cleanup();

    // Set fields
    m_transparency = {transparency};

    // Initialize
    initialize(filePath);
  }

  auto Texture::reinitialize(
    std::int32_t width, std::int32_t height, COLORREF color, bool transparency
  ) -> void
  {
    // Clean instance
    cleanup();

    // Set fields
    m_transparency = {transparency};

    // Initialize
    initialize(width, height, color);
  }

  auto Texture::render(
    const GDI::DeviceContext& deviceContext, std::int32_t x, std::int32_t y
  ) const -> void
  {
    // Create memory device context
    const GDI::DeviceContext memoryDeviceContext{
      GDI::DeviceContext::Action::CREATE, deviceContext.getHandle()
    };

    // Select the bitmap into the memory device context
    memoryDeviceContext.selectObject(m_bitmap.getHandle());

    // Render the bitmap
    deviceContext.transferBits(
      memoryDeviceContext,
      Math::Rectangle<std::int32_t>{
        0, 0, m_bitmap.getWidth(), m_bitmap.getHeight()
      },
      Math::Rectangle<std::int32_t>{
        x, y, m_bitmap.getWidth(), m_bitmap.getHeight()
      },
      m_transparency
    );
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Texture::getBitmap() const noexcept -> const GDI::Bitmap&
  {
    return m_bitmap;
  }

  [[nodiscard]]
  auto Texture::getWidth() const noexcept -> std::int32_t
  {
    return m_bitmap.getWidth();
  }

  [[nodiscard]]
  auto Texture::getHeight() const noexcept -> std::int32_t
  {
    return m_bitmap.getHeight();
  }

  /*--------------------------------------------------------------------------*\
  *| [private]: Methods                                                       |*
  \*--------------------------------------------------------------------------*/

  auto Texture::initialize(const std::wstring& filePath) -> void
  {
    try
    {
      // Load the bitmap
      m_bitmap.reinitialize(filePath);
    }
    catch (...)
    {
      cleanup();
      throw;
    }
  }

  auto Texture::initialize(
    std::int32_t width, std::int32_t height, COLORREF color
  ) -> void
  {
    try
    {
      // Get screen device context
      const GDI::DeviceContext screenDeviceContext{
        GDI::DeviceContext::Action::ACQUIRE
      };

      // Create bitmap
      m_bitmap.reinitialize(screenDeviceContext.getHandle(), width, height);

      // Create memory device context
      const GDI::DeviceContext memoryDeviceContext{
        GDI::DeviceContext::Action::CREATE, screenDeviceContext.getHandle()
      };

      // Select the bitmap into the memory device context
      memoryDeviceContext.selectObject(m_bitmap.getHandle());

      // Create the brush
      const GDI::Brush brush{color};

      // Fill the bitmap with the brush
      const RECT rect{0, 0, width, height};
      FillRect(memoryDeviceContext.getHandle(), &rect, brush.getHandle());
    }
    catch (...)
    {
      cleanup();
      throw;
    }
  }

  auto Texture::cleanup() noexcept -> void
  {
    // Reset fields
    // m_bitmap: Automatic cleanup
    m_transparency = {false};
  }
} // namespace Engine::Graphics
