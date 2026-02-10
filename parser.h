#ifndef MYHEADER_H
#define MYHEADER_H

struct CPUStatus
{
    /* data */
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
    unsigned long long guest;
    unsigned long long guest_nice;
};

int parse_cpu_line(const char *line, struct CPUStatus *out);

#endif