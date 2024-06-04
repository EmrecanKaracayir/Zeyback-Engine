#pragma once

#include "Platform/Windows/GDI/Bitmap.hpp"
#include "Platform/Windows/GDI/DeviceContext.hpp"

#include <windef.h>

#include <cstdint>
#include <string>

namespace Engine::Graphics
{
  class Texture
  {
  public:
    /*------------------------------------------------------------------------*\
    *| [public]: Types                                                        |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Constructors                                                 |*
    \*------------------------------------------------------------------------*/

    Texture(const Texture&) noexcept = delete;
    Texture(Texture&&) noexcept      = delete;
    Texture() noexcept               = default;
    Texture(const std::wstring& filePath, bool transparency);
    Texture(
      std::int32_t width, std::int32_t height, COLORREF color, bool transparency
    );

    /*------------------------------------------------------------------------*\
    *| [public]: Destructor                                                   |*
    \*------------------------------------------------------------------------*/

    ~Texture();

    /*------------------------------------------------------------------------*\
    *| [public]: Operators                                                    |*
    \*------------------------------------------------------------------------*/

    auto operator=(const Texture&) noexcept -> Texture& = delete;
    auto operator=(Texture&&) noexcept -> Texture&      = delete;

    /*------------------------------------------------------------------------*\
    *| [public]: Static methods                                               |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Static fields                                                |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Methods                                                      |*
    \*------------------------------------------------------------------------*/

    auto reinitialize(const std::wstring& filePath, bool transparency) -> void;
    auto reinitialize(
      std::int32_t width, std::int32_t height, COLORREF color, bool transparency
    ) -> void;
    auto render(
      const Platform::Windows::GDI::DeviceContext& deviceContext,
      std::int32_t                                 x,
      std::int32_t                                 y
    ) const -> void;

    /*------------------------------------------------------------------------*\
    *| [public]: Fields                                                       |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Accessors                                                    |*
    \*------------------------------------------------------------------------*/

    [[nodiscard]]
    auto getBitmap() const noexcept -> const Platform::Windows::GDI::Bitmap&;
    [[nodiscard]]
    auto getWidth() const noexcept -> std::int32_t;
    [[nodiscard]]
    auto getHeight() const noexcept -> std::int32_t;

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

    /*------------------------------------------------------------------------*\
    *| [private]: Destructor                                                  |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Operators                                                   |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Static methods                                              |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Static fields                                               |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [private]: Methods                                                     |*
    \*------------------------------------------------------------------------*/

    auto initialize(const std::wstring& filePath) -> void;
    auto initialize(std::int32_t width, std::int32_t height, COLORREF color)
      -> void;
    auto cleanup() noexcept -> void;

    /*------------------------------------------------------------------------*\
    *| [private]: Fields                                                      |*
    \*------------------------------------------------------------------------*/

    Platform::Windows::GDI::Bitmap m_bitmap;
    bool                           m_transparency{false};

    /*------------------------------------------------------------------------*\
    *| [private]: Friends                                                     |*
    \*------------------------------------------------------------------------*/
  };
} // namespace Engine::Graphics
