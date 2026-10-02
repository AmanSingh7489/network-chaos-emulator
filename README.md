# Network Latency & Packet-Loss Chaos Emulator

## 1. Project Overview

The Network Latency & Packet-Loss Chaos Emulator is a Linux-based system programming project that simulates controlled network degradation.

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
