#include "cpu_stats.h"

#include <stdio.h>

unsigned long long idle_time(struct CPUStatus* s) { return s->idle; }

unsigned long long total_time(struct CPUStatus* s) {
  return s->guest + s->guest_nice + s->idle + s->iowait + s->irq + s->nice +
         s->softirq + s->steal + s->system + s->user;
}

double compute_usage(struct CPUStatus* prev, struct CPUStatus* curr) {
  // Take difference in idle time
  unsigned long long idle_diff = idle_time(curr) - idle_time(prev);

  // Take difference in everything else
  unsigned long long total_diff = total_time(curr) - total_time(prev);

  // Return percentage
  double usage_percent = idle_diff/total_diff;
  return usage_percent;
}