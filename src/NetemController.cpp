#include "NetemController.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

bool NetemController::apply(
    const NetworkConfig& config
) {
    std::stringstream command;

    command << "sudo tc qdisc replace dev "
            << config.interfaceName
            << " root netem";

    // Add latency and jitter
    if (!config.latency.empty()) {

        command << " delay "
                << config.latency;

        if (!config.jitter.empty()) {
            command << " "
                    << config.jitter;
        }
    }

    // Add packet loss
    if (!config.loss.empty()) {

        command << " loss "
                << config.loss;
    }

    std::cout
        << "[INFO] Applying network configuration...\n";

    std::cout
        << "[COMMAND] "
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
    // First check whether netem is actually active.
    std::string checkCommand =
        "tc qdisc show dev " +
        interfaceName;

    FILE* pipe = popen(
        checkCommand.c_str(),
        "r"
    );

    if (pipe == nullptr) {

        std::cerr
            << "[ERROR] Unable to inspect interface.\n";

        return false;
    }

    char buffer[256];
    std::string output;

    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }

    pclose(pipe);

    // Already clear
    if (output.find("netem") == std::string::npos) {

        std::cout
            << "[INFO] No netem configuration found.\n";

        std::cout
            << "[SUCCESS] Interface is already clear.\n";

        return true;
    }

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
