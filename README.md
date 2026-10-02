# Network Latency & Packet-Loss Chaos Emulator

## 1. Project Overview

The **Network Latency & Packet-Loss Chaos Emulator** is a Linux-based system programming project that simulates controlled network degradation.

The system automatically detects the active network configuration, measures baseline network performance, applies controlled network impairment using Linux Traffic Control (`tc`) and `netem`, measures the degraded network, compares the results, and restores the network configuration.

The project demonstrates practical concepts of:

- Linux networking
- Network latency
- Packet loss
- Linux Traffic Control
- Network emulation
- C++ system programming
- Process and command execution
- Network monitoring
- Experimental testing
- Git and GitHub

---

## 2. Objectives

The main objectives of the project are:

1. Automatically detect the available network interface.
2. Detect the local IP address and gateway.
3. Measure baseline latency and packet loss.
4. Apply controlled network degradation.
5. Measure network performance after impairment.
6. Compare baseline and degraded performance.
7. Automatically restore the network configuration.
8. Provide a simple command-line interface for experimentation.

---

## 3. System Workflow

The application follows this workflow:

```text
Start Application
       |
       v
Network Discovery
       |
       v
Baseline Measurement
       |
       v
Chaos Engine
       |
       v
Apply Network Impairment
       |
       v
Measure Degraded Network
       |
       v
Compare Results
       |
       v
Restore Network
       |
       v
Experiment Complete
```

---

## 4. Technologies Used

- C++17
- Linux / Ubuntu
- Linux Traffic Control (`tc`)
- `netem`
- `ping`
- `ip` networking utilities
- Git
- GitHub

---

## 5. Project Structure

```text
network-chaos-emulator/
│
├── include/
│   ├── Config.hpp
│   ├── Validator.hpp
│   ├── NetemController.hpp
│   ├── NetworkMonitor.hpp
│   └── ChaosEngine.hpp
│
├── src/
│   ├── main.cpp
│   ├── Validator.cpp
│   ├── NetemController.cpp
│   ├── NetworkMonitor.cpp
│   └── ChaosEngine.cpp
│
├── tests/
├── logs/
├── docs/
├── scripts/
├── README.md
└── .gitignore
```

---

## 6. How to Build and Run

Clone the repository:

```bash
git clone https://github.com/AmanSingh7489/network-chaos-emulator.git
cd network-chaos-emulator
```

Compile the project:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o chaos-emulator
```

Run the emulator:

```bash
./chaos-emulator
```

The application automatically detects the network configuration and runs the controlled experiment.

---

## 7. Chaos Configuration

The default experiment uses:

- Test Interface: `lo` (Loopback)
- Delay: `100 ms`
- Packet Loss: `10%`

The loopback interface is used to keep the default experiment isolated from the user's active network connection.

---

## 8. Example Result

Example result from a test run:

| Metric | Baseline | After Chaos |
|---|---:|---:|
| Average Latency | 0.451 ms | 100.720 ms |
| Minimum Latency | 0.240 ms | 100.482 ms |
| Maximum Latency | 1.292 ms | 100.887 ms |
| Packet Loss | 0% | 0% |

The observed latency increase in this run was approximately **100.269 ms**.

*Results may vary between runs.*

---

## 9. Key Concepts Demonstrated

- Linux networking
- Network performance monitoring
- Network latency and packet loss
- Linux Traffic Control
- `tc` and `netem`
- C++ system programming
- Linux command execution
- Modular software design
- Experimental testing
- Git and GitHub

---

## 10. Safety

The default chaos experiment operates on the Linux loopback interface (`lo`) rather than the active network interface.

This prevents the default experiment from intentionally disrupting the user's actual network connection.

After the experiment, the applied network impairment is removed and the loopback configuration is restored.

---

## 11. Future Enhancements

- Configurable chaos profiles
- Additional network impairment types
- Automated report generation
- Graphical monitoring dashboard
- Extended statistical analysis

---

## 12. Conclusion

The **Network Latency & Packet-Loss Chaos Emulator** demonstrates how Linux networking tools and C++ system programming can be combined to simulate, measure, and analyze controlled network degradation.

The project provides practical experience with network monitoring, Linux Traffic Control, network emulation, system-level programming, and experimental analysis.
