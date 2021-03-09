#include <stdbool.h>
#include <stdio.h>
#include <systemd/sd-daemon.h>
#include <unistd.h>

#define SLEEP(t)                 \
    do {                         \
        printf("sleeping ... "); \
        fflush(stdout);          \
        sleep(t);                \
        printf("DONE\n");        \
    } while (0)

int main() {
    printf("Starting program ...\n");
    SLEEP(5);
    printf("Send notification to SystemD ... ");
    int rc = sd_notify(/*unset_environment=*/false, "READY=1");
    if (rc < 0) {
        fprintf(stderr, "error: READY=1 could not be sent: return code of sd_notify(): %d\n", rc);
    } else if (rc == 0) {
        fprintf(stderr,
                "error: READY=1 could not be sent: You probably starting the program not via a SystemD service\n"
                "       or the service type is NOT notify.\n");
    }
    printf("DONE\n");
    SLEEP(3);

    printf("doing stuff ...\n");
    SLEEP(5);
    printf("sending notification again ...\n");

    rc = sd_notify(/*unset_environment=*/false, "READY=1");
    if (rc < 1) {
        fprintf(stderr, "error: READY=1 could not be sent: return code of sd_notify(): %d\n", rc);
    }
    printf("DONE\n");
    SLEEP(3);

    printf("exiting\n");

    return 0;
}
