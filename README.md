# linux-daemon
A from-scratch Linux system monitor written in C to build a deep understanding of operating systems, low-level system data, and embedded-style software architecture.

This project reads raw kernel statistics from /proc, parses them manually, and computes real system metrics such as CPU usage. The long-term goal is to evolve this design into a platform-independent monitoring module that can run in an RTOS environment.
