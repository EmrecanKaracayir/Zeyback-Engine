#include "pch.hpp"

#include "Platform/Windows/GDI/Color.hpp"

#include <windef.h>
#include <wingdi.h>

#include <cstdint>

namespace Platform::Windows::GDI
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue) noexcept
    : m_color{RGB(red, green, blue)}
  {}

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  [[nodiscard]]
  auto Color::getReference() const noexcept -> COLORREF
  {
    return m_color;
  }

  [[nodiscard]]
  auto Color::getRed() const noexcept -> std::uint8_t
  {
    return GetRValue(m_color);
  }

  [[nodiscard]]
  auto Color::getGreen() const noexcept -> std::uint8_t
  {
    return GetGValue(m_color);
  }

  [[nodiscard]]
  auto Color::getBlue() const noexcept -> std::uint8_t
  {
    return GetBValue(m_color);
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Mutators                                                       |*
  \*--------------------------------------------------------------------------*/

  auto Color::setReference(
    std::uint8_t red, std::uint8_t green, std::uint8_t blue
  ) noexcept -> void
  {
    m_color = RGB(red, green, blue);
  }

  auto Color::setRed(std::uint8_t red) noexcept -> void
  {
    m_color = RGB(red, getGreen(), getBlue());
  }

  auto Color::setGreen(std::uint8_t green) noexcept -> void
  {
    m_color = RGB(getRed(), green, getBlue());
  }

  auto Color::setBlue(std::uint8_t blue) noexcept -> void
  {
    m_color = RGB(getRed(), getGreen(), blue);
  }

} // namespace Platform::Windows::GDI
