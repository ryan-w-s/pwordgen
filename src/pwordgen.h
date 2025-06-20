#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define PWORDGEN_EXPORT __declspec(dllexport)
#else
  #define PWORDGEN_EXPORT
#endif

PWORDGEN_EXPORT void pwordgen();
PWORDGEN_EXPORT void pwordgen_print_vector(const std::vector<std::string> &strings);
