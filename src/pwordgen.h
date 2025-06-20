#pragma once

#include <string>

#ifdef _WIN32
  #define PWORDGEN_EXPORT __declspec(dllexport)
#else
  #define PWORDGEN_EXPORT
#endif

struct PasswordOptions {
    int length = 16;
    bool use_lowercase = true;
    bool use_uppercase = true;
    bool use_numbers = true;
    bool use_symbols = true;
};

PWORDGEN_EXPORT std::string generate_password(const PasswordOptions& options);
