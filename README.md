# Linux System Monitor (C → RTOS Path)
A from-scratch Linux system monitor written in C to build a deep understanding of operating systems, low-level system data, and embedded-style software architecture.

This project reads raw kernel statistics from /proc, parses them manually, and computes real system metrics such as CPU usage. The long-term goal is to evolve this design into a platform-independent monitoring module that can run in an RTOS environment.

## Motivation
As a Computer Engineering student preparing for embedded systems work, I wanted a project that:
  - Strengthens C fundamentals
  - Builds intuition for how operating systems expose system state
  - Practices parsing structured system data
  - Introduces real-time style design patterns
  - Creates a foundation for RTOS migration

## Current Features
  - Reads raw CPU data from /proc/stat

## Planned Learning Milestones
Linux Systems Programming
  - Threaded metric collection
  - Mutexes and synchronization
  - Producer/consumer monitoring model
  - Signal handling
  - Daemonization

Real-Time / Embedded Direction
  - Hardware-independent monitoring interface
  - Port to RTOS scheduler model
  - Timing accuracy analysis
  - Resource-constrained design

## Project Status
Early-stage, actively developing. Architecture and functionality are priorities over features.

## Author
Justin Chan
Computer Engineering
Aspiring Embedded Systems Engineer
