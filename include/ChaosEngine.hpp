#ifndef CHAOS_ENGINE_HPP
#define CHAOS_ENGINE_HPP

#include "NetworkMonitor.hpp"

class ChaosEngine {
public:
    static bool runExperiment(
        const NetworkStats& baseline
    );

private:
    static bool applyChaos(
        const std::string& interfaceName
    );

    static bool clearChaos(
        const std::string& interfaceName
    );

    static void printComparison(
        const NetworkStats& baseline,
        const NetworkStats& degraded
    );
};

#endif
