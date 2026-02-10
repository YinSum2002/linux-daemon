#include <stdio.h>
#include "parser.h"

int parse_cpu_line(const char *line, struct CPUStatus *out){
    if ((line == NULL) || (out == NULL)){
        return -1;
    }
    char label[4];
    if (sscanf(line, "%3s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", label, &out->user, &out->nice, &out->system, &out->idle, &out->iowait, &out->irq, &out->softirq, &out->steal, &out->guest, &out->guest_nice) == 5){
        return 0;
    }
    return -1;
}