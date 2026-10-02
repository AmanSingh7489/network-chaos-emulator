#include "ChaosEngine.hpp"

#include <cstdlib>
#include <iostream>
#include <string>


bool ChaosEngine::applyChaos(
    const std::string& interfaceName
) {
    std::cout
        << "\n[CHAOS] Applying controlled network latency...\n";

    /*
     * For the first experiment we use a fixed,
     * controlled 100 ms delay.
     *
     * Later, the engine will calculate this
     * automatically from baseline measurements.
     */

    std::string command =
        "sudo tc qdisc replace dev " +
        interfaceName +
        " root netem delay 100ms";

    int result =
        std::system(command.c_str());

    if (result != 0) {

        std::cerr
            << "[ERROR] Failed to apply network chaos.\n";

        return false;
    }

    std::cout
        << "[CHAOS] 100 ms latency applied successfully.\n";

    return true;
}


bool ChaosEngine::clearChaos(
    const std::string& interfaceName
) {
    std::cout
        << "\n[CHAOS] Restoring network configuration...\n";

    std::string command =
        "sudo tc qdisc del dev " +
        interfaceName +
        " root 2>/dev/null";

    int result =
        std::system(command.c_str());

    if (result != 0) {

        std::cout
            << "[CHAOS] Interface was already clear.\n";

        return true;
    }

    std::cout
        << "[CHAOS] Network configuration restored.\n";

    return true;
}


void ChaosEngine::printComparison(
    const NetworkStats& baseline,
    const NetworkStats& degraded
) {
    std::cout
        << "\n===============================================\n"
        << " CHAOS EXPERIMENT RESULT\n"
        << "===============================================\n";

    std::cout
        << "Metric              Baseline       After Chaos\n";

    std::cout
        << "-----------------------------------------------\n";

    std::cout
        << "Packet Loss         "
        << baseline.packetLoss
        << "%             "
        << degraded.packetLoss
        << "%\n";

    std::cout
        << "Average Latency     "
        << baseline.avgLatency
        << " ms          "
        << degraded.avgLatency
        << " ms\n";

    std::cout
        << "Minimum Latency     "
        << baseline.minLatency
        << " ms          "
        << degraded.minLatency
        << " ms\n";

    std::cout
        << "Maximum Latency     "
        << baseline.maxLatency
        << " ms          "
        << degraded.maxLatency
        << " ms\n";

    std::cout
        << "===============================================\n";

    double latencyIncrease =
        degraded.avgLatency -
        baseline.avgLatency;

    std::cout
        << "Latency Increase: "
        << latencyIncrease
        << " ms\n";
}


bool ChaosEngine::runExperiment(
    const NetworkStats& baseline
) {
    if (baseline.interfaceName.empty()) {

        std::cerr
            << "[ERROR] No network interface available.\n";

        return false;
    }

    // Step 1: Apply controlled impairment
    if (!applyChaos(
            baseline.interfaceName)) {

        return false;
    }

    // Step 2: Measure network after impairment
    std::cout
        << "\n[CHAOS] Measuring network under impairment...\n";

    NetworkStats degraded =
        NetworkMonitor::collect();

    // Step 3: Always restore the network
    clearChaos(
        baseline.interfaceName
    );

    if (!degraded.success) {

        std::cerr
            << "[ERROR] Failed to measure degraded network.\n";

        return false;
    }

    // Step 4: Compare measurements
    printComparison(
        baseline,
        degraded
    );

    return true;
}
