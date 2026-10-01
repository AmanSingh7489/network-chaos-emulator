#ifndef NETEM_CONTROLLER_HPP
#define NETEM_CONTROLLER_HPP

#include "Config.hpp"

class NetemController {
public:

    static bool apply(const NetworkConfig& config);

    static bool clear(const std::string& interfaceName);

    static bool show(const std::string& interfaceName);
};

#endif
