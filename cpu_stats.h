#ifndef CPUSTATS_H
#define CPUSTATS_H
#include "parser.h"

double compute_usage(struct CPUStatus* prev, struct CPUStatus* curr);

#endif