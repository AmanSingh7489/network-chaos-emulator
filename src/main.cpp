#include <iostream>
#include <string>

#include "Config.hpp"
#include "Validator.hpp"
#include "NetemController.hpp"
#include "NetworkMonitor.hpp"

void printHelp() {

    std::cout << "\n";
    std::cout << "===============================================\n";
    std::cout << " Network Latency & Packet-Loss Chaos Emulator\n";
    std::cout << "===============================================\n\n";

    std::cout << "Automatic mode:\n";
    std::cout << "  ./chaos-emulator\n\n";

    std::cout << "Manual options:\n";
    std::cout << "  --help                 Show help\n";
    std::cout << "  --interface <name>     Select interface\n";
    std::cout << "  --latency <value>      Add latency\n";
    std::cout << "  --jitter <value>       Add jitter\n";
    std::cout << "  --loss <percentage>    Add packet loss\n";
    std::cout << "  --clear                Clear configuration\n";
    std::cout << "  --status               Show configuration\n\n";
}


int main(int argc, char* argv[]) {

    /*
     * ==========================================
     * AUTOMATIC MODE
     * ==========================================
     *
     * Running:
     *
     *     ./chaos-emulator
     *
     * automatically discovers the network and
     * measures baseline performance.
     */

    if (argc == 1) {

        std::cout
            << "\n===============================================\n"
            << " Network Latency & Packet-Loss Chaos Emulator\n"
            << "===============================================\n";

        NetworkStats stats =
            NetworkMonitor::collect();

        if (!stats.success) {

            std::cerr
                << "\n[ERROR] Unable to collect network statistics.\n";

            return 1;
        }

        std::cout
            << "\n===============================================\n"
            << " BASELINE NETWORK SUMMARY\n"
            << "===============================================\n";

        std::cout
            << "Interface       : "
            << stats.interfaceName
            << "\n";

        std::cout
            << "IP Address      : "
            << stats.ipAddress
            << "\n";

        std::cout
            << "Gateway         : "
            << stats.gateway
            << "\n";

        std::cout
            << "Packets Sent    : "
            << stats.packetsSent
            << "\n";

        std::cout
            << "Packets Received: "
            << stats.packetsReceived
            << "\n";

        std::cout
            << "Packet Loss     : "
            << stats.packetLoss
            << "%\n";

        std::cout
            << "Min Latency     : "
            << stats.minLatency
            << " ms\n";

        std::cout
            << "Average Latency : "
            << stats.avgLatency
            << " ms\n";

        std::cout
            << "Max Latency     : "
            << stats.maxLatency
            << " ms\n";

        std::cout
            << "===============================================\n";

        return 0;
    }


    /*
     * ==========================================
     * MANUAL / ADVANCED MODE
     * ==========================================
     */

    NetworkConfig config;


    for (int i = 1; i < argc; i++) {

        std::string argument = argv[i];


        // HELP
        if (argument == "--help") {

            printHelp();
            return 0;
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
                    << config.latency
                    << "\n";

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
                    << config.jitter
                    << "\n";

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
                    << config.loss
                    << "\n";

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


        // UNKNOWN
        else {

            std::cerr
                << "[ERROR] Unknown option: "
                << argument
                << "\n";

            return 1;
        }
    }


    /*
     * ==========================================
     * EXECUTE MANUAL OPERATION
     * ==========================================
     */

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
        !config.jitter.empty() ||
        !config.loss.empty()) {

        return NetemController::apply(
            config
        ) ? 0 : 1;
    }


    std::cout
        << "\n[INFO] No operation specified.\n";

    printHelp();

    return 0;
}
