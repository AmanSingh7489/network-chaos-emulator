#include "Validator.hpp"

#include <cctype>
#include <regex>

bool Validator::isValidInterface(
    const std::string& interfaceName
) {
    if (interfaceName.empty()) {
        return false;
    }

    for (char c : interfaceName) {

        if (!(std::isalnum(
                  static_cast<unsigned char>(c)
              ) ||
              c == '_' ||
              c == '-' ||
              c == '.')) {

            return false;
        }
    }

    return true;
}

bool Validator::isValidLatency(
    const std::string& latency
) {
    std::regex pattern(
        R"(^[0-9]+(ms|s)$)"
    );

    return std::regex_match(
        latency,
        pattern
    );
}

bool Validator::isValidPercentage(
    const std::string& percentage
) {
    std::regex pattern(
        R"(^(100|[0-9]{1,2})%$)"
    );

    return std::regex_match(
        percentage,
        pattern
    );
}
