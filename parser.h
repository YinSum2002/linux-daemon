#ifndef MYHEADER_H
#define MYHEADER_H

struct CPUStatus
{
    /* data */
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
};

int parse_cpu_line(const char *line, struct CPUStatus *out);

#endif