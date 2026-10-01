#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>

class Validator {
public:

    static bool isValidInterface(
        const std::string& interfaceName
    );

    static bool isValidLatency(
        const std::string& latency
    );

    static bool isValidPercentage(
        const std::string& percentage
    );
};

#endif
