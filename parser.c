#include <stdio.h>
#include "parser.h"

int parse_cpu_line(const char *line, struct CPUStatus *out){
    if (line == NULL){
        return -1;
    }
    if (sscanf(line, "cpu", &out->user, &out->nice, &out->system, &out->idle) != 0){
        return 0;
    }
    return -1;
}