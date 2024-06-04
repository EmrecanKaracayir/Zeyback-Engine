#pragma once

#include <windef.h>

#include <cstdint>
#include <string>

namespace Platform::Windows::GDI
{
  class Bitmap
  {
  public:
    /*------------------------------------------------------------------------*\
    *| [public]: Types                                                        |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Constructors                                                 |*
    \*------------------------------------------------------------------------*/

    Bitmap(const Bitmap&) noexcept = delete;
    Bitmap(Bitmap&&) noexcept      = delete;
    Bitmap() noexcept              = default;
    explicit Bitmap(const std::wstring& filePath);
    Bitmap(HDC deviceContext, std::int32_t width, std::int32_t height);

    /*------------------------------------------------------------------------*\
    *| [public]: Destructor                                                   |*
    \*------------------------------------------------------------------------*/

    ~Bitmap();

    /*------------------------------------------------------------------------*\
    *| [public]: Operators                                                    |*
    \*------------------------------------------------------------------------*/

    auto operator=(const Bitmap&) noexcept -> Bitmap& = delete;
    auto operator=(Bitmap&&) noexcept -> Bitmap&      = delete;

    /*------------------------------------------------------------------------*\
    *| [public]: Static methods                                               |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Static fields                                                |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Methods                                                      |*
    \*------------------------------------------------------------------------*/

    auto reinitialize(const std::wstring& filePath) -> void;
    auto reinitialize(
      HDC deviceContext, std::int32_t width, std::int32_t height
    ) -> void;

    /*------------------------------------------------------------------------*\
    *| [public]: Fields                                                       |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Accessors                                                    |*
    \*------------------------------------------------------------------------*/

    [[nodiscard]]
    auto getHandle() const -> HBITMAP;
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
    auto initialize(HDC deviceContext) -> void;
    auto cleanup() noexcept -> void;

    /*------------------------------------------------------------------------*\
    *| [private]: Fields                                                      |*
    \*------------------------------------------------------------------------*/

    HBITMAP      m_bitmap{nullptr};
    std::int32_t m_width{};
    std::int32_t m_height{};

    /*------------------------------------------------------------------------*\
    *| [private]: Friends                                                     |*
    \*------------------------------------------------------------------------*/
  };
} // namespace Platform::Windows::GDI