#include "cpu_stats.h"

#include <stdio.h>

double compute_usage(struct CPUStatus* prev, struct CPUStatus* curr) {
  // Take difference in idle time
  unsigned long long idle_time = curr->idle - prev->idle;

  // Take difference in everything else

  // Return percentage
}