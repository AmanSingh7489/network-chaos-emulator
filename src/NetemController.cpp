#include "NetemController.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>

bool NetemController::apply(
    const NetworkConfig& config
) {
    std::stringstream command;

    command << "sudo tc qdisc replace dev "
            << config.interfaceName
            << " root netem";

    if (!config.latency.empty()) {

        command << " delay "
                << config.latency;

        if (!config.jitter.empty()) {
            command << " "
                    << config.jitter;
        }
    if (config.clear) {
        return NetemController::clear(
            config.interfaceName
        ) ? 0 : 1;
    }

    if (config.status) {
        return NetemController::show(
            config.interfaceName
        ) ? 0 : 1;
    }

    if (!config.latency.empty() ||
        !config.loss.empty()) {

        return NetemController::apply(
            config
        ) ? 0 : 1;
    }

    std::cout << "\n[CONFIGURATION]\n";
    std::cout << "Interface : "
              << config.interfaceName << "\n";

    return 0;
    }

    if (!config.loss.empty()) {

        command << " loss "
                << config.loss;
    }

    std::cout << "[INFO] Applying network configuration...\n";

    std::cout << "[COMMAND] "
              << command.str()
              << "\n";

    int result = std::system(
        command.str().c_str()
    );

    if (result == 0) {

        std::cout
            << "[SUCCESS] Network configuration applied.\n";

        return true;
    }

    std::cerr
        << "[ERROR] Failed to apply network configuration.\n";

    return false;
}


bool NetemController::clear(
    const std::string& interfaceName
) {
    std::string command =
        "sudo tc qdisc del dev " +
        interfaceName +
        " root";

    std::cout
        << "[INFO] Clearing network configuration...\n";

    int result = std::system(
        command.c_str()
    );

    if (result == 0) {

        std::cout
            << "[SUCCESS] Network configuration cleared.\n";

        return true;
    }

    std::cerr
        << "[ERROR] Failed to clear configuration.\n";

    return false;
}


bool NetemController::show(
    const std::string& interfaceName
) {
    std::string command =
        "tc qdisc show dev " +
        interfaceName;

    std::cout
        << "[INFO] Current network configuration:\n";

    int result = std::system(
        command.c_str()
    );

    return result == 0;
}
