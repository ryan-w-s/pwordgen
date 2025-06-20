#include "pwordgen.h"
#include <vector>
#include <string>

int main() {
    pwordgen();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    pwordgen_print_vector(vec);
}
