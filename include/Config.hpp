#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

struct NetworkConfig {

    std::string interfaceName = "lo";

    std::string latency;
    std::string jitter;
    std::string loss;

    bool clear = false;
    bool status = false;
};

#endif
