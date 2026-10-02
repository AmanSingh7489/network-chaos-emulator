#include "NetworkMonitor.hpp"

#include <cstdio>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

namespace {

std::string runCommand(const std::string& command) {

    FILE* pipe = popen(command.c_str(), "r");

    if (pipe == nullptr) {
        return "";
    }

    char buffer[256];
    std::string result;

    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    pclose(pipe);

    return result;
}

}


std::string NetworkMonitor::detectInterface() {

    std::string output =
        runCommand(
            "ip route show default 2>/dev/null"
        );

    std::regex pattern(
        R"(default\s+via\s+\S+\s+dev\s+(\S+))"
    );

    std::smatch match;

    if (std::regex_search(output, match, pattern)) {
        return match[1].str();
    }

    
    output =
        runCommand(
            "ip -o link show 2>/dev/null"
        );

    std::stringstream stream(output);
    std::string line;

    while (std::getline(stream, line)) {

        std::regex fallbackPattern(
            R"(^\d+:\s+([^:]+):)"
        );

        if (std::regex_search(
                line,
                match,
                fallbackPattern)) {

            std::string interfaceName =
                match[1].str();

            if (interfaceName != "lo" &&
                interfaceName.find("@") == std::string::npos) {

                return interfaceName;
            }
        }
    }

    return "";
}


std::string NetworkMonitor::detectIPAddress(
    const std::string& interfaceName
) {

    std::string command =
        "ip -4 -o addr show dev " +
        interfaceName +
        " 2>/dev/null";

    std::string output =
        runCommand(command);

    std::regex pattern(
        R"(inet\s+(\d+\.\d+\.\d+\.\d+))"
    );

    std::smatch match;

    if (std::regex_search(output, match, pattern)) {
        return match[1].str();
    }

    return "";
}


std::string NetworkMonitor::detectGateway() {

    std::string output =
        runCommand(
            "ip route show default 2>/dev/null"
        );

    std::regex pattern(
        R"(default\s+via\s+(\d+\.\d+\.\d+\.\d+))"
    );

    std::smatch match;

    if (std::regex_search(output, match, pattern)) {
        return match[1].str();
    }

    return "";
}


bool NetworkMonitor::measureLatency(
    const std::string& target,
    NetworkStats& stats
) {

    if (target.empty()) {
        return false;
    }

    std::string command =
        "LANG=C ping -c 10 -W 1 " +
        target +
        " 2>/dev/null";

    std::string output =
        runCommand(command);

    if (output.empty()) {
        return false;
    }

    
    std::regex packetPattern(
        R"((\d+)\s+packets transmitted,\s+(\d+)\s+(?:packets )?received,\s+([0-9.]+)%\s+packet loss)"
    );

    std::smatch packetMatch;

    if (std::regex_search(
            output,
            packetMatch,
            packetPattern)) {

        stats.packetsSent =
            std::stoi(packetMatch[1].str());

        stats.packetsReceived =
            std::stoi(packetMatch[2].str());

        stats.packetLoss =
            std::stod(packetMatch[3].str());
    }

   
    std::regex latencyPattern(
    R"(=\s*([0-9.]+)/([0-9.]+)/([0-9.]+))"
);

    std::smatch latencyMatch;

    if (std::regex_search(
            output,
            latencyMatch,
            latencyPattern)) {

        stats.minLatency =
            std::stod(latencyMatch[1].str());

        stats.avgLatency =
            std::stod(latencyMatch[2].str());

        stats.maxLatency =
            std::stod(latencyMatch[3].str());
    }

    return true;
}


NetworkStats NetworkMonitor::collect() {

    NetworkStats stats;

    std::cout
        << "\n[1] Detecting network interface...\n";

    stats.interfaceName =
        detectInterface();

    if (stats.interfaceName.empty()) {

        std::cerr
            << "[ERROR] Could not detect network interface.\n";

        return stats;
    }

    stats.ipAddress =
        detectIPAddress(
            stats.interfaceName
        );

    stats.gateway =
        detectGateway();

    std::cout
        << "    Interface : "
        << stats.interfaceName
        << "\n";

    std::cout
        << "    IP Address: "
        << (stats.ipAddress.empty()
                ? "Unavailable"
                : stats.ipAddress)
        << "\n";

    std::cout
        << "    Gateway   : "
        << (stats.gateway.empty()
                ? "Unavailable"
                : stats.gateway)
        << "\n";


    std::cout
        << "\n[2] Measuring baseline network...\n";

   
    std::string target =
        stats.gateway;

    if (target.empty()) {
        target = "1.1.1.1";
    }

    std::cout
        << "    Test target: "
        << target
        << "\n";

    if (!measureLatency(target, stats)) {

        std::cerr
            << "[ERROR] Network measurement failed.\n";

        return stats;
    }

    stats.success = true;

    return stats;
}
