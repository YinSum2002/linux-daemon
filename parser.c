#include <stdio.h>
#include "parser.h"

int parse_cpu_line(const char *line, struct CPUStatus *out){
    if ((line == NULL) || (out == NULL)){
        return -1;
    }
    char label[4];
    if (sscanf(line, "%3s %d %d %d %d", label, &out->user, &out->nice, &out->system, &out->idle) == 5){
        return 0;
    }
    return -1;
}