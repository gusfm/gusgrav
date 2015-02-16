#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <execinfo.h>
#include <time.h>

#include "universe_mgr.h"

/* Obtain a backtrace and print it to stdout. */
void print_trace(void)
{
    void *array[10];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, 10);
    strings = backtrace_symbols(array, size);

    printf("Obtained %lu stack frames.\n", size);

    for (i = 0; i < size; i++)
        printf("%s\n", strings[i]);

    free(strings);
}

void signal_callback_handler(int signum)
{
    universe_mgr_terminate();
    printf("Caught signal %d\n", signum);
    print_trace();
    exit(signum);
}

int main(int argc, char const* argv[])
{
    int ret;
    /* Register signal haldler callback */
    signal(SIGINT, signal_callback_handler);
    signal(SIGKILL, signal_callback_handler);
    signal(SIGTERM, signal_callback_handler);
    signal(SIGFPE, signal_callback_handler);
    signal(SIGSEGV, signal_callback_handler);

    srand(time(NULL));

    ret = universe_mgr_init("gusgrav", 1024, 800);
    if (ret < 0) {
        printf("Error: could not create game manager!\n");
        exit(EXIT_FAILURE);
    }
    universe_mgr_main_loop();
    universe_mgr_terminate();

    return 0;
}

