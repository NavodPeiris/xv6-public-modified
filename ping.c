#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf(2, "Usage: ping <IP address>\n");
    exit();
  }

  char *ip_address = argv[1];
  int pid = getpid();

  while (1) {
    printf(1, "%d: Pinging %s...\n", pid, ip_address);
    int status = system("ping -c 1 %s > /dev/null", ip_address);
    if (status == 0) {
      printf(1, "%d: %s is up!\n", pid, ip_address);
    } else {
      printf(1, "%d: %s is down!\n", pid, ip_address);
    }
    sleep(1000);
  }

  exit();
}
