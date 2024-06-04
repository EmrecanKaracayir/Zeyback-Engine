#include "pch.hpp"

#include "Engine/File/Util/path.hpp"

#include <fileapi.h>
#include <minwindef.h>
#include <winnt.h>

#include <array>
#include <string>

namespace Engine::File::Util
{
  auto getFullPath(
    const std::wstring& path, std::array<TCHAR, MAX_PATH>& buffer
  ) noexcept -> void
  {
    // Write the full path to the buffer
    GetFullPathName(path.c_str(), MAX_PATH, buffer.data(), nullptr);
  }
} // namespace Engine::File::Util
