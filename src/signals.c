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
    signal(SIGINT, handle_sigint);
}