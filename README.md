# Virtual Smart Home Fan & Temperature Controller

## 1. Project Overview

The Virtual Smart Home Fan & Temperature Controller is a Linux-based C/C++ project that simulates an automatic home fan control system based on temperature.

The system determines the fan state according to the temperature:

| Temperature        | Fan State |
| ------------------ | --------- |
| Below 25°C         | OFF       |
| 25°C to below 35°C | LOW       |
| 35°C and above     | HIGH      |

The project also demonstrates Linux Device Driver concepts, TCP socket communication, multithreading, mutex synchronization, and file logging.

---

## 2. Objectives

- Automatically control fan state based on temperature.
- Demonstrate C++ object-oriented programming.
- Demonstrate multithreading and mutex synchronization.
- Demonstrate TCP/IP socket communication on Linux.
- Implement a basic Linux kernel module as a virtual fan driver.
- Maintain temperature and fan-status logs.
- Provide a simple software architecture suitable for a smart-home control system.

---

## 3. Features

- Temperature-based automatic fan control
- Three fan states: OFF, LOW and HIGH
- C++17 implementation
- Multithreading using `std::thread`
- Mutex synchronization using `std::mutex`
- TCP client-server communication
- Linux kernel module / device driver source
- File-based logging
- Makefile-based compilation
- Linux command-line execution

---

## 4. System Architecture

```text
             +----------------------+
             |   Temperature Input  |
             +----------+-----------+
                        |
                        v
             +----------------------+
             |   Fan Controller     |
             |      C++ Class       |
             +----------+-----------+
                        |
              +---------+---------+
              |                   |
              v                   v
       +-------------+     +-------------+
       | Fan Control |     | File Logger |
       | OFF/LOW/HIGH|     | fan_log.txt |
       +-------------+     +-------------+
              |
              v
       +----------------+
       | TCP Client     |
       | Port 8080      |
       +-------+--------+
               |
               v
       +----------------+
       | TCP Server     |
       | Temperature    |
       | Monitoring     |
       +----------------+

       +----------------------+
       | Linux Fan Driver     |
       | fan_driver.c         |
       | Kernel Module (.ko)  |
       +----------------------+
```
