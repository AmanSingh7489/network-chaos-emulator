#include <iostream>
#include <string>

#include "NetworkMonitor.hpp"
#include "ChaosEngine.hpp"


int main(int argc, char* argv[])
{
    // ============================================================
    // AUTOMATIC MODE
    // Run simply with:
    //
    // ./chaos-emulator
    //
    // ============================================================

    if (argc == 1)
    {
        std::cout
            << "\n===============================================\n"
            << "   NETWORK LATENCY & PACKET-LOSS CHAOS EMULATOR\n"
            << "===============================================\n";

        // --------------------------------------------------------
        // STEP 1: Detect network and measure baseline
        // --------------------------------------------------------

        NetworkStats stats = NetworkMonitor::collect();

        if (!stats.success)
        {
            std::cerr
                << "\n[ERROR] Failed to collect baseline network data.\n";

            return 1;
        }

        // --------------------------------------------------------
        // STEP 2: Display baseline results
        // --------------------------------------------------------

        std::cout
            << "\n===============================================\n"
            << " BASELINE NETWORK SUMMARY\n"
            << "===============================================\n";

        std::cout
            << "Interface        : "
            << stats.interfaceName
            << "\n";

        std::cout
            << "IP Address       : "
            << stats.ipAddress
            << "\n";

        std::cout
            << "Gateway          : "
            << stats.gateway
            << "\n";

        std::cout
            << "Packets Sent     : "
            << stats.packetsSent
            << "\n";

        std::cout
            << "Packets Received : "
            << stats.packetsReceived
            << "\n";

        std::cout
            << "Packet Loss      : "
            << stats.packetLoss
            << "%\n";

        std::cout
            << "Min Latency      : "
            << stats.minLatency
            << " ms\n";

        std::cout
            << "Average Latency  : "
            << stats.avgLatency
            << " ms\n";

        std::cout
            << "Max Latency      : "
            << stats.maxLatency
            << " ms\n";

        std::cout
            << "===============================================\n";


        // --------------------------------------------------------
        // STEP 3: Start Chaos Engine
        // --------------------------------------------------------

        std::cout
            << "\n[ENGINE] Starting chaos experiment...\n";

        bool result =
            ChaosEngine::runExperiment(stats);


        // --------------------------------------------------------
        // STEP 4: Return experiment status
        // --------------------------------------------------------

        if (!result)
        {
            std::cerr
                << "\n[ERROR] Chaos experiment failed.\n";

            return 1;
        }

        std::cout
            << "\n===============================================\n"
            << " EXPERIMENT COMPLETED SUCCESSFULLY\n"
            << "===============================================\n";

        return 0;
    }


    // ============================================================
    // HELP
    // ============================================================

    if (argc == 2 &&
        std::string(argv[1]) == "--help")
    {
        std::cout
            << "\nNetwork Latency & Packet-Loss Chaos Emulator\n\n"
            << "Usage:\n"
            << "  ./chaos-emulator\n\n"
            << "Automatic mode:\n"
            << "  Detects the network automatically and runs\n"
            << "  a controlled chaos experiment.\n\n"
            << "Options:\n"
            << "  --help    Show this help message\n";

        return 0;
    }


    // ============================================================
    // INVALID ARGUMENTS
    // ============================================================

    std::cerr
        << "\n[ERROR] Unknown arguments.\n"
        << "Run './chaos-emulator --help' for usage.\n";

    return 1;
}
