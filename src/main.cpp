#include <iostream>
#include <string>

#include "NetworkMonitor.hpp"
#include "ChaosEngine.hpp"


int main(int argc, char* argv[])
{
   

    if (argc == 1)
    {
        std::cout
            << "\n===============================================\n"
            << "   NETWORK LATENCY & PACKET-LOSS CHAOS EMULATOR\n"
            << "===============================================\n";

       
        NetworkStats stats = NetworkMonitor::collect();

        if (!stats.success)
        {
            std::cerr
                << "\n[ERROR] Failed to collect baseline network data.\n";

            return 1;
        }

     
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


       

        std::cout
            << "\n[ENGINE] Starting chaos experiment...\n";

        bool result =
            ChaosEngine::runExperiment(stats);


        
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


    

    std::cerr
        << "\n[ERROR] Unknown arguments.\n"
        << "Run './chaos-emulator --help' for usage.\n";

    return 1;
}
