#include "cpu_stats.h"

#include <stdio.h>

unsigned long long idle_time(struct CPUStatus* s) { return s->idle; }

unsigned long long total_time(struct CPUStatus* s) {
  return s->guest + s->guest_nice + s->idle + s->iowait + s->irq + s->nice +
         s->softirq + s->steal + s->system + s->user;
}

void print_metric(const char *label, double value_fraction) {
    printf("%-12s : %8.4f%%\n", label, value_fraction * 100.0);
}

void print_data(struct CPUUsage* u){
    printf("\n================ CPU MONITOR ================\n");

    print_metric("User", u->user);
    print_metric("System", u->system);
    print_metric("Nice", u->nice);
    print_metric("Idle", u->idle);
    print_metric("IO Wait", u->iowait);
    print_metric("IRQ", u->irq);
    print_metric("Soft IRQ", u->softirq);
    print_metric("Steal", u->steal);

    printf("---------------------------------------------\n");
    print_metric("Total Usage", u->total);

    printf("=============================================\n");

}

double compute_percent(unsigned long long curr, unsigned long long total){
    double percent = 1.0 - ((double) curr/total);
    return percent;
}

double compute_usage(struct CPUStatus* prev, struct CPUStatus* curr, struct CPUUsage* out) {
  // Take difference in idle time
  unsigned long long idle_diff = idle_time(curr) - idle_time(prev);

  // Take difference in everything else
  unsigned long long total_diff = total_time(curr) - total_time(prev);

  // Fill out CPUUsage data
  out->total = compute_percent(idle_diff, total_diff);
  out->user = compute_percent(curr->user - prev->user, total_diff);
  out->nice = compute_percent(curr->nice - prev->nice, total_diff);
  out->system = compute_percent(curr->system - prev->system, total_diff);
  out->idle = compute_percent(curr->idle - prev->idle, total_diff);
  out->iowait = compute_percent(curr->iowait - prev->iowait, total_diff);
  out->irq = compute_percent(curr->irq - prev->irq, total_diff);
  out->softirq = compute_percent(curr->softirq - prev->softirq, total_diff);
  out->steal = compute_percent(curr->steal - prev->steal, total_diff);
  out->guest = compute_percent(curr->guest - prev->guest, total_diff);
  out->guest_nice = compute_percent(curr->guest_nice - prev->guest_nice, total_diff);

  // Return percentage
  return out->total;
}