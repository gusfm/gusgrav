#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "universe_mgr.h"

int main(int argc, char const* argv[])
{
    int ret;
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
