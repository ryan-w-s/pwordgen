#include "pwordgen.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void print_usage(const std::string& program_name) {
    std::cout << "Usage: " << program_name << " [options]\n\n"
              << "Options:\n"
              << "  -l, --length <n>      Set password length (default: 16).\n"
              << "  --no-lowercase        Exclude lowercase characters.\n"
              << "  --no-uppercase        Exclude uppercase characters.\n"
              << "  --no-numbers          Exclude numbers.\n"
              << "  --no-symbols          Exclude symbols.\n"
              << "  -h, --help            Show this help message.\n";
}

int main(int argc, char* argv[]) {
    PasswordOptions options;
    std::vector<std::string> args(argv + 1, argv + argc);

    for (size_t i = 0; i < args.size(); ++i) {
        std::string& arg = args[i];

        if (arg == "-h" || arg == "--help") {
            print_usage(argv[0]);
            return 0;
        } else if ((arg == "-l" || arg == "--length")) {
            if (i + 1 < args.size()) {
                try {
                    options.length = std::stoi(args[++i]);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: Invalid number for length." << std::endl;
                    return 1;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: Length is out of range." << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Error: --length option requires an argument." << std::endl;
                return 1;
            }
        } else if (arg == "--no-lowercase") {
            options.use_lowercase = false;
        } else if (arg == "--no-uppercase") {
            options.use_uppercase = false;
        } else if (arg == "--no-numbers") {
            options.use_numbers = false;
        } else if (arg == "--no-symbols") {
            options.use_symbols = false;
        } else {
            std::cerr << "Error: Unknown option '" << arg << "'." << std::endl;
            print_usage(argv[0]);
            return 1;
        }
    }

    std::string password = generate_password(options);
    if (password.empty()) {
        std::cerr << "Error: Could not generate password. Ensure at least one character set is enabled." << std::endl;
        return 1;
    }

    std::cout << password << std::endl;

    return 0;
}
