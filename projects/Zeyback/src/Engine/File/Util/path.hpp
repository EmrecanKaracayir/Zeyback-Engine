#pragma once

#include <minwindef.h>
#include <winnt.h>

#include <array>
#include <string>

namespace Engine::File::Util
{
  auto getFullPath(
    const std::wstring& path, std::array<TCHAR, MAX_PATH>& buffer
  ) noexcept -> void;
}
