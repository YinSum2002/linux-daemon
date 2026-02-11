#include "parser.h"

#include <stdio.h>

#define CPU_TIME_FIELDS 10
#define CPU_SCAN_COUNT (1 + CPU_TIME_FIELDS)

int parse_cpu_line(const char* line, struct CPUStatus* out) {
  if ((line == NULL) || (out == NULL)) {
    return -1;
  }
  char label[4];
  if (sscanf(line, "%3s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
             label, &out->user, &out->nice, &out->system, &out->idle,
             &out->iowait, &out->irq, &out->softirq, &out->steal, &out->guest,
             &out->guest_nice) == CPU_SCAN_COUNT) {
    return 0;
  }
  return -1;
}