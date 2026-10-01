#include <iostream>
#include <string>

#include "Config.hpp"
#include "Validator.hpp"
#include "NetemController.hpp"

void printHelp() {

    std::cout << "\n";
    std::cout << "===============================================\n";
    std::cout << " Network Latency & Packet-Loss Chaos Emulator\n";
    std::cout << "===============================================\n\n";

    std::cout << "Usage:\n";
    std::cout << "  ./chaos-emulator [options]\n\n";

    std::cout << "Options:\n";
    std::cout << "  --help                 Show this help message\n";
    std::cout << "  --interface <name>     Select network interface\n";
    std::cout << "  --latency <value>      Add network latency\n";
    std::cout << "  --jitter <value>       Add latency variation\n";
    std::cout << "  --loss <percentage>    Add packet loss\n";
    std::cout << "  --clear                Clear network configuration\n";
    std::cout << "  --status               Show current configuration\n\n";
}


int main(int argc, char* argv[]) {

    NetworkConfig config;

    // No arguments
    if (argc == 1) {
        printHelp();
        return 0;
    }


    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {

        std::string argument = argv[i];


        // HELP
        if (argument == "--help") {

            printHelp();
        }


        // INTERFACE
        else if (argument == "--interface") {

            if (i + 1 >= argc) {

                std::cerr
                    << "[ERROR] --interface requires a value.\n";

                return 1;
            }

            config.interfaceName = argv[++i];

            if (!Validator::isValidInterface(
                    config.interfaceName)) {

                std::cerr
                    << "[ERROR] Invalid interface name.\n";

                return 1;
            }
        }


        // LATENCY
        else if (argument == "--latency") {

            if (i + 1 >= argc) {

                std::cerr
                    << "[ERROR] --latency requires a value.\n";

                return 1;
            }

            config.latency = argv[++i];

            if (!Validator::isValidLatency(
                    config.latency)) {

                std::cerr
                    << "[ERROR] Invalid latency value: "
                    << config.latency << "\n";

                return 1;
            }
        }


        // JITTER
        else if (argument == "--jitter") {

            if (i + 1 >= argc) {

                std::cerr
                    << "[ERROR] --jitter requires a value.\n";

                return 1;
            }

            config.jitter = argv[++i];

            if (!Validator::isValidLatency(
                    config.jitter)) {

                std::cerr
                    << "[ERROR] Invalid jitter value: "
                    << config.jitter << "\n";

                return 1;
            }
        }


        // PACKET LOSS
        else if (argument == "--loss") {

            if (i + 1 >= argc) {

                std::cerr
                    << "[ERROR] --loss requires a value.\n";

                return 1;
            }

            config.loss = argv[++i];

            if (!Validator::isValidPercentage(
                    config.loss)) {

                std::cerr
                    << "[ERROR] Invalid packet loss value: "
                    << config.loss << "\n";

                return 1;
            }
        }


        // CLEAR
        else if (argument == "--clear") {

            config.clear = true;
        }


        // STATUS
        else if (argument == "--status") {

            config.status = true;
        }


        // UNKNOWN OPTION
        else {

            std::cerr
                << "[ERROR] Unknown option: "
                << argument << "\n";

            return 1;
        }
    }


    // ==============================
    // EXECUTE REQUESTED OPERATION
    // ==============================

    // CLEAR
    if (config.clear) {

        return NetemController::clear(
            config.interfaceName
        ) ? 0 : 1;
    }


    // STATUS
    if (config.status) {

        return NetemController::show(
            config.interfaceName
        ) ? 0 : 1;
    }


    // APPLY NETWORK CONFIGURATION
    if (!config.latency.empty() ||
        !config.jitter.empty() ||
        !config.loss.empty()) {

        return NetemController::apply(
            config
        ) ? 0 : 1;
    }


    // NOTHING TO EXECUTE
    std::cout << "\n[CONFIGURATION]\n";

    std::cout << "Interface : "
              << config.interfaceName
              << "\n";

    return 0;
}
