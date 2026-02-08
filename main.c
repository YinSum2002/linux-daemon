#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

int main() {
  char buffer[BUFFER_SIZE];

  // Open /proc/stat in read mode
  FILE* fp = fopen("/proc/stat", "r");
  while (1) {
    // Read the first line using fgets()
    if (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
      printf("Data from /proc/stat: %s", buffer);
    } else {
      printf("Count not read a line or file is empty.\n");
    }
    sleep(1);
  }

  fclose(fp);

  return 0;
}
