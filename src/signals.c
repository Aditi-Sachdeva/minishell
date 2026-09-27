#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "signals.h"

static void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
}

void setup_signals(void)
{
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}
