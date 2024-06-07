#pragma once

#include <type_traits>

namespace Engine::Math
{
  template <typename T> requires std::is_arithmetic_v<T>
  class Rectangle
  {
  public:
    /*------------------------------------------------------------------------*\
    *| [public]: Types                                                        |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Constructors                                                 |*
    \*------------------------------------------------------------------------*/

    Rectangle(const Rectangle&) noexcept = default;
    Rectangle(Rectangle&&) noexcept      = default;
    Rectangle(T x, T y, T width, T height) noexcept;

    /*------------------------------------------------------------------------*\
    *| [public]: Destructor                                                   |*
    \*------------------------------------------------------------------------*/

    ~Rectangle() noexcept = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Operators                                                    |*
    \*------------------------------------------------------------------------*/

    auto operator=(const Rectangle&) noexcept -> Rectangle& = default;
    auto operator=(Rectangle&&) noexcept -> Rectangle&      = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Static methods                                               |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Static fields                                                |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Methods                                                      |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Fields                                                       |*
    \*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*\
    *| [public]: Accessors                                                    |*
    \*------------------------------------------------------------------------*/

    [[nodiscard]]
    auto getX() const noexcept -> T;
    [[nodiscard]]
    auto getY() const noexcept -> T;
    [[nodiscard]]
    auto getWidth() const noexcept -> T;
    [[nodiscard]]
    auto getHeight() const noexcept -> T;
    [[nodiscard]]
    auto getLeft() const noexcept -> T;
    [[nodiscard]]
    auto getTop() const noexcept -> T;
    [[nodiscard]]
    auto getRight() const noexcept -> T;
    [[nodiscard]]
    auto getBottom() const noexcept -> T;

    /*------------------------------------------------------------------------*\
    *| [public]: Mutators                                                     |*
    \*------------------------------------------------------------------------*/

    auto setX(T x) noexcept -> void;
    auto setY(T y) noexcept -> void;
    auto setWidth(T width) noexcept -> void;
    auto setHeight(T height) noexcept -> void;
    auto setLeft(T left) noexcept -> void;
    auto setTop(T top) noexcept -> void;
    auto setRight(T right) noexcept -> void;
    auto setBottom(T bottom) noexcept -> void;

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

    /*------------------------------------------------------------------------*\
    *| [private]: Fields                                                      |*
    \*------------------------------------------------------------------------*/

    T m_x{};
    T m_y{};
    T m_width{};
    T m_height{};

    /*------------------------------------------------------------------------*\
    *| [private]: Friends                                                     |*
    \*------------------------------------------------------------------------*/
  };
} // namespace Engine::Math

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<< Template Definitions >>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

namespace Engine::Math
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  template <typename T> requires std::is_arithmetic_v<T>
  Rectangle<T>::Rectangle(T x, T y, T width, T height) noexcept
    : m_x{x}
    , m_y{y}
    , m_width{width}
    , m_height{height}
  {}

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]]
  auto Rectangle<T>::getX() const noexcept -> T
  {
    return m_x;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]]
  auto Rectangle<T>::getY() const noexcept -> T
  {
    return m_y;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]]
  auto Rectangle<T>::getWidth() const noexcept -> T
  {
    return m_width;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]]
  auto Rectangle<T>::getHeight() const noexcept -> T
  {
    return m_height;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]]
  auto Rectangle<T>::getLeft() const noexcept -> T
  {
    return m_x;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]]
  auto Rectangle<T>::getTop() const noexcept -> T
  {
    return m_y;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]]
  auto Rectangle<T>::getRight() const noexcept -> T
  {
    return m_x + m_width;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]]
  auto Rectangle<T>::getBottom() const noexcept -> T
  {
    return m_y + m_height;
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Mutators                                                       |*
  \*--------------------------------------------------------------------------*/

  template <typename T> requires std::is_arithmetic_v<T>
  auto Rectangle<T>::setX(T x) noexcept -> void
  {
    m_x = x;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  auto Rectangle<T>::setY(T y) noexcept -> void
  {
    m_y = y;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  auto Rectangle<T>::setWidth(T width) noexcept -> void
  {
    m_width = width;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  auto Rectangle<T>::setHeight(T height) noexcept -> void
  {
    m_height = height;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  auto Rectangle<T>::setLeft(T left) noexcept -> void
  {
    m_x = left;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  auto Rectangle<T>::setTop(T top) noexcept -> void
  {
    m_y = top;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  auto Rectangle<T>::setRight(T right) noexcept -> void
  {
    m_width = right - m_x;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  auto Rectangle<T>::setBottom(T bottom) noexcept -> void
  {
    m_height = bottom - m_y;
  }
} // namespace Engine::Math
