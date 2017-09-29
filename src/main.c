#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "window.h"

static int parse_args(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "ch")) != -1) {
        switch (opt) {
            case 'c':
                printf(
                    "%s:\n"
                    "Controls:\n"
                    "A:                 Render body info\n"
                    "Keyboard arrows:   Move screen\n"
                    "Mouse scroll:      Zoom in/out\n"
                    "Right mouse btn:   Create a body\n"
                    "ESQ:               Quit program\n",
                    argv[0]);
                exit(EXIT_SUCCESS);
            default:
                return -1;
        }
    }
    return 0;
}

static void print_help(char **argv)
{
    fprintf(stderr,
            "Usage: %s [options]\n"
            "Options:\n"
            "  -c\t\tPrint keyboard controls\n"
            "  -h\t\tPrint help and exit\n",
            argv[0]);
}

int main(int argc, char *argv[])
{
    if (parse_args(argc, argv) < 0) {
        print_help(argv);
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    if (window_init("gusgrav", 1024, 800) < 0) {
        printf("Error: could not create game manager!\n");
        exit(EXIT_FAILURE);
    }
    window_main_loop();
    window_terminate();
    return 0;
}

