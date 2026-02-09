#ifndef MYHEADER_H
#define MYHEADER_H

struct CPUStatus
{
    /* data */
    int user;
    int nice;
    int system;
    int idle;
};

int parse_cpu_line(const char *line, struct CPUStatus *out);

#endif