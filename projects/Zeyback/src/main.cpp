#include "pch.hpp"

#include "App/App.hpp"

#include <minwindef.h>
#include <sal.h>
#include <winnt.h>

#include <cstdlib>
#include <Support/util>

// NOLINTBEGIN(readability-inconsistent-declaration-parameter-name)

auto WINAPI WinMain(
  _In_ HINSTANCE instance,
  _In_opt_       HINSTANCE /*unused*/,
  _In_           LPSTR /*unused*/,
  _In_ int /*unused*/
) -> int
{
  // Get instance
  auto& app = App::App::getInstance();

  // Initialize the application
  if (not app.onCreate(instance))
  {
    return EXIT_FAILURE;
  }

  // Run the application
  return gsl::narrow_cast<int>(App::App::run());
}

// NOLINTEND(readability-inconsistent-declaration-parameter-name)
