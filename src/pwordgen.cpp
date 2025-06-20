#include "pwordgen.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

std::string generate_password(const PasswordOptions& options) {
    if (options.length <= 0) {
        return "";
    }

    const std::string lower_chars = "abcdefghijklmnopqrstuvwxyz";
    const std::string upper_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string number_chars = "0123456789";
    const std::string symbol_chars = "!@#$%^&*()_+-=[]{}|;':,./<>?";

    std::string char_pool;
    std::vector<char> password_guaranteed_chars;

    // Use a random device and a high-resolution clock to seed the generator for better randomness.
    std::mt19937 generator(std::random_device{}() ^ (unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count());

    if (options.use_lowercase) {
        char_pool += lower_chars;
        password_guaranteed_chars.push_back(lower_chars[std::uniform_int_distribution<int>(0, lower_chars.length() - 1)(generator)]);
    }
    if (options.use_uppercase) {
        char_pool += upper_chars;
        password_guaranteed_chars.push_back(upper_chars[std::uniform_int_distribution<int>(0, upper_chars.length() - 1)(generator)]);
    }
    if (options.use_numbers) {
        char_pool += number_chars;
        password_guaranteed_chars.push_back(number_chars[std::uniform_int_distribution<int>(0, number_chars.length() - 1)(generator)]);
    }
    if (options.use_symbols) {
        char_pool += symbol_chars;
        password_guaranteed_chars.push_back(symbol_chars[std::uniform_int_distribution<int>(0, symbol_chars.length() - 1)(generator)]);
    }

    if (char_pool.empty()) {
        return ""; // No character sets selected.
    }
    
    // The final password characters will be stored here
    std::vector<char> password_chars;

    // If the length is too short to have one of each guaranteed character, we abandon the guarantee and just pull from the pool.
    if (options.length < password_guaranteed_chars.size()) {
        password_guaranteed_chars.clear();
    }

    // Add the guaranteed characters to the password
    for (char c : password_guaranteed_chars) {
        password_chars.push_back(c);
    }
    
    // Fill the rest of the password length with random characters from the entire pool
    int remaining_length = options.length - password_chars.size();
    if (remaining_length > 0) {
        std::uniform_int_distribution<int> distribution(0, char_pool.length() - 1);
        for (int i = 0; i < remaining_length; ++i) {
            password_chars.push_back(char_pool[distribution(generator)]);
        }
    }

    // Shuffle the entire password to mix guaranteed and random characters
    std::shuffle(password_chars.begin(), password_chars.end(), generator);
    
    // Construct the final string
    std::string password(password_chars.begin(), password_chars.end());

    return password;
} 