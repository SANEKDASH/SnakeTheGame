#ifndef CONTROL_HEADER
#define CONTROL_HEADER

#include <termios.h>
#include <unistd.h>
#include <poll.h>
#include <time.h>

static const int POLL_TIMEOUT = 100; // sec * 10 ^ (-3)

static const char DEFAULT_CHAR = EOF;

class Control {
    char prevChar_ = DEFAULT_CHAR;

    struct termios curTermios_;
public:

    Control()
    {
        struct termios newTermios;
        cfmakeraw(&newTermios);

        tcgetattr(STDIN_FILENO, &curTermios_);

        tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    }

    int getControlChar()
    {
        tcflush(STDIN_FILENO, TCIFLUSH);

        struct pollfd pfd = {.fd      = STDIN_FILENO,
                             .events  = POLLIN,
                             .revents = POLLIN};

        struct timespec timeStart, timeEnd;

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        int err = poll(&pfd, 1, POLL_TIMEOUT);

        if (err < 0) {
            exit(EXIT_FAILURE);
        }

        if (err == 0) {
            return prevChar_;
        }

        clock_gettime(CLOCK_MONOTONIC, &timeEnd);

        int timeDelta = ((timeEnd.tv_sec  - timeStart.tv_sec)  * 1000000000 +
                          timeEnd.tv_nsec - timeStart.tv_nsec) / 1000000;

        if (timeDelta < POLL_TIMEOUT) {
            usleep((POLL_TIMEOUT - timeDelta) * 1000);
        }

        read(STDIN_FILENO, &prevChar_, sizeof(prevChar_));

        return prevChar_;
    }

    ~Control()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &curTermios_);
    }
};



#endif /* TEXT_VIEW_HEADER */
