#ifndef NETWORK_MONITOR_HPP
#define NETWORK_MONITOR_HPP

#include <string>

struct NetworkStats {
    std::string interfaceName;
    std::string ipAddress;
    std::string gateway;

    double packetLoss = 0.0;
    double minLatency = 0.0;
    double avgLatency = 0.0;
    double maxLatency = 0.0;

    int packetsSent = 0;
    int packetsReceived = 0;

    bool success = false;
};

class NetworkMonitor {
public:
    static NetworkStats collect();

private:
    static std::string detectInterface();
    static std::string detectIPAddress(
        const std::string& interfaceName
    );
    static std::string detectGateway();
    static bool measureLatency(
        const std::string& target,
        NetworkStats& stats
    );
};

#endif
